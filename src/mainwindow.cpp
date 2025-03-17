#include "mainwindow.h"
#include "singletonwebenginepage.h"
#include <QApplication>
#include <QAction>
#include <QSettings>
#include <QWebEngineProfile>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      notificationsTitleRegExp("^\\([1-9]\\d*\\).*"),
      trayIconRead(":/images/iconfinder_Whatsapp_3721678_grayscale.png"),
      trayIconUnread(":/images/iconfinder_Whatsapp_3721678.png")
{
    setWindowTitle("WhatsAppQT");
    setWindowIcon(QIcon(":/images/iconfinder_Whatsapp_3721678.svg"));
    setMinimumWidth(800);
    setMinimumHeight(600);
    readSettings();

    createActions();
    createStatusBar();
    createTrayIcon();
    createWebEngine();

    // Connect signals and slots
    connect(webEngine, &QWebEngineView::titleChanged,
            this, &MainWindow::handleWebViewTitleChanged);
    connect(webEngine, &QWebEngineView::loadStarted,
            this, &MainWindow::handleLoadStarted);
    connect(webEngine, &QWebEngineView::loadProgress,
            this, &MainWindow::handleLoadProgress);
    connect(QWebEngineProfile::defaultProfile(), &QWebEngineProfile::downloadRequested,
            this, &MainWindow::handleDownloadRequested);

    // showOutOfMaintenance();
}

void MainWindow::readSettings()
{
    QSettings settings("bit3.io", "WhatsAppQT");
    restoreGeometry(settings.value("main/geometry").toByteArray());
    restoreState(settings.value("main/windowState").toByteArray());
}

void MainWindow::showOutOfMaintenance()
{
    QMessageBox about(this);
    about.setWindowTitle(tr("WhatsAppQT"));
    about.setIconPixmap(QPixmap(":/images/iconfinder_Whatsapp_3721678_64.png"));
    about.setTextFormat(Qt::TextFormat::RichText);
    about.setText(tr("Out of maintenance.<br>"
                     "Personally, I haven't used WhatsApp since the last questionable change to the terms and conditions.<br>"
                     "This means that I no longer support WhatsAppQT.<br>"
                     "<br>"
                     "Anyone interested in the takeover is welcome to <a href=\"https://gitlab.com/bit3/whatsappqt/-/issues\">get in touch</a>."));
    about.addButton(QMessageBox::StandardButton::Close);
    about.exec();
}

void MainWindow::showAbout()
{
    QMessageBox about(this);
    about.setWindowTitle(tr("WhatsAppQT"));
    about.setIconPixmap(QPixmap(":/images/iconfinder_Whatsapp_3721678_64.png"));
    about.setTextFormat(Qt::TextFormat::RichText);
    about.setText(tr("Unofficial WhatsApp Web Desktop Client.<br>"
                     "<a href=\"https://gitlab.com/bit3/whatsappqt\">https://gitlab.com/bit3/whatsappqt</a><br>"
                     "<br>"
                     "License: MIT<br>"
                     "<br>"
                     "Attribution: Icon by Teguh Sulistio<br>"
                     "<a href=\"https://www.iconfinder.com/VISOEALE\">https://www.iconfinder.com/VISOEALE</a>"));
    about.addButton(QMessageBox::StandardButton::Ok);
    about.exec();
}

void MainWindow::showAboutQt()
{
    QMessageBox::aboutQt(this, tr("WhatsAppQT"));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("bit3.io", "WhatsAppQT");
    settings.setValue("main/geometry", saveGeometry());
    settings.setValue("main/windowState", saveState());
    QMainWindow::closeEvent(event);
}

void MainWindow::createActions()
{
    reloadAction = new QAction(tr("Re&load"), this);
    reloadAction->setShortcut(Qt::Key_F5);
    connect(reloadAction, &QAction::triggered, this, &MainWindow::doReload);
    addAction(reloadAction);

    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);
    addAction(minimizeAction);

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, &QAction::triggered, this, &QWidget::showMaximized);
    addAction(maximizeAction);

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);
    addAction(restoreAction);

    aboutAction = new QAction(tr("About"), this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);

    aboutAction = new QAction(tr("About"), this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);

    aboutQtAction = new QAction(tr("About QT"), this);
    connect(aboutQtAction, &QAction::triggered, this, &MainWindow::showAboutQt);

    quitAction = new QAction(tr("&Quit"), this);
    quitAction->setShortcut(QKeySequence(Qt::Modifier::CTRL + Qt::Key_Q));
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    addAction(quitAction);
}

void MainWindow::createStatusBar()
{
    QStatusBar *statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
    statusBar->hide();
    this->statusBar = statusBar;

    QProgressBar *progressBar = new QProgressBar(this->statusBar);
    statusBar->addWidget(progressBar, 1);
    progressBar->setTextVisible(false);
    progressBar->hide();
    this->progressBar = progressBar;
}

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(reloadAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(aboutAction);
    trayIconMenu->addAction(aboutQtAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(trayIconRead, this);
    trayIcon->setContextMenu(trayIconMenu);

    trayIcon->show();

    connect(trayIcon, &QSystemTrayIcon::messageClicked,
            this, &MainWindow::messageClicked);
    connect(trayIcon, &QSystemTrayIcon::activated,
            this, &MainWindow::iconActivated);
}

void MainWindow::createWebEngine()
{
    QSizePolicy widgetSize;
    widgetSize.setHorizontalPolicy(QSizePolicy::Expanding);
    widgetSize.setVerticalPolicy(QSizePolicy::Expanding);
    widgetSize.setHorizontalStretch(1);
    widgetSize.setVerticalStretch(1);

    QWebEngineView *webEngine = new QWebEngineView(this);
    setCentralWidget(webEngine);
    webEngine->setSizePolicy(widgetSize);
    webEngine->show();
    this->webEngine = webEngine;

    QWebEnginePage *page = new SingletonWebEnginePage(webEngine);
    webEngine->setPage(page);
    page->setUrl(QUrl("https://web.whatsapp.com/"));
}

void MainWindow::handleWebViewTitleChanged(QString title) {
    setWindowTitle(title);

    if (notificationsTitleRegExp.exactMatch(title))
    {
        trayIcon->setIcon(trayIconUnread);
    }
    else
    {
        trayIcon->setIcon(trayIconRead);
    }
}

void MainWindow::handleLoadStarted()
{
    statusBar->show();
    progressBar->show();
}

void MainWindow::handleLoadProgress(int progress)
{
    if (progress >= 100)
    {
        progressBar->hide();
        statusBar->hide();
    }
    else
    {
        progressBar->setValue(progress);
    }
}

void MainWindow::handleDownloadRequested(QWebEngineDownloadRequest *download)
{
    QFileDialog dialog;
    dialog.setAcceptMode(QFileDialog::AcceptMode::AcceptSave);
    dialog.setFileMode(QFileDialog::FileMode::AnyFile);
    dialog.selectFile(download->suggestedFileName());

    if (dialog.exec() && dialog.selectedFiles().size() > 0)
    {
        download->setDownloadDirectory(dialog.directory().absolutePath());
        download->setDownloadFileName(dialog.selectedFiles().at(0));
        download->accept();
    }
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (isVisible()) {
        hide();
    } else {
        showNormal();
    }
}

void MainWindow::messageClicked()
{
    if (isVisible()) {
        hide();
    } else {
        showNormal();
    }
}

void MainWindow::doReload()
{
    this->webEngine->triggerPageAction(QWebEnginePage::ReloadAndBypassCache, false);
}
