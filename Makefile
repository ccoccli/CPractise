LIB_NAME := libsys_base.a
UNITTEST_TARGET := unitTest
######################################################################################
CC := gcc
CXX := g++
RM := rm -rf
MK := mkdir -p
AR := ar rcs
MV := mv
TOUCH := touch
STRIP := strip
FIND := find
CD := cd
MAKE := make
ECHO := @echo
CP := cp
######################################################################################
OUT := ./out
SRCS := $(wildcard base/time/src/*.c)
SRCS += $(wildcard base/log/src/*.c)
SRCS += $(wildcard base/sys/src/*.c)

OBJS := $(patsubst %.c,%.o,$(SRCS))
INC_DIR := -I./base/sys \
					 -I./base/time/inc \
					 -I./base/log/inc \
					 -I./base/sys/inc

BIN := ./bin

BASE_DIR := base
INCLUDES_DIR := includes

BASE_INC_DIRS := $(wildcard $(BASE_DIR)/*/inc)
INCLUDES_DIRS := $(patsubst $(BASE_DIR)/%,$(INCLUDES_DIR)/%,$(BASE_INC_DIRS))
######################################################################################
CFLAGS := -std=c11 -Wall

DEBUG_CFLAGS := -g
RELEASE_CFLAGS := -O2

debug: CFLAGS += $(DEBUG_CFLAGS)
release: CFLAGS += $(RELEASE_CFLAGS)
######################################################################################

LDFLAGS = -lpthread

######################################################################################
all: debug install unitTest_install

debug: $(LIB_NAME)

release: $(LIB_NAME)
	$(STRIP) $(LIB_NAME)
$(LIB_NAME): $(OBJS)
	$(AR) $@ $^
%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@ $(LDFLAGS)
install: copy_includes
	$(MK) $(OUT)
	$(MK) $(BIN)
	$(MV) $(LIB_NAME) $(BIN)
	$(MV) $(BIN) out/
	$(MV) $(INCLUDES_DIR) $(OUT)
clean: includes_clean
	$(ECHO) -e "\033[32;1mCleaning binary files\033[0m"
	$(RM) $(LIB_NAME) $(OBJS) $(BIN) $(OUT)
unitTest:
	$(ECHO) -e "\033[32;1mStart compile unit test\033[0m"
	$(CD) $(UNITTEST_TARGET) && $(MAKE)
unitTest_install: unitTest
	$(CD) $(UNITTEST_TARGET) && $(MV) $(UNITTEST_TARGET) ../$(OUT)/$(BIN)/$(UNITTEST_TARGET)
copy_includes: $(INCLUDES_DIRS)

$(INCLUDES_DIR)/%: $(BASE_DIR)/%
	$(ECHO) -e "\033[32;1mCopying $< to $@\033[0m"
	$(MK) $(@D)
	$(CP) -r $< $@
includes_clean:
	$(ECHO) -e "\033[32;1mCleaning includes directory\033[0m"
	$(RM) $(INCLUDES_DIR)
help:
	$(ECHO) -e "\033[36;1mUsage: make [target]"
	$(ECHO) -e "\033[36;1mTargets:"
	$(ECHO) -e "\033[36;1m  [all               ] Build debug and install\033[0m"
	$(ECHO) -e "\033[36;1m  [debug             ] Build debug version\033[0m"
	$(ECHO) -e "\033[36;1m  [release           ] Build release version and strip debug symbols\033[0m"
	$(ECHO) -e "\033[36;1m  [install           ] Install the library\033[0m"
	$(ECHO) -e "\033[36;1m  [clean             ] Remove build artifacts\033[0m"
	$(ECHO) -e "\033[36;1m  [unitTest          ] Build and execute unitTest\033[0m"
	$(ECHO) -e "\033[36;1m  [unitTest_install  ] Install unitTest\033[0m"
	$(ECHO) -e "\033[36;1m  [help              ] Show this help message\033[0m"
.PHONY: all debug release clean unitTest unitTest_install help copy_includes