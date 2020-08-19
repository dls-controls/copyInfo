TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS BELOW HERE

# Use typed rset structure (see 3.16.1 release notes)
USR_CPPFLAGS += -DUSE_TYPED_RSET

# Build the IOC application
PROD_IOC = copyInfoExample

# copyInfoExample.dbd will be created and installed
DBD += copyInfoExample.dbd

# copyInfoExample.dbd will include these files:
copyInfoExample_DBD += base.dbd
copyInfoExample_DBD += devCopyInfo.dbd

# copyInfoExample_registerRecordDeviceDriver.cpp derives from copyInfoExample.dbd
copyInfoExample_SRCS += copyInfoExample_registerRecordDeviceDriver.cpp

# Build the main IOC entry point where needed
copyInfoExample_SRCS_DEFAULT += copyInfoExampleMain.cpp
copyInfoExample_SRCS_vxWorks += -nil-

# Link in the code from our support library
copyInfoExample_LIBS += copyInfo

# Link QSRV (pvAccess Server) if available
ifdef EPICS_QSRV_MAJOR_VERSION
    copyInfoExample_LIBS += qsrv
    copyInfoExample_LIBS += $(EPICS_BASE_PVA_CORE_LIBS)
    copyInfoExample_DBD += PVAServerRegister.dbd
    copyInfoExample_DBD += qsrv.dbd
endif

# Finally link IOC to the EPICS Base libraries
copyInfoExample_LIBS += $(EPICS_BASE_IOC_LIBS)

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD EXTRA GNUMAKE RULES BELOW HERE
