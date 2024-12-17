/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:44 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/17 20:50:09 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

static void ft_thinking(t_philo *philosopher)
{
    ft_print("is thinking", philosopher->env, philosopher->id);
}

static void ft_eating(t_philo *philosopher)
{
    ft_print("is eating", philosopher->env, philosopher->id);
    pthread_mutex_lock(&philosopher->meal_lock);
    philosopher->last_meal_time = ft_get_time() - philosopher->env->start_time;
    philosopher->meals_eaten++;
    pthread_mutex_unlock(&philosopher->meal_lock);
    usleep(philosopher->env->time_to_eat * 1000);
}

static void ft_sleeping(t_philo *philosopher)
{
    ft_print("is sleeping", philosopher->env, philosopher->id);
    usleep(philosopher->env->time_to_sleep * 1000); // El temps que el filòsof passa dor0mint
}
static void ft_take_forks(t_philo *philosopher)
{
    if (philosopher->id % 2 != 0)
    {
        if (pthread_mutex_lock(&philosopher->env->forks[philosopher->left_fork]) == 0)
        {
            ft_print("has taken the left fork", philosopher->env, philosopher->id);
            if (pthread_mutex_lock(&philosopher->env->forks[philosopher->right_fork]) == 0)
            {
                ft_print("has taken the right fork", philosopher->env, philosopher->id);
                ft_eating(philosopher);
                ft_print("has dropped both forks.", philosopher->env, philosopher->id);
                pthread_mutex_unlock(&philosopher->env->forks[philosopher->right_fork]);
                pthread_mutex_unlock(&philosopher->env->forks[philosopher->left_fork]);
            }
            else
            {
                ft_print("has NOT taken the right fork.", philosopher->env, philosopher->id);
                pthread_mutex_unlock(&philosopher->env->forks[philosopher->left_fork]);
            }
        }
    }
    else
    {
        if (pthread_mutex_lock(&philosopher->env->forks[philosopher->right_fork]) == 0)
        {
            ft_print("has taken the right fork", philosopher->env, philosopher->id);
            if (pthread_mutex_lock(&philosopher->env->forks[philosopher->left_fork]) == 0)
            {
                ft_print("has taken the left fork", philosopher->env, philosopher->id);
                ft_eating(philosopher);
                ft_print("has dropped both forks.", philosopher->env, philosopher->id);
                pthread_mutex_unlock(&philosopher->env->forks[philosopher->right_fork]);
                pthread_mutex_unlock(&philosopher->env->forks[philosopher->left_fork]);
            }
            else
            {
                ft_print("has NOT taken the left fork.", philosopher->env, philosopher->id);
                pthread_mutex_unlock(&philosopher->env->forks[philosopher->right_fork]);
            }
        }
    }
}

void *ft_lifecycle(void *arg)
{
    t_philo *philosopher;
    
    philosopher = (t_philo *)arg;
    if (philosopher->id % 2 == 0 && philosopher->id != 2)
        usleep(1);
    while (philosopher->env->simulation_running)
    {
        ft_take_forks(philosopher);
        if (!philosopher->env->simulation_running)
            break ;
        ft_sleeping(philosopher);
        if (!philosopher->env->simulation_running)
            break ;
        ft_thinking(philosopher);
        usleep(1);
    }
    return (NULL);
}
