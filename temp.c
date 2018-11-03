#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include "ifttt.h"

#define SIZE 1
#define NUMELEM 74

int main(int argc, char *argv[]) 
{
  float min = 100, max = 0, cur, prev;
  int count = 0;
  FILE *fp;
  char cur_S[50];
  char min_S[50];
  char max_S[50];
  char id[20];
  char buff[100];
  char temp_raw[5];
  char name[100] = "/sys/devices/w1_bus_master1/";
  memset(buff,0,sizeof(buff));

  printf("Enter the id of the scanner: ");
  scanf("%s", id);
  strcat(name, id);
  strcat(name, "/w1_slave");  

  for(;;)
  {
    fp = fopen(name, "r");
 
    if (fp == NULL)
    {
      printf("\n Error! File is empty\n\n");
      return 1;
    }

    if(SIZE*NUMELEM != fread(buff,SIZE,NUMELEM,fp))
    {
      printf("\n fread() failed\n");
      return 1;
    }
  
    temp_raw[0] = buff[69];
    temp_raw[1] = buff[70];
    temp_raw[2] = buff[71];
    temp_raw[3] = buff[72];
    temp_raw[4] = buff[73];
    temp_raw[5] = buff[74];

    /* Determine current, max, min int */
    sscanf(temp_raw, "%f", &cur);
    cur = cur / 1000;
    if(cur < min)
      min = cur;
    if(cur > max)
      max = cur;
  
    snprintf(cur_S, 50, "%f", cur);
    snprintf(max_S, 50, "%f", max);
    snprintf(min_S, 50, "%f", min);
  
    printf("Current Temp: %.3f\n", cur);
    printf("Max Temp: %.3f\n", max);
    printf("Min Temp: %.3f\n", min);
    
    /* Handles IFTTT */
    if(count == 0) 
    {
      printf("\nSERVER CONTACTED\n");
      ifttt("https://maker.ifttt.com/trigger/temperature_changed/with/key/mZZA4uLIfY-Bj2Xc-VoBu0AtVIzTle82sjLHYNs9nA_", cur_S, cur_S, cur_S);
      prev = cur;
      count++;
    }

    if((prev-cur > 1) || (cur - prev > 1)) 
    {
      printf("\nSERVER CONTACTED\n");
      ifttt("https://maker.ifttt.com/trigger/temperature_changed/with/key/mZZA4uLIfY-Bj2Xc-VoBu0AtVIzTle82sjLHYNs9nA_", cur_S, max_S, min_S);      
    }

    prev = cur;
    
    sleep(5);
  }
  return 0;
}
