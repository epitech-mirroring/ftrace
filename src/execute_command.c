/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** execute_command.c
*/

#include "ftrace.h"

int execute_command(ftrace_struct_t *args)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        return 1;
    }
    args->pid = pid;
    if (pid == 0) {
        execvp(args->given_cmd.cmd, args->given_cmd.args);
        perror("execvp failed");
        return 1;
    } else {
        return follow_pid(args);
    }
}
