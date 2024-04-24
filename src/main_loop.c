/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** main_loop.c
*/

#include "ftrace.h"

int ptrace_getregs(ftrace_struct_t *args, struct user_regs_struct *regs)
{
    if (ptrace(PTRACE_GETREGS, args->pid, NULL, regs) == -1) {
        perror("ptrace getregs");
        return 1;
    }
    return 0;
}

int ptrace_singlestep(ftrace_struct_t *args)
{
    if (ptrace(PTRACE_SINGLESTEP, args->pid, NULL, NULL) == -1) {
        perror("ptrace singlestep");
        return 1;
    }
    return 0;
}

int main_loop(ftrace_struct_t *args)
{
    struct user_regs_struct regs;
    int status;

    while (!WIFEXITED(args->status)) {
        status = ptrace_getregs(args, &regs);
        if (status == 1)
            return 1;
        if ((int)regs.orig_rax >= 0)
            print_syscall_info(&regs);
        status = ptrace_singlestep(args);
        if (status == 1)
            return 1;
        waitpid(args->pid, &args->status, 0);
    }
    return 0;
}
