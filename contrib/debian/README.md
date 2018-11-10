
Debian
====================
This directory contains files used to package proeliod/proelio-qt
for Debian-based Linux systems. If you compile proeliod/proelio-qt yourself, there are some useful files here.

## proelio: URI support ##


proelio-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install proelio-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your proelioqt binary to `/usr/bin`
and the `../../share/pixmaps/proelio128.png` to `/usr/share/pixmaps`

proelio-qt.protocol (KDE)

