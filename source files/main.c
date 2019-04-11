#include <sys/wait.h>
#include "functions.h"

int main(int argc, char* argv[]){

  int n;                                                                          /*number of products we want to make*/

  if( argc != 2){                                                               /*get argument from command line*/
        printf("Invalid number of arguments.\n");
        exit(0);
    }
    else{
        n = atoi(argv[1]);
      }

  struct timespec tStart={0,0} , tPaint={0,0}, tEnd={0,0} ;

  pid_t pid, pid1, pid2, pid3;
  key_t key, key1_1, key1_2, key1_3, key2;

  int empty, mutex, full, empty_1, empty_2,empty_3, mutex_1, mutex_2, mutex_3, full_1, full_2, full_3, emptyAssembler, fullAssembler, mutexAssembler;          /*the semaphores we'll need*/
  int status;


  int ShMem_ID, ShMem_ID1_1, ShMem_ID1_2, ShMem_ID1_3, ShMem_ID2;                                                                                             /*we 'll use five shared memeory segments*/
  shMem_Seg *ShMem_PTR, *ShMem_PTR1_1, *ShMem_PTR1_2, *ShMem_PTR1_3, *ShMem_PTR2;       //pointer to the shared memory segments

////// Initializing first shared memory segment for the Manufacturers-PaintShop interaction //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if ((key = ftok("main.c", 'P')) == -1) {                //producing a random key for shared memory
        printf("*** Key wasn't prodused (ftok error) ***\n");
            exit(1);
    }

    ShMem_ID = shMemCreate(key);                                 //Creating and Attaching shared memory segment
    if (ShMem_ID < 0) {
        printf("***Shared Memory Segment could not be created (shmget error (server)) ***\n");
        exit(1);
    }

    ShMem_PTR = shMemAttach(ShMem_ID);
    if (ShMem_PTR == (shMem_Seg *)(-1)){
        printf("*** Could not attach Shared Memeory Segment (shmat error (server))***\n");
        exit(1);
    }
/////// Initializing shared memory segments for the PaintShop-Inspectors interaction ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if ((key1_1 = ftok("main.c", 'Q')) == -1) {                //producing a random key for shared memory
        printf("*** Key wasn't prodused (ftok error) ***\n");
          exit(1);
        }

    ShMem_ID1_1 = shMemCreate(key1_1);                                 //Creating and Attaching shared memory segment
    if (ShMem_ID1_1 < 0) {
        printf("***Shared Memory Segment could not be created (shmget error (server)) ***\n");
        exit(1);
    }

    ShMem_PTR1_1 = shMemAttach(ShMem_ID1_1);
    if (ShMem_PTR1_1 == (shMem_Seg *)(-1)){
        printf("*** Could not attach Shared Memeory Segment (shmat error (server))***\n");
        exit(1);
    }
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if ((key1_2 = ftok("main.c", 'S')) == -1) {                //producing a random key for shared memory
        printf("*** Key wasn't prodused (ftok error) ***\n");
          exit(1);
        }

    ShMem_ID1_2 = shMemCreate(key1_2);                                 //Creating and Attaching shared memory segment
    if (ShMem_ID1_2 < 0) {
        printf("***Shared Memory Segment could not be created (shmget error (server)) ***\n");
        exit(1);
    }

    ShMem_PTR1_2 = shMemAttach(ShMem_ID1_2);
    if (ShMem_PTR1_2 == (shMem_Seg *)(-1)){
        printf("*** Could not attach Shared Memeory Segment (shmat error (server))***\n");
        exit(1);
    }
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
if ((key1_3 = ftok("main.c", 'A')) == -1) {                //producing a random key for shared memory
    printf("*** Key wasn't prodused (ftok error) ***\n");
      exit(1);
    }

ShMem_ID1_3 = shMemCreate(key1_3);                                 //Creating and Attaching shared memory segment
if (ShMem_ID1_3 < 0) {
    printf("***Shared Memory Segment could not be created (shmget error (server)) ***\n");
    exit(1);
}

ShMem_PTR1_3 = shMemAttach(ShMem_ID1_3);
if (ShMem_PTR1_3 == (shMem_Seg *)(-1)){
    printf("*** Could not attach Shared Memeory Segment (shmat error (server))***\n");
    exit(1);
}

////// Initializing fifth shared memory segment for the Inspectors-Assebler interaction/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if ((key2 = ftok("main.c", 'M')) == -1) {                //producing a random key for shared memory
    printf("*** Key wasn't prodused (ftok error) ***\n");
      exit(1);
    }

ShMem_ID2 = shMemCreate(key2);                                 //Creating and Attaching shared memory segment
if (ShMem_ID2 < 0) {
    printf("***Shared Memory Segment could not be created (shmget error (server)) ***\n");
    exit(1);
}

ShMem_PTR2 = shMemAttach(ShMem_ID2);
if (ShMem_PTR2 == (shMem_Seg *)(-1)){
    printf("*** Could not attach Shared Memeory Segment (shmat error (server))***\n");
    exit(1);
}
////// Initializng the binary semaphores for the Manufacturers-paintShop processes's iteractions //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    empty = semCreate((key_t)3246,1,1);
        if (empty < 0){
            printf("***Semaphore error***\n");
            exit(0);
    }

    mutex = semCreate((key_t)2345,1,1);
        if (mutex < 0){
            printf("***Semaphore error***\n");
            exit(0);
    }

    full = semCreate((key_t)99887,1,0);
    if (full < 0){
        printf("***Semaphore error***\n");
        exit(0);
  }
////// Initializng the binary semaphores for the paintShop-Inspectors processes's iteractions //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
empty_1 = semCreate((key_t)8423,1,1);
    if (empty_1 < 0){
        printf("***Semaphore error***\n");
        exit(0);
}

empty_2 = semCreate((key_t)5468,1,1);
    if (empty_2 < 0){
        printf("***Semaphore error***\n");
        exit(0);
}

empty_3 = semCreate((key_t)2348,1,1);
    if (empty_3 < 0){
        printf("***Semaphore error***\n");
        exit(0);
}

mutex_1 = semCreate((key_t)4321,1,1);
    if (mutex_1 < 0){
        printf("***Semaphore error***\n");
        exit(0);
}

mutex_2 = semCreate((key_t)2134,1,1);
    if (mutex_2 < 0){
        printf("***Semaphore error***\n");
        exit(0);
}

mutex_3 = semCreate((key_t)3421,1,1);
    if (mutex_3 < 0){
        printf("***Semaphore error***\n");
        exit(0);
}

full_1 = semCreate((key_t)1234,1,0);
if (full_1 < 0){
    printf("***Semaphore error***\n");
    exit(0);
}

full_2 = semCreate((key_t)7234,1,0);
if (full_2 < 0){
    printf("***Semaphore error***\n");
    exit(0);
}

full_3 = semCreate((key_t)4756,1,0);
if (full_3 < 0){
    printf("***Semaphore error***\n");
    exit(0);
}
///// Initializng the binary semaphores for the Inspectors-Assembler processes's iteractions //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    emptyAssembler = semCreate((key_t)3264,1,1);
        if (emptyAssembler < 0){
            printf("***Semaphore error***\n");
            exit(0);
    }

    mutexAssembler = semCreate((key_t)2845,1,1);
        if (mutexAssembler < 0){
            printf("***Semaphore error***\n");
            exit(0);
    }

    fullAssembler = semCreate((key_t)9687,1,0);
    if (fullAssembler < 0){
        printf("***Semaphore error***\n");
        exit(0);
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*+++++++++++++++++++++++++++++++PROCESSES+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/****************************MANUFACTURERS*************************************/
    int i;
    for(i=0; i<3; i++){
      pid = fork();
      if(pid==0){
        Manufacture(n, i+1, mutex, empty,full, ShMem_PTR, tStart);
          exit(0);
        }
      }
/*****************************PAINTSHOP****************************************/
    pid1=fork();
    if(pid1==0){
      PaintShop(n, mutex, mutex_1, mutex_3, mutex_2, empty, empty_1, empty_2, empty_3, full, full_1, full_2, full_3, ShMem_PTR, ShMem_PTR1_1, ShMem_PTR1_2, ShMem_PTR1_3 ,tStart, tPaint);
      exit(0);
        }
/************************INSPECTORS********************************************/
    int x;
    for(x=0; x<3;x++){
      pid2=fork();
      if(pid2==0){
        if(x==0){
            Inspect(n, x+1, mutex_1, mutexAssembler, emptyAssembler, empty_1, fullAssembler, full_1, ShMem_PTR2, ShMem_PTR1_1);
          }
        else if(x==1){
            Inspect(n, x+1, mutex_2, mutexAssembler, emptyAssembler, empty_2, fullAssembler, full_2, ShMem_PTR2, ShMem_PTR1_2);
          }
        else if(x==2){
            Inspect(n, x+1, mutex_3, mutexAssembler, emptyAssembler, empty_3, fullAssembler, full_3, ShMem_PTR2, ShMem_PTR1_3);
            }
      exit(0);
    }
  }
/***********************ASSEMBLER**********************************************/
    pid3=fork();
    if(pid3==0){
        Assemble(n, mutexAssembler, emptyAssembler, fullAssembler, ShMem_PTR2, tEnd);
        exit(0);
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  for (;;) {  // Remove the zombie process, and get the pid and return code

  pid = wait(&status);
  pid1 = wait(&status);
  pid2 = wait(&status);
  pid3 = wait(&status);

if (pid < 0 && pid1 < 0 && pid2 < 0 && pid3 <0){
  if (errno == ECHILD) {
    break;
      }
  else {
    perror("Could not wait");
      }
    }
}
///////////// Delete all the shared memory segments and semaphores //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (shMemDetach(ShMem_PTR) == -1) {                  //Detaching and Deleting the first shared memory segment
        printf(" ***Shared Memory Segment could not be detached(shmdt failed)***\n");
        exit(1);
    }
    if (shMemDelete(ShMem_ID) == -1) {
        printf(" ***Shared Memory Segment could not be deleted(shmctl(IPC_RMID) failed)***\n");
        exit(1);
      }

    if (shMemDetach(ShMem_PTR1_1) == -1) {                  //Detaching and Deleting the second shared memory segments
        printf(" ***Shared Memory Segment could not be detached(shmdt failed)***\n");
        exit(1);
      }
    if (shMemDelete(ShMem_ID1_1) == -1) {
        printf(" ***Shared Memory Segment could not be deleted(shmctl(IPC_RMID) failed)***\n");
        exit(1);
      }

      if (shMemDetach(ShMem_PTR1_2) == -1) {                  //Detaching and Deleting the second shared memory segments
          printf(" ***Shared Memory Segment could not be detached(shmdt failed)***\n");
          exit(1);
      }
      if (shMemDelete(ShMem_ID1_2) == -1) {
          printf(" ***Shared Memory Segment could not be deleted(shmctl(IPC_RMID) failed)***\n");
          exit(1);
        }

      if (shMemDetach(ShMem_PTR1_3) == -1) {                  //Detaching and Deleting the second shared memory segments
          printf(" ***Shared Memory Segment could not be detached(shmdt failed)***\n");
          exit(1);
        }
      if (shMemDelete(ShMem_ID1_3) == -1) {
          printf(" ***Shared Memory Segment could not be deleted(shmctl(IPC_RMID) failed)***\n");
          exit(1);
          }

      if (shMemDetach(ShMem_PTR2) == -1) {                  //Detaching and Deleting the third shared memory segments
            printf(" ***Shared Memory Segment could not be detached(shmdt failed)***\n");
            exit(1);
        }
      if (shMemDelete(ShMem_ID2) == -1) {
            printf(" ***Shared Memory Segment could not be deleted(shmctl(IPC_RMID) failed)***\n");
            exit(1);
          }

      semDelete(full);
      semDelete(full_1);
      semDelete(full_2);
      semDelete(full_3);
      semDelete(fullAssembler);
      semDelete(empty);
      semDelete(empty_1);
      semDelete(empty_2);
      semDelete(empty_3);
      semDelete(emptyAssembler);
      semDelete(mutex);
      semDelete(mutex_1);
      semDelete(mutex_2);
      semDelete(mutex_3);
      semDelete(mutexAssembler);

      exit(0);
      return 0;
    }
