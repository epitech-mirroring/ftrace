/*
** EPITECH PROJECT, 2024
** B-PSU-400-NAN-4-1-ftrace-axel.eckenberg
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "ftrace.h"
#include "../syscall.h"

static void print_reg(unsigned long long int reg, int type)
{
    if (type == NUM)
        printf("%lld", reg);
    else if (type == UNSIGNED)
        printf("%llu", reg);
    else
        printf("0x%llx", reg);
}

void print_syscall_info_detailled(struct user_regs_struct *regs)
{
    unsigned long long int regs_table[] = {
        regs->rdi, regs->rsi, regs->rdx, regs->r10, regs->r8, regs->r9
    };
    int args_table[] = {
        table[regs->orig_rax].arg1, table[regs->orig_rax].arg2,
        table[regs->orig_rax].arg3, table[regs->orig_rax].arg4,
        table[regs->orig_rax].arg5, table[regs->orig_rax].arg6
    };

    printf("%s(", table[regs->orig_rax].name);
    for (int i = 0; i < table[regs->orig_rax].nb_args; i++) {
        if (i != 0)
            printf(", ");
        print_reg(regs_table[i], args_table[i]);
    }
    printf(")\t = ");
    print_reg(regs->rax, table[regs->orig_rax].return_type);
    printf("\n");
}
