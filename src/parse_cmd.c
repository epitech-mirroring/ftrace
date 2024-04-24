/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** parse_arg.c
*/

#include "ftrace.h"

void parse_cmd(char **argv, ftrace_struct_t *args)
{
    args->given_cmd.cmd = argv[1];
    args->given_cmd.args = &argv[1];
}
