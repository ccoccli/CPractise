#CROSS_COMPILE :=

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
CP := cp -raf


LIB := lib
OUT := out
BIN := bin
INCLUDES := includes

DS_DIR := ds
LINKLIST := linklist
SORT := sort

BASE_DIR := base
SYS := sys
LOG := log
TIME := time
INC  := inc
SRC := src

TOOLS := tools
STATISTICS := statistics

UNITTEST := unitTest

