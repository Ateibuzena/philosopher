/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 00:52:32 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/27 15:33:56 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

static void	ft_check_deaths(t_env *env)
{
	int			i;
	long int	time;

	i = 0;
	while (i < env->num_philos)
	{
		pthread_mutex_lock(&env->simulation_lock);
		time = ft_get_time() - env->start_time;
		if ((time - env->philos[i].last_meal_time) > env->time_to_die)
		{
			pthread_mutex_unlock(&env->simulation_lock);
			ft_print("died", env, env->philos[i].id);
			pthread_mutex_lock(&env->simulation_lock);
			env->simulation_running = 0;
			pthread_mutex_unlock(&env->simulation_lock);
			return ;
		}
		pthread_mutex_unlock(&env->simulation_lock);
		i++;
	}
}

static int	ft_check_meals(t_env *env)
{
	int	i;
	int	all_ate_enough;

	all_ate_enough = 1;
	i = 0;
	while (i < env->num_philos)
	{
		pthread_mutex_lock(&env->simulation_lock);
		if ((env->meals_required == -1)
			|| (env->philos[i].meals_eaten < env->meals_required))
		{
			all_ate_enough = 0;
			pthread_mutex_unlock(&env->simulation_lock);
			break ;
		}
		pthread_mutex_unlock(&env->simulation_lock);
		i++;
	}
	return (all_ate_enough);
}

void	*ft_monitoring(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	while (1)
	{
		if (ft_simulation_lock(env))
			return (NULL);
		if (ft_check_meals(env))
		{
			pthread_mutex_lock(&env->simulation_lock);
			env->simulation_running = 0;
			pthread_mutex_unlock(&env->simulation_lock);
			return (NULL);
		}
		if (ft_simulation_lock(env))
			return (NULL);
		ft_check_deaths(env);
		usleep(100);
	}
	return (NULL);
}

/*printf("%ld %d All philosophers have eaten",
				ft_get_time() - env->start_time, 0);*/