#include <QApplication>
#include <QtWidgets>
#include <QWebEngineProfile>
#include <QStandardPaths>
#include <QDir>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("bit3");
    QCoreApplication::setOrganizationDomain("bit3.io");
    QCoreApplication::setApplicationName("WhatsAppQT");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    app.setWindowIcon(QIcon("iconfinder_whatsapp-square-social-media_764939.png"));

    // Create a named disk-backed profile (must have a storageName to persist)
    QWebEngineProfile *profile = new QWebEngineProfile("whatsappqt_profile", &app);
    profile->setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);
    profile->setHttpUserAgent("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36");

    qDebug() << "Is Off-the-Record:" << profile->isOffTheRecord();
    qDebug() << "Persistent Storage Path:" << profile->persistentStoragePath();

    MainWindow window;
    window.show();

    return app.exec();
}
