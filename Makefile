PROGRAM = gnuciv
CC = gcc -g
OBJCOPY = objcopy
CFLAGS = `pkg-config --cflags sdl3 sdl3-image sdl3-ttf`
LDFLAGS = `pkg-config --libs sdl3 sdl3-image sdl3-ttf`
OBJS = main.o game.o
OBJS += bwt/app.o bwt/event.o
OBJS += bwt/layer.o bwt/layer_list.o bwt/grid.o bwt/bg.o
OBJS += bwt/widget.o bwt/widget_box.o bwt/position.o

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
