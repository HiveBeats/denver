SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
# or . if you want it in the current directory

EXE := $(BIN_DIR)/denver
SRC := $(shell find src/ ! -name "test_processor.c" -name "*.c")
TEST_SRC := $(shell find src/ ! -name "main.c" -name "*.c")

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_OBJ := $(TEST_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS := -MMD -MP -I/usr/local/include -L/usr/local/lib -I./include # -I is a preprocessor flag, not a compiler flag
CFLAGS   := -Wall              # some warnings about bad code
LDFLAGS  := #-Llib              # -L is a linker flag
LDLIBS   := #-lm                # Left empty if no libs are needed

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) ./$^ $(LDLIBS) -o ./$@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)

