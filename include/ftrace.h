/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** ftrace.h
*/

#pragma once

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>
#include <elf.h>
#include <fcntl.h>
#include <libelf.h>
#include <gelf.h>
#include <signal.h>

#define SYSCALL_CODE 0x80

typedef struct syscall_s {
    int id;
    char *name;
    int nb_args;
    int return_type;
    int arg1;
    int arg2;
    int arg3;
    int arg4;
    int arg5;
    int arg6;
} syscall_t;

typedef struct command_s {
    char *cmd;
    char **args;
} command_t;

typedef struct elf_symbol_struct_s {
    int fd;
    Elf *elf;
    Elf_Scn *scn;
    GElf_Shdr shdr;
} elf_symbol_struct_t;

typedef struct func_info_s {
    unsigned long address;
    char *name;
    struct func_info_s *next;
} func_info_t;

typedef struct ftrace_struct_s {
    int status;
    pid_t pid;
    command_t given_cmd;
    func_info_t *func_info;
} ftrace_struct_t;


int attach_ptrace(ftrace_struct_t *args);
int main(int argc, char **argv);
int print_help(int status);
int execute_command(ftrace_struct_t *args);
void print_syscall_info_tree(struct user_regs_struct *regs);
void print_syscall_info_two(struct user_regs_struct *regs);
void print_syscall_info(struct user_regs_struct *regs);
void my_elf_reader(elf_symbol_struct_t *elf_struct);
int ptrace_getregs(ftrace_struct_t *args, struct user_regs_struct *regs);
int ptrace_singlestep(ftrace_struct_t *args);
int main_loop(ftrace_struct_t *args);
void parse_cmd(char **argv, ftrace_struct_t *args);
int follow_pid(ftrace_struct_t *args);
void init_elf(void);
void add_function(unsigned long address, char *name, func_info_t *func_list);
char *find_function_name(unsigned long address, func_info_t *func_list);
int my_file_opener(const char *filepath);
void list_elf_symbols(const char *filepath, func_info_t *func_list);
void list_functions(func_info_t *func_list);
