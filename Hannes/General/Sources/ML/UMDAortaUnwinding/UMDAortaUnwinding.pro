# -----------------------------------------------------------------------------
# UMDAortaUnwinding project profile
#
# \file
# \author  Hannes
# \date    2017-05-09
# -----------------------------------------------------------------------------


TEMPLATE   = lib
TARGET     = UMDAortaUnwinding

DESTDIR    = $$(MLAB_CURRENT_PACKAGE_DIR)/lib
DLLDESTDIR = $$(MLAB_CURRENT_PACKAGE_DIR)/lib

# Set high warn level (warn 4 on MSVC)
WARN = HIGH

# Add used projects here (see included pri files below for available projects)
CONFIG += dll ML

MLAB_PACKAGES += Hannes_General \
                 MeVisLab_Standard

# make sure that this file is included after CONFIG and MLAB_PACKAGES
include ($(MLAB_MeVis_Foundation)/Configuration/IncludePackages.pri)

DEFINES += UMDAORTAUNWINDING_EXPORTS

# Enable ML deprecated API warnings. To completely disable the deprecated API, change WARN to DISABLE.
DEFINES += ML_WARN_DEPRECATED

HEADERS += \
    UMDAortaUnwindingInit.h \
    UMDAortaUnwindingSystem.h \
    mlAortaUnwindingOutputImageHandler.h \
    mlAortaUnwinding.h \

SOURCES += \
    UMDAortaUnwindingInit.cpp \
    mlAortaUnwindingOutputImageHandler.cpp \
    mlAortaUnwinding.cpp \