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
    qDebug() << "Navigation request: [" + url.toDisplayString() + "] " + QVariant::fromValue(type).toString();

    if (type == QWebEnginePage::NavigationTypeLinkClicked)
    {
        // Allow WhatsApp Web to handle its own internal links
        if (url.host() == "web.whatsapp.com" || url.host().endsWith(".whatsapp.com"))
        {
            return true;
        }

        // Open external links (e.g. links sent in chat messages) in the system default browser
        QDesktopServices::openUrl(url);
        return false;
    }

    return QWebEnginePage::acceptNavigationRequest(url, type, isMainFrame);
}


QWebEnginePage *SingletonWebEnginePage::createWindow(QWebEnginePage::WebWindowType type)
{
    // Create a temporary page to catch the requested popup URL
    QWebEnginePage *popupPage = new QWebEnginePage(this);

    connect(popupPage, &QWebEnginePage::urlChanged, this, [popupPage](const QUrl &url) {
        if (!url.isEmpty() && url.isValid()) {
            QDesktopServices::openUrl(url);
        }
        popupPage->deleteLater();
    });

    return popupPage;
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
