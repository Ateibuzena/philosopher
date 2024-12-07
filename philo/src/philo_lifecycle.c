/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:44 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/06 21:05:34 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

static void ft_thinking(t_philo *philosopher)
{
    printf("Filòsof %d està pensant.\n", philosopher->id);
    usleep(philosopher->env->time_to_sleep * 1000); // El temps que el filòsof passa pensant
}

static void ft_sleeping(t_philo *philosopher)
{
    printf("Filòsof %d està dormint.\n", philosopher->id);
    usleep(philosopher->env->time_to_sleep * 1000); // El temps que el filòsof passa dormint
}

static void ft_take_forks(t_philo *philosopher)
{
    // Agafa el tenedor esquerre
    pthread_mutex_lock(&philosopher->env->forks[philosopher->left_fork]);
    printf("Filòsof %d ha agafat el tenedor esquerre.\n", philosopher->id);

    // Agafa el tenedor dret
    pthread_mutex_lock(&philosopher->env->forks[philosopher->right_fork]);
    printf("Filòsof %d ha agafat el tenedor dret.\n", philosopher->id);
}

static void ft_eating(t_philo *philosopher)
{
    printf("Filòsof %d està menjant.\n", philosopher->id);

    // Actualitzar l'últim temps de menjada i incrementar les menjades
    philosopher->last_meal_time = ft_get_time();
    philosopher->meals_eaten++;

    // El temps que el filòsof menja
    usleep(philosopher->env->time_to_eat * 1000);
}

void *ft_lifecycle(void *arg)
{
    t_philo *philosopher;
    
    philosopher = (t_philo *)arg;
    printf("Filòsof %d ha començat.\n", philosopher->id);
    while (philosopher->env->simulation_running)
    {
        // Filòsof pensant
        ft_thinking(philosopher);

        // Filòsof agafant els tenedors
        ft_take_forks(philosopher);

        // Filòsof menjant
        ft_eating(philosopher);

        // Filòsof deixant els tenedors
        pthread_mutex_unlock(&philosopher->env->forks[philosopher->left_fork]);
        pthread_mutex_unlock(&philosopher->env->forks[philosopher->right_fork]);
        printf("Filòsof %d ha deixat els tenedors.\n", philosopher->id);

        // Filòsof dormint
        ft_sleeping(philosopher);
    }

    return (NULL);
}
