# MakefilePre.mk

CC = gcc
AR = ar
RANLIB = ranlib
RM = rm
MKDIR = mkdir
MAKE = make

ROOT_SRC_DIR = $(PROJ_ROOT)/Source
ROOT_OUT_DIR = $(PROJ_ROOT)/Out
ROOT_LIB_DIR = $(ROOT_OUT_DIR)/Library

INC_DIRS = -I$(PROJ_ROOT)/Include

ifeq ($(RELEASE), 1)
OBJS_DIR = Release
DBG_FLAGS = -O2 -DNDEBUG
else
OBJS_DIR = Debug
DBG_FLAGS = -g -O0 -DDEBUG
endif

DEPEND_FILE = $(OBJS_DIR)/depend_file

LIB_DIRS = -L$(ROOT_LIB_DIR)/$(OBJS_DIR)