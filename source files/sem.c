#include "sem.h"



int semCreate(key_t key, int sem_num , int sem_flags){          //for semaphore sets 

  union semun arg;
  int sem_id,count;

  if ((key < 0) || (sem_num <= 0))
      return -1;

  sem_id = semget(key, sem_num,  0666|IPC_CREAT );

  if (sem_id < 0){
    fprintf(stderr, "Failed to initialize semaphore\n");
    exit(EXIT_FAILURE);
    //return -1;
  }

  arg.val = sem_flags;
  for( count = 0; count < sem_num; count++ ){


     if(semctl(sem_id, count, SETVAL, arg) < 0 ) {   
          perror("Could not set value of semaphore");
          exit(EXIT_FAILURE);   
        }
  }

  return sem_id;

}


int semDelete(int sem_id){

  if (sem_id < 0){
    fprintf(stderr, "Failed to delete semaphore\n");
    exit(EXIT_FAILURE);
    //return -1;
  }

  return semctl(sem_id,0,IPC_RMID);

}


int semGet(int sem_id, int sem_num){

  union semun arg;

  if (sem_id < 0 || sem_num < 0){
    fprintf(stderr, "Failed to get semaphore\n");
    exit(EXIT_FAILURE);
  }

  return semctl(sem_id,sem_num,GETVAL,arg);

}


int semSet(int sem_id, int sem_num, int value){

  union semun arg;

  if (sem_id < 0 || sem_num < 0){
    fprintf(stderr, "Failed to set semaphore\n");
    exit(EXIT_FAILURE);
  }
  arg.val = value;

  return semctl(sem_id,sem_num,SETVAL,arg);

}


int sem_P(int sem_id, int sem_num){

  struct sembuf sem_b;

  sem_b.sem_num = sem_num;
  sem_b.sem_op = -1; 
  sem_b.sem_flg = 0;

  if (sem_id < 0 || sem_num < 0){
    fprintf(stderr, "Failed to reduce semaphore's value\n");
    exit(EXIT_FAILURE);
  }

return semop(sem_id, &sem_b, 1);      

}

int sem_V(int sem_id, int sem_num){

  struct sembuf sem_b;

  sem_b.sem_num = sem_num;
  sem_b.sem_op = 1; 
  sem_b.sem_flg = 0;

  if (sem_id < 0 || sem_num < 0){
    fprintf(stderr, "Failed to ...  semaphore's value\n");
    exit(EXIT_FAILURE);
  }

  return semop(sem_id, &sem_b, 1);      

}
