#ifndef SINGLETONWEBENGINEPAGE_H
#define SINGLETONWEBENGINEPAGE_H

#include <QWebEnginePage>


class SingletonWebEnginePage : public QWebEnginePage
{
    Q_OBJECT
public:
    SingletonWebEnginePage(QObject *parent = nullptr);

protected:
    bool acceptNavigationRequest(const QUrl &url, QWebEnginePage::NavigationType type, bool isMainFrame) override;
    QWebEnginePage* createWindow(QWebEnginePage::WebWindowType type) override;

public slots:
    void handleFeaturePermissionRequested(const QUrl &securityOrigin, QWebEnginePage::Feature feature);
    void handleLoadFinished(bool ok);
};

#endif // SINGLETONWEBENGINEPAGE_H
