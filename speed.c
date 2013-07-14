#include <stdio.h>
#include "speed.h"

double get_speed_kph(){
  double speed;

  /* Wait for a course and speed accross ground message */
  while(1){
    if(getchar() != '$') break;
    if(getchar() != 'G') break;
    if(getchar() != 'P') break;
    if(getchar() != 'V') break;
    if(getchar() != 'T') break;
    if(getchar() != 'G') break;
  }

  /* Extract the speed, but ignore the rest */
  while(getchar() != ',');
  while(getchar() != ',');//Direction,
  while(getchar() != ',');//T,
  while(getchar() != ',');//Direction,
  while(getchar() != ',');//M,
  while(getchar() != ',');//Speed(knots),
  while(getchar() != ',');//N,
  scanf("%f", &speed);
  printf("gps speed kph: %f\r\n", speed);

  return speed;
}
