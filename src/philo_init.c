/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:37 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/27 13:37:23 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

static int	ft_init_philosophers(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_philos)
	{
		env->philos[i].id = i + 1;
		env->philos[i].left_fork = env->philos[i].id - 1;
		env->philos[i].right_fork = (env->philos[i].id) % env->num_philos;
		env->philos[i].last_meal_time = 0;
		env->philos[i].meals_eaten = 0;
		env->philos[i].env = env;
		i++;
	}
	env->simulation_running = 1;
	return (0);
}

int	ft_init_environment(t_env *env, int argc, char **argv)
{
	int	i;

	env->num_philos = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	env->start_time = ft_get_time();
	if (argc == 6)
		env->meals_required = ft_atoi(argv[5]);
	else
		env->meals_required = -1;
	env->forks = malloc(env->num_philos * sizeof(pthread_mutex_t));
	if (!env->forks)
		return (printf("Error: Creating forks"));
	i = -1;
	while (++i < env->num_philos)
		if (pthread_mutex_init(&env->forks[i], NULL) != 0)
			return (printf("Error: Initializing forks' mutexes\n"));
	if (pthread_mutex_init(&env->simulation_lock, NULL) != 0)
		return (printf("Error: Initializing print and simulation mutexes\n"));
	env->philos = malloc(env->num_philos * sizeof(t_philo));
	if (!env->philos)
		return (printf("Error: Creating philos"));
	return (ft_init_philosophers(env));
}
