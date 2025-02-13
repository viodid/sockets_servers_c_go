#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(void)
{
  	int				sfd;
	struct addrinfo	hints;
	struct addrinfo	*result, *rp;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family =  AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (close(sfd) == -1)
	{
		perror("close");
		return (-1);
	}
	return (0);
}
