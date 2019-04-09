#ifndef _common
#define _common

#include <cstdio>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


void TestFileOpen(const char* fileName);
void TestCreateFile(const char* fileName);

#endif