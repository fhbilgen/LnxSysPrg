
#include "common.h"

int main()
{
    //printf("hello from FileTest!\n");
	TestFileOpen("test.txt");
	TestCreateFile("test.txt");
	// Need a test without any file
    return 0;
}