#include <QApplication>
#include <QtWidgets>
#include <QWebEngineProfile>
#include <QStandardPaths>
#include <QDir>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Organization details are required by Qt to resolve proper AppData locations
    QCoreApplication::setOrganizationName("bit3");
    QCoreApplication::setOrganizationDomain("bit3.io");
    QCoreApplication::setApplicationName("WhatsAppQT");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    app.setWindowIcon(QIcon("iconfinder_whatsapp-square-social-media_764939.png"));

    // Prepare persistent directories
    QString dataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dataLocation + "/webengine");
    QDir().mkpath(dataLocation + "/cache");

    // Configure the default profile for persistent storage
    QWebEngineProfile *profile = QWebEngineProfile::defaultProfile();
    profile->setPersistentStoragePath(dataLocation + "/webengine");
    profile->setCachePath(dataLocation + "/cache");
    profile->setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);
    profile->setHttpUserAgent("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36");

    MainWindow window;
    window.show();

    return app.exec();
}
