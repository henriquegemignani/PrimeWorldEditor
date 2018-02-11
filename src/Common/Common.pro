#-------------------------------------------------
#
# Project created by QtCreator 2015-12-13T15:27:18
#
#-------------------------------------------------

QT -= core gui
DEFINES += PWE_COMMON

CONFIG += staticlib
TEMPLATE = lib
DESTDIR = $$BUILD_DIR/Common

unix {
    target.path = /usr/lib
    QMAKE_CXXFLAGS += /WX
    INSTALLS += target
}

CONFIG (debug, debug|release) {
    # Debug Config
    OBJECTS_DIR = $$BUILD_DIR/Common/debug
    TARGET = Commond

    # Debug Libs
    LIBS += -L$$EXTERNALS_DIR/boost_1_63_0/lib64-msvc-14.0 -llibboost_filesystem-vc140-mt-gd-1_63 \
            -L$$EXTERNALS_DIR/tinyxml2/lib -ltinyxml2d
}

CONFIG (release, debug|release) {
    # Release Config
    OBJECTS_DIR = $$BUILD_DIR/build/Common/release
    TARGET = Common

    # Release Libs
    LIBS += -L$$EXTERNALS_DIR/boost_1_63_0/lib64-msvc-14.0 -llibboost_filesystem-vc140-mt-1_63 \
            -L$$EXTERNALS_DIR/tinyxml2/lib -ltinyxml2
}

# Include Paths
INCLUDEPATH += $$PWE_MAIN_INCLUDE \
               $$EXTERNALS_DIR/boost_1_63_0 \
               $$EXTERNALS_DIR/tinyxml2/include

# Header Files
HEADERS += \
    CColor.h \
    CFourCC.h \
    CTimer.h \
    EKeyInputs.h \
    EMouseInputs.h \
    ETransformSpace.h \
    Flags.h \
    TString.h \
    types.h \
    Log.h \
    FileUtil.h \
    AssertMacro.h \
    CScopedTimer.h \
    CAssetID.h \
    Hash\CFNV1A.h \
    Serialization/IArchive.h \
    Serialization/CXMLWriter.h \
    Serialization/CXMLReader.h \
    EGame.h \
    Serialization/CBasicBinaryWriter.h \
    Serialization/CBasicBinaryReader.h \
    Serialization/CBinaryWriter.h \
    Serialization/CBinaryReader.h \
    Serialization/CSerialVersion.h \
    Serialization/XML.h \
    Serialization/Binary.h \
    FileIO\CFileInStream.h \
    FileIO\CFileOutStream.h \
    FileIO\CMemoryInStream.h \
    FileIO\CMemoryOutStream.h \
    FileIO\CTextInStream.h \
    FileIO\CTextOutStream.h \
    FileIO\CVectorOutStream.h \
    FileIO\IOUtil.h \
    FileIO\IInputStream.h \
    FileIO\IOutputStream.h \
    FileIO\CBitStreamInWrapper.h \
    FileIO\CFileLock.h \
    FileIO.h \
    Common.h \
    Hash/CCRC32.h

# Source Files
SOURCES += \
    CColor.cpp \
    CTimer.cpp \
    TString.cpp \
    Log.cpp \
    FileUtil.cpp \
    CAssetID.cpp \
    EGame.cpp \
    Serialization/CSerialVersion.cpp \
    FileIO\CFileInStream.cpp \
    FileIO\CFileOutStream.cpp \
    FileIO\CMemoryInStream.cpp \
    FileIO\CMemoryOutStream.cpp \
    FileIO\CTextInStream.cpp \
    FileIO\CTextOutStream.cpp \
    FileIO\CVectorOutStream.cpp \
    FileIO\IOUtil.cpp \
    FileIO\IInputStream.cpp \
    FileIO\IOutputStream.cpp \
    FileIO\CBitStreamInWrapper.cpp \
    Hash/CCRC32.cpp
