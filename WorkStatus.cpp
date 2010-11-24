#include "WorkStatus.h"

/**
 * Warning: the solution to get the context menu to work is *very* hacky.
 * Apparently, Qt 4.7 on OS X fails to pass through double-click and
 * right-click events. Even an event filter wouldn't work.
 * So, instead, I've opted to dynamically enable/disable a context menu when
 * you've clicked the item: after 1 second, a context menu with a "Quit"
 * option will be displayed. After 1 more second, this menu will disappear
 * again.
 * If you know of a better way, please let me know, because I *really* hate
 * this hacky solution.
 */

WorkStatus::WorkStatus(QObject * parent) : QObject(parent) {
    QPixmap canvas(128, 128);

    // Paint red icon.
    canvas.fill(QColor(220, 20, 60));
    redIcon.addPixmap(canvas);

    // Paint orange icon.
    canvas.fill(QColor(255, 165, 0));
    orangeIcon.addPixmap(canvas);

    // Paint green icon.
    canvas.fill(QColor(50, 205, 50));
    greenIcon.addPixmap(canvas);

    // Build context menu.
    this->contextMenu = new QMenu();
    this->contextMenu->addAction("Quit", this, SLOT(quitActionClicked()));

    // Set default status.
    this->status = AVAILABLE;
    this->showContextMenuTimer = -1;
    this->hideContextMenuTimer = -1;

    // Create system tray.
    this->tray = new QSystemTrayIcon(this->icon());
    this->tray->setContextMenu(NULL);
    connect(this->tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconClicked(QSystemTrayIcon::ActivationReason)));
    this->tray->show();

    //tray->showMessage("Thingamajig", "Isn't it time for a break yet?");
}

WorkStatus::~WorkStatus() {
    delete this->tray;
    delete this->contextMenu;
}

void WorkStatus::trayIconClicked(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
        this->next();
        this->tray->setIcon(this->icon());
        if (this->showContextMenuTimer == -1)
            this->showContextMenuTimer = this->startTimer(1000);
    }
}

void WorkStatus::timerEvent(QTimerEvent * e) {
    if (e->timerId() == this->showContextMenuTimer) {
        this->tray->setContextMenu(this->contextMenu);
        this->killTimer(this->showContextMenuTimer);
        this->showContextMenuTimer = -1;
        this->hideContextMenuTimer = this->startTimer(1000);
    }
    else if (e->timerId() == this->hideContextMenuTimer) {
        this->tray->setContextMenu(NULL);
        this->killTimer(this->hideContextMenuTimer);
        this->hideContextMenuTimer = -1;
    }
}

void WorkStatus::quitActionClicked() {
    emit quit();
}

void WorkStatus::next() {
    this->status++;
    if (this->status > AVAILABLE)
        this->status = DND;
}

const QIcon & WorkStatus::icon() {
    switch (this->status) {
    case DND:
        return this->redIcon;
    case INTERRUPTABLE:
        return this->orangeIcon;
    case AVAILABLE:
        return this->greenIcon;
    default:
        return this->greenIcon;
    }
}
