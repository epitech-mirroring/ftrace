/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** print_syscall_info.c
*/

#include "ftrace.h"
#include "syscall.h"

static void print_reg(unsigned long long int reg)
{
    printf("0x%llx", reg);
}

void print_syscall_info(struct user_regs_struct *regs)
{
    unsigned long long int regs_table[] = {
        regs->rdi, regs->rsi, regs->rdx, regs->r10, regs->r8, regs->r9
    };

    printf("%s(", table[regs->orig_rax].name);
    for (int i = 0; i < table[regs->orig_rax].nb_args; i++) {
        if (i != 0)
            printf(", ");
        print_reg(regs_table[i]);
    }
    printf(")\t = %lld\n", regs->rax);
}
