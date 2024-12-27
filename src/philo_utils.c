/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:49 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/27 15:30:37 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

int	ft_simulation_lock(t_env *env)
{
	pthread_mutex_lock(&env->simulation_lock);
	if (!env->simulation_running)
	{
		pthread_mutex_unlock(&env->simulation_lock);
		return (1);
	}
	pthread_mutex_unlock(&env->simulation_lock);
	return (0);
}

void	ft_msleep(time_t time)
{
	time_t	current_time;

	current_time = ft_get_time();
	while (ft_get_time() - current_time < time)
		usleep(time * 10);
}

void	ft_print(char *str, t_env *env, int i)
{
	t_color	color;

	pthread_mutex_lock(&env->simulation_lock);
	if (!env->simulation_running)
	{
		pthread_mutex_unlock(&env->simulation_lock);
		return ;
	}
	pthread_mutex_unlock(&env->simulation_lock);
	color = ft_generate_color(i);
	pthread_mutex_lock(&env->simulation_lock);
	if (env->simulation_running)
	{
		printf("\033[38;2;%d;%d;%dm%ld %ld %s\033[0m\n",
			color.r, color.g, color.b,
			ft_get_time() - env->start_time,
			env->philos[i - 1].id,
			str);
	}
	pthread_mutex_unlock(&env->simulation_lock);
}

long int	ft_get_time(void)
{
	long int		time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

t_color	ft_generate_color(int i)
{
	t_color	color;

	color.r = (i * 73) % 256;
	color.g = (i * 131) % 256;
	color.b = (i * 211) % 256;
	return (color);
}
