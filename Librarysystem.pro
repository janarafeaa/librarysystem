
QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    librarianhome.cpp \
    librarydata.cpp \
    main.cpp \
    loginwindow.cpp \
    addbookwindow.cpp

HEADERS += \
    librarianhome.h \
    librarydata.h \
    loginwindow.h \
    addbookwindow.h

FORMS += \
    loginwindow.ui \
    LibrarianHome.ui \
    AddBookWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
