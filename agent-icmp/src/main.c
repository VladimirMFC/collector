#include "config.h"
#include "utils.h"

#include <syslog.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	openlog(strrchr(argv[0], '/') != NULL ? strrchr(argv[0], '/') + 1 : argv[0], LOG_CONS | LOG_PERROR, LOG_DAEMON);

	options_parse(argc, argv);

	if (!config_exist())
	{
		syslog(LOG_ERR, "Config file not loaded, exiting");
		return EXIT_FAILURE;
	}

	if (!config_handler())
	{
		syslog(LOG_ERR, "Can't set config handler, exiting");
		return EXIT_FAILURE;
	}

#ifndef NDEBUG
	/*printf("C date %ld\n", __STDC_VERSION__);*/
	syslog(LOG_ERR, "Started!!!");
#endif /* !NDEBUG */

	printf("key: %s\n", "section/param");
	printf("value: %s\n", config_value("section/param"));

	config_close();
	closelog();

	return EXIT_SUCCESS;
}
