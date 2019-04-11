#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {

  int val;
  struct semid_ds *buf;
  unsigned short *array;

};

int semCreate(key_t, int, int);       /*function to create st of semaphores*/

int semDelete(int);                     /*function to delete set of semaphores*/

int semGet(int,int);                    /*function to get the value of semaphore*/

int semSet(int,int,int);                  /*function to change the value of a semaphore*/

int sem_P(int, int);                /*function to reduce a semaphore's value*/

int sem_V(int, int);                /*function to .... a semaphore's value*/
