
#include "common.h"

int main()
{
	int iChoice;
	// Put the PollTest at the beginning to test the following :)
	// ./FileTest.out < test.txt
	// PollTest();
    //printf("hello from FileTest!\n");
	
	//TestO_CREATEandO_EXCL("test.txt");
	//TestCreateFile("test.txt");
	//TestcreatFile("test.txt");
	//TestFileOpen("test.txt");
	//TestCreatePermission("test.txt");
	// Need a test without any file


	// Append Test
	//StartAppending();

	// Simple Write test
	//StartWriting();


	printf("1: Append Test\n");
	printf("2: Write Test\n");
	printf("3: Write Speed Test\n");
	printf("4: Seek File Test\n");
	printf("5: Truncate Test\n");
	printf("6: Select Test\n");
	printf("7: Poll Test\n");
	scanf("%d", &iChoice);

	switch (iChoice)
	{
		case 1:
			StartAppending();
			break;
		
		case 2:
			StartWriting();
			break;
		
		case 3:
			StartWriteSpeedTest();
			break;

		case 4:
			StartSeekTest();
			break;

		case 5:
			StartTruncTest();
			break;

		case 6:
			SelectTest();
			break;

		case 7:
			PollTest();
			break;

		default:
			break;
	}
	

    return 0;
}