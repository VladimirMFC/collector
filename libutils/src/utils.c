#include "config.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <fcntl.h>
#include <signal.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include <sys/resource.h>
#include <sys/stat.h>

static const char *config_path;
static const char *pid_path;
static sigset_t mask;

static int lockfile(int fd)
{
	struct flock fl;

	fl.l_type = F_WRLCK;
	fl.l_start = 0;
	fl.l_whence = SEEK_SET;
	fl.l_len = 0;

	return fcntl(fd, F_SETLK, &fl);
}

static bool already_running(const char* pid_file)
{
	int fd;
	char buf[16];

	fd = open(pid_file, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		syslog(LOG_ERR, "Can't open %s, %s", pid_file, strerror(errno));
		exit(1);
	}

	if (lockfile(fd) < 0)
	{
		if (errno == EACCES || errno == EAGAIN)
		{
			close(fd);
			return true;
		}

		syslog(LOG_ERR, "Can't lock %s, %s", pid_file, strerror(errno));
		exit(1);
	}

	ftruncate(fd, 0);
	sprintf(buf, "%ld", (long)getpid());
	write(fd, buf, strlen(buf));

	return false;
}

void daemonize(const char* cmd)
{
	int fd0, fd1, fd2;
	pid_t pid;
	struct rlimit rl;
	struct sigaction sa;

	umask(0);

	if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
	{
		syslog(LOG_ERR, "Can't get max file descriptor");
		exit(1);
	}

	if ((pid = fork()) < 0)
	{
		syslog(LOG_ERR, "Error calling function 'fork'");
		exit(1);
	}
	else
		if (pid != 0)
			exit(0);

	setsid();

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0)
	{
		syslog(LOG_ERR, "Can't ignore SIGHUP signal");
		exit(1);
	}

	if ((pid = fork()) < 0)
	{
		syslog(LOG_ERR, "Error calling function 'fork'");
		exit(1);
	}
	else
		if (pid != 0)
			exit(0);

	if (chdir("/") < 0)
	{
		syslog(LOG_ERR, "Can't change working dir to /");
		exit(1);
	}

	if (rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;

	for (size_t i = 0; i < rl.rlim_max; i++)
		close(i);

	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if (fd0 != 0 || fd1 != 1 || fd2 != 2)
	{
		syslog(LOG_ERR, "Wrong file descriptors %d %d %d", fd0, fd1, fd2);
		exit(1);
	}
}

void options_parse(int argc, char** argv)
{
	int ch = 0;
	const char *opt_short = "hdc:p:";
	struct option opt_long[] =
	{
		{"help",	no_argument,		NULL,	'h'},
		{"daemon",	no_argument,		NULL,	'd'},
		{"config",	required_argument,	NULL,	'c'},
		{"pid",		required_argument,	NULL,	'p'},
		{NULL,		0,			NULL,	0}
	};

	while ((ch = getopt_long(argc, argv, opt_short, opt_long, NULL)) != -1)
	{
		switch (ch)
		{
		case 'h':
			printf("Usage: %s [OPTIONS]\n", argv[0]);
			printf("  -d, --daemon              run in daemon mode\n");
			printf("  -c file, --config=file    path to config file\n");
			printf("  -p file, --pid=file       path to PID file\n");
			printf("  -h, --help                print this help and exit\n");
			exit(0);
			break;

		case 'd':
			daemonize(strrchr(argv[0], '/') != NULL ? strrchr(argv[0], '/') + 1 : argv[0]);
			break;

		case 'c':
			config_path = (const char*)optarg;
			if (!config_open(config_path))
			{
				syslog(LOG_ERR, "Can't load config file %s", config_path);
				exit(0);
			}
			break;

		case 'p':
			pid_path = optarg;
			if (already_running(pid_path))
			{
				syslog(LOG_ERR, "Already running, PID file %s", pid_path);
				exit(0);
			}
			break;

		default:
			syslog(LOG_ERR, "invalid option -- %c", ch);
			/*syslog(LOG_ERR, "Try `%s --help' for more information.", argv[0]);*/
			exit(0);
		}
	}
}

static void* thr_fun(void* arg)
{
	int err, signo;

	while (true)
	{
		if ((err = sigwait(&mask, &signo)) != 0)
		{
			syslog(LOG_ERR, "Error calling function sigwait, exiting");
			exit(1);
		}

		switch (signo)
		{
		case SIGHUP:
			syslog(LOG_INFO, "Reload config file");
			config_close();
			if (!config_open(config_path))
			{
				syslog(LOG_INFO, "Can't open config file %s, exiting", config_path);
				exit(0);
			}
			break;

		case SIGTERM:
			syslog(LOG_INFO, "Received signal SIGTERM, exiting");
			exit(0);
			break;

		case SIGINT:
			syslog(LOG_INFO, "Received signal SIGINT, exiting");
			exit(0);
			break;

		default:
			syslog(LOG_INFO, "Received unexpected signal %d\n", signo);
		}

	}

	return NULL;
}

bool config_handler()
{
	int err;
	pthread_t tid;

	struct sigaction sa;
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0)
	{
		syslog(LOG_ERR, "Can't restore action SIG_DFL for SIGHUP");
		exit(1);
	}

	sigfillset(&mask);
	if ((err = pthread_sigmask(SIG_BLOCK, &mask, NULL)) != 0)
	{
		syslog(LOG_ERR, "%s, error executing operation SIG_BLOCK", strerror(err));
		exit(1);
	}

	if ((err = pthread_create(&tid, NULL, thr_fun, 0)) != 0)
	{
		syslog(LOG_ERR, "%s, can't create thread", strerror(err));
		exit(1);
	}

	return true;
}
