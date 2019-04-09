
#include "common.h"

void TestFileOpen(const char* fileName)
{
	int fd;
	
	printf("Opening file with ReadOnly flag\n");

	fd = open(fileName, O_RDONLY);

	if (fd == -1)
	{
		perror("Error happened during opening the file read only: ");
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

	printf("Opening file with create\n");
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

	/*******
	printf("Opening file with Create_Excl\n");
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
	******/

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


}