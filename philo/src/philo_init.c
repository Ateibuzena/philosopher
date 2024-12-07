/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:37 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/06 20:58:01 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

// Funció per inicialitzar l'entorn
int ft_init_environment(t_env *env, int argc, char **argv)
{
	int i;

	i = 0;
    env->num_philos = ft_atoi(argv[1]);
    env->time_to_die = ft_atoi(argv[2]);
    env->time_to_eat = ft_atoi(argv[3]);
    env->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        env->meals_required = ft_atoi(argv[5]);
	else
        env->meals_required = -1;
    env->forks = malloc(env->num_philos * sizeof(pthread_mutex_t));
    if (!env->forks)
    {
        printf("Malloc error in forks");
        return (1);
    }
    i = 0;
    while (i < env->num_philos)
	{
        if (pthread_mutex_init(&env->forks[i], NULL) != 0)
		{
            printf("Error inicialitzant els mutex dels tenedors\n");
            return (1);
        }
        i++;
    }
    if (pthread_mutex_init(&env->print_lock, NULL) != 0)
	{
        printf("Error inicialitzant el mutex de la impressió\n");
        return (1);
    }
    env->philos = malloc(env->num_philos * sizeof(t_philo));
    if (!env->philos)
    {
        printf("Malloc error in philos");
        return (1);
    }
    i = 0;
	while (i < env->num_philos)
	{
        env->philos[i].id = i + 1;
        env->philos[i].left_fork = i;
        env->philos[i].right_fork = (i + 1) % env->num_philos;
        env->philos[i].last_meal_time = 0;
        env->philos[i].meals_eaten = 0;
        env->philos[i].env = env;
		i++;
    }
    env->simulation_running = 1;
    return (0);
}
