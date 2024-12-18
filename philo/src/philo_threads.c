/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:40 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/18 01:25:38 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

static int	ft_join_threads(t_env *env)
{
	int	i;

	if (pthread_join(env->thread, NULL) != 0)
	{
		ft_clean_up(env);
		return (1);
	}
	i = 0;
	while (i < env->num_philos)
	{
		if (pthread_detach(env->philos[i].thread) != 0)
		{
			ft_clean_up(env);
			return (1);
		}
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
			printf("Error creant el filòsof %d\n", i + 1);
			return (1);
		}
		i++;
	}
	if (pthread_create(&env->thread, NULL, ft_monitoring, env) != 0)
	{
		printf("Error al crear el fil de monitorització.\n");
		ft_clean_up(env);
		return (1);
	}
	return (ft_join_threads(env));
}
