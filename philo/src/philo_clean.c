/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:32 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/18 02:41:36 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

void	ft_clean_up(t_env *env, int len)
{
	int	i;

	if (env->simulation_running)
	{
		pthread_mutex_lock(&env->simulation_lock);
		env->simulation_running = 0;
		pthread_mutex_unlock(&env->simulation_lock);
	}
	pthread_mutex_destroy(&env->print_lock);
	pthread_mutex_destroy(&env->simulation_lock);
	i = 0;
	while (i < env->num_philos && i < len)
	{
		pthread_mutex_destroy(&env->forks[i]);
		pthread_mutex_destroy(&env->philos[i].meal_lock);
		i++;
	}
	if (env->forks)
		free(env->forks);
	if (env->philos)
		free(env->philos);
	if (env)
		free(env);
}
