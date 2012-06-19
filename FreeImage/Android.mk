LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)


LOCAL_MODULE := png
LOCAL_SRC_FILES := \
		LibPNG/png.c \
		LibPNG/pngerror.c \
		LibPNG/pngget.c \
		LibPNG/pngmem.c \
		LibPNG/pngpread.c \
		LibPNG/pngread.c \
		LibPNG/pngrio.c \
		LibPNG/pngrtran.c \
		LibPNG/pngrutil.c \
		LibPNG/pngset.c \
		LibPNG/pngtrans.c \
		LibPNG/pngwio.c \
		LibPNG/pngwrite.c \
		LibPNG/pngwtran.c \
		LibPNG/pngwutil.c 

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := jpeg
LOCAL_SRC_FILES := \
		LibJPEG/ansi2knr.c \
		LibJPEG/cdjpeg.c \
		LibJPEG/cjpeg.c \
		LibJPEG/ckconfig.c \
		LibJPEG/djpeg.c \
		LibJPEG/jaricom.c \
		LibJPEG/jcapimin.c \
		LibJPEG/jcapistd.c \
		LibJPEG/jcarith.c \
		LibJPEG/jccoefct.c \
		LibJPEG/jccolor.c \
		LibJPEG/jcdctmgr.c \
		LibJPEG/jchuff.c \
		LibJPEG/jcinit.c \
		LibJPEG/jcmainct.c \
		LibJPEG/jcmarker.c \
		LibJPEG/jcmaster.c \
		LibJPEG/jcomapi.c \
		LibJPEG/jcparam.c \
		LibJPEG/jcprepct.c \
		LibJPEG/jcsample.c \
		LibJPEG/jctrans.c \
		LibJPEG/jdapimin.c \
		LibJPEG/jdapistd.c \
		LibJPEG/jdarith.c \
		LibJPEG/jdatadst.c \
		LibJPEG/jdatasrc.c \
		LibJPEG/jdcoefct.c \
		LibJPEG/jdcolor.c \
		LibJPEG/jddctmgr.c \
		LibJPEG/jdhuff.c \
		LibJPEG/jdinput.c \
		LibJPEG/jdmainct.c \
		LibJPEG/jdmarker.c \
		LibJPEG/jdmaster.c \
		LibJPEG/jdmerge.c \
		LibJPEG/jdpostct.c \
		LibJPEG/jdsample.c \
		LibJPEG/jdtrans.c \
		LibJPEG/jerror.c \
		LibJPEG/jfdctflt.c \
		LibJPEG/jfdctfst.c \
		LibJPEG/jfdctint.c \
		LibJPEG/jidctflt.c \
		LibJPEG/jidctfst.c \
		LibJPEG/jidctint.c \
		LibJPEG/jmemansi.c \
		LibJPEG/jmemmgr.c \
		LibJPEG/jmemname.c \
		LibJPEG/jmemnobs.c \
		LibJPEG/jpegtran.c \
		LibJPEG/jquant1.c \
		LibJPEG/jquant2.c \
		LibJPEG/jutils.c \
		LibJPEG/rdbmp.c \
		LibJPEG/rdcolmap.c \
		LibJPEG/rdgif.c \
		LibJPEG/rdjpgcom.c \
		LibJPEG/rdppm.c \
		LibJPEG/rdrle.c \
		LibJPEG/rdswitch.c \
		LibJPEG/rdtarga.c \
		LibJPEG/transupp.c \
		LibJPEG/wrbmp.c \
		LibJPEG/wrgif.c \
		LibJPEG/wrjpgcom.c \
		LibJPEG/wrppm.c \
		LibJPEG/wrrle.c \
		LibJPEG/wrtarga.c

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := zlib
LOCAL_SRC_FILES := \
		ZLib/adler32.c \
		ZLib/compress.c \
		ZLib/crc32.c \
		ZLib/deflate.c \
		ZLib/gzclose.c \
		ZLib/gzlib.c \
		ZLib/gzread.c \
		ZLib/gzwrite.c \
		ZLib/infback.c \
		ZLib/inffast.c \
		ZLib/inflate.c \
		ZLib/inftrees.c \
		ZLib/trees.c \
		ZLib/uncompr.c \
		ZLib/zutil.c

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)


LOCAL_MODULE := freeimage
LOCAL_C_INCLUDES := $(LOCAL_PATH)/ $(LOCAL_PATH)/OpenEXR/IlmImf/ $(LOCAL_PATH)/OpenEXR/Half/ $(LOCAL_PATH)/OpenEXR/Iex/ $(LOCAL_PATH)/OpenEXR/IlmThread/ $(LOCAL_PATH)/OpenEXR/Imath/
LOCAL_SRC_FILES := \
		FreeImage/FreeImageC.c \
		FreeImage/BitmapAccess.cpp \
		FreeImage/CacheFile.cpp \
		FreeImage/ColorLookup.cpp \
		FreeImage/Conversion.cpp \
		FreeImage/Conversion4.cpp \
		FreeImage/Conversion8.cpp \
		FreeImage/Conversion16_555.cpp \
		FreeImage/Conversion16_565.cpp \
		FreeImage/Conversion24.cpp \
		FreeImage/Conversion32.cpp \
		FreeImage/ConversionFloat.cpp \
		FreeImage/ConversionRGB16.cpp \
		FreeImage/ConversionRGBF.cpp \
		FreeImage/ConversionType.cpp \
		FreeImage/ConversionUINT16.cpp \
		FreeImage/FreeImage.cpp \
		FreeImage/FreeImageIO.cpp \
		FreeImage/GetType.cpp \
		FreeImage/Halftoning.cpp \
		FreeImage/J2KHelper.cpp \
		FreeImage/MemoryIO.cpp \
		FreeImage/MNGHelper.cpp \
		FreeImage/MultiPage.cpp \
		FreeImage/NNQuantizer.cpp \
		FreeImage/PixelAccess.cpp \
		FreeImage/Plugin.cpp \
		FreeImage/PluginBMP.cpp \
		FreeImage/PluginGIF.cpp \
		FreeImage/PluginICO.cpp \
		FreeImage/PluginJPEG.cpp \
		FreeImage/PluginPCX.cpp \
		FreeImage/PluginPSD.cpp \
		FreeImage/PluginPNG.cpp \
		FreeImage/PluginTARGA.cpp \
		FreeImage/PSDParser.cpp \
		FreeImage/tmoColorConvert.cpp \
		FreeImage/tmoDrago03.cpp \
		FreeImage/tmoFattal02.cpp \
		FreeImage/tmoReinhard05.cpp \
		FreeImage/ToneMapping.cpp \
		FreeImage/WuQuantizer.cpp \
		FreeImage/ZLibInterface.cpp \
		Metadata/Exif.cpp \
		Metadata/FIRational.cpp \
		Metadata/FreeImageTag.cpp \
		Metadata/IPTC.cpp \
		Metadata/TagConversion.cpp \
		Metadata/TagLib.cpp \
		Metadata/XTIFF.cpp \
		FreeImageToolkit/Background.cpp \
		FreeImageToolkit/BSplineRotate.cpp \
		FreeImageToolkit/Channels.cpp \
		FreeImageToolkit/ClassicRotate.cpp \
		FreeImageToolkit/Colors.cpp \
		FreeImageToolkit/CopyPaste.cpp \
		FreeImageToolkit/Display.cpp \
		FreeImageToolkit/Flip.cpp \
		FreeImageToolkit/JPEGTransform.cpp \
		FreeImageToolkit/MultigridPoissonSolver.cpp \
		FreeImageToolkit/Rescale.cpp \
		FreeImageToolkit/Resize.cpp

LOCAL_CPP_FEATURES += exceptions
LOCAL_STATIC_LIBRARIES := png jpeg zlib

include $(BUILD_STATIC_LIBRARY)

