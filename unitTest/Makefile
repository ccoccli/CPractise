CC := gcc
TOUCH := touch
CFLAGS := -std=c11 -Wall

INC_DIR := -I../base/sys \
					 -I../base/time/inc \
					 -I../base/log/inc \
					 -I../base/sys/inc

LDFLAGS := -L../bin -lsys_base -lpthread

TARGET := unitTest

all: touch $(TARGET)

touch:
	$(TOUCH) main.c
$(TARGET): main.c
	$(CC) $(CFLAGS) $(INC_DIR) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(TARGET)

.PHONY: all clean
