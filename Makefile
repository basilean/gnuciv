PROGRAM = gnuciv
CC = gcc
OBJCOPY = objcopy
CFLAGS = `pkg-config --cflags sdl3 sdl3-image`
LDFLAGS = `pkg-config --libs sdl3 sdl3-image`
OBJS = main.o app.o event.o game.o
OBJS += layer/layer.o layer/layer_list.o layer/grid.o layer/bg.o
OBJS += layer/widget.o layer/widget_box.o

ifneq ($(V),1)
Q := @
endif

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	@printf " LD $(subst $(shell pwd)/,,$(@))\n"
	$(Q)$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@printf " CC $(subst $(shell pwd)/,,$(@))\n"
	$(Q)$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@printf " CLEAN $(subst $(shell pwd)/,,$(OBJS))\n"
	$(Q)rm -f $(OBJS)
	@printf " CLEAN $(PROGRAM)\n"
	$(Q)rm $(PROGRAM)
