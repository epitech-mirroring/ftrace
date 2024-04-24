/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** ftrace.c
*/

#include "ftrace.h"

int main(int argc, char **argv)
{
    ftrace_struct_t args;

    for (int i = 0; i < argc; i++)
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
            return print_help(0);
    parse_cmd(argv, &args);
    return execute_command(&args);
}
