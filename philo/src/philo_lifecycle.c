/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:44 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/21 00:25:11 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

int	ft_simulation_lock(t_env *env, int change)
{
	if (!change)
	{
		pthread_mutex_lock(&env->simulation_lock);
		if (!env->simulation_running)
		{
			pthread_mutex_unlock(&env->simulation_lock);
			return (1);
		}
		pthread_mutex_unlock(&env->simulation_lock);
	}
	else
	{
		pthread_mutex_lock(&env->simulation_lock);
		if (!env->simulation_running)
		{
			pthread_mutex_unlock(&env->simulation_lock);
			return (1);
		}
		env->simulation_running = 0;
		pthread_mutex_unlock(&env->simulation_lock);
	}
	return (0);
}

static void	ft_eating(t_philo *philo)
{
	if (ft_simulation_lock(philo->env, 0))
		return ;
	ft_print("is eating", philo->env, philo->id);

	pthread_mutex_lock(&philo->env->simulation_lock);
	pthread_mutex_lock(&philo->mutex_philo);
	philo->last_meal_time = ft_get_time() - philo->env->start_time;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->mutex_philo);
	pthread_mutex_unlock(&philo->env->simulation_lock);

	pthread_mutex_lock(&philo->env->simulation_lock);
	if (!philo->env->simulation_running)
	{
		pthread_mutex_unlock(&philo->env->simulation_lock);
		pthread_mutex_unlock(&philo->env->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->env->forks[philo->left_fork]);
		return ;
	}
	if (philo->env->simulation_running)
		usleep(philo->env->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->env->simulation_lock);
}

static void	ft_sleeping(t_philo *philo)
{
	if (ft_simulation_lock(philo->env, 0))
		return ;
	ft_print("is sleeping", philo->env, philo->id);
	usleep(philo->env->time_to_sleep * 1000);
}

static void	ft_take_even_forks(t_philo *philo)
{
	if (ft_simulation_lock(philo->env, 0))
		return ;
	if (pthread_mutex_lock(&philo->env->forks[philo->left_fork]) == 0)
	{
		pthread_mutex_lock(&philo->env->simulation_lock);
		if (!philo->env->simulation_running)
		{
			pthread_mutex_unlock(&philo->env->simulation_lock);
			pthread_mutex_unlock(&philo->env->forks[philo->left_fork]);
			return ;
		}
		pthread_mutex_unlock(&philo->env->simulation_lock);
		ft_print("has taken a fork", philo->env, philo->id);
		//printf("right_fork: %ld, left_fork: %ld",philo->right_fork, philo->left_fork);
		if (pthread_mutex_lock(&philo->env->forks[philo->right_fork]) == 0)
		{
			pthread_mutex_lock(&philo->env->simulation_lock);
			if (!philo->env->simulation_running)
			{
				pthread_mutex_unlock(&philo->env->simulation_lock);
				pthread_mutex_unlock(&philo->env->forks[philo->right_fork]);
				pthread_mutex_unlock(&philo->env->forks[philo->left_fork]);
				return ;
			}
			pthread_mutex_unlock(&philo->env->simulation_lock);
			ft_print("has taken a fork", philo->env, philo->id);
			ft_eating(philo);
			
			pthread_mutex_unlock(&philo->env->forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->env->forks[philo->left_fork]);
		}
		else
		{
			pthread_mutex_lock(&philo->env->simulation_lock);
			if (!philo->env->simulation_running)
			{
				pthread_mutex_unlock(&philo->env->simulation_lock);
				pthread_mutex_unlock(&philo->env->forks[philo->left_fork]);
				return ;
			}
			pthread_mutex_unlock(&philo->env->simulation_lock);
			pthread_mutex_unlock(&philo->env->forks[philo->left_fork]);
		}
	}
}

static void	ft_take_forks(t_philo *philo)
{
	if (ft_simulation_lock(philo->env, 0))
		return ;
	if (philo->id % 2 == 0)
	{
		ft_simulation_lock(philo->env, 0);	
		if (pthread_mutex_lock(&philo->env->forks[philo->right_fork]) == 0)
		{
			pthread_mutex_lock(&philo->env->simulation_lock);
			if (!philo->env->simulation_running)
			{
				pthread_mutex_unlock(&philo->env->simulation_lock);
				pthread_mutex_unlock(&philo->env->forks[philo->right_fork]);
				return ;
			}
			pthread_mutex_unlock(&philo->env->simulation_lock);
			ft_print("has taken a fork", philo->env, philo->id);
			if (pthread_mutex_lock(&philo->env->forks[philo->left_fork]) == 0)
			{
				pthread_mutex_lock(&philo->env->simulation_lock);
				if (!philo->env->simulation_running)
				{
					pthread_mutex_unlock(&philo->env->simulation_lock);
					pthread_mutex_unlock(&philo->env->forks[philo->left_fork]);
					pthread_mutex_unlock(&philo->env->forks[philo->right_fork]);
					return ;
				}
				pthread_mutex_unlock(&philo->env->simulation_lock);
				ft_print("has taken a fork", philo->env, philo->id);
				ft_eating(philo);
				pthread_mutex_unlock(&philo->env->forks[philo->left_fork]);
				pthread_mutex_unlock(&philo->env->forks[philo->right_fork]);
			}
			else
			{
				pthread_mutex_lock(&philo->env->simulation_lock);
				if (!philo->env->simulation_running)
				{
					pthread_mutex_unlock(&philo->env->simulation_lock);
					pthread_mutex_unlock(&philo->env->forks[philo->right_fork]);
					return ;
				}
				pthread_mutex_unlock(&philo->env->simulation_lock);
				pthread_mutex_unlock(&philo->env->forks[philo->right_fork]);
			}
		}
	}
	else
		ft_take_even_forks(philo);
}

void	*ft_lifecycle(void *arg)
{
	t_philo		*philo;
	long int	simulation_running;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(200);
	pthread_mutex_lock(&philo->env->simulation_lock);
	simulation_running = philo->env->simulation_running;
	pthread_mutex_unlock(&philo->env->simulation_lock);
	while (simulation_running)
	{
		ft_take_forks(philo);
		if (ft_simulation_lock(philo->env, 0))
			return (NULL);
		ft_sleeping(philo);
		if (ft_simulation_lock(philo->env, 0))
			return (NULL);
		ft_print("is thinking", philo->env, philo->id);
		usleep(500);
		pthread_mutex_lock(&philo->env->simulation_lock);
		simulation_running = philo->env->simulation_running;
		pthread_mutex_unlock(&philo->env->simulation_lock);
	}
	return (NULL);
}
