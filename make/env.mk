#CROSS_COMPILE := arm-linux-gnueabihf-

CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
AR := $(CROSS_COMPILE)ar rcs
STRIP := $(CROSS_COMPILE)strip

RM := rm -rf
MK := mkdir -p
MV := mv
TOUCH := touch
FIND := find
CD := cd
MAKE := make
ECHO := @echo
CP := cp -rf

OUT := out
BIN := bin
BASE_DIR := base
DS_DIR := ds
LINKLIST := linklist
INCLUDES_DIR := includes
SYS := sys
LOG := log
TIME := time
INC  := inc
SRC := src