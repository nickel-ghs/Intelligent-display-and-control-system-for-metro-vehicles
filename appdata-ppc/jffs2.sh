#!/bin/sh

./mkfs.jffs2 -o appdata_ppc_TPX6X.img  -e 0x20000 -r project -p -b
#./sumtool -i rootfs.img  -o rootfs.jffs2  -e 0x40000 -p
#rm -f rootfs.img


