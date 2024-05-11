/*
** EPITECH PROJECT, 2023
** Empire
** File description:
** empire
*/

#include "../include/empire.h"

int get_nbr_romans(char **argv)
{
    for (int i = 0; argv[i]; i++) {
        if (strcmp(argv[i], "-p") == 0)
            return (atoi(argv[i + 1]));
    }
    return (0);
}

int get_max_eats(char **argv)
{
    for (int i = 0; argv[i]; i++) {
        if (strcmp(argv[i], "-e") == 0)
            return (atoi(argv[i + 1]));
    }
    return (0);
}

void destroy_mutex(Roman *romans, int nbr_romans)
{
    for (int i = 0; i != nbr_romans; i++) {
        pthread_mutex_destroy(romans[i].left_fork);
        pthread_mutex_destroy(romans[i].right_fork);
    }
}

void create_thread(int nbr_romans, pthread_t *threads, Roman *romans)
{
    for (int i = 0; i != nbr_romans; i++) {
        if (pthread_create(&threads[i], NULL, roman_thread, &romans[i]) != 0)
            exit(84);
    }
    for (int i = 0; i != nbr_romans; i++) {
        if (pthread_join(threads[i], NULL) != 0)
            exit(84);
    }
}
