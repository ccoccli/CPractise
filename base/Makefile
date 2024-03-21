include ../make/env.mk

LIB_NAME := libsys_base.a

SRCS := $(wildcard ./$(TIME)/$(SRC)/*.c)
SRCS += $(wildcard ./$(LOG)/$(SRC)/*.c)
SRCS += $(wildcard ./$(SYS)/$(SRC)/*.c)

INC_DIR := -I./$(SYS) \
					 -I./$(TIME)/$(INC) \
					 -I./$(LOG)/$(INC) \
					 -I./$(SYS)/$(INC)

OBJS := $(patsubst %.c,%.o,$(SRCS))

BASE_INC_DIRS := $(wildcard ./*/$(INC)) $(wildcard ./$(SYS)/*.h)

CFLAGS := -std=c11 -Wall -g

all: $(LIB_NAME) install

$(LIB_NAME): $(OBJS)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJS) $(LIB_NAME)

install:
	$(CP) $(LIB_NAME) ../$(OUT)/$(LIB)

.PHONY: clean all install

