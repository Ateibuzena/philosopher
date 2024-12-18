/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:40 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/18 02:39:28 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

static int	ft_join_threads(t_env *env)
{
	int	i;

	if (pthread_join(env->thread, NULL) != 0)
		return (1);
	i = 0;
	while (i < env->num_philos)
	{
		if (pthread_detach(env->philos[i].thread) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_create_threads(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_philos)
	{
		if (pthread_create(&env->philos[i].thread, NULL,
				ft_lifecycle, &env->philos[i]) != 0)
		{
			pthread_mutex_lock(&env->simulation_lock);
			env->simulation_running = 0;
			pthread_mutex_unlock(&env->simulation_lock);
			printf("Error: creating philosopher %d\n", i + 1);
			return (i + 1);
		}
		i++;
	}
	if (pthread_create(&env->thread, NULL, ft_monitoring, env) != 0)
	{
		pthread_mutex_lock(&env->simulation_lock);
		env->simulation_running = 0;
		pthread_mutex_unlock(&env->simulation_lock);
		printf("Error: creating the monitoring thread.\n");
		return (env->num_philos);
	}
	return (ft_join_threads(env));
}
