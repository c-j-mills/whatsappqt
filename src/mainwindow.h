#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QStatusBar>
#include <QWebEngineView>
#include <QIcon>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QRegExp>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void createActions();
    void createStatusBar();
    void createTrayIcon();
    void createWebEngine();

    QRegExp notificationsTitleRegExp;
    QIcon trayIconRead;
    QIcon trayIconUnread;

    QAction *reloadAction;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *quitAction;

    QMenu *trayIconMenu;
    QSystemTrayIcon *trayIcon;

    QWebEngineView *webEngine;
    QStatusBar *statusBar;
    QProgressBar *progressBar;
    void reload();
    void readSettings();
    void showOutOfMaintenance();

public slots:
    void handleWebViewTitleChanged(QString title);
    void handleLoadStarted();
    void handleLoadProgress(int progress);
    void handleDownloadRequested(QWebEngineDownloadItem *download);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void messageClicked();
    void doReload();
    void showAbout();
    void showAboutQt();

signals:

};

#endif // MAINWINDOW_H
