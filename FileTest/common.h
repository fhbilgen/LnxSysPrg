#ifndef _common
#define _common

#include <cstdio>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <time.h>


void TestFileOpen(const char* fileName);
void TestCreateFile(const char* fileName);
void TestCreatePermission(const char* fileName);
void TestO_CREATEandO_EXCL(const char* fileName);
void TestcreatFile(const char* fileName);

int CreateTheFile(const char* fileName);

void StartAppending();
void StartWriting();
void StartWriteSpeedTest();
void StartSeekTest();
void StartTruncTest();

int SelectTest();
int PollTest();

#define CLOCK_PRECISION 1000000000L
#endif