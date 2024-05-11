/*
** EPITECH PROJECT, 2023
** Empire
** File description:
** empire
*/

#pragma once
#include "extern.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

typedef enum {
    THINK,
    EAT,
    SLEEP
} State;

typedef struct {
    int nbr_romans;
    int max_eats;
    int eat_count;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    State state;
} Roman;

int get_max_eats(char **argv);
int get_nbr_romans(char **argv);
void destroy_mutex(Roman *romans, int nbr_romans);
void *roman_thread(void *args);
void create_thread(int nbr_romans, pthread_t *threads, Roman *romans);
