/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:32 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/20 16:10:43 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

void	ft_clean_up(t_env *env, int len)
{
	int	i;

	if (env->simulation_running)
		env->simulation_running = 0;
	i = 1;
	while (i < env->num_philos && i < len)
	{
		//pthread_mutex_destroy(&env->forks[i]);
		pthread_mutex_destroy(&env->philos[i].mutex_philo);
		i++;
	}
	if (env->forks)
		free(env->forks);
	if (env->philos)
		free(env->philos);
	if (env)
		free(env);
	pthread_mutex_destroy(&env->simulation_lock);
}
