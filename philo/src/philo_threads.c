/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:40 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/20 22:18:48 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

int	ft_join_threads(t_env *env)
{
	//int	i;
	(void)env;
	/*i = 0;
	while (i < env->num_philos)
	{
		if (pthread_detach(env->philos[i].thread) != 0)
			break ;
		i++;
	}
	if (pthread_join(env->thread, NULL) != 0)
		return (1);*/
	return (0);
}

int	ft_create_threads(t_env *env)
{
	int	i;
	int	j;

	i = 0;
	while (i < env->num_philos)
	{
		if (pthread_create(&env->philos[i].thread, NULL,
				ft_lifecycle, &env->philos[i]) != 0)
		{
			/*pthread_mutex_lock(&env->simulation_lock);
			env->simulation_running = 0;
			pthread_mutex_unlock(&env->simulation_lock);*/
			printf("Error: Creating philosophers %d\n", i + 1);
			j = i;
			while (--i >= 0)
            	pthread_detach(env->philos[i].thread);
			return (j);
		}
		i++;
	}
	if (pthread_create(&env->thread, NULL, ft_monitoring, env) != 0)
	{
		/*pthread_mutex_lock(&env->simulation_lock);
		env->simulation_running = 0;
		pthread_mutex_unlock(&env->simulation_lock);*/
		printf("Error: Creating monitoring thread.\n");
		while (--i >= 0)
        {
			pthread_detach(env->philos[i].thread);
		}
		return (env->num_philos);
	}
	while (--i >= 0)
	{
        pthread_detach(env->philos[i].thread);
	}
	pthread_join(env->thread, NULL);
	return (0);
}
