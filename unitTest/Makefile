include ../make/env.mk

CFLAGS := -std=c11 -Wall

INC_DIR := -I../$(BASE_DIR)/sys \
					 -I../$(BASE_DIR)/time/inc \
					 -I../$(BASE_DIR)/log/inc \
					 -I../$(BASE_DIR)/sys/inc \
					 -I../$(DS_DIR)/$(LINKLIST)/inc

LDFLAGS := -L../$(BASE_DIR) -L../$(DS_DIR) -lds -lsys_base -lpthread -lm

SRCS := main.c
OBJS := $(SRCS:.c=.o)

TARGET := sample

all: $(TARGET) install

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(TARGET) *.o

install:
	$(MV) $(TARGET) ../$(OUT)/$(BIN)
.PHONY: all clean install
