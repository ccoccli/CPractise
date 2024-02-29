CC := gcc
CFLAGS := -std=c11 -Wall

INC_DIR := -I../base/sys \
					 -I../base/time/inc \
					 -I../base/log/inc \
					 -I../base/sys/inc

LDFLAGS := -L../out/bin -lsys_base -lpthread

TARGET := unitTest

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) $(INC_DIR) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
