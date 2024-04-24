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

int parse_arg(int argc, char **argv, ftrace_struct_t *args)
{
    int opt;

    args->given_cmd.cmd = NULL;
    if (argc < 2)
        return print_help(1);
    for (opt = 1; opt < argc; opt++) {
        if (strcmp(argv[opt], "-p") == 0 && opt + 1 < argc) {
            args->pid = atoi(argv[opt + 1]);
            args->pid_flag = 1;
            return 0;
        }
        if (strcmp(argv[opt], "-s") == 0) {
            args->is_detailled = 1;
        }
    }
    parse_cmd(argc, argv, args);
    return args->given_cmd.cmd == NULL ? print_help(1) : 0;
}
