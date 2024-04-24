/*
** EPITECH PROJECT, 2024
** ftrace
** File description:
** test
*/

int main(void);
void toto(void);
void tutu(void);
int sleep(int seconds);
int getpid(void);

#include <stdio.h>

int main(void)
{
    while (1) {
        printf("i am in main()\n");
        toto();
        tutu();
        sleep(1);
    }
    return (0);
}

void toto(void)
{
    printf("i am in toto()\n");
}

void tutu(void)
{
    printf("i am in tutu()\n");
}
