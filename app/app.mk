
CC      := gcc
SRC_FMT := c
CFLAGS  := -I../../include 
CFLAGS  += -g        # for debugging
CFLAGS  += -O0       # optimization for debugging
CFLAGS	+= -Wall -Wextra
LDFLAGS := -lcrypt
LDFLAGS += -lbsd
LDFLAGS += -lm

BIN_DIR := ../../bin

SRC_DIRS := ../../src
SRC_DIRS += .

SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.$(SRC_FMT)))
OBJS := $(patsubst %.$(SRC_FMT),$(BIN_DIR)/%.o,$(SRCS))
DEPS := $(patsubst %.$(SRC_FMT),$(BIN_DIR)/%.d,$(SRCS))

all: $(BIN_DIR)/$(APP)

$(BIN_DIR)/$(APP): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BIN_DIR)/%.o: %.$(SRC_FMT)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -MMD -MP -MF $(patsubst %.o,%.d,$@) -MT $@ -c $< -o $@

-include $(DEPS)

clean:
	@rm -rf bin $(APP)