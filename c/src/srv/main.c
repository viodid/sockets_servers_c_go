#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(void)
{
  	int				sfd, cfd;
	struct addrinfo	hints;
	struct addrinfo	*result, *rp;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family =  AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(NULL, "5555", &hints, &result) != 0)
	{
		perror("getaddrinfo");
		exit(EXIT_FAILURE);
	}

	for (rp = result; rp != NULL; rp = rp->ai_next)
	{
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1)
			continue;
		if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
			break;
		close(sfd);
	}
	if (rp == NULL)
	{
		perror("Could not bind");
		exit(EXIT_FAILURE);
	}
	if (listen(sfd, 0) == -1)
	{
		perror("listen");
		close(sfd);
        freeaddrinfo(result);
		exit(EXIT_FAILURE);
	}
	cfd = accept(sfd, rp->ai_addr, &rp->ai_addrlen);
	if (cfd == -1)
	{
		perror("accept");
		close(sfd);
        freeaddrinfo(result);
		exit(EXIT_FAILURE);
	}
	write(cfd, "hey there!", 11);
	freeaddrinfo(result);
	close(cfd);
	close(sfd);
	return (0);
}
