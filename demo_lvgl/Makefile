TARGET   = lvgl_demo
CROSS    = aarch64-linux-gnu
CC       = $(CROSS)-gcc-11
AS       = $(CROSS)-as-11
LD       = $(CROSS)-ld-11
LIB_DIR  = -Lliblvgl 
LIBS     = -llvgl -lm
LVGL_DIR = ../littlevgl-8
CFLAGS   = -I$(LVGL_DIR)/lvgl -I$(LVGL_DIR)/lv_drivers -I$(LVGL_DIR)/ -Iui/ -I.
SRCS    :=   evdev.c  ui.c  ui_helpers.c ui_Screen1.c mouse_cursor_icon.c ui_img_tux_png.c ui_img_tux2_png.c ui_events.c  fbdev.c  main.c 
OBJECTS := $(SRCS:.c=.o)

VPATH = ./ui:./ui/screens/:./fb_files/:./ui/images

all: $(TARGET)

lvgl_demo: $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@  ${LIB_DIR}  ${LIBS}  

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
%.o: %.S
	$(AS) $(AFLAGS) -c $< -o $@
clean:
	rm -rf  $(OBJECTS) *.elf *.bin .*~ *~ *.map *.d *.hex *.lst $(TARGET)
.PHONY: clean


