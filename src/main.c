/*
** EPITECH PROJECT, 2023
** Empire
** File description:
** main
*/

#include "../include/empire.h"

void thread(Roman *roman)
{
    if (roman->state == THINK) {
        lempire_take_fork(roman->left_fork);
        lempire_take_fork(roman->right_fork);
        lempire_eat();
        lempire_release_fork(roman->right_fork);
        lempire_release_fork(roman->left_fork);
        roman->eat_count++;
        roman->state = EAT;
    }
    if (roman->state == SLEEP) {
        lempire_take_fork(roman->left_fork);
        lempire_think();
        lempire_release_fork(roman->left_fork);
        roman->state = THINK;
    }
    if (roman->state == EAT) {
        lempire_sleep();
        roman->state = SLEEP;
    }
}

void *roman_thread(void *args)
{
    Roman *roman = (Roman *)args;
    roman->state = EAT;
    while (roman->eat_count != roman->max_eats) {
        thread(roman);
    }
    return NULL;
}

void free_memory(int nbr_romans, Roman *romans, pthread_t *threads,
pthread_mutex_t *forks)
{
    destroy_mutex(romans, nbr_romans);
    free(romans);
    free(threads);
    free(forks);
}

void empire(int max_eats, int nbr_romans, int argc, char **argv)
{
    Roman *romans = (Roman *)malloc(sizeof(Roman) * nbr_romans);
    pthread_mutex_t *forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
    * nbr_romans);
    for (int i = 0; i != nbr_romans; i++) {
        romans[i].eat_count = 0;
        romans[i].max_eats = max_eats;
        romans[i].nbr_romans = nbr_romans;
        romans[i].left_fork = &forks[i];
        romans[i].right_fork = &forks[(i + 1) % nbr_romans];
    }
    pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t) * nbr_romans);
    RCFStartup(argc, argv);
    create_thread(nbr_romans, threads, romans);
    RCFCleanup();
    free_memory(nbr_romans, romans, threads, forks);
}

int main(int argc, char **argv)
{
    if (argc != 5)
        return (84);
    int nbr_romans = get_nbr_romans(argv);
    int max_eats = get_max_eats(argv);
    if (nbr_romans < 0 || max_eats < 0)
        return (84);
    empire(max_eats, nbr_romans, argc, argv);
    return (0);
}
