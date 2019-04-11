#include "functions.h"



void Manufacture(int n, int type, int mutex, int empty, int full, shMem_Seg *ShMem_PTR, struct timespec tStart){      /*function to create the parts*/

  int j;
  for(j=0; j<n; j++){                                                                                               /*we need to make n items of each type*/

      sem_P(empty,0);                                                                                                 /*based on the bounded buffer logic*/
      sem_P(mutex,0);

      srand(time(NULL)^(type+rand()));                                                                               /*rand which will generate different IDs*/
      int num = (rand() % (9999 - 1000 + 1)) + 1000;                                                                  /*writting to the first shared memory segment*/
      ShMem_PTR->var= type;
      sprintf(ShMem_PTR->id, "%d", num);
      clock_gettime(CLOCK_MONOTONIC, &tStart);                                                                        /*get the clock starting*/
      ShMem_PTR->tm = tStart;
      printf("|| {}{}{}{}{}    PART with || ID:%s || of type %d CREATED!    {}{}{}{}{} ||\n",ShMem_PTR->id, ShMem_PTR->var);

      sem_V(mutex,0);                                                                                                     /*up semaphoters so the next process can access the shared memory */
      sem_V(full,0);
      }
}


void PaintShop(int n, int mutex, int mutex_1, int mutex_2, int mutex_3, int empty, int empty_1, int empty_2, int empty_3, int full, int full_1, int full_2, int full_3, shMem_Seg *ShMem_PTR, shMem_Seg *ShMem_PTR1_1, shMem_Seg *ShMem_PTR1_2, shMem_Seg *ShMem_PTR1_3, struct timespec tStart, struct timespec tPaint){

  long double seconds=0,ns=0;
  int j;
  for(j=0; j<3*n; j++){                                                                                       /*until all parts are painted*/
         sem_P(full,0);                                                                                          /*block other processes from accessing that part*/
         sem_P(mutex,0);

         clock_gettime(CLOCK_MONOTONIC, &tPaint);                                                                              /*get the time the process made it to the paint shop*/
         usleep(1000*ShMem_PTR->var);                                                                                          /*the time it takes for the paintShop to paint part of certain type*/
         printf("|| <><><><><>    PART with || ID:%s || of type %d PAINTED!    <><><><><> ||\n", ShMem_PTR->id, ShMem_PTR->var);

          if(ShMem_PTR->var==1){
            sem_P(empty_1,0);                                                                                   /*make part accessible to Inspector of type 1*/
            sem_P(mutex_1,0);
            ShMem_PTR1_1->var=ShMem_PTR->var;
            ShMem_PTR1_1->tm=ShMem_PTR->tm;
            strcpy(ShMem_PTR1_1->id, ShMem_PTR->id);
            seconds=tPaint.tv_sec-(ShMem_PTR->tm).tv_sec;                                                             /*calculate the time it took to reach the paint shop since that part was created*/
            ns=tPaint.tv_nsec-(ShMem_PTR->tm).tv_nsec;
            if ((ShMem_PTR->tm).tv_nsec > tPaint.tv_nsec) { // clock underflow
                 --seconds;
                  ns += 1000000000;
                }
            ShMem_PTR1_1->ht = seconds+ns/1000000000;
            sem_V(mutex_1,0);
            sem_V(full_1,0);
            }
          else if(ShMem_PTR->var==2){
            sem_P(empty_2,0);                                                                                  /*make part accessible to Inspector of type 2*/
            sem_P(mutex_2,0);
            ShMem_PTR1_2->var=ShMem_PTR->var;
            ShMem_PTR1_2->tm=ShMem_PTR->tm;
            strcpy(ShMem_PTR1_2->id, ShMem_PTR->id);
            seconds=tPaint.tv_sec-(ShMem_PTR->tm).tv_sec;                                                        /*calculate the time it took to reach the paint shop since that part was created*/
            ns=tPaint.tv_nsec-(ShMem_PTR->tm).tv_nsec;
            if ((ShMem_PTR->tm).tv_nsec > tPaint.tv_nsec) { // clock underflow
                 --seconds;
                  ns += 1000000000;
                }
            ShMem_PTR1_2->ht = seconds+ns/1000000000;
            sem_V(mutex_2,0);
            sem_V(full_2,0);
          }
          else if(ShMem_PTR->var==3){
            sem_P(empty_3,0);                                                                                        /*"make part accessible to Inspector of type 3*/
            sem_P(mutex_3,0);
            ShMem_PTR1_3->var=ShMem_PTR->var;
            ShMem_PTR1_3->tm=ShMem_PTR->tm;
            strcpy(ShMem_PTR1_3->id, ShMem_PTR->id);
             seconds=tPaint.tv_sec-(ShMem_PTR->tm).tv_sec;                                                    /*calculate the time it took to reach the paint shop since that part was created*/
             ns=tPaint.tv_nsec-(ShMem_PTR->tm).tv_nsec;
            if ((ShMem_PTR->tm).tv_nsec > tPaint.tv_nsec) { // clock underflow
                 --seconds;
                  ns += 1000000000;
                }
            ShMem_PTR1_3->ht = seconds+ns/1000000000;
            sem_V(mutex_3,0);
            sem_V(full_3,0);
            }

            sem_V(mutex,0);                                                                                     /*up the semaphores about the paintShop- Manufacturers interaction*/
            sem_V(empty,0);
          }
}

void Inspect( int n, int type,int otherMutex, int mutexAssembler, int emptyAssembler, int empty1, int fullAssembler, int full1, shMem_Seg *ShMem_PTR2, shMem_Seg *ShMem_PTR1){

    for(int j=0; j<n;j++){

      sem_P(full1,0);                                                                                      /*block other processes from readind that part while the current one is reading*/
      sem_P(otherMutex,0);
      usleep(1500*(type));                                                                                                    /*the time it takes for the Inspector to inspect part of certain type*/
      printf("|| ~~~~~~~~~~    PART with || ID:%s || of type %d CHECKED!    ~~~~~~~~~~ ||\n", ShMem_PTR1->id, ShMem_PTR1->var);
      sem_V(otherMutex,0);

        sem_P(emptyAssembler,0);                                                            /*semaphores and critical section about the Inspectors-Assembler interaction*/
        sem_P(mutexAssembler,0);

        ShMem_PTR2->var=ShMem_PTR1->var;                                                    /*copying the parts info from one shared memory to another (making the inspected part accessible to the Assebler)*/
        ShMem_PTR2->tm=ShMem_PTR1->tm;
        strcpy(ShMem_PTR2->id, ShMem_PTR1->id);
        ShMem_PTR2->ht = ShMem_PTR1->ht;

        sem_V(mutexAssembler,0);
        sem_V(fullAssembler,0);

      sem_V(empty1,0);                                                                       /*when certain procces is finished allow the next one to access the Inspector of the correct type*/
    }
}

void Assemble( int n, int mutexAssembler,int emptyAssembler, int fullAssembler, shMem_Seg *ShMem_PTR2, struct timespec tEnd){

  long double average_time =0, production_time=0, a=0, b=0, c=0, cns=0, bns=0, bseconds=0, cseconds=0, ans=0, aseconds=0;
  int count=0;

  Queue *A=ConstructQueue(n);                                                                           /*making  queues to keep parts of each type*/
  Queue *B=ConstructQueue(n);
  Queue *C=ConstructQueue(n);

  for(int y=0; y<3*n; y++){

    NODE *pN;
    pN = (NODE*) malloc(sizeof (NODE));                                                            /*create a Node to keep the part's data*/

    sem_P(fullAssembler,0);                                                                       /*bounded buffer logic*/
    sem_P(mutexAssembler,0);

    usleep(3000);                                                                                /*assemble takes standard time for every type of  part*/

    if(ShMem_PTR2->var == 1){                                                                       /*for each part enqueue it to the right queue*/
      pN->type.var = ShMem_PTR2->var;
      pN->type.ht=ShMem_PTR2->ht;
      strcpy(pN->type.id, ShMem_PTR2->id);
      pN->type.tm=ShMem_PTR2->tm;
      Enqueue(A, pN);
    }
    else if(ShMem_PTR2->var == 2){
      pN->type.var = ShMem_PTR2->var;
      pN->type.ht=ShMem_PTR2->ht;
      strcpy(pN->type.id, ShMem_PTR2->id);
      pN->type.tm=ShMem_PTR2->tm;
      Enqueue(B, pN);
    }
    else if(ShMem_PTR2->var == 3){
      pN->type.var = ShMem_PTR2->var;
      pN->type.ht=ShMem_PTR2->ht;
      strcpy(pN->type.id, ShMem_PTR2->id);
      pN->type.tm=ShMem_PTR2->tm;
      Enqueue(C, pN);
    }

    sem_V(mutexAssembler,0);
    sem_V(emptyAssembler,0);                                                                  /*Assebler ready to be used by another proccess*/

    while(isEmpty(A)==0 && isEmpty(B)==0 && isEmpty(C)==0){                                     /*while there are parts in all the queues make items and get rid of the parts*/

      NODE *aN,*bN, *cN;

      aN = Dequeue(A);
      bN = Dequeue(B);
      cN = Dequeue(C);

       clock_gettime(CLOCK_MONOTONIC, &tEnd);                                                       /*get the time the item was created*/
       aseconds=tEnd.tv_sec-(aN->type.tm).tv_sec;                                                         /*calculate the time part type 1 of the item took to be assembled i an item*/
       ans=tEnd.tv_nsec-(aN->type.tm).tv_nsec;
            if ((aN->type.tm).tv_nsec > tEnd.tv_nsec) { // clock underflow
                 --aseconds;
                  ans += 1000000000;
                }
      a = aseconds+ans/1000000000;

       bseconds=tEnd.tv_sec-(bN->type.tm).tv_sec;                                                 /*calculate the time part type 2 of the item took to be assembled i an item*/
       bns=tEnd.tv_nsec-(bN->type.tm).tv_nsec;
            if ((bN->type.tm).tv_nsec > tEnd.tv_nsec) { // clock underflow
                 --bseconds;
                  bns += 1000000000;
                }
       b = bseconds+bns/1000000000;

       cseconds = tEnd.tv_sec-(cN->type.tm).tv_sec;                                               /*calculate the time part type 3 of the item took to be assembled i an item*/
       cns=tEnd.tv_nsec-(cN->type.tm).tv_nsec;
            if ((cN->type.tm).tv_nsec > tEnd.tv_nsec) { // clock underflow
                 --cseconds;
                  cns += 1000000000;
                }
       c = cseconds+cns/1000000000;

      average_time += aN->type.ht + bN->type.ht + cN->type.ht;                                        /*adding the times of all parts from constructure until they wrer painted*/
      if(a > b && a > c){                                                                                   /*find the part that took longer to be assembled on a final product and add to production_time*/
        production_time += a;
      }
      else if(b > a && b > c ){
        production_time += b;
      }else if(c > b && c > a){
        production_time += c;
      }
      count++;
      printf("\n\n\n***------   ------- ITEM NO:%d with || ID:%s%s%s || ASSEMBLED ------ ------***\n\n\n", count, aN->type.id, bN->type.id, cN->type.id);

      free(aN);                                                                                 /*deallocate memory*/
      free(bN);
      free(cN);
    }
  }
  printf("\n*******************************************************************************\n*The average time from the manufacturer to the paint shop is %Lf seconds.*\n",  (average_time/(3*n)) );
  printf("*                 Average production time %Lf seconds.                   *\n*******************************************************************************\n", (production_time/n));

  DestructQueue(A);                                                                         /*deallocate memory*/
  DestructQueue(B);
  DestructQueue(C);

}
