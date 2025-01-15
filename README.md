# WhatsAppQT


## Description

Unofficial WhatsApp Web Desktop Client using Qt 6.8 Framework.

Purpose of the project is to provide a simple yet integrated Qt-based WhatsApp client into
(primarily) the KDE Plasma desktop.


## TODO

- [ ] Remove deprecation warnings.
- [ ] Create a script to build a toolbx under Fedora Linux.
- [ ] Upload to Flathub
- [ ] Notifications
- [ ] Menu


## Installation

Download the Git repository and navigate to the correct directory:

    cd /path/to/whatsappqt

To set up your Fedora system, use the included Toolbx script.

    ./toolbx_whatsappqt.sh

> [!NOTE]
> To build the application outside of Fedora Linux, read the script and follow the same steps in
> your system.

The build requires dependencies from [Flathub](flathub.org) there ensure it has been added as a
remote.

    flatpak remote-add --user --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo

Build the application, with or without making edits:

    flatpak-builder --user \
        --force-clean \
        --install-deps-from=flathub \
        --install \
        build-dir io.bit3.WhatsAppQT.yml

> [!IMPORTANT]
> This command installs the application in your Flatpak *user scope* only. Other users cannot use
> the application.

Run the application:

    flatpak run io.bit3.WhatsAppQT

## Usage

The application is an encapsulated webpage pointed at https://web.whatsapp.com, and provides the
same features that can be experienced there.


## Development

Follow the steps above and re-build the application after any changes. Here are some useful links
to get started.

- [Building your first Flatpak, flatpak.org](https://docs.flatpak.org/en/latest/first-build.html)
- [QtWebEngine BaseApp](https://github.com/flathub/io.qt.qtwebengine.BaseApp)
- [Qt WebEngine, qt.io](https://doc.qt.io/qt-6/qtwebengine-index.html)
- [Qt WebView, qt.io](https://doc.qt.io/qt-6/qtwebview-index.html)
- [Bug: qt.qpa.xcb: could not connect to display](https://github.com/flatpak/flatpak/issues/5448#issuecomment-1721703481)
(a very important comment that helped considerably and requires more consideration!)


## Acknowledgements

- Original application by [Tristan Lins](https://github.com/tristanlins).
- Icon by Teguh Sulistio https://www.iconfinder.com/VISOEALE


## Contact

Please contact the owner of this repository with any questions. Note that no support is provided
with this application.
