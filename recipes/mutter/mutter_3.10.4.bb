require mutter.inc

PR = "r5"

LIC_FILES_CHKSUM = "file://COPYING;md5=94d55d512a9ba36caa9b7df079bae19f"

SRC_URI += "file://nodocs.patch \
            file://nozenity.patch \
            file://fix_pkgconfig.patch \
	    file://0001-window-actor-Guard-against-NULL-frame-mask.patch \
           "
SRC_URI[md5sum] = "e25602e010097aa44611da102c514c7c"
SRC_URI[sha256sum] = "9159c40ea9f5c5e3d1e67cc12ebcbd6328a7b732274195b4e5bdacb3cb1771e6"
