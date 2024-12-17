/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:49 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/17 20:53:08 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

/*void ft_print_environment(t_env *env)
{
	long int i;

	i = 0;
    printf("Número de filósofos: %ld\n", env->num_philos);
    printf("Tiempo para morir: %ld ms\n", env->time_to_die);
    printf("Tiempo para comer: %ld ms\n", env->time_to_eat);
    printf("Tiempo para dormir: %ld ms\n", env->time_to_sleep);
    printf("Número de veces que cada filósofo debe comer: %ld\n", env->meals_required);

    // Imprimir el estado de los mutex de los tenedores
    printf("Mutex para los tenedores: ");
    while (i < env->num_philos)
	{
        printf("Tenedor %ld: %p  ", i + 1, (void *)&env->forks[i]);
		i++;
    }
    printf("\n");

    // Imprimir información sobre los filósofos
    printf("Filósofos:\n");
	i = 0;
    while (i < env->num_philos)
	{
        printf("Filósofo %ld:\n", i + 1);
        printf("  - ID: %ld\n", env->philos[i].id);
        printf("  - Última comida: %ld ms\n", env->philos[i].last_meal_time);
        printf("  - Comidas realizadas: %ld\n", env->philos[i].meals_eaten);
        printf("  - Puntero al entorno: %p\n", (void *)env->philos[i].env);
        // Comprobar el hilo asociado al filósofo
        printf("  - Identificador del hilo (pthread_t): %p\n", (void *)&env->philos[i].thread);
        // Mensaje de confirmación
        if (env->philos[i].thread)
            printf("    -> Hilo del filósofo %ld creado correctamente.\n", i + 1);
        else
            printf("    -> Error: Hilo del filósofo %ld no creado.\n", i + 1);
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
}*/

static t_color generate_color(int id)
{
    t_color color;

    color.r = (id * 50) % 256;  // Componente rojo (0-255)
    color.g = (id * 100) % 256; // Componente verde (0-255)
    color.b = (id * 150) % 256; // Componente azul (0-255)

    return color;  // Retorna el color generado
}

void ft_print(char *str, t_env *env, int i)
{
    t_color color;

    // Generar el color para el filósofo
    color = generate_color(i);

    // Bloquear el mutex para la sección crítica de impresión
    pthread_mutex_lock(&env->print_lock);

    // Verificar si la simulación está corriendo
    if (env->simulation_running)
    {
        // Imprimir el mensaje con color y el tiempo transcurrido
        printf("\033[38;2;%d;%d;%dm%ld %ld %s\033[0m\n",
               color.r, color.g, color.b, 
               ft_get_time() - env->start_time, 
               env->philos[i - 1].id,  // ID del filósofo
               str);  // El mensaje

    }

    // Desbloquear el mutex después de imprimir
    pthread_mutex_unlock(&env->print_lock);
}

long int    ft_get_time()
{
    long int        time;
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (time);
}

static void ft_check_deaths(t_env *env)
{
    int         i;
    long int    time;

    i = 0;
    time = ft_get_time(env) - env->start_time;
    while (i < env->num_philos)
    {
        //pthread_mutex_lock(&env->philos[i].meal_lock);
        if ((time - env->philos[i].last_meal_time) > env->time_to_die)
        {
            ft_print("died", env, env->philos[i].id);
            pthread_mutex_lock(&env->simulation_lock);
            env->simulation_running = 0;
            pthread_mutex_unlock(&env->simulation_lock);
            return ;
        }
        //pthread_mutex_unlock(&env->philos[i].meal_lock);
        i++;
    }
}

static void ft_check_meals(t_env *env)
{
    int i;
    int all_ate_enough;
    
    all_ate_enough = 1;
    i = 0;
    while (i < env->num_philos)
    {
        //pthread_mutex_lock(&env->philos[i].meal_lock);
        if ((env->meals_required == -1)
                || (env->philos[i].meals_eaten < env->meals_required))
        {
            all_ate_enough = 0;   
            break ;
        }
        //pthread_mutex_unlock(&env->philos[i].meal_lock);
        i++;
    }
    if (all_ate_enough)
    {
        pthread_mutex_lock(&env->simulation_lock);
        env->simulation_running = 0;
        pthread_mutex_unlock(&env->simulation_lock);
    }
}

void    *ft_monitoring(void *arg)
{
    t_env *env;

    env = (t_env *)arg;
    while (env->simulation_running)
    {
        ft_check_deaths(env);
        if (!env->simulation_running)
            return (NULL) ;
        ft_check_meals(env);
        usleep(100);
    }
    return (NULL);
}