#ifndef UTILS_H
#define UTILS_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define	LISTENQ	1024
#define MAXLINE 4096

void error_quit(const char *fmt, ...)
{
    va_list arguments;

	va_start(arguments, fmt);
    printf("%s", fmt);
    va_end(arguments);

    printf("\n");

    exit(1);
}

#endif