# Application name
APPL ?= ds_twr_resp3_test

# Optimization Level
# Please Refer to toolchain_xxx.mk for this option
OLEVEL ?= O2

##
# Current Board And Core
##
BOARD ?= emsk
BD_VER ?= 22
CUR_CORE ?= arcem7d

##
# select debugging jtag
##
JTAG ?= usb

##
# Set toolchain
##
#TOOLCHAIN ?= mw
TOOLCHAIN ?= gnu


STACKSZ = 4096

# Selected OS
#OS_SEL ?= freertos

#
# root dir of embARC
#
EMBARC_ROOT = ../

MID_SEL = common

# application source dirs
APPL_CSRC_DIR = ../
APPL_ASMSRC_DIR = ../
APPL_CSRC_DIR += ../decadriver
APPL_CSRC_DIR += ../platform

# application include dirs
APPL_INC_DIR = ../
APPL_INC_DIR += ../decadriver
APPL_INC_DIR += ../platform

# include current project makefile
COMMON_COMPILE_PREREQUISITES += makefile

### Options above must be added before include options.mk ###
# include key embARC build system makefile
override EMBARC_ROOT := $(strip $(subst \,/,$(EMBARC_ROOT)))
include $(EMBARC_ROOT)/options/options.mk
