include make/env.mk

all: makedir base ds unitTest

makedir:
	$(MK) $(OUT) && $(CD) $(OUT) && $(MK) $(LIB) && $(MK) $(BIN) && $(MK) $(INCLUDES)
base:
	$(CD) $(BASE_DIR) && $(MAKE)

ds:
	$(CD) $(DS_DIR) && $(MAKE)

unitTest:
	$(CD) $(UNITTEST) && $(MAKE)

clean:
	$(RM) $(OUT)
	$(CD) $(BASE_DIR) && $(MAKE) clean
	$(CD) $(DS_DIR) && $(MAKE) clean
	$(CD) $(UNITTEST) && $(MAKE) clean

.PHONY: all base ds unitTest clean help
