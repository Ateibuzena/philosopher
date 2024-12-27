/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_prints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:36:05 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/27 15:35:57 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philoft.h"

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
	printf("\nEstado de la simulación: \n");
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
	printf("\nMutex para los tenedores: \n");
	while (i < env->num_philos)
	{
		printf("Tenedor %ld: %p  ", i + 1, (void *)&env->forks[i]);
		i++;
	}
	ft_print_philosophers(env);
}
