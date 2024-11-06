APP := fics-server

CC      := gcc
SRC_FMT := c
CFLAGS  := -Iinclude 
CFLAGS  += -g        # for debugging
CFLAGS  += -O0       # optimization for debugging
CFLAGS	+= -Wall -Wextra
LDFLAGS := -lm
# for linux
LDFLAGS += -lcrypt
LDFLAGS += -lbsd
# for dsb comment tow above lines

BIN_DIR := bin

SRC_DIRS := src

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

install: bin/$(APP)
	@install -m 755 bin/$(APP) /usr/local/bin

clean:
	@rm -rf bin $(APP)
