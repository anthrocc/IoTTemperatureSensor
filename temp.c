#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ifttt.h"

int main(int argc, char *argv[]) 
{
  int c, i = 0;
  char id[20];
  char name[100] = "/sys/devices/w1_bus_master1/";
  char holder[256];
  FILE *file;

  printf("Enter the id of the scanner: ");
  scanf("%s", id);
  strcat(name, id);
  strcat(name, "/w1_slave"); 
  
  file = fopen(name, "r");
  
  while(fgets(holder, sizeof(holder), file))
  {
    i++;
    if(i == 2)
    {   
      strtok(holder, "t=");
      printf("%s\n", holder);
    }
  }






  /*
  char holder[1000];
  FILE *fptr;

  if((fptr = fopen("text.txt", "r")) == NULL)
  {
    printf("ERROR! File not found!");
    exit(1);
  }
  
  /* Read text until newline
  fscanf(fptr,"%[^/n]", holder);
  
  printf("Data from the file:%s\n", holder);
  fclose(fptr);
  */
    
  return 0;
}
