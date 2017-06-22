# -----------------------------------------------------------------------------
# UMDVTKXmarkerMapper project profile
#
# \file
# \author  Hannes
# \date    2017-06-21
# -----------------------------------------------------------------------------


TEMPLATE   = lib
TARGET     = UMDVTKXmarkerMapper

DESTDIR    = $$(MLAB_CURRENT_PACKAGE_DIR)/lib
DLLDESTDIR = $$(MLAB_CURRENT_PACKAGE_DIR)/lib

# Set high warn level (warn 4 on MSVC)
WARN = HIGH

# Add used projects here (see included pri files below for available projects)
CONFIG += dll ML MLBase vtk 

MLAB_PACKAGES += Hannes_General \
                 MeVisLab_Standard \
				 FMEwork_ThirdParty

# make sure that this file is included after CONFIG and MLAB_PACKAGES
include ($(MLAB_MeVis_Foundation)/Configuration/IncludePackages.pri)
include ($(MLAB_FMEwork_ThirdParty)/Configuration/DefaultProjectSetup.pri)
DEFINES += UMDVTKXMARKERMAPPER_EXPORTS

# Enable ML deprecated API warnings. To completely disable the deprecated API, change WARN to DISABLE.
DEFINES += ML_WARN_DEPRECATED

HEADERS += \
    UMDVTKXmarkerMapperInit.h \
    UMDVTKXmarkerMapperSystem.h \
    mlVTKXmarkerMapper.h \

SOURCES += \
    UMDVTKXmarkerMapperInit.cpp \
    mlVTKXmarkerMapper.cpp \