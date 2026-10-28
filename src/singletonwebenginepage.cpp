#include "singletonwebenginepage.h"

#include <QDesktopServices>
#include <QWebEngineProfile>

SingletonWebEnginePage::SingletonWebEnginePage(QObject *parent)
: QWebEnginePage(parent)
{
    // Connect new permission signal
    connect(this, &QWebEnginePage::permissionRequested,
            this, &SingletonWebEnginePage::handlePermissionRequested);
    connect(this, &QWebEnginePage::loadFinished,
            this, &SingletonWebEnginePage::handleLoadFinished);
}

bool SingletonWebEnginePage::acceptNavigationRequest(const QUrl &url, QWebEnginePage::NavigationType type, bool isMainFrame)
{
    if (type == QWebEnginePage::NavigationTypeLinkClicked)
    {
        if (url.host() == "web.whatsapp.com" || url.host().endsWith(".whatsapp.com"))
        {
            return true;
        }

        QDesktopServices::openUrl(url);
        return false;
    }

    return QWebEnginePage::acceptNavigationRequest(url, type, isMainFrame);
}

QWebEnginePage *SingletonWebEnginePage::createWindow(QWebEnginePage::WebWindowType type)
{
    Q_UNUSED(type);

    QWebEnginePage *popupPage = new QWebEnginePage(this);
    connect(popupPage, &QWebEnginePage::urlChanged, this, [popupPage](const QUrl &url) {
        if (!url.isEmpty() && url.isValid()) {
            QDesktopServices::openUrl(url);
        }
        popupPage->deleteLater();
    });

    return popupPage;
}

void SingletonWebEnginePage::handlePermissionRequested(const QWebEnginePermission &permission)
{
    if (permission.permissionType() == QWebEnginePermission::PermissionType::Notifications)
    {
        permission.grant();
    }
}

void SingletonWebEnginePage::handleLoadFinished(bool ok)
{
    Q_UNUSED(ok);

    // Pre-grant notifications for WhatsApp Web using modern API
    QWebEnginePermission permission = profile()->queryPermission(
        QUrl("https://web.whatsapp.com/"),
                                                                 QWebEnginePermission::PermissionType::Notifications
    );

    if (permission.state() != QWebEnginePermission::State::Granted)
    {
        permission.grant();
    }
}
