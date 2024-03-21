include make/env.mk

LIB_NAME := libsys_base.a
UNITTEST_TARGET := unitTest
######################################################################################
SRCS := $(wildcard $(BASE_DIR)/$(TIME)/$(SRC)/*.c)
SRCS += $(wildcard $(BASE_DIR)/$(LOG)/$(SRC)/*.c)
SRCS += $(wildcard $(BASE_DIR)/$(SYS)/$(SRC)/*.c)
SRCS += $(wildcard $(DS_DIR)/$(LINKLIST)/$(SRC)/*.c)

OBJS := $(patsubst %.c,%.o,$(SRCS))

INC_DIR := -I./$(BASE_DIR)/$(SYS) \
					 -I./$(BASE_DIR)/$(TIME)/$(INC) \
					 -I./$(BASE_DIR)/$(LOG)/$(INC) \
					 -I./$(BASE_DIR)/$(SYS)/$(INC) \
					 -I./$(DS_DIR)/$(LINKLIST)/$(INC)

BASE_INC_DIRS := $(wildcard $(BASE_DIR)/*/$(INC)) $(wildcard $(BASE_DIR)/$(SYS)/*.h)
INCLUDES_DIRS := $(patsubst $(BASE_DIR)/%,$(INCLUDES_DIR)/%,$(BASE_INC_DIRS))
######################################################################################
CFLAGS := -std=c11 -Wall -g
######################################################################################
LDFLAGS = -lpthread -lm
######################################################################################
all: $(LIB_NAME) $(UNITTEST_TARGET) install

$(LIB_NAME): $(OBJS)
	$(AR) $@ $^
%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@ $(LDFLAGS)
$(UNITTEST_TARGET):
	$(CD) $(UNITTEST_TARGET) && $(MAKE)

install: copy_includes
	$(STRIP) $(LIB_NAME)
	$(MK) $(BIN)
	$(MV) $(LIB_NAME) $(BIN)
	$(MK) $(OUT)
	$(MV) $(BIN) $(OUT)
	$(CP) $(INCLUDES_DIR) $(OUT)
copy_includes: $(INCLUDES_DIRS)

$(INCLUDES_DIR)/%: $(BASE_DIR)/%
	$(MK) $(@D)
	$(CP) -r $< $@

clean: includes_clean unitTest_clean
	$(RM) $(LIB_NAME) $(OBJS) $(BIN) $(OUT)
includes_clean:
	$(RM) $(INCLUDES_DIR)
unitTest_clean:
	$(CD) $(UNITTEST_TARGET) && $(MAKE) clean

help:
	$(ECHO) "Usage: make [target]"
	$(ECHO) "Targets:"
	$(ECHO) "  [all               ] Build debug and install"
	$(ECHO) "  [install           ] Install the library"
	$(ECHO) "  [clean             ] Remove build artifacts"
	$(ECHO) "  [unitTest          ] Build and execute unitTest"
	$(ECHO) "  [help              ] Show this help message"
.PHONY: all clean unitTest install unitTest_install help copy_includes