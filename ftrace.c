/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** ftrace.c
*/

#include "ftrace.h"

int attach_ptrace(ftrace_struct_t *args)
{
    if (ptrace(PTRACE_ATTACH, args->pid) == -1) {
        perror("ptrace attach");
        return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    ftrace_struct_t args;
    int check;

    args.pid_flag = 0;
    check = parse_arg(argc, argv, &args);
    if (check == 1)
        return 84;
    if (!args.pid_flag)
        return execute_command(&args);
    else
        return follow_pid(&args);
}
