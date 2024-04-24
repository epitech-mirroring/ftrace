/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** print_help.c
*/

#include "ftrace.h"

int print_help(int status)
{
    printf("USAGE: ./ftrace [-s] [-p <pid>|<command>]\n");
    printf("    -s: print detailled output\n");
    printf("    -p: attach to a running process\n");
    printf("    <command>: execute the command\n");
    return status;
}
