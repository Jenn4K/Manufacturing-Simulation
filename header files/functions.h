#pragma once
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "sharedMem.h"
#include "sem.h"
#include "Queue.h"


void Manufacture(int n, int type, int mutex, int empty, int full, shMem_Seg *ShMem_PTR, struct timespec tStart);

void PaintShop(int n, int mutex, int mutex_1, int mutex_2, int mutex_3, int empty, int empty_1, int empty_2, int empty_3, int full, int full_1, int full_2, int full_3, shMem_Seg *ShMem_PTR, shMem_Seg *ShMem_PTR1_1, shMem_Seg *ShMem_PTR1_2, shMem_Seg *ShMem_PTR1_3, struct timespec tStart, struct timespec tPaint);

void Inspect( int n, int type,int otherMutex, int mutexAssembler,int emptyAssembler, int empty1, int fullAssembler, int full1, shMem_Seg *ShMem_PTR2, shMem_Seg *ShMem_PTR1);

void Assemble( int n, int mutexAssembler,int emptyAssembler, int fullAssembler, shMem_Seg *ShMem_PTR2, struct timespec tEnd);
