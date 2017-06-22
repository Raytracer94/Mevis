# -----------------------------------------------------------------------------
# UMDUnwinding project profile
#
# \file
# \author  Hannes
# \date    2017-06-20
# -----------------------------------------------------------------------------


TEMPLATE   = lib
TARGET     = UMDUnwinding

DESTDIR    = $$(MLAB_CURRENT_PACKAGE_DIR)/lib
DLLDESTDIR = $$(MLAB_CURRENT_PACKAGE_DIR)/lib

# Set high warn level (warn 4 on MSVC)
WARN = HIGH

# Add used projects here (see included pri files below for available projects)
CONFIG += dll ML MLBase

MLAB_PACKAGES += Hannes_General \
                 MeVisLab_Standard

# make sure that this file is included after CONFIG and MLAB_PACKAGES
include ($(MLAB_MeVis_Foundation)/Configuration/IncludePackages.pri)

DEFINES += UMDUNWINDING_EXPORTS

# Enable ML deprecated API warnings. To completely disable the deprecated API, change WARN to DISABLE.
DEFINES += ML_WARN_DEPRECATED

HEADERS += \
    UMDUnwindingInit.h \
    UMDUnwindingSystem.h \
    mlUnwinding.h \
	cUnwinding.h\

SOURCES += \
    UMDUnwindingInit.cpp \
    mlUnwinding.cpp \
	cUnwinding.cpp\