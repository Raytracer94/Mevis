# -----------------------------------------------------------------------------
# UMDTest project profile
#
# \file
# \author  Hannes
# \date    2017-05-12
# -----------------------------------------------------------------------------


TEMPLATE   = lib
TARGET     = UMDTest

DESTDIR    = $$(MLAB_CURRENT_PACKAGE_DIR)/lib
DLLDESTDIR = $$(MLAB_CURRENT_PACKAGE_DIR)/lib

# Set high warn level (warn 4 on MSVC)
WARN = HIGH

# Add used projects here (see included pri files below for available projects)
CONFIG += dll ML MLBase vtk MLVTKSupport

MLAB_PACKAGES += Hannes_General \
                 MeVisLab_Standard

# make sure that this file is included after CONFIG and MLAB_PACKAGES
include ($(MLAB_MeVis_Foundation)/Configuration/IncludePackages.pri)
include ($(MLAB_FMEwork_VTK)/Configuration/DefaultProjectSetup.pri)
include ($(MLAB_FMEwork_VTK)/Configuration/FMEwork_VTK.pri)

DEFINES += UMDTEST_EXPORTS

# Enable ML deprecated API warnings. To completely disable the deprecated API, change WARN to DISABLE.
DEFINES += ML_WARN_DEPRECATED

HEADERS += \
    UMDTestInit.h \
    UMDTestSystem.h \
    mlTest.h \
	Unwinding.h \

SOURCES += \
    UMDTestInit.cpp \
    mlTest.cpp \
	Unwinding.cpp \