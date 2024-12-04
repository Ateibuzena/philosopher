/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:37 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/04 21:49:48 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

// Funció per inicialitzar l'entorn
int ft_init_environment(t_env *env, int argc, char **argv)
{
	int i;

	i = 0;
    // Parseig dels arguments
    env->num_philosophers = ft_atoi(argv[1]);
    env->time_to_die = ft_atoi(argv[2]);
    env->time_to_eat = ft_atoi(argv[3]);
    env->time_to_sleep = ft_atoi(argv[4]);

    if (argc == 6)
        env->meals_required = ft_atoi(argv[5]);
	else
        env->meals_required = -1;  // No es necessita un número fix de menjades

    // Inicialitzem els mutex per als tenedors
    env->forks = malloc(env->num_philosophers * sizeof(pthread_mutex_t));
    while (i < env->num_philosophers)
	{
        if (pthread_mutex_init(&env->forks[i], NULL) != 0)
		{
            printf("Error inicialitzant els mutex dels tenedors\n");
            return (1);
        }
		i++;
    }

    // Inicialitzem el mutex per a la impressió
    if (pthread_mutex_init(&env->print_lock, NULL) != 0)
	{
        printf("Error inicialitzant el mutex de la impressió\n");
        return (1);
    }

    // Inicialitzem els filòsofs
    env->philosophers = malloc(env->num_philosophers * sizeof(t_philo));
    i = 0;
	while (i < env->num_philosophers)
	{
        env->philosophers[i].id = i + 1;  // Identificador del filòsof
        env->philosophers[i].last_meal_time = 0;
        env->philosophers[i].meals_eaten = 0;
        env->philosophers[i].env = env;   // Referència a l'entorn
		i++;
    }

    // Inicialització completa
    env->simulation_running = 1;
    return (0);
}
