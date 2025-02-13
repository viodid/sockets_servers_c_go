#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void)
{
	const int sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (close(sfd) == -1)
	{
		perror("close");
		return (-1);
	}
	return (0);
}
