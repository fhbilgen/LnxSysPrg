
#include "common.h"

#define TIMEOUT 5
#define BUF_LEN 1024

int SelectTest()
{
	struct timeval tv;
	fd_set readfds;
	int ret;

	/* Wait on stdin for input */
	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);

	/* Wait up to five seconds*/
	tv.tv_sec = 5;
	tv.tv_usec = 0;

	/* All right, now block!*/
	ret = select(STDIN_FILENO+1, &readfds, NULL, NULL, &tv);
	if (ret == -1)
	{
		perror("Error happened with select");
		return -1;
	}
	else if (!ret)
	{
		/* Timeout has happened*/
		printf("%d seconds elapsed.\n", TIMEOUT - tv.tv_sec);
		return 0;
	}

	/*
	* Is our file descriptor ready to read?
	* It must be, as it was the only fd that we provided and the call returned nonzero, 
	* but we will humor ourselves :)
	*/

	if (FD_ISSET(STDIN_FILENO, &readfds))
	{
		char buf[BUF_LEN + 1];
		int len;
		/*guaranteed to not block*/
		len = read(STDIN_FILENO, buf, BUF_LEN);
		if (len == -1)
		{
			perror("Error happened with read");
			return -1;
		}
		if (len)
		{
			buf[len] = '\0';
			printf("read: %s\t Remaining Time: %d\n", buf, tv.tv_sec);
		}
		return 0;
	}

	printf("This should not have happened\n");
	return -1;

}


int PollTest()
{
	struct pollfd fds[2];
	int ret;

	/* Watch stdin for input*/
	fds[0].fd = STDIN_FILENO;
	fds[0].events = POLLIN;

	///* Watch stdout for ability to write (almost always true)*/
	//fds[1].fd = STDOUT_FILENO;
	//fds[1].events = POLLOUT;

	/* All set, block!*/
	ret = poll(fds, 2, TIMEOUT * 1000);
	if (ret == -1)
	{
		perror("poll failed with error ");
		return -1;
	}

	if (!ret)
	{
		printf("%d seconds elapsed.\n", TIMEOUT);
		return 0;
	}

	if (fds[0].revents & POLLIN)
		printf("STDIN is readable\n");

	if (fds[1].revents & POLLOUT)
		printf("STDOUT is writeable\n");

	return 0;
}