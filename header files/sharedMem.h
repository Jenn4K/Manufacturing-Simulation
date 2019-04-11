#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>


typedef struct shMem{

  int var;                              /*type of part*/
  char id[5];                           /*ID of part*/
  struct timespec tm;                    /*creation time*/
  long double ht;                        /*time until it gets in the PaintShop*/

}shMem_Seg;


int shMemCreate(key_t);     /*function to create shared memory*/

int shMemDelete(int);       /*function to delete shared memory*/


shMem_Seg* shMemAttach(int);        /*function to get a pointer to the segment*/

int shMemDetach(shMem_Seg *);    /*function to detach shared memory*/
