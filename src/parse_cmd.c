/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** parse_arg.c
*/

#include "ftrace.h"

void parse_cmd(int argc, char **argv, ftrace_struct_t *args)
{
    int opt;

    for (opt = 1; opt < argc; opt++) {
        if (argv[opt][0] != '-' && args->given_cmd.cmd == NULL) {
            args->given_cmd.cmd = argv[opt];
            args->given_cmd.args = &argv[opt];
        }
    }
}
