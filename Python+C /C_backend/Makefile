CC=gcc
SRCS= src/utils.c src/linalg.c src/ops_explicit.c src/ista_core.c
TARGET= libista.so

# Default modes and flags
# This functionality is provided for analysing the backend
# Debug: easiest to debug (-O0, -g)
# Dev: fast compile, decent optimizations (-O2, -g)
# Release: max optimizations (-O3), may use -march=native for best speed (not portable)
BUILD_DEBUG = -O0 -g -fno-omit-frame-pointer
BUILD_DEV   = -O2 -g
BUILD_RELEASE = -O3 -march=native

PIC_FLAG= -fPIC
INCLUDE = -Iinclude
LDFLAGS= -shared
LIBS= -lm

# Mode may be passed via "make MODE=dev" or interactive menu will ask 
MODE ?=


# Resolve CFLAGS based on MODE
ifeq ($(MODE),debug)
    CFLAGS = $(BUILD_DEBUG) $(PIC_FLAG) $(INCLUDE)
    OUT = libista_debug.so
else ifeq ($(MODE),dev)
    CFLAGS = $(BUILD_DEV) $(PIC_FLAG) $(INCLUDE)
    OUT = libista_dev.so
else ifeq ($(MODE),release)
    CFLAGS = $(BUILD_RELEASE) $(PIC_FLAG) $(INCLUDE)
    OUT = $(TARGET)
else
    # MODE not set or unrecognized -> default target will run the menu
    CFLAGS =
    OUT =
endif

.PHONY: all menu debug dev release clean help

# default: if MODE specified, build accordingly; otherwise show menu
all:
	@if [ -n "$(MODE)" ]; then \
	  echo "Building mode: $(MODE)"; \
	  echo "  CC: $(CC)"; \
	  echo "  CFLAGS: $(CFLAGS)"; \
	  echo "  Output: $(OUT)"; \
	  $(CC) $(CFLAGS) $(LDFLAGS) -o $(OUT) $(SRCS) $(LIBS); \
	  echo "Built $(OUT)"; \
	else \
	  echo "Select build mode:"; \
	  echo "  1) debug   : -O0 -g (best for debugging)"; \
	  echo "  2) dev     : -O2 -g (fast compile, good testing)"; \
	  echo "  3) release : -O3 -march=native (max perf, not portable)"; \
	  echo "  q) quit"; \
	  printf "Enter choice [1/2/3/q]: "; \
	  read CHOICE; \
	  case "$$CHOICE" in \
	    1) MODE=debug ;; \
	    2) MODE=dev ;; \
	    3) MODE=release ;; \
	    q) echo "Aborting."; exit 0 ;; \
	    *) echo "Invalid choice"; exit 1 ;; \
	  esac; \
	  if [ "$$MODE" = "debug" ]; then CFLAGS_S="$(BUILD_DEBUG) $(PIC_FLAG) $(INCLUDE)"; OUT_S="libista_debug.so"; fi; \
	  if [ "$$MODE" = "dev" ]; then CFLAGS_S="$(BUILD_DEV) $(PIC_FLAG) $(INCLUDE)"; OUT_S="libista_dev.so"; fi; \
	  if [ "$$MODE" = "release" ]; then CFLAGS_S="$(BUILD_RELEASE) $(PIC_FLAG) $(INCLUDE)"; OUT_S="$(TARGET)"; fi; \
	  echo "You chose $$MODE"; \
	  echo "  CC: $(CC)"; echo "  CFLAGS: $$CFLAGS_S"; echo "  Output: $$OUT_S"; \
	  $(CC) $$CFLAGS_S $(LDFLAGS) -o $$OUT_S $(SRCS) $(LIBS); \
	  echo "Built $$OUT_S"; \
	fi

# Non-interactive convenience targets (no recursion)
debug:
	@echo "Building debug..."
	@echo "  CC: $(CC)"
	@echo "  CFLAGS: $(BUILD_DEBUG) $(PIC_FLAG) $(INCLUDE)"
	@$(CC) $(BUILD_DEBUG) $(PIC_FLAG) $(INCLUDE) $(LDFLAGS) -o libista_debug.so $(SRCS) $(LIBS)
	@echo "Built libista_debug.so"

dev:
	@echo "Building dev..."
	@echo "  CC: $(CC)"
	@echo "  CFLAGS: $(BUILD_DEV) $(PIC_FLAG) $(INCLUDE)"
	@$(CC) $(BUILD_DEV) $(PIC_FLAG) $(INCLUDE) $(LDFLAGS) -o libista_dev.so $(SRCS) $(LIBS)
	@echo "Built libista_dev.so"

release:
	@echo "Building release..."
	@echo "  CC: $(CC)"
	@echo "  CFLAGS: $(BUILD_RELEASE) $(PIC_FLAG) $(INCLUDE)"
	@$(CC) $(BUILD_RELEASE) $(PIC_FLAG) $(INCLUDE) $(LDFLAGS) -o $(TARGET) $(SRCS) $(LIBS)
	@echo "Built $(TARGET)"

clean:
	@rm -f libista_debug.so libista_dev.so $(TARGET) *.o
	@echo "cleaned"

help:
	@echo "Usage:"
	@echo "  make           -> interactive menu (select a build mode)"
	@echo "  make MODE=dev  -> non-interactive, builds dev (or MODE=debug/release)"
	@echo "  make dev       -> builds dev (convenience target)"
	@echo ""
	@echo "Notes:"
	@echo "  - release uses -march=native (best speed on current CPU; not portable)."
	@echo "  - For CI / reproducible builds, avoid -march=native and use a fixed architecture flag."
