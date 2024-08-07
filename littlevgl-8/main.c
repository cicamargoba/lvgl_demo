#include "lvgl.h"
#include "fbdev.h"
#include "src/extra/widgets/chart/lv_chart.h"
#include <unistd.h>
#define DISP_BUF_SIZE (128 * 1024)
static void add_data(lv_timer_t * t)
{
    lv_obj_t * chart = t->user_data;
    lv_chart_series_t * ser = lv_chart_get_series_next(chart, NULL);
    lv_chart_set_next_value(chart, ser, lv_rand(10, 90));
    uint16_t p = lv_chart_get_point_count(chart);
    uint16_t s = lv_chart_get_x_start_point(chart, ser);
    lv_coord_t * a = lv_chart_get_y_array(chart, ser);

    a[(s + 1) % p] = LV_CHART_POINT_NONE;
    a[(s + 2) % p] = LV_CHART_POINT_NONE;
    a[(s + 2) % p] = LV_CHART_POINT_NONE;
   lv_chart_refresh(chart);
}



int main(void)
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

  lv_example_chart_8(); 
    /*Create a "Hello world!" label*/
   lv_obj_t * label = lv_label_create(lv_scr_act());
   lv_label_set_text(label, "Hello world!");
   lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

  /*Handle LitlevGL tasks (tickless mode)*/
   while(1) {
										      lv_timer_handler();
										      usleep(5000);
										    }

    return 0;
}
