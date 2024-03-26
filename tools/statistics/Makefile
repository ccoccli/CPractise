include ../../make/env.mk

CFLAGS := -std=c11 -Wall

INC_DIR := -I./$(INC) \
					 -I../../$(BASE_DIR)/sys \
					 -I../../$(BASE_DIR)/time/$(INC) \
					 -I../../$(BASE_DIR)/log/$(INC) \
					 -I../../$(BASE_DIR)/sys/$(INC) \
					 -I../../$(DS_DIR)/$(LINKLIST)/$(INC)

LDFLAGS := -L../../$(BASE_DIR) -L../../$(DS_DIR) -lds -lsys_base -lpthread -lm

SRCS := $(SRC)/main.c
OBJS := $(SRCS:.c=.o)

TARGET := statistics

all: $(TARGET) install

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(TARGET) *.o

install:
	$(MV) $(TARGET) ../../$(OUT)/$(BIN)
.PHONY: all clean install