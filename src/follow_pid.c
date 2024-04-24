/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** follow_pid.c
*/

#include "ftrace.h"

int follow_pid(ftrace_struct_t *args)
{
    int check = attach_ptrace(args);

    if (check == 1)
        return 84;
    waitpid(args->pid, &args->status, 0);
    check = main_loop(args);
    if (check == 1)
        return 84;
    ptrace(PTRACE_DETACH, args->pid, NULL, NULL);
    return 0;
}
