#ifndef GPS_H
#define GPS_H

#include <stdint.h>

double get_speed_knots(void);
int is_bst();
int get_year();
int get_month();
int get_day();
int get_hour();
int get_minute();
int get_second();
int get_gps_good();

#endif
