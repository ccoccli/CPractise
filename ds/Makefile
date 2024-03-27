include ../make/env.mk

LIB_NAME := libds.a

SRCS := $(wildcard ./$(LINKLIST)/$(SRC)/*.c)
SRCS += $(wildcard ./$(SORT)/$(SRC)/*.c)

INC_DIR := -I../$(BASE_DIR)/$(SYS) \
					 -I../$(BASE_DIR)/$(TIME)/$(INC) \
					 -I../$(BASE_DIR)/$(LOG)/$(INC) \
					 -I../$(BASE_DIR)/$(SYS)/$(INC) \
					 -I ./$(LINKLIST)/$(INC) \
					 -I ./$(SORT)/$(INC)

OBJS := $(patsubst %.c,%.o,$(SRCS))

CFLAGS := -std=c11 -Wall -g

all: $(LIB_NAME) install 

$(LIB_NAME): $(OBJS)
	$(AR) $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJS) $(LIB_NAME)

install:
	$(CP) $(LIB_NAME) ../$(OUT)/$(LIB)
.PHONY: clean all install

