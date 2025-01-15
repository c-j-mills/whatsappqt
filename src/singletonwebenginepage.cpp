#include "singletonwebenginepage.h"

#include <QDesktopServices>

SingletonWebEnginePage::SingletonWebEnginePage(QObject *parent)
    : QWebEnginePage(parent)
{
    // Connect signals and slots
    connect(this, &QWebEnginePage::featurePermissionRequested,
            this, &SingletonWebEnginePage::handleFeaturePermissionRequested);
    connect(this, &QWebEnginePage::loadFinished,
            this, &SingletonWebEnginePage::handleLoadFinished);
}

bool SingletonWebEnginePage::acceptNavigationRequest(const QUrl &url, QWebEnginePage::NavigationType type, bool isMainFrame)
{
    qDebug() << "Navigation request: [" + url.toDisplayString() + "] " + QVariant(type).toString();

    if (QWebEnginePage::NavigationType::NavigationTypeLinkClicked == type)
    {
        QDesktopServices::openUrl(url);
        return false;
    }

    return QWebEnginePage::acceptNavigationRequest(url, type, isMainFrame);
}

QWebEnginePage *SingletonWebEnginePage::createWindow(QWebEnginePage::WebWindowType type)
{
    return new SingletonWebEnginePage();
}

void SingletonWebEnginePage::handleFeaturePermissionRequested(const QUrl &securityOrigin, QWebEnginePage::Feature feature)
{
    if (QWebEnginePage::Feature::Notifications == feature)
    {
        setFeaturePermission(
                    securityOrigin,
                    feature,
                    QWebEnginePage::PermissionPolicy::PermissionGrantedByUser
        );
    }
}

void SingletonWebEnginePage::handleLoadFinished(bool ok)
{
    setFeaturePermission(
                QUrl("https://web.whatsapp.com/"),
                QWebEnginePage::Feature::Notifications,
                QWebEnginePage::PermissionPolicy::PermissionGrantedByUser
    );
}
