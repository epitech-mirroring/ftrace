/*
** EPITECH PROJECT, 2024
** mirror_ftrace
** File description:
** utils
*/

#include "ftrace.h"

void add_function(unsigned long address, char *name, func_info_t *func_list)
{
    func_info_t *new_func = (func_info_t *)malloc(sizeof(func_info_t));
    func_info_t *current = func_list;

    new_func->address = address;
    new_func->name = name;
    new_func->next = NULL;
    if (func_list == NULL) {
        func_list = new_func;
        return;
    }
    for (; current->next != NULL; current = current->next);
    current->next = new_func;
}

char *find_function_name(unsigned long address, func_info_t *func_list)
{
    func_info_t *current = func_list;

    for (; current != NULL; current = current->next) {
        if (current->address == address) {
            return current->name;
        }
    }
    return NULL;
}

int my_file_opener(const char *filepath)
{
    int fd = open(filepath, O_RDONLY);

    if (fd < 0) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    return fd;
}

void my_elf_reader(elf_symbol_struct_t *elf_struct)
{
    elf_struct->elf = elf_begin(elf_struct->fd, ELF_C_READ, NULL);
    if (!elf_struct->elf) {
        fprintf(stderr, "Failed to read ELF file: %s\n", elf_errmsg(-1));
        close(elf_struct->fd);
        exit(EXIT_FAILURE);
    }
}

void list_functions(func_info_t *func_list)
{
    func_info_t *current = func_list;

    for (; current != NULL; current = current->next) {
        printf("--> Function: %s at address %lx\n",
            current->name, current->address);
    }
}
