/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** print_syscall_info.c
*/

#include "ftrace.h"
#include "syscall.h"

void print_syscall_info_tree(struct user_regs_struct *regs)
{
    if (table[regs->orig_rax].nb_args == 5)
        printf("0x%llx, 0x%llx, 0x%llx, 0x%llx, 0x%llx", regs->rdi,
            regs->rsi, regs->rdx, regs->r10, regs->r8);
    else if (table[regs->orig_rax].nb_args == 6)
        printf("0x%llx, 0x%llx, 0x%llx, 0x%llx, 0x%llx, 0x%llx",
            regs->rdi, regs->rsi, regs->rdx, regs->r10, regs->r8, regs->r9);
    else
        printf("Unknown number of arguments");
}

void print_syscall_info_two(struct user_regs_struct *regs)
{
    if (table[regs->orig_rax].nb_args == 3)
        printf("0x%lld, 0x%llx, 0x%llx", regs->rdi, regs->rsi, regs->rdx);
    else if (table[regs->orig_rax].nb_args == 4)
        printf("0x%llx, 0x%llx, 0x%llx, 0x%llx",
            regs->rdi, regs->rsi, regs->rdx, regs->r10);
    else
        print_syscall_info_tree(regs);
}

void print_syscall_info(struct user_regs_struct *regs)
{
    printf("%s(", table[regs->orig_rax].name);
    if (table[regs->orig_rax].nb_args == 1)
        printf("%c", (char)regs->rdi);
    else if (table[regs->orig_rax].nb_args == 2)
        printf("0x%llx, 0x%llx", regs->rdi, regs->rsi);
    else
        print_syscall_info_two(regs);
    printf(")\t = %lld\n", regs->rax);
}
