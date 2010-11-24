#ifndef WORKSTATUS_H
#define WORKSTATUS_H

#include <QObject>
#include <QIcon>
#include <QPixmap>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QTimerEvent>
#include <QDebug>

enum States { DND, INTERRUPTABLE, AVAILABLE };

class WorkStatus : public QObject {
    Q_OBJECT
public:
    WorkStatus(QObject * parent = NULL);
    ~WorkStatus();

signals:
    void quit(void);

public slots:
    void trayIconClicked(QSystemTrayIcon::ActivationReason reason);
    void timerEvent(QTimerEvent * e);
    void quitActionClicked();

protected:
    void next();
    const QIcon & icon();

    QSystemTrayIcon * tray;
    int status;
    QIcon redIcon;
    QIcon orangeIcon;
    QIcon greenIcon;

    QMenu * contextMenu;
    int showContextMenuTimer;
    int hideContextMenuTimer;
};


#endif // WORKSTATUS_H
