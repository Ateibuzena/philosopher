/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 00:52:32 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/20 23:32:11 by azubieta         ###   ########.fr       */
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
		pthread_mutex_lock(&env->simulation_lock);
		pthread_mutex_lock(&env->philos->mutex_philo);
		if ((time - env->philos[i].last_meal_time) > env->time_to_die)
		{
			pthread_mutex_unlock(&env->philos->mutex_philo);
			pthread_mutex_unlock(&env->simulation_lock);
			usleep(100);
			ft_print("died", env, env->philos[i].id);
			pthread_mutex_lock(&env->simulation_lock);
			env->simulation_running = 0;
			pthread_mutex_unlock(&env->simulation_lock);
			return ;
		}
		pthread_mutex_unlock(&env->philos->mutex_philo);
		pthread_mutex_unlock(&env->simulation_lock);
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
		pthread_mutex_lock(&env->simulation_lock);
		//pthread_mutex_lock(&env->philos[i].mutex_philo);
		if ((env->meals_required == -1)
			|| (env->philos[i].meals_eaten < env->meals_required))
		{
			//pthread_mutex_unlock(&env->philos[i].mutex_philo);
			all_ate_enough = 0;
			pthread_mutex_unlock(&env->simulation_lock);
			break ;
		}
		//pthread_mutex_unlock(&env->philos[i].mutex_philo);
		pthread_mutex_unlock(&env->simulation_lock);
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
	t_env		*env;
	long int	simulation_running;

	env = (t_env *)arg;
	pthread_mutex_lock(&env->simulation_lock);
	simulation_running = env->simulation_running;
	pthread_mutex_unlock(&env->simulation_lock);
	
	while (simulation_running)
	{
		ft_check_deaths(env);
		pthread_mutex_lock(&env->simulation_lock);
		simulation_running = env->simulation_running;
		pthread_mutex_unlock(&env->simulation_lock);
		if (!simulation_running)
			return (NULL);
		ft_check_meals(env);
		usleep(500);
		pthread_mutex_lock(&env->simulation_lock);
		simulation_running = env->simulation_running;
		pthread_mutex_unlock(&env->simulation_lock);
	}
	return (NULL);
}
