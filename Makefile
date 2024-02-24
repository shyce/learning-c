# Makefile

.PHONY: all clean subdirs

all: subdirs

OUT_DIR = ./.bin
MAKEFLAGS += -s

SUBDIRS = $(shell find . -type d -name '*' -exec sh -c 'find "{}" -maxdepth 1 -name "*.c" | grep -q "."' \; -print)

subdirs:
	echo "Select a subfolder to compile from the list below:"; \
	selected=$$(printf '%s\n' $(SUBDIRS) | fzf --height=50% --reverse --preview 'echo "Compiling in directory: {}"' --select-1); \
	echo "Compiling in directory: $$selected"; \
	dirname=$$(basename $$selected); \
	mkdir -p $(OUT_DIR); \
	if [ -f $$selected/Makefile ]; then \
		echo "Using Makefile in directory: $$selected"; \
		$(MAKE) -C $$selected; \
		mv $$selected/$$dirname $(OUT_DIR)/; \
	else \
		echo "Using root Makefile"; \
		$(CC) $(CFLAGS) -o $(OUT_DIR)/$$dirname $$selected/*.c; \
	fi; \
	chmod +x $(OUT_DIR)/$$dirname; \
	./$(OUT_DIR)/$$dirname

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	rm -rf $(OUT_DIR)/*
