include make/env.mk

all: makedir base ds tools unitTest copy_inc

makedir:
	$(MK) $(OUT) && $(CD) $(OUT) && $(MK) $(LIB) && $(MK) $(BIN) && $(MK) $(INCLUDES)

base:
	$(CD) $(BASE_DIR) && $(MAKE)

ds:
	$(CD) $(DS_DIR) && $(MAKE)

unitTest:
	$(CD) $(UNITTEST) && $(MAKE)

tools:
	$(CD) $(TOOLS) && $(MAKE)

#拷贝所有头文件到输出目录
copy_inc:
	$(FIND) . -type d -name 'inc' | while read -r dir; do \
		dest="./$(OUT)/$(INCLUDES)/$$(dirname "$${dir#./}")"; \
		$(MK) "$$dest"; \
		$(CP) "$$dir"/* "$$dest"; \
	done

clean:
	$(RM) $(OUT)
	$(CD) $(BASE_DIR) && $(MAKE) clean
	$(CD) $(DS_DIR) && $(MAKE) clean
	$(CD) $(UNITTEST) && $(MAKE) clean
	$(CD) $(TOOLS) && $(MAKE) clean

.PHONY: all base ds unitTest clean tools copy_inc
