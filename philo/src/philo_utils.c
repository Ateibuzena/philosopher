/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:49 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/18 02:13:00 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

t_color	ft_generate_color(int i)
{
	t_color	color;

	color.r = (i * 73) % 256;
	color.g = (i * 131) % 256;
	color.b = (i * 211) % 256;
	return (color);
}

void	ft_print(char *str, t_env *env, int i)
{
	t_color	color;

	pthread_mutex_lock(&env->simulation_lock);
	if (!env->simulation_running)
		return ;
	pthread_mutex_unlock(&env->simulation_lock);
	color = ft_generate_color(i);
	pthread_mutex_lock(&env->print_lock);
	if (env->simulation_running)
	{
		printf("\033[38;2;%d;%d;%dm%ld %ld %s\033[0m\n",
			color.r, color.g, color.b,
			ft_get_time() - env->start_time,
			env->philos[i - 1].id,
			str);
	}
	pthread_mutex_unlock(&env->print_lock);
}

long int	ft_get_time(void)
{
	long int		time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	ft_print_philosophers(t_env *env)
{
	long int	i;

	printf("\nPhilosophers:\n");
	i = 0;
	while (i < env->num_philos)
	{
		printf("Philosopher %ld:\n", i + 1);
		printf("  - ID: %ld\n", env->philos[i].id);
		printf("  - Last meal: %ld ms\n", env->philos[i].last_meal_time);
		printf("  - Meals eaten: %ld\n", env->philos[i].meals_eaten);
		printf("  - Pointer to environment: %p\n", (void *)env->philos[i].env);
		printf("  - Thread identifier: %p\n", (void *)&env->philos[i].thread);
		if (env->philos[i].thread)
			printf(" -> Philosopher %ld's thread created.\n", i + 1);
		else
			printf(" -> Error: Philosopher %ld's thread not created.\n", i + 1);
		i++;
	}
}

void	ft_print_environment(t_env *env)
{
	long int	i;

	i = 0;
	printf("\nEstado de la simulación: ");
	if (env->simulation_running)
		printf("En ejecución\n");
	else
		printf("Detenida\n");
	printf("Número de filósofos: %ld\n", env->num_philos);
	printf("Tiempo para morir: %ld ms\n", env->time_to_die);
	printf("Tiempo para comer: %ld ms\n", env->time_to_eat);
	printf("Tiempo para dormir: %ld ms\n", env->time_to_sleep);
	printf("Número de veces que cada filósofo debe comer: %ld\n",
		env->meals_required);
	i = 0;
	printf("\nMutex para los tenedores: ");
	while (i < env->num_philos)
	{
		printf("Tenedor %ld: %p  ", i + 1, (void *)&env->forks[i]);
		i++;
	}
	printf("\nMutex de impresión: %p\n", (void *)&env->print_lock);
	ft_print_philosophers(env);
}
