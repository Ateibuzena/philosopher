/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:44 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/07 13:02:08 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

static void ft_thinking(t_philo *philosopher)
{
    long int    time;
    
    time = ft_get_time() - philosopher->env->start_time;
    printf("[%ld] %d is thinking.\n", time, philosopher->id);
    usleep(philosopher->env->time_to_sleep * 1000); // El temps que el filòsof passa pensant
}

static void ft_sleeping(t_philo *philosopher)
{
    long int    time;

    time = ft_get_time() - philosopher->env->start_time;
    printf("[%ld] %d is sleeping.\n", time, philosopher->id);
    usleep(philosopher->env->time_to_sleep * 1000); // El temps que el filòsof passa dormint
}

static void ft_take_forks(t_philo *philosopher)
{
    long int    time;
    time = ft_get_time() - philosopher->env->start_time;
    // Agafa el tenedor esquerre
    if (philosopher->id % 2 == 0)
    {
        pthread_mutex_lock(&philosopher->env->forks[philosopher->right_fork]);
        printf("[%ld] %d has taken the right fork.\n", time, philosopher->id);
        pthread_mutex_unlock(&philosopher->env->forks[philosopher->right_fork]);
        pthread_mutex_lock(&philosopher->env->forks[philosopher->left_fork]);
        printf("[%ld] %d has taken the left fork.\n", time, philosopher->id);
        pthread_mutex_unlock(&philosopher->env->forks[philosopher->left_fork]);
    }
    else
    {
    //time = ft_get_time() - philosopher->env->start_time;
    pthread_mutex_lock(&philosopher->env->forks[philosopher->left_fork]);
    printf("[%ld] %d has taken the left fork.\n", time, philosopher->id);
    pthread_mutex_unlock(&philosopher->env->forks[philosopher->left_fork]);
    //time = ft_get_time() - philosopher->env->start_time;
    // Agafa el tenedor dret
    pthread_mutex_lock(&philosopher->env->forks[philosopher->right_fork]);
    printf("[%ld] %d has taken the right fork.\n", time, philosopher->id);
    pthread_mutex_unlock(&philosopher->env->forks[philosopher->right_fork]);
    }
}

static void ft_eating(t_philo *philosopher)
{
    long int    time;
    time = ft_get_time() - philosopher->env->start_time;
    printf("[%ld] %d is eating.\n", time, philosopher->id);

    // Bloqueig per actualitzar last_meal_time de forma segura
    pthread_mutex_lock(&philosopher->meal_lock);
    philosopher->last_meal_time = time;
    philosopher->meals_eaten++;
    pthread_mutex_unlock(&philosopher->meal_lock);

    // El temps que el filòsof menja
    usleep(philosopher->env->time_to_eat * 1000);
}

void *ft_lifecycle(void *arg)
{
    t_philo *philosopher;
    
    philosopher = (t_philo *)arg;
    //printf("%d has started.\n", philosopher->id);
    while (philosopher->env->simulation_running)
    {
        // Filòsof pensant
        ft_thinking(philosopher);
        if (!philosopher->env->simulation_running)
            break ;
        //pthread_mutex_lock(&philosopher->env->forks[philosopher->left_fork]);
        //pthread_mutex_lock(&philosopher->env->forks[philosopher->right_fork]);
        // Filòsof agafant els tenedors
        ft_take_forks(philosopher);
        if (!philosopher->env->simulation_running)
            break ;
        // Filòsof menjant
        ft_eating(philosopher);
        if (!philosopher->env->simulation_running)
            break ;
        // Filòsof deixant els tenedors
        //pthread_mutex_unlock(&philosopher->env->forks[philosopher->left_fork]);
        //pthread_mutex_unlock(&philosopher->env->forks[philosopher->right_fork]);
        if (!philosopher->env->simulation_running)
            break ;
        //printf("%d has put down the forks.\n", philosopher->id);

        // Filòsof dormint
        ft_sleeping(philosopher);
    }

    return (NULL);
}
