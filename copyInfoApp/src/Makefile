TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#==================================================
# build a support library

LIBRARY_IOC += copyInfo

# install copyInfo.dbd into <top>/dbd
DBD += devCopyInfo.dbd

# specify all source files to be compiled and added to the library
copyInfo_SRCS += devCopyInfo.c

copyInfo_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

