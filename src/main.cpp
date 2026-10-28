#include <QApplication>
#include <QtWidgets>
//#include <QtWebView>
#include <QWebEngineProfile>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
//QtWebView::initialize();

    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("");
    QCoreApplication::setApplicationName("WhatsAppQT");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    app.setWindowIcon(QIcon("iconfinder_whatsapp-square-social-media_764939.png"));

    QWebEngineProfile *profile = QWebEngineProfile::defaultProfile();
    profile->setHttpUserAgent("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36");

    MainWindow window;
    window.show();

    return app.exec();
}
