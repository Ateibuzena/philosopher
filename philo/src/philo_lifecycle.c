/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:44 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/18 02:12:39 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

static void	ft_eating(t_philo *philo)
{
	if (!philo->env->simulation_running)
		return ;
	ft_print("is eating", philo->env, philo->id);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = ft_get_time() - philo->env->start_time;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	usleep(philo->env->time_to_eat * 1000);
}

static void	ft_sleeping(t_philo *philo)
{
	if (!philo->env->simulation_running)
		return ;
	ft_print("is sleeping", philo->env, philo->id);
	usleep(philo->env->time_to_sleep * 1000);
}

static void	ft_take_even_forks(t_philo *philo)
{
	if (!philo->env->simulation_running)
		return ;
	if (pthread_mutex_lock(&philo->env->forks[philo->left_fork]) == 0)
	{
		ft_print("has taken the left fork", philo->env, philo->id);
		if (pthread_mutex_lock(&philo->env->forks[philo->right_fork]) == 0)
		{
			ft_print("has taken the right fork", philo->env, philo->id);
			ft_eating(philo);
			ft_print("has dropped both forks.", philo->env, philo->id);
			pthread_mutex_unlock(&philo->env->forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->env->forks[philo->left_fork]);
		}
		else
		{
			ft_print("has NOT taken the right fork.", philo->env, philo->id);
			pthread_mutex_unlock(&philo->env->forks[philo->left_fork]);
		}
	}
}

static void	ft_take_forks(t_philo *philo)
{
	if (!philo->env->simulation_running)
		return ;
	if (philo->id % 2 != 0)
	{
		if (pthread_mutex_lock(&philo->env->forks[philo->right_fork]) == 0)
		{
			ft_print("has taken the right fork", philo->env, philo->id);
			if (pthread_mutex_lock(&philo->env->forks[philo->left_fork]) == 0)
			{
				ft_print("has taken the left fork", philo->env, philo->id);
				ft_eating(philo);
				ft_print("has dropped both forks.", philo->env, philo->id);
				pthread_mutex_unlock(&philo->env->forks[philo->right_fork]);
				pthread_mutex_unlock(&philo->env->forks[philo->left_fork]);
			}
			else
			{
				ft_print("has NOT taken the left fork.", philo->env, philo->id);
				pthread_mutex_unlock(&philo->env->forks[philo->right_fork]);
			}
		}
	}
	else
		ft_take_even_forks(philo);
}

void	*ft_lifecycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(500);
	while (philo->env->simulation_running)
	{
		ft_take_forks(philo);
		if (!philo->env->simulation_running)
			break ;
		ft_sleeping(philo);
		if (!philo->env->simulation_running)
			break ;
		ft_print("is thinking", philo->env, philo->id);
		usleep(500);
	}
	return (NULL);
}
