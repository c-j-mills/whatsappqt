QT += widgets core5compat webenginecore webenginewidgets 

CONFIG += c++11 console

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/singletonwebenginepage.cpp

RESOURCES += \
        WhatsAppQT.qrc

TRANSLATIONS += \
        WhatsAppQT_de_DE.ts

RC_ICONS = images/iconfinder_whatsapp-square-social-media_764939.ico
ICON = images/iconfinder_whatsapp-square-social-media_764939.icns

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

DISTFILES += \
    .gitlab-ci.yml \
    io.bit3.WhatsAppQT.yml \
    LICENSE \
    README.adoc

HEADERS += \
    src/mainwindow.h \
    src/singletonwebenginepage.h

isEmpty(PREFIX):PREFIX = /usr/local

target.path = $$PREFIX/bin/
INSTALLS += target

icons.path = $$PREFIX/share/icons
icons.files += desktop/share/icons/*
INSTALLS += icons

desktop.path = $$PREFIX/share/applications
desktop.files += desktop/share/applications/*
INSTALLS += desktop

appstream.path = $$PREFIX/share/metainfo
appstream.files += desktop/share/metainfo/*
INSTALLS += appstream
