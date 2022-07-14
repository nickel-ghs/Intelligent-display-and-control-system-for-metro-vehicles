CXX = g++
CC=arm-linux-gcc
CCPPC=	powerpc-603e-linux-g++
OBJECT=app
OBJECT_ARM=armapp
OBJECT_PPC=ppcapp

CFLAGS = -Wall\
	-DG_DISABLE_DEPRECATED\
	-DGDK_DISABLE_DEPRECATED\
	-DGDK_PIXBUF_DISABLE_DEPRECATED\
	-DGTK_DISABLE_DEPRECATED\
  -Wno-deprecated

SRC=main.cxx\
    surface/train-ningbo.cxx\
    src/callback.cxx\
    src/network_data.cxx\
    src/main_data.cxx\
    src/io_A.cxx\
    src/io_B.cxx\
    src/io_C.cxx\
  
INCLUDE = -I/usr/X11R6/include\
          -I/usr/local/fltk/pc/include\
          -I/usr/local/fltk/pc/include/comm
          
INCLUDE_ARM = -I/usr/X11R6/include\
          -I/usr/local/fltk/arm/include\
          -I/usr/local/fltk/arm/include/comm

LIB	=  -L/usr/local/fltk/pc/lib/X11  -lXext -lX11 \
           -L/usr/local/fltk/pc/lib/linux  -lz -ljpeg -lm -lpthread
	
FLTKLIB =   /usr/local/fltk/pc/lib/fltk/libfltk.a\
 /usr/local/fltk/pc/lib/fltk/libfltk_images.a\
   /usr/local/fltk/pc/lib/fltk/libfltk_png.a\
 /usr/local/fltk/pc/lib/comm/libmvb.a\
 /usr/local/fltk/pc/lib/comm/libtpx20.a
 
LIB_ARM	=  -L/usr/local/fltk/arm/lib/X11  -lXext -lX11\
           -L/usr/local/fltk/arm/lib/linux  -lz -ljpeg -lm -lpthread
	
FLTKLIB_ARM =   /usr/local/fltk/arm/lib/fltk/libfltk.a\
 /usr/local/fltk/arm/lib/fltk/libfltk_images.a\
 /usr/local/fltk/pc/lib/fltk/libfltk_png.a\
 /usr/local/fltk/arm/lib/comm/libmvb_arm.a\
 /usr/local/fltk/arm/lib/comm/libtpx20_arm.a

INCLUDE_PPC = -I/usr/X11R6/include   \
          -I/usr/local/fltk/ppc/include\
          -I/usr/local/fltk/ppc/include/comm \

LIB_PPC	=  -L/usr/local/fltk/ppc/lib/X11  -lXext -lX11  \
           -L/usr/local/fltk/ppc/lib/linux  -lz -lm -lpthread
           

FLTKLIB_PPC =   /usr/local/fltk/ppc/lib/fltk/libfltk.a \
 /usr/local/fltk/ppc/lib/fltk/libfltk_images.a\
 /usr/local/fltk/pc/lib/fltk/libfltk_png.a\
 /usr/local/fltk/ppc/lib/fltk/libfltk_jpeg.a\
 /usr/local/fltk/ppc/lib/comm/libmvb_ppc.a\
 /usr/local/fltk/ppc/lib/comm/libtpx20_ppc.a
 

$(OBJECT):$(SRC)
	$(CXX) $(SRC) -o $(OBJECT) $(CFLAGS)   $(INCLUDE) $(LIB) $(FLTKLIB)	      
       
PHONY:arm
arm:
	$(CC) $(SRC) -o $(OBJECT_ARM) $(CFLAGS)   $(INCLUDE_ARM) $(LIB_ARM) $(FLTKLIB_ARM)
	
PHONY:ppc
ppc:
	$(CCPPC) $(SRC) -o $(OBJECT_PPC) $(CFLAGS)   $(INCLUDE_PPC) $(LIB_PPC) $(FLTKLIB_PPC)

clean: 
	rm -f *.o $(OBJECT) $(OBJECT_ARM) $(OBJECT_PPC)
