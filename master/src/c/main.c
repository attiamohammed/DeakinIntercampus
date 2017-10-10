#include <pebble.h>

static Window *s_main_window;
static TextLayer *s_time_layer;
static TextLayer *s_bus_layer;
static TextLayer *m_bus_layer2;
static TextLayer *m_bus_layer;
static TextLayer *s_bus_layer2;
static TextLayer *t_bus_layer;
static TextLayer *t_bus_layer2;
typedef struct {
  int hours;  // Name of this tea
  int mins;       // Minutes to steep this tea
} BusInfo;

// Array of different teas for tea timer
// {<Tea Name>, <Brew time in minutes>}
BusInfo time_waurn[] = {
  {6,45},
  {7,15},
  {7,50},
  {8,20},
  {8,55},
  {9,25},
  {10,10},
  {10,40},
  {11,15},
  {11,45},
  {12,20},
  {12,50},
  {13,25},
  {13,55},
  {14,40},
  {15,10},
  {15,45},
  {16,15},
  {16,50},
  {17,20},
  {17,55},
  {18,25},
  {19,10},
  {19,40}
};
BusInfo time_wfront[] = {
{7,25},
{7,55},
{8,30},
{9,00},
{9,45},
{10,15},
{10,50},
{11,20},
{11,55},
{12,25},
{13,00},
{13,30},
{14,15},
{14,45},
{15,20},
{15,50},
{16,25},
{16,55},
{17,30},
{18,00},
{18,45},
{19,15},
{19,50},
{20,20}
};
static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  // Write the current hours and minutes into a buffer
  static char s_buffer[10];
  strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ?
                                          "%H:%M" : "%I:%M %P", tick_time);

  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, s_buffer);
  
  int time_diff=0,i=0;
  do{
    time_diff=(time_waurn[i].hours-tick_time->tm_hour)*60+(time_waurn[i].mins-tick_time->tm_min);
  i++;
  }
  while (time_diff<0 &&i<25);
  //bus_time.tm_min=clock_is_24h_style();
  struct tm bus_time;
  bus_time.tm_min=time_diff%60;
  bus_time.tm_hour=time_diff/60;
 static char s_buffer_bus[8];
  strftime(s_buffer_bus, sizeof(s_buffer), "%H:%M", &bus_time);

  text_layer_set_text(s_bus_layer, s_buffer_bus);
  i=0;
    do{
    time_diff=(time_wfront[i].hours-tick_time->tm_hour)*60+(time_wfront[i].mins-tick_time->tm_min);
  i++;
  }
  while (time_diff<0&&i<25);
  struct tm bus_time2;
  bus_time2.tm_min=time_diff%60;
  bus_time2.tm_hour=time_diff/60;
 static char s_buffer_bus2[8];
  strftime(s_buffer_bus2, sizeof(s_buffer), "%H:%M", &bus_time2);
  text_layer_set_text(s_bus_layer2, s_buffer_bus2);
  
}


static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

static void main_window_load(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Create the TextLayer with specific bounds
  s_time_layer = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(17, 15), bounds.size.w, 50));

  // Improve the layout to be more like a watchface
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_text(s_time_layer, "00:00");
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
  
  // Add next bus layer
  s_bus_layer = text_layer_create(
      GRect(15, PBL_IF_ROUND_ELSE(70, 70), bounds.size.w, 50));
  s_bus_layer2 = text_layer_create(
      GRect(15, PBL_IF_ROUND_ELSE(110, 110), bounds.size.w, 50));
  m_bus_layer = text_layer_create(
      GRect(80, PBL_IF_ROUND_ELSE(70, 70), bounds.size.w, 50));
  m_bus_layer2 = text_layer_create(
      GRect(80, PBL_IF_ROUND_ELSE(110, 110), bounds.size.w, 50));
  t_bus_layer = text_layer_create(
      GRect(10, PBL_IF_ROUND_ELSE(50, 50), bounds.size.w, 50));
  t_bus_layer2 = text_layer_create(
      GRect(10, PBL_IF_ROUND_ELSE(90, 90), bounds.size.w, 50));

  // Improve the layout to be more like a watchface
  text_layer_set_background_color(s_bus_layer, GColorClear);
  text_layer_set_text_color(s_bus_layer, GColorBlack);
  text_layer_set_text(s_bus_layer, "00:00");
  text_layer_set_font(s_bus_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(s_bus_layer, GTextAlignmentLeft);
  //
  layer_add_child(window_layer, text_layer_get_layer(s_bus_layer));
   // Add next bus layer
  

  // Improve the layout to be more like a watchface
  text_layer_set_background_color(s_bus_layer2, GColorClear);
  text_layer_set_text_color(s_bus_layer2, GColorBlack);
  text_layer_set_text(s_bus_layer2, "00:00");
  text_layer_set_font(s_bus_layer2, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(s_bus_layer2, GTextAlignmentLeft);
  //
  layer_add_child(window_layer, text_layer_get_layer(s_bus_layer2));
  
  

  // Improve the layout to be more like a watchface
  text_layer_set_background_color(t_bus_layer, GColorClear);
  text_layer_set_text_color(t_bus_layer, GColorBlack);
  text_layer_set_text(t_bus_layer, "To Water front in:");
  text_layer_set_font(t_bus_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(t_bus_layer, GTextAlignmentLeft);
  //
  layer_add_child(window_layer, text_layer_get_layer(t_bus_layer));
   // Add next bus layer
  

  // Improve the layout to be more like a watchface
  text_layer_set_background_color(t_bus_layer2, GColorClear);
  text_layer_set_text_color(t_bus_layer2, GColorBlack);
  text_layer_set_text(t_bus_layer2, "To Waurn Ponds in:");
  text_layer_set_font(t_bus_layer2, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(t_bus_layer2, GTextAlignmentLeft);
  //
  layer_add_child(window_layer, text_layer_get_layer(t_bus_layer2));
   // Improve the layout to be more like a watchface
  text_layer_set_background_color(m_bus_layer, GColorClear);
  text_layer_set_text_color(m_bus_layer, GColorBlack);
  text_layer_set_text(m_bus_layer, "mins");
  text_layer_set_font(m_bus_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(m_bus_layer, GTextAlignmentLeft);
  //
  layer_add_child(window_layer, text_layer_get_layer(m_bus_layer));
   // Add next bus layer
  

  // Improve the layout to be more like a watchface
  text_layer_set_background_color(m_bus_layer2, GColorClear);
  text_layer_set_text_color(m_bus_layer2, GColorBlack);
  text_layer_set_text(m_bus_layer2, "mins");
  text_layer_set_font(m_bus_layer2, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(m_bus_layer2, GTextAlignmentLeft);
  //
  layer_add_child(window_layer, text_layer_get_layer(m_bus_layer2));

}

static void main_window_unload(Window *window) {
  // Destroy TextLayer
  text_layer_destroy(s_time_layer);
    text_layer_destroy(s_bus_layer);
  text_layer_destroy(s_bus_layer2);

}


static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);

  // Make sure the time is displayed from the start
  update_time();

  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}