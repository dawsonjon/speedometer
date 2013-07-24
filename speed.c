#include <stdio.h>
#include "speed.h"

double get_speed_kph(){
  double speed;

  /* Wait for Recomended Minimum Content*/
  while(1){
    if(getchar() != '$') continue;
    if(getchar() != 'G') continue;
    if(getchar() != 'P') continue;
    if(getchar() != 'R') continue;
    if(getchar() != 'M') continue;
    if(getchar() != 'C') continue;
    break;
  }

  /* Extract the speed, but ignore the rest */
  while(getchar() != ',');
  while(getchar() != ',');//time,
  while(getchar() != ',');//A,
  while(getchar() != ',');//latidude,
  while(getchar() != ',');//N/S,
  while(getchar() != ',');//longitude,
  while(getchar() != ',');//E/W,
  scanf("%f", &speed);
  printf("gps speed knots: %f\r\n", speed);

  return speed;
}
