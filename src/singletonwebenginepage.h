#ifndef SINGLETONWEBENGINEPAGE_H
#define SINGLETONWEBENGINEPAGE_H

#include <QWebEnginePage>
#include <QWebEnginePermission>

class SingletonWebEnginePage : public QWebEnginePage
{
    Q_OBJECT
public:
    explicit SingletonWebEnginePage(QWebEngineProfile *profile, QObject *parent = nullptr);
    explicit SingletonWebEnginePage(QObject *parent = nullptr);

protected:
    bool acceptNavigationRequest(const QUrl &url, QWebEnginePage::NavigationType type, bool isMainFrame) override;
    QWebEnginePage* createWindow(QWebEnginePage::WebWindowType type) override;

public slots:
    void handlePermissionRequested(const QWebEnginePermission &permission);
    void handleLoadFinished(bool ok);
};

#endif // SINGLETONWEBENGINEPAGE_H
