/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:44 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/27 20:22:46 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

static void	ft_sleeping(t_philo *philo)
{
	if (ft_simulation_lock(philo->env))
		return ;
	ft_print("is sleeping", philo->env, philo->id);
	usleep(philo->env->time_to_sleep * 1000);
}

static void	ft_forks_ids(t_philo *philo, long int *first, long int *second)
{
	if (philo->id % 2 == 0)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

static int	ft_take_forks(t_philo *philo, long int *first, long int *second)
{
	if (ft_simulation_lock(philo->env))
		return (0);
	ft_forks_ids(philo, first, second);
	pthread_mutex_lock(&philo->env->forks[*first]);
	ft_print("has taken a fork", philo->env, philo->id);
	if ((philo->env->num_philos == 1)
		|| (pthread_mutex_lock(&philo->env->forks[*second]) != 0))
	{
		pthread_mutex_unlock(&philo->env->forks[*first]);
		return (0);
	}
	ft_print("has taken a fork", philo->env, philo->id);
	return (1);
}

static int	ft_eating(t_philo *philo)
{
	long int	first_fork;
	long int	second_fork;

	first_fork = -1;
	second_fork = -1;
	if (ft_simulation_lock(philo->env))
		return (0);
	if (!ft_take_forks(philo, &first_fork, &second_fork))
		return (0);
	ft_print("is eating", philo->env, philo->id);
	pthread_mutex_lock(&philo->env->simulation_lock);
	philo->last_meal_time = ft_get_time() - philo->env->start_time;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->env->simulation_lock);
	usleep(philo->env->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->env->forks[second_fork]);
	pthread_mutex_unlock(&philo->env->forks[first_fork]);
	return (1);
}

void	*ft_lifecycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(500);
	while (1)
	{
		if (!ft_eating(philo))
			break ;
		if (ft_simulation_lock(philo->env))
			break ;
		ft_sleeping(philo);
		if (ft_simulation_lock(philo->env))
			break ;
		ft_print("is thinking", philo->env, philo->id);
		usleep(500);
	}
	return (NULL);
}
