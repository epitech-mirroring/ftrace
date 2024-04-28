/*
** EPITECH PROJECT, 2024
** mirror_ftrace
** File description:
** map_function_adress
*/

#include "ftrace.h"

void get_elf_data(elf_symbol_struct_t *elf_struct, func_info_t *func_list)
{
    int count;
    Elf_Data *data;
    GElf_Sym sym;
    char *name;

    data = elf_getdata(elf_struct->scn, NULL);
    count = elf_struct->shdr.sh_size / elf_struct->shdr.sh_entsize;
    for (int i = 0; i < count; ++i) {
        if (gelf_getsym(data, i, &sym) != &sym)
            continue;
        name = elf_strptr(elf_struct->elf,
            elf_struct->shdr.sh_link, sym.st_name);
        if (name && *name && GELF_ST_TYPE(sym.st_info) == STT_FUNC) {
            add_function((unsigned long)sym.st_value, name, func_list);
        }
    }
}

void list_elf_symbols(const char *filepath, func_info_t *func_list)
{
    elf_symbol_struct_t elf_struct;

    elf_struct.fd = my_file_opener(filepath);
    my_elf_reader(&elf_struct);
    elf_struct.scn = elf_nextscn(elf_struct.elf, elf_struct.scn);
    while (elf_struct.scn != NULL) {
        if (gelf_getshdr(elf_struct.scn, &elf_struct.shdr) != &elf_struct.shdr)
            continue;
        if (elf_struct.shdr.sh_type == SHT_SYMTAB ||
            elf_struct.shdr.sh_type == SHT_DYNSYM) {
            get_elf_data(&elf_struct, func_list);
        }
        elf_struct.scn = elf_nextscn(elf_struct.elf, elf_struct.scn);
    }
    elf_end(elf_struct.elf);
    close(elf_struct.fd);
}
