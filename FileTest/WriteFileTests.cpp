
#include "common.h"

const char* string1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char* string2 = "12345678901234567890123456";

int GetUserChoiceForStringType()
{
	int ret;
	printf("1: for %s\n", string1);
	printf("2: for %s\n", string2);
	scanf("%d", &ret);

	if (2 < ret || ret < 1)
	{
		printf("Invalid choice\n");
		exit(-1);
	}

	return ret;
}

bool FileExists(const char* fileName)
{
	int fd;

	fd = open(fileName, O_RDONLY);

	if (-1 == fd && errno == ENOENT)
	{
		printf("Open file failed with %d\n", errno);
		return false;
	}
	else
	{
		close(fd);
		return true;
	}
}

int AppendToFile(const char* fileName, const char* buffer, int count, int interval)
{
	int fd;
	int counter;
	ssize_t bytesWritten;

	// FIRST  : Check file existance. If it does not exist create one.
	// SECOND : Open the file
	if (!FileExists(fileName))
	{
		fd = creat(fileName, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
		if (-1 == fd)
		{
			perror("Error happened while creating file: ");
			return -1;
		}
		else
		{
			printf("File %s created successfully\n", fileName);
			if (close(fd) == -1)
				perror("closing file descriptor failed: ");

			fd = open(fileName, O_WRONLY | O_APPEND);
			if (-1 == fd)
			{
				perror("Error happenned while opening file after having created it: ");
				return -1;
			}
		}
	}
	else
	{
		fd = open(fileName, O_WRONLY | O_APPEND);

		if (-1 == fd)
		{
			perror("Error happened while opening file: ");
		}
	}

	size_t bufferSize;
	bufferSize = strlen(buffer);

	// THIRD : Start the loop
	for (counter = 0; counter != count; counter++)
	{

		bytesWritten = write(fd, buffer, bufferSize);
		if (-1 == bytesWritten)
		{
			perror("Error happened while writing to file");
		}
		else
		{
			// Actually the following compiler warning happens
			// comparison between signed and unsigned integer expressions [-Wsign-compare]
			//     if (bytesWritten != bufferSize)
			//         ~~~~~~~~~~~~~^~~~~~~~~~~~~
			if (bytesWritten != bufferSize)
			{
				printf("The number of bytes written (%d) is different than the buffer length (%d)\n ", bytesWritten, bufferSize);
			}
		}
		sleep(interval);
		printf("Completed the iteration %d \n", counter);
	}

	close(fd);
	printf("Completed appending, exiting\n");

	return 0;
}


int WriteToFileAlternating(const char* fileName, /*const char* buffer,*/ size_t bufferSize, int count, int interval)
{
	int fd;
	int counter;
	ssize_t bytesWritten;
	const char* currentBuffer;

	// FIRST  : Check the existance of the file. If it does not exist create one.
	// SECOND : Open the file
	if (!FileExists(fileName))
	{
		fd = creat(fileName, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
		if (-1 == fd)
		{
			perror("Error happened while creating file: ");
			return -1;
		}
		else
		{
			printf("File %s created successfully\n", fileName);

			if (close(fd) == -1)
				perror("closing file descriptor failed: ");

			fd = open(fileName, O_WRONLY | O_APPEND);
			if (-1 == fd)
			{
				perror("Error happenned while opening file after having created it: ");
				return -1;
			}
		}
	}
	else
	{
		
		fd = open(fileName, O_WRONLY);
		if (-1 == fd)
		{
			perror("Error happened while opening file: ");
		}
	}

	//currentBuffer = string1;

	// THIRD : Start the loop
	for (counter = 0; counter != count; counter++)
	{

		//bytesWritten = write(fd, currentBuffer, bufferSize);
		//if (-1 == bytesWritten)
		//{
		//	perror("Error happened while writing to file");
		//}
		//else
		//{
		//	// Actually the following compiler warning happens
		//	// comparison between signed and unsigned integer expressions [-Wsign-compare]
		//	//     if (bytesWritten != bufferSize)
		//	//         ~~~~~~~~~~~~~^~~~~~~~~~~~~
		//	if (bytesWritten != bufferSize)
		//	{
		//		printf("The number of bytes written (%d) is different than the buffer length (%d)\n ", bytesWritten, bufferSize);
		//	}
		//}



		if (counter % 2 == 1)
			currentBuffer = string1;
		else
			currentBuffer = string2;

		bufferSize = strlen(currentBuffer);

		// Defensive code for partial write cases
		while (bufferSize != 0 && (bytesWritten = write(fd, currentBuffer, bufferSize)) != 0)
		{
			if (bytesWritten == -1)
			{
				if (errno == EINTR)
				{
					printf("EINTR happened. Continuing writing the buffer\n");					
					continue;
				}
				perror("Error happened while writing");
				break;
			}
			bufferSize -= bytesWritten;
			currentBuffer += bytesWritten;
		}
				
		sleep(interval);
		printf("Completed the iteration %d \n", counter);
	}

	close(fd);
	printf("Completed appending, exiting\n");

	return 0;
}


int WriteToFile(const char* fileName, const char* buffer, int count, int interval)
{
	int fd;
	int counter;
	ssize_t bytesWritten;
	size_t bufferSize;
	const char* currentBuffer;

	// FIRST  : Check the existance of the file. If it does not exist create one.
	// SECOND : Open the file
	if (!FileExists(fileName))
	{
		fd = creat(fileName, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
		if (-1 == fd)
		{
			perror("Error happened while creating file: ");
			return -1;
		}
		else
		{
			printf("File %s created successfully\n", fileName);

			if (close(fd) == -1)
				perror("closing file descriptor failed: ");

			fd = open(fileName, O_WRONLY);
			if (-1 == fd)
			{
				perror("Error happenned while opening file after having created it: ");
				return -1;
			}
		}
	}
	else
	{
		fd = open(fileName, O_WRONLY);
		if (-1 == fd)
		{
			perror("Error happened while opening file: ");
		}
	}
		
	// THIRD : Start the loop
	for (counter = 0; counter != count; counter++)
	{
				
		bufferSize = strlen(buffer);
		currentBuffer = buffer;

		// Defensive code for partial write cases
		while (bufferSize != 0 && (bytesWritten = write(fd, currentBuffer, bufferSize)) != 0)
		{
			if (bytesWritten == -1)
			{
				if (errno == EINTR)
				{
					printf("EINTR happened. Continuing writing the buffer\n");
					continue;
				}
				perror("Error happened while writing");
				break;
			}
			bufferSize -= bytesWritten;
			currentBuffer += bytesWritten;
		}

		// I have commented out sleep to write into the same file by multiple processes
		// 
		sleep(interval);
		printf("Completed the iteration %d \n", counter);
	}

	close(fd);
	printf("Completed appending, exiting\n");

	return 0;
}

// It iş more descriptive to run 2 instances at once too see that the file position is updated correctly

void StartAppending()
{
	int choice;

	choice = GetUserChoiceForStringType();

	const char* cp = NULL;

	switch (choice)
	{
	case 1:
		cp = string1;
		break;
	case 2:
		cp = string2;
		break;
	default:
		break;
	}

	AppendToFile("test.txt", cp, 10, 1);
}

void StartWriting()
{
	//WriteToFileAlternating("test.txt", 25, 10, 1);

	int choice;

	choice = GetUserChoiceForStringType();

	const char* cp = NULL;

	switch (choice)
	{
	case 1:
		cp = string1;
		break;
	case 2:
		cp = string2;
		break;
	default:
		break;
	}

	// The actual passed arguments are 10.
	// With high iteration I was hoping to corrupt the file position but it did not work out
	// WriteToFile("test.txt", cp, 1000000, 1);
	WriteToFile("test.txt", cp, 10, 1);
}


int CreateTheFile(const char* fileName)
{
	int fd;

	// FIRST  : Create the file
	fd = creat(fileName, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (-1 == fd)
	{
		perror("Error happened while creating file: ");
		return -1;
	}
	else
	{
		printf("File %s created successfully\n", fileName);

		if (close(fd) == -1)
			perror("closing file descriptor failed: ");

		return 0;
	}
}

 int DiffInMill(struct timespec start, struct timespec stop)
{
	 return (int)(((stop.tv_sec - start.tv_sec) * 1000000000L + (stop.tv_nsec - start.tv_nsec)) / 1000000L);
}


int TestWriteSpeed(const char* fileName, const char* buffer, int count)
{
	int fd;
	int counter;
	ssize_t bytesWritten;
	size_t bufferSize;
	const char* currentBuffer;
	struct timespec tmStart, tmEnd;

	
	if (CreateTheFile(fileName) == -1)
	{
		printf("Could not create the file\n");
		return -1;
	}
	else
	{
		fd = open(fileName, O_WRONLY);
		if (-1 == fd)
		{
			perror("Error happenned while opening file after having created it: ");
			return -1;
		}
	}	
	
	// FIRST : Start the loop
	printf("\nTEST #1: Plain test\n");	
	printf("===================\n");
	printf("Populating the file\n");
	printf("Buffer Length = %d\n", strlen(buffer) );
	
	clock_gettime(CLOCK_MONOTONIC, &tmStart);
	for (counter = 0; counter != count; counter++)
	{

		bufferSize = strlen(buffer);
		currentBuffer = buffer;

		// Defensive code for partial write cases
		while (bufferSize != 0 && (bytesWritten = write(fd, currentBuffer, bufferSize)) != 0)
		{
			if (bytesWritten == -1)
			{
				if (errno == EINTR)
				{
					printf("EINTR happened. Continuing writing the buffer\n");
					continue;
				}
				perror("Error happened while writing");
				break;
			}
			bufferSize -= bytesWritten;
			currentBuffer += bytesWritten;
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &tmEnd);
	
	if (close(fd) == -1)
		perror("Error happened while closing the file");
	
	printf("The file is populated in %d msec\n", DiffInMill(tmStart, tmEnd) );



	if (CreateTheFile(fileName) == -1)
	{
		printf("Could not create the file\n");
		return -1;
	}
	else
	{
		fd = open(fileName, O_WRONLY);
		if (-1 == fd)
		{
			perror("Error happenned while opening file after having created it: ");
			return -1;
		}
	}

	// SECOND : Start the loop
	printf("\nTEST #2: fdatasync after each write\n");
	printf("====================================\n");
	printf("Populating the file\n");
	printf("Buffer Length = %d\n", strlen(buffer));

	clock_gettime(CLOCK_MONOTONIC, &tmStart);
	for (counter = 0; counter != count; counter++)
	{

		bufferSize = strlen(buffer);
		currentBuffer = buffer;

		// Defensive code for partial write cases
		while (bufferSize != 0 && (bytesWritten = write(fd, currentBuffer, bufferSize)) != 0)
		{
			if (bytesWritten == -1)
			{
				if (errno == EINTR)
				{
					printf("EINTR happened. Continuing writing the buffer\n");
					continue;
				}
				perror("Error happened while writing");
				break;
			}
			bufferSize -= bytesWritten;
			currentBuffer += bytesWritten;
		}
				
		if (fdatasync(fd) == -1)
			perror("fdatasync failed ");

	}
	clock_gettime(CLOCK_MONOTONIC, &tmEnd);

	if (close(fd) == -1)
		perror("Error happened while closing the file");

	printf("The file is populated in %d msec\n", DiffInMill(tmStart, tmEnd));



	if (CreateTheFile(fileName) == -1)
	{
		printf("Could not create the file\n");
		return -1;
	}
	else
	{
		fd = open(fileName, O_WRONLY);
		if (-1 == fd)
		{
			perror("Error happenned while opening file after having created it: ");
			return -1;
		}
	}

	// THIRD : Start the loop
	printf("\nTEST #3: fsync after each write\n");
	printf("================================\n");
	printf("Populating the file\n");
	printf("Buffer Length = %d\n", strlen(buffer));

	clock_gettime(CLOCK_MONOTONIC, &tmStart);
	for (counter = 0; counter != count; counter++)
	{

		bufferSize = strlen(buffer);
		currentBuffer = buffer;

		// Defensive code for partial write cases
		while (bufferSize != 0 && (bytesWritten = write(fd, currentBuffer, bufferSize)) != 0)
		{
			if (bytesWritten == -1)
			{
				if (errno == EINTR)
				{
					printf("EINTR happened. Continuing writing the buffer\n");
					continue;
				}
				perror("Error happened while writing");
				break;
			}
			bufferSize -= bytesWritten;
			currentBuffer += bytesWritten;
		}

		if (fsync(fd) == -1)
			perror("fsync failed ");

	}
	clock_gettime(CLOCK_MONOTONIC, &tmEnd);

	if (close(fd) == -1)
		perror("Error happened while closing the file");

	printf("The file is populated in %d msec\n", DiffInMill(tmStart, tmEnd));







	if (CreateTheFile(fileName) == -1)
	{
		printf("Could not create the file\n");
		return -1;
	}
	else
	{
		fd = open(fileName, O_WRONLY | O_SYNC);
		if (-1 == fd)
		{
			perror("Error happenned while opening file after having created it: ");
			return -1;
		}
	}

	// FOURTH : Start the loop
	printf("\nTEST #4: O_SYNC while opening file\n");
	printf("===================================\n");
	printf("Populating the file\n");
	printf("Buffer Length = %d\n", strlen(buffer));

	clock_gettime(CLOCK_MONOTONIC, &tmStart);
	for (counter = 0; counter != count; counter++)
	{

		bufferSize = strlen(buffer);
		currentBuffer = buffer;

		// Defensive code for partial write cases
		while (bufferSize != 0 && (bytesWritten = write(fd, currentBuffer, bufferSize)) != 0)
		{
			if (bytesWritten == -1)
			{
				if (errno == EINTR)
				{
					printf("EINTR happened. Continuing writing the buffer\n");
					continue;
				}
				perror("Error happened while writing");
				break;
			}
			bufferSize -= bytesWritten;
			currentBuffer += bytesWritten;
		}
	}

	clock_gettime(CLOCK_MONOTONIC, &tmEnd);

	if (close(fd) == -1)
		perror("Error happened while closing the file");

	printf("The file is populated in %d msec\n", DiffInMill(tmStart, tmEnd));

	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	/* O_DIRECT fails with EINVALID  */
	/* This makes sense because memory alignment to disk sector size should be exercised. */
	/* I won't bother with that!!! */
	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/


	if (CreateTheFile(fileName) == -1)
	{
		printf("Could not create the file\n");
		return -1;
	}
	else
	{
		fd = open(fileName, O_WRONLY | O_DIRECT);
		if (-1 == fd)
		{
			perror("Error happenned while opening file after having created it: ");
			return -1;
		}
	}

	// FIVE : Start the loop
	printf("\nTEST #5: O_DIRECT while opening file\n");
	printf("==============================================\n");
	printf("Populating the file\n");
	printf("Buffer Length = %d\n", strlen(buffer));

	clock_gettime(CLOCK_MONOTONIC, &tmStart);
	for (counter = 0; counter != count; counter++)
	{

		bufferSize = strlen(buffer);
		currentBuffer = buffer;

		// Defensive code for partial write cases
		while (bufferSize != 0 && (bytesWritten = write(fd, currentBuffer, bufferSize)) != 0)
		{
			if (bytesWritten == -1)
			{
				if (errno == EINTR)
				{
					printf("EINTR happened. Continuing writing the buffer\n");
					continue;
				}
				perror("Error happened while writing");
				break;
			}
			bufferSize -= bytesWritten;
			currentBuffer += bytesWritten;
		}
	}

	clock_gettime(CLOCK_MONOTONIC, &tmEnd);

	if (close(fd) == -1)
		perror("Error happened while closing the file");

	printf("The file is populated in %d msec\n", DiffInMill(tmStart, tmEnd));





	// ONE BYTE BUFFER TESTS
	
	//if (CreateTheFile(fileName) == -1)
	//{
	//	printf("Could not create the file\n");
	//	return -1;
	//}
	//else
	//{
	//	fd = open(fileName, O_WRONLY);
	//	if (-1 == fd)
	//	{
	//		perror("Error happenned while opening file after having created it: ");
	//		return -1;
	//	}
	//}

	//printf("\nTEST #2\n");
	//printf("=======\n");
	//printf("Populating the file\n");
	//printf("Buffer Length = %d\n", 1);

	//clock_gettime(CLOCK_MONOTONIC, &tmStart);
	//for (counter = 0; counter != count; counter++)
	//{
	//	
	//	bufferSize = strlen(buffer);
	//	currentBuffer = buffer;
	//	
	//	// The for loop makes the write buffer 1 byte
	//	// TODO : The buffer length should be configurable for performance tests.
	//	for (int innerloop = 0; innerloop != bufferSize; innerloop++)
	//	{
	//		currentBuffer = &(buffer[innerloop]);

	//		// Defensive code for partial write cases
	//		while (bufferSize != 0 && (bytesWritten = write(fd, currentBuffer, 1)) != 0)
	//		{
	//			if (bytesWritten == -1)
	//			{
	//				if (errno == EINTR)
	//				{
	//					printf("EINTR happened. Continuing writing the buffer\n");
	//					continue;
	//				}
	//				perror("Error happened while writing");
	//				break;
	//			}
	//			bufferSize -= bytesWritten;				
	//		}
	//	}
	//}
	//clock_gettime(CLOCK_MONOTONIC, &tmEnd);

	//if (close(fd) == -1)
	//	perror("Error happened while closing the file");

	//printf("The file is populated in %d msec\n", DiffInMill(tmStart, tmEnd));
	
	

	return 0;
}


void StartWriteSpeedTest()
{	
	int ret;
	printf("Each file content iteration is 26 byte long. How many iterations for the file content?\n");
	scanf("%d", &ret);

	TestWriteSpeed("test.txt", string1, ret);
}