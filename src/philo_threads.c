/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:40 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/27 15:36:45 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

int	ft_create_threads(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_philos)
	{
		if (pthread_create(&env->philos[i].thread, NULL,
				ft_lifecycle, &env->philos[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(env->philos[i].thread, NULL);
			return (printf("Error: Creating philosophers %d\n", i + 1));
		}
		i++;
	}
	if (pthread_create(&env->thread, NULL, ft_monitoring, env) != 0)
	{
		while (--i >= 0)
			pthread_join(env->philos[i].thread, NULL);
		return (printf("Error: Creating monitoring thread.\n"));
	}
	while (--i >= 0)
		pthread_join(env->philos[i].thread, NULL);
	pthread_join(env->thread, NULL);
	return (0);
}
