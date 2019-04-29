
#include "common.h"

extern const char* string1;
extern const char* string2;


// To measure the file size and disk size
// dbgusr@DebugOnLinux:~/ LinuxSysProg / FileTest / bin / x64 / Debug$ du -h | cut -f1 | sort -h | uniq -c | sort -rn | head
// 1 580K
// https://askubuntu.com/questions/122091/difference-between-filesize-and-size-on-disk
// First column will contain the count, second column the approximate file size.If you have a lot of small files, the count will be high for the top few lines with size < 4k.– jippie Apr 15 '12 at 8:33 

int CreateFilewithHole(const char* fileName, int count1, off_t seekSize, int count2 )
{
	int fd;
	int counter;
	int pos;
	const char* buffer;
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


	buffer = string1;
	// Populate the initial part
	for (counter = 0; counter != count1; counter++)
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
	
	// Create the hole
	pos = lseek(fd, seekSize, SEEK_CUR);
	if (pos == (off_t)-1)
	{
		perror("lseek failed with");
		return -1;
	}	


	buffer = string2;
	// Populate the part after the hole
	for (counter = 0; counter != count1; counter++)
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

	if (close(fd) == -1)
		perror("Error happened while closing the file");

	
	struct stat st;
	if (stat(fileName, &st) == -1)
	{
		perror("Error happened with stat");
		return -1;
	}

	printf("File size   is: %9jd\n", (__intmax_t) st.st_size);
	printf("Block size  is: %9jd\n", (__intmax_t)st.st_blksize);
	printf("Block count is: %9jd\n", (__intmax_t)st.st_blocks);


	return 0;
}

int TruncateTest(const char* fileName, off_t truncSize)
{
	   
	struct stat st;
	if (stat(fileName, &st) == -1)
	{
		perror("Error happened with stat");
		return -1;
	}

	printf("The beginning size information of the file %s\n", fileName);
	printf("File size   is: %9jd\n", (__intmax_t)st.st_size);
	printf("Block size  is: %9jd\n", (__intmax_t)st.st_blksize);
	printf("Block count is: %9jd\n", (__intmax_t)st.st_blocks);


	if (truncate(fileName, truncSize) == -1)
	{
		perror("Error with truncating");
		return -1;
	}

	if (stat(fileName, &st) == -1)
	{
		perror("Error happened with stat");
		return -1;
	}

	printf("The size information of the file after truncating%s\n", fileName);
	printf("File size   is: %9jd\n", (__intmax_t)st.st_size);
	printf("Block size  is: %9jd\n", (__intmax_t)st.st_blksize);
	printf("Block count is: %9jd\n", (__intmax_t)st.st_blocks);

	return 0;

}

void StartTruncTest()
{
	int iH;
	off_t sSize;

	printf("What is the truncation size the file?\n");
	scanf("%d", &iH);
	sSize = (off_t)iH;

	TruncateTest("test.txt", sSize);
}

void StartSeekTest()
{
	int i1, i2, iH;
	off_t sSize;

	printf("Each file content iteration is 26 byte long. How many iterations for the beginning of the file content?\n");
	scanf("%d", &i1);

	printf("How long should be the hole size (in bytes) in the file?\n");
	scanf("%d", &iH);
	sSize = (off_t)iH;

	printf("Each file content iteration is 26 byte long. How many iterations for the file content after the hole?\n");
	scanf("%d", &i2);

	CreateFilewithHole("test.txt", i1, sSize, i2);

}