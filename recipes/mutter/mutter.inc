SECTION = "x11/wm"
DESCRIPTION = "Metacity is the boring window manager for the adult in you. Mutter is metacity + clutter."
LICENSE = "GPLv2"
DEPENDS = "startup-notification gsettings-desktop-schemas upower gtk+3 gnome-desktop3 gconf clutter-1.0 cogl-1.0 libxcomposite gdk-pixbuf-native intltool glib-2.0-native"
RDEPENDS = "gsettings-desktop-schemas"
# gobject-introspection
inherit gnome update-alternatives

SHRT_VER = "${@d.getVar('PV',1).split('.')[0]}.${@d.getVar('PV',1).split('.')[1]}"
SRC_URI = "${GNOME_MIRROR}/${BPN}/${SHRT_VER}/${BPN}-${PV}.tar.xz"

ALTERNATIVE_${PN} = "x-window-manager"
ALTERNATIVE_TARGET[x-window-manager] = "${bindir}/mutter"
ALTERNATIVE_PRIORITY = "11"

EXTRA_OECONF += "--disable-verbose-mode	\
		 --disable-schemas-compile \
		 --disable-startup-notification \
		 --enable-compile-warnings=yes \
		 --enable-introspection=no \
	         --without-libcanberra"
# --disable-sm --disable-schemas-compile


#RDEPENDS_${PN} = "zenity"

FILES_${PN} += "${datadir}/themes ${libdir}/mutter/plugins/*.so ${datadir}/gnome/wm-properties/ ${datadir}/gnome-control-center/keybindings/*.xml"
FILES_${PN}-dbg += "${libdir}/mutter/plugins/.debug/*"

CFLAGS_FOR_BUILD += "-I${STAGING_INCDIR_NATIVE}/glib-2.0 -I${STAGING_INCDIR_NATIVE}/glib-2.0/include"
LDFLAGS_FOR_BUILD += "-L${STAGING_LIBDIR_NATIVE} -lglib-2.0"

do_configure_prepend () {
        echo "EXTRA_DIST=" > ${S}/gnome-doc-utils.make
}		

pkg_postinst_${PN} () {
#!/bin/sh -e
if [ "x$D" != "x" ]; then
    exit 1
fi

. ${sysconfdir}/init.d/functions

gconftool-2 --config-source=xml::$D${sysconfdir}/gconf/gconf.xml.defaults --direct --type list --list-type string --set /apps/mutter/general/clutter_plugins '[default]'

gconftool-2 --config-source=xml::$D${sysconfdir}/gconf/gconf.xml.defaults --direct --type bool --set /apps/mutter/general/compositing_manager true

glib-compile-schemas ${datadir}/usr/share/glib-2.0/schemas
}

pkg_postrm_${PN} () {
#!/bin/sh -e

glib-compile-schemas ${datadir}/usr/share/glib-2.0/schemas
}
