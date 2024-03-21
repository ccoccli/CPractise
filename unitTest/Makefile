include ../make/env.mk

CFLAGS := -std=c11 -Wall

INC_DIR := -I../$(BASE_DIR)/sys \
					 -I../$(BASE_DIR)/time/inc \
					 -I../$(BASE_DIR)/log/inc \
					 -I../$(BASE_DIR)/sys/inc \
					 -I../$(DS_DIR)/$(LINKLIST)/$(INC)

LDFLAGS := -L../$(BIN) -L../ -lsys_base -lpthread

TARGET := unitTest

all: touch $(TARGET)

touch:
	$(TOUCH) main.c
$(TARGET): main.c
	$(CC) $(CFLAGS) $(INC_DIR) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(TARGET) *.log

.PHONY: all clean
