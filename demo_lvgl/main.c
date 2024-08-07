
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#define _DEFAULT_SOURCE /* needed for usleep() */
#include <unistd.h>
#define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" issue*/
//#include <SDL2/SDL.h>
//#include "lvgl/lvgl.h"
#include "lvgl.h"
//#include "lv_drivers/sdl/sdl.h"
#include "fb_files/fbdev.h"
#include "fb_files/evdev.h"
#include "ui/ui.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define DISP_BUF_SIZE (128 * 2048)
static void hal_init(void);

uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}

int main(int argc, char **argv)
{
  (void)argc; /*Unused*/
  (void)argv; /*Unused*/

  /*Initialize LVGL*/
  lv_init();
  /*Initialize the HAL (display, input devices, tick) for LVGL*/
  hal_init();
  //lv_example_checkbox_1();
  ui_init(); 
  while(1) {
      /* Periodically call the lv_task handler.
       * It could be done in a timer interrupt or an OS task too.*/ 
        lv_timer_handler();
        usleep(5000);

  }
  return 0;
}


/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Initialize the Hardware Abstraction Layer (HAL) for LVGL
 */
static void hal_init(void)
{
	/*LVGL init*/
  lv_init();
  /*Linux frame buffer device init*/
  fbdev_init();
  /*A small buffer for LittlevGL to draw the screen's content*/
  static lv_color_t buf[DISP_BUF_SIZE];

  /*Initialize a descriptor for the buffer*/
  static lv_disp_draw_buf_t disp_buf;
  lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);
  /*Initialize and register a display driver*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.draw_buf   = &disp_buf;
  disp_drv.flush_cb   = fbdev_flush;
  disp_drv.hor_res    = 320;
  disp_drv.ver_res    = 240;
  lv_disp_drv_register(&disp_drv);
  evdev_init();
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);                 /*Basic initialization*/
  indev_drv.type = LV_INDEV_TYPE_POINTER;        
  indev_drv.read_cb = evdev_read;                
  // WARNING must be mouse_indev
  //lv_indev_drv_register(&indev_drv);
  lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv);
 
 
    /*Set a cursor for the mouse*/
    LV_IMG_DECLARE(mouse_cursor_icon);
    lv_obj_t * cursor_obj = lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
    lv_img_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
    lv_indev_set_cursor(mouse_indev, cursor_obj);             /*Connect the image  object to the driver*/

 
}



