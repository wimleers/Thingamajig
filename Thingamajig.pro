QT += core gui

TARGET = Thingamajig
TEMPLATE = app
OBJECTS_DIR = .obj
MOC_DIR = .moc
RCC_DIR = .rcc

SOURCES += main.cpp WorkStatus.cpp

HEADERS  += WorkStatus.h

# Mac OS X specific setting: use the provided custom .plist file that sets
# LSUIElement = 1, which makes the app hidden.
OTHER_FILES += Info.plist
macx:QMAKE_INFO_PLIST = Info.plist
