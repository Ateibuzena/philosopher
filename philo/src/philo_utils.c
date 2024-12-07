/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:49 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/06 21:08:07 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

void ft_print_environment(t_env *env)
{
	int i;

	i = 0;
    printf("Número de filósofos: %d\n", env->num_philos);
    printf("Tiempo para morir: %d ms\n", env->time_to_die);
    printf("Tiempo para comer: %d ms\n", env->time_to_eat);
    printf("Tiempo para dormir: %d ms\n", env->time_to_sleep);
    printf("Número de veces que cada filósofo debe comer: %d\n", env->meals_required);

    // Imprimir el estado de los mutex de los tenedores
    printf("Mutex para los tenedores: ");
    while (i < env->num_philos)
	{
        printf("Tenedor %d: %p  ", i + 1, (void *)&env->forks[i]);
		i++;
    }
    printf("\n");

    // Imprimir información sobre los filósofos
    printf("Filósofos:\n");
	i = 0;
    while (i < env->num_philos)
	{
        printf("Filósofo %d:\n", i + 1);
        printf("  - ID: %d\n", env->philos[i].id);
        printf("  - Última comida: %ld ms\n", env->philos[i].last_meal_time);
        printf("  - Comidas realizadas: %d\n", env->philos[i].meals_eaten);
        printf("  - Puntero al entorno: %p\n", (void *)env->philos[i].env);
        // Comprobar el hilo asociado al filósofo
        printf("  - Identificador del hilo (pthread_t): %p\n", (void *)&env->philos[i].thread);
        // Mensaje de confirmación
        if (env->philos[i].thread)
            printf("    -> Hilo del filósofo %d creado correctamente.\n", i + 1);
        else
            printf("    -> Error: Hilo del filósofo %d no creado.\n", i + 1);
		i++;
    }

    // Mutex de impresión
    printf("Mutex de impresión: %p\n", (void *)&env->print_lock);

    // Estado de la simulación
	printf("Estado de la simulación: ");
	if (env->simulation_running)
		printf("En ejecución\n");
	else
		printf("Detenida\n");
}

int ft_get_time()
{
    long int             time;
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (time);
}

static void  ft_check_deaths(t_env *env)
{
    int i;
    int time;

    i = 0;
    while (i < env->num_philos)
	{
        time = ft_get_time();
        if ((time - env->philos[i].last_meal_time) > env->time_to_die)
        {
            pthread_mutex_lock(&env->print_lock); // Bloqueja l'accés als logs
            printf("[%d] %d : Died\n", time, env->philos[i].id);
            pthread_mutex_unlock(&env->print_lock);
            env->simulation_running = 0;
        }
        i++;
    }
}

static void ft_check_meals(t_env *env)
{
    int i;
    int all_ate_enough;
    
    all_ate_enough = 1; // Marcar si tots els filòsofs han menjat prou
    i = 0;
    while (i < env->num_philos)
    {
        if ((env->meals_required != -1)
                && (env->philos[i].meals_eaten < env->meals_required))
        {
            all_ate_enough = 0;
            break ;
        }
        i++;
    }
    if (all_ate_enough)
    {
        pthread_mutex_lock(&env->print_lock); // Bloqueig per a la seguretat dels logs
        printf("Tots els filòsofs han menjat les vegades requerides.\n");
        pthread_mutex_unlock(&env->print_lock);
        env->simulation_running = 0; // Atura la simulació
    }
}

void    *ft_monitoring(void *arg)
{
    t_env *env;

    env = (t_env *)arg;
    while (env->simulation_running)
    {
        ft_check_deaths(env);
        ft_check_meals(env);
        usleep(1000);
    }
    return (NULL);
}