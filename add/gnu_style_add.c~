/* add.c - sum numbers from arguments or stdin
   Copyright (C) 2026 William Arnold
   License GPLv3+: GNU GPL version 3 or later
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation.  */

#define _POSIX_C_SOURCE 200809L // make portable later
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <stdbool.h>
#include <error.h>

#define PROGRAM_NAME "add"
#define VERSION "0.1"

#define _(x) (x)                // replace with gettext later


static void print_help(void)
{
    printf(_("Usage: %s [OPTION]... [NUMBER...]\n"), PROGRAM_NAME);
    puts(_("Sum the numbers given as arguments or from standard input."));
    puts("");
    puts(_("Options:"));
    puts(_("   -h --help      display this help & exit"));
    puts(_("   -v --version   output version information & exit"));
}

static void print_version(void)
{
    printf("%s %s\n", PROGRAM_NAME, VERSION);
}

static double parse_number(const char *str)
{
    char *endptr;
    errno = 0;
    double val = strtod(str, &endptr);

    if (errno != 0 || *endptr != '\0')
        error(EXIT_FAILURE, 0, _("invalid number: %s"), str);

    return val;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    static struct option long_options[] = {
        { "help", no_argument, NULL, 'h' },
        { "version", no_argument, NULL, 'v' },
        { 0, 0, 0, 0 }
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "hv", long_options, NULL)) != -1) {
        switch (opt) {
        case 'h':
            print_help();
            return EXIT_SUCCESS;
        case 'v':
            print_version();
            return EXIT_SUCCESS;
        default:
            fprintf(stderr, _("Try '%s --help' for more information.\n"),
                    PROGRAM_NAME);
            return EXIT_FAILURE;
        }
    }

    /* Functionality starts here */

    double sum = 0.0;

    if (optind < argc) {
        for (int i = optind; i < argc; i++)
            sum += parse_number(argv[i]);
    } else {
        /* check if stdin is a terminal */
        if (isatty(fileno(stdin))) {
            fprintf(stderr, "%s: missing operand\n", PROGRAM_NAME);
            fprintf(stderr, _("Try '%s --help' for more information.\n"),
                    PROGRAM_NAME);
            return EXIT_FAILURE;
        }
        /* Read from stdin */
        char *line = NULL;      // buffer ptr, initially NULL
        size_t len = 0;         // buffer size
        long nread;

        while ((nread = getline(&line, &len, stdin)) != -1) {
            char *ptr = line;

            while (1) {
                // skip whitespace
                while (isspace((unsigned char) *ptr))
                    ptr++;
                if (*ptr == '\0')
                    break;

                char *endptr;
                errno = 0;
                double val = strtod(ptr, &endptr);

                if (errno != 0 || ptr == endptr
                    || (!isspace((unsigned char) *endptr) && *endptr != '\0'))
                    error(EXIT_FAILURE, 0, _("invalid number in input: %s"),
                          ptr);

                sum += val;
                ptr = endptr;
            }
        }
        free(line);
    }

    printf("%g\n", sum);
    return EXIT_SUCCESS;
}
