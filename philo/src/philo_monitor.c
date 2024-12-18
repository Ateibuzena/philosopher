/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 00:52:32 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/18 02:01:38 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

static void	ft_check_deaths(t_env *env)
{
	int			i;
	long int	time;

	i = 0;
	time = ft_get_time() - env->start_time;
	while (i < env->num_philos)
	{
		pthread_mutex_lock(&env->philos->meal_lock);
		if ((time - env->philos[i].last_meal_time) > env->time_to_die)
		{
			pthread_mutex_unlock(&env->philos->meal_lock);
			usleep(100);
			ft_print("died", env, env->philos[i].id);
			pthread_mutex_lock(&env->simulation_lock);
			env->simulation_running = 0;
			pthread_mutex_unlock(&env->simulation_lock);
			return ;
		}
		pthread_mutex_unlock(&env->philos->meal_lock);
		i++;
	}
}

static void	ft_check_meals(t_env *env)
{
	int	i;
	int	all_ate_enough;

	all_ate_enough = 1;
	i = 0;
	while (i < env->num_philos)
	{
		if ((env->meals_required == -1)
			|| (env->philos[i].meals_eaten < env->meals_required))
		{
			all_ate_enough = 0;
			break ;
		}
		i++;
	}
	if (all_ate_enough)
	{
		pthread_mutex_lock(&env->simulation_lock);
		env->simulation_running = 0;
		pthread_mutex_unlock(&env->simulation_lock);
	}
}

void	*ft_monitoring(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	while (env->simulation_running)
	{
		ft_check_deaths(env);
		if (!env->simulation_running)
			return (NULL);
		ft_check_meals(env);
		usleep(500);
	}
	return (NULL);
}
