#include <stdio.h>
#include "gps.h"

double speed;
int hour, utc_hour , minute, second;
int day, utc_day, month, utc_month, year;
char good;

/*These functions return the date, time and GPS status*/

int get_year(){return year;}
int get_month(){return month;}
int get_day(){return day;}
int get_hour(){return hour;}
int get_minute(){return minute;}
int get_second(){return second;}
int get_gps_good(){return good;}


/*
 * This function calculates the day of the week.
 *
 */

int day_of_week(int y, int m, int d)
{
       static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
       y -= m < 3;
       return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

/*
 * This function determines whether we are in BST or GMT
 * based on the time of year.
 *
 */

int is_bst(){
  int i, last_sunday_in_october, last_sunday_in_march;

  /*Find last Sunday of March*/
  for(i=31; i>=1; i--){
    if(day_of_week(year + 2000, 3, i) == 0) break;
  }
  last_sunday_in_march = i;

  /*Find last Sunday of October*/
  for(i=31; i>=1; i--){
    if(day_of_week(year + 2000, 10, i) == 0) break;
  }
  last_sunday_in_october = i;

  /*If before 1:00 GMT on last Sunday in March return false*/
  if(month < 3) return 0;
  if(month == 3) {
    if(utc_day < last_sunday_in_march) return 0;
    if(utc_day == last_sunday_in_march && utc_hour < 1) return 0;
  }

  /*If after 1:00 GMT on last Sunday in October return false*/
  if(month > 10) return 0;
  if(month == 10) {
    if(utc_day > last_sunday_in_october) return 0;
    if(utc_day == last_sunday_in_october && utc_hour >= 1) return 0;
  }
  return 1;

}

/* 
*
* this function decides whether to adjust the day and hour
* for daylight saving time.
*
*/

void adjust_daylight_saving()
{

  /*No need to adjust for leap years, because it will never be BST in Feb.*/
  int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  /*Add an hour to get BST, skip to the next day if it is close to midnight*/
  if(is_bst()){
    if(utc_hour == 23)
    {
      hour = 0;
      if(utc_day == days_in_month[month-1])
      {
        day = 1;
	month = utc_month + 1;
      }
      else
      {
        day = utc_day + 1;
	month = utc_month;
      }
    }
    else
    {
      hour = utc_hour + 1;
      day = utc_day;
      month = utc_month;
    }
  }
  else
  {
    hour = utc_hour;
    day = utc_day;
    month = utc_month;
  }
}

/* 
* This function reads thwe data from the gps module
* and extracts the information that we need.
* After this function has been called, the day and date
* functions may also be called.
*
*/

double get_speed_knots(){


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

  /* Extract the speed, date and time */
  while(getchar() != ',');
  scanf("%2u%2u%2u", &utc_hour, &minute, &second);
  while(getchar() != ',');//time,
  scanf("%c", &good);
  while(getchar() != ',');//A,
  while(getchar() != ',');//latidude,
  while(getchar() != ',');//N/S,
  while(getchar() != ',');//longitude,
  while(getchar() != ',');//E/W,
  scanf("%f", &speed);
  while(getchar() != ',');//speed in knots,
  while(getchar() != ',');//course made good,
  scanf("%2u%2u%2u", &utc_day, &utc_month, &year);
  while(getchar() != ',');//date,

  /*send to UART for debug*/
  printf("GPS speed knots: %f\r\n", speed);
  printf("date (utc): %2u-%2u-%2u\r\n", utc_day, utc_month, year);
  printf("time (utc): %2u:%2u:%2u\r\n", utc_hour, minute, second);

  /*adjust for daylight saving*/
  adjust_daylight_saving();
  printf("date (local): %2u-%2u-%2u\r\n", day, month, year);
  printf("time (local): %2u:%2u:%2u\r\n", hour, minute, second);

  return speed;
}
