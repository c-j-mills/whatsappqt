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
    // Auto-grant permissions requested by WhatsApp (Notifications, AudioCapture, etc.)
    if (permission.permissionType() == QWebEnginePermission::PermissionType::Notifications ||
        permission.permissionType() == QWebEnginePermission::PermissionType::AudioCapture ||
        permission.permissionType() == QWebEnginePermission::PermissionType::VideoCapture ||
        permission.permissionType() == QWebEnginePermission::PermissionType::ClipboardReadWrite)
    {
        permission.grant();
    }
}

void SingletonWebEnginePage::handleLoadFinished(bool ok)
{
    Q_UNUSED(ok);

    QUrl origin("https://web.whatsapp.com/");

    // Grant Notifications
    QWebEnginePermission notifPermission = profile()->queryPermission(
        origin,
        QWebEnginePermission::PermissionType::Notifications
    );
    if (notifPermission.state() != QWebEnginePermission::State::Granted) {
        notifPermission.grant();
    }
}
