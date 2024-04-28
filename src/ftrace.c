/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** ftrace.c
*/

#include "ftrace.h"

void signalhandler(int signum)
{
    printf("Caught signal %d\n", signum);
    exit(84);
}

void init_elf(void)
{
    if (elf_version(EV_CURRENT) == EV_NONE) {
        fprintf(stderr,
            "Error initializing ELF library: %s\n", elf_errmsg(-1));
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{
    ftrace_struct_t ftrace_struct;

    signal(SIGSEGV, signalhandler);
    signal(SIGINT, signalhandler);
    signal(SIGFPE, signalhandler);
    signal(SIGILL, signalhandler);
    signal(SIGTERM, signalhandler);
    signal(SIGABRT, signalhandler);
    ftrace_struct.func_info = malloc(sizeof(func_info_t));
    for (int i = 0; i < argc; i++)
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
            return print_help(0);
    parse_cmd(argv, &ftrace_struct);
    init_elf();
    list_elf_symbols(ftrace_struct.given_cmd.args[0], ftrace_struct.func_info);
    list_functions(ftrace_struct.func_info);
    return execute_command(&ftrace_struct);
}
