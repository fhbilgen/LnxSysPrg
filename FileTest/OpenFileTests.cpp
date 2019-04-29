
#include "common.h"


void TestO_CREATEandO_EXCL(const char* fileName)
{
	int fd, step;

	/*****************************************************************************
	********************** O_CREAT ***********************************************/
	printf("Enter a char to continue with O_CREAT\n");
	scanf("%d", &step);

	printf("Opening file with create\n");
	//fd = open(fileName, O_RDWR | O_CREAT, 0644);
	fd = open(fileName, O_RDWR | O_CREAT);
	if (fd == -1)
	{
		perror("Error happened during opening the file Create: ");
	}
	else
	{
		printf("File opened successfully Create\n ");
		close(fd);
	}

	printf("Enter a char to continue with O_CREATE and O_EXCL\n");
	scanf("%d", &step);

	/*****************************************************************************
	********************** O_CREAT | O_EXCL **************************************/

	printf("Opening file with O_CREATE and O_EXCL\n");
	//fd = open(fileName, O_RDWR | O_CREAT, 0644);
	fd = open(fileName, O_RDWR | O_CREAT | O_EXCL);
	if (fd == -1)
	{
		perror("Error happened during opening the file Create and Excl: ");
	}
	else
	{
		printf("File opened successfully O_CREATE and O_EXCL\n ");
		close(fd);
	}

	printf("Enter a char to continue\n");
	scanf("%d", &step);

}


void TestcreatFile(const char* fileName)
{
	int fd, step;

	printf("Enter a char to continue with creat\n");
	scanf("%d", &step);

	
	fd = creat(fileName, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

	if (-1 == fd)
	{
		perror("Failed to creat file: ");
	}
	else
	{
		printf("Successfully created the file with creat\n");
		close(fd);
	}
	
	printf("Enter a char to continue with O_CREAT O_TRUNC \n");
	scanf("%d", &step);

	fd = open(fileName, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd == -1)
	{
		perror("Error happened during opening the file O_TRUNC | O_CREAT: ");
	}
	else
	{
		printf("File opened successfully O_TRUNC | O_CREAT\n ");
		close(fd);
	}

	printf("Enter a char to continue\n");
	scanf("%d", &step);

}

void TestFileOpen(const char* fileName)
{
	int fd;
		
	printf("Opening file with ReadOnly flag\n");

	fd = open(fileName, O_RDONLY);

	if (fd == -1)
	{
		perror("Error happened during opening the file read only: ");
		printf("The error no is %d\n", errno);
		if (errno == ENOENT)
			printf("it holds\n");
	}
	else
	{
		printf("File opened successfully read-only\n ");
		close(fd);
	}
	
	printf("Opening file with Read_and_Write\n");
	fd = open(fileName, O_RDWR);
	if (fd == -1)
	{
		perror("Error happened during opening the file Read_and_Write: ");
	}
	else
	{
		printf("File opened successfully Read_and_Write\n ");
		close(fd);
	}


	printf("Opening file with Append\n");
	fd = open(fileName, O_RDWR | O_APPEND);
	if (fd == -1)
	{
		perror("Error happened during opening the file Append: ");
	}
	else
	{
		printf("File opened successfully Append\n ");
		close(fd);
	}

	printf("Opening file with Asynchronous\n");
	fd = open(fileName, O_RDWR | O_ASYNC);
	if (fd == -1)
	{
		perror("Error happened during opening the file Asynchronous: ");
	}
	else
	{
		printf("File opened successfully Asynchronous\n ");
		close(fd);
	}

	printf("Opening file with close-on-exec\n");
	fd = open(fileName, O_RDWR | O_CLOEXEC);
	if (fd == -1)
	{
		perror("Error happened during opening the file close-on-exec: ");
	}
	else
	{
		printf("File opened successfully close-on-exec\n ");
		close(fd);
	}

	printf("Opening file with DirectIO\n");
	fd = open(fileName, O_RDWR | O_DIRECT);
	if (fd == -1)
	{
		perror("Error happened during opening the file DirectIO: ");
	}
	else
	{
		printf("File opened successfully DirectIO\n ");
		close(fd);
	}

	printf("Opening file with Directory\n");
	fd = open(fileName, O_RDWR | O_DIRECTORY);
	if (fd == -1)
	{
		perror("Error happened during opening the file Directory: ");
	}
	else
	{
		printf("File opened successfully Directory\n ");
		close(fd);
	}

	printf("Opening file with Excl\n");
	fd = open(fileName, O_RDWR | O_EXCL);
	if (fd == -1)
	{
		perror("Error happened during opening the file Excl: ");
	}
	else
	{
		printf("File opened successfully Excl\n ");
		close(fd);
	}


	printf("Opening file with LargeFile\n");
	fd = open(fileName, O_RDWR | O_LARGEFILE);
	if (fd == -1)
	{
		perror("Error happened during opening the file as Large File: ");
	}
	else
	{
		printf("File opened successfully Large File\n ");
		close(fd);
	}


	printf("Opening file with NoAccessTime\n");
	fd = open(fileName, O_RDWR | O_NOATIME);
	if (fd == -1)
	{
		perror("Error happened during opening the file NoAccessTime: ");
	}
	else
	{
		printf("File opened successfully NoAccessTime\n ");
		close(fd);
	}


	printf("Opening file with NoControlTerminal\n");
	fd = open(fileName, O_RDWR | O_NOCTTY);
	if (fd == -1)
	{
		perror("Error happened during opening the file NoControlTerminal: ");
	}
	else
	{
		printf("File opened successfully NoControlTerminal\n ");
		close(fd);
	}


	printf("Opening file with NoFollow\n");
	fd = open(fileName, O_RDWR | O_NOFOLLOW);
	if (fd == -1)
	{
		perror("Error happened during opening the file NoFollow: ");
	}
	else
	{
		printf("File opened successfully NoFollow\n ");
		close(fd);
	}

	printf("Opening file with NonBlock\n");
	fd = open(fileName, O_RDWR | O_NONBLOCK);
	if (fd == -1)
	{
		perror("Error happened during opening the file NonBlock: ");
	}
	else
	{
		printf("File opened successfully NonBlock\n ");
		close(fd);
	}


	printf("Opening file with Synchronous\n");
	fd = open(fileName, O_RDWR | O_SYNC);
	if (fd == -1)
	{
		perror("Error happened during opening the file Synchronous: ");
	}
	else
	{
		printf("File opened successfully Synchronous\n ");
		close(fd);
	}

}

void TestCreateFile(const char* fileName)
{
	int fd;
	bool fFileExists = false;

	printf("Check if the file %s exists\n", fileName);

	fd = open(fileName, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (-1 == fd)
	{
		if (EEXIST == errno)
			fFileExists = true;
		else
			fFileExists = false;
	}

	/*If file exists try to recreate file with O_CREAT and NO !!!! O_EXCL*/
	if (fFileExists)
	{
		close(fd);

		printf("The file exists and trying to re-create the file with O_CREATE and O_EXCL\n");
		fd = open(fileName, O_RDWR | O_CREAT | O_EXCL);
		if (-1 == fd)
			perror("Error opening file with O_CREAT and O_EXCL : ");
		else
		{
			printf("This should not have happened!!!\n");
			close(fd);
		}

		printf("The file exists and trying to re-create the file with O_CREATE and NO!!! O_EXCL\n");

		fd = open(fileName, O_RDWR | O_CREAT);
		if (-1 == fd)
			perror("Error opening file with O_CREAT: ");
		else
			printf("File is created successfully\n");

		close(fd);
	}
	else
	{
		printf("The file doesn't exist. Try to create one with O_CREAT\n");

		fd = open(fileName, O_RDWR | O_CREAT);
		if (-1 == fd)
			perror("Error opening file with O_CREAT: ");
		else
		{
			printf("The new file has been created\n");
			close(fd);
		}

		close(fd);
	}


	printf("\nTesting File Creation\n");
	printf("=====================\n");

	/*printf("Creating file with ReadWrite, Truncate and Creat\n");
	fd = open(fileName, O_RDWR | O_TRUNC | O_CREAT);

	if (-1 == fd)
	{
		perror("Failed to create a file with ReadWrite, Truncate and Creat:");
	}
	else
	{
		printf("Successfully created the file with ReadWrite, Truncate and Creat\n");
		close(fd);
	}*/

	printf("Creating file creat()\n");
	//fd = creat(fileName, 0644);
	fd = creat(fileName, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

	if (-1 == fd)
	{
		perror("Failed to creat file: ");
	}
	else
	{
		printf("Successfully created the file with creat\n");
		close(fd);
	}


	printf("displaying the value of FileDecriptor when opening the file with just O_RDWR and after closing it\n");
	fd = open(fileName, O_RDWR);

	printf("File Descriptor value is %d\n", fd);
	close(fd);
	printf("File Descriptor value is %d\n", fd);

}

void TestCreatePermission(const char* fileName)
{
	int fd;

	fd = creat(fileName, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

	if (-1 == fd)
	{
		perror("Failed to creat file: ");
	}
	else
	{
		printf("Successfully created the file with creat\n");
		close(fd);
	}


}