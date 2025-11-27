#include "main.h"

#include <libcqp/cqp.h> /* all cqp_**** functions */
#include <stdio.h> /* printf and perror */
#include <string.h> /* strncpy */
#include <sys/socket.h> /* socket and connect*/
#include <sys/un.h> /* sockaddr_un */
#include <unistd.h> /* sleep */
#include <stdlib.h> /* getenv */

const char *str_try = "Try:%s\n";
const char *str_fail = "%s failed with error code %i\n";
const char *str_success = "Request sent successfully.\n";

int main(int argc, char **argv)
{
	/* CQP socket */

	/* Socket descriptor */
	int fd;

	/* Address */
	struct sockaddr_un tmp_addr;

	/* ------------------- */

	/* Counters */
	int i;

	/* Error Code */
	int err = 0;

	i = argc - 1;

	if (!i)
	{
		printf("Usage: cqp_unit_tests [sockets]\n\n");
		printf("No sockets listed. Nothing to test.\n");
		return 0;
	}

	while (i)
	{
		printf("Connecting to %s\n", argv[i]);

		fd = socket(AF_UNIX, SOCK_STREAM, 0);
		if (fd == -1)
		{
			perror("Failed to create socket");
			return -1;
		}

		printf("Socket descriptor: %i\n", fd);

		tmp_addr.sun_family = AF_UNIX;
		strncpy(tmp_addr.sun_path, argv[i], sizeof(tmp_addr.sun_path));

		if (connect(fd, (struct sockaddr*)&tmp_addr, sizeof(tmp_addr)) == -1)
		{
			perror("Failed to connect to server");
			return -1;
		}

		printf("Successfully connected.\n");

		sleep(1);

		/* Send a 'Cast Point' request */
		printf(str_try, "cqp_cast_point(\%fd%, 1.23, 4.56, 7.89)");
		err = cqp_cast_point(fd, 1.23, 4.56, 7.89);
        if (err)
		{
			printf(str_fail, "cqp_cast_point(\%fd%, 1.23, 4.56, 7.89)", err);
		}
		else
		{
			printf(str_success);
		}

		sleep(1);

		/* Send a 'Cast Ray' request */
		printf(str_try,
			"cqp_cast_ray(\%fd%, 1.23, 4.56, 7.89, 98.7, 65.4, 32.1)"
		);
		err = cqp_cast_ray(fd, 1.23, 4.56, 7.89, 98.7, 65.4, 32.1);
        if (err) 
		{
			printf(str_fail,
				"cqp_cast_ray(\%fd%, 1.23, 4.56, 7.89, 98.7, 65.4, 32.1)", err
			);
		}
        else
		{
			printf(str_success);
		}

		sleep(1);

		/* ...Onto the next socket. If any. */
		printf("closing socket %i\n", fd);
		close(fd);

		--i;
	}

	return 0;
}

