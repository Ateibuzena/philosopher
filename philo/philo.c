/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:55 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/04 21:57:32 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philoft.h"

static void ft_print_environment(t_env *env)
{
	int i;

	i = 0;
    printf("Número de filósofos: %d\n", env->num_philosophers);
    printf("Tiempo para morir: %d ms\n", env->time_to_die);
    printf("Tiempo para comer: %d ms\n", env->time_to_eat);
    printf("Tiempo para dormir: %d ms\n", env->time_to_sleep);
    printf("Número de veces que cada filósofo debe comer: %d\n", env->meals_required);

    // Imprimir el estado de los mutex de los tenedores
    printf("Mutex para los tenedores: ");
    while (i < env->num_philosophers)
	{
        printf("Tenedor %d: %p  ", i + 1, (void *)&env->forks[i]);
		i++;
    }
    printf("\n");

    // Imprimir información sobre los filósofos
    printf("Filósofos:\n");
	i = 0;
    while (i < env->num_philosophers)
	{
        printf("Filósofo %d:\n", i + 1);
        printf("  - ID: %d\n", env->philosophers[i].id);
        printf("  - Última comida: %ld ms\n", env->philosophers[i].last_meal_time);
        printf("  - Comidas realizadas: %d\n", env->philosophers[i].meals_eaten);
        printf("  - Puntero al entorno: %p\n", (void *)env->philosophers[i].env);
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

// Funció per validar els arguments de la línia de comandes
static int ft_check_args(int argc, char **argv)
{
	int		i;
	char	*endptr;
	long	arg;

    // Comprovem que hi hagi entre 4 i 5 arguments
    if (argc < 5 || argc > 6)
	{
        printf("Error: Número incorrecte d'arguments.\n");
        return (1);
    }
    // Comprovem que els arguments siguin enters positius
	i = 1;
    while (i < argc)
	{
        
        arg = ft_strtol(argv[i], &endptr, 10);
        if (*endptr != '\0' || arg <= 0 || arg > INT_MAX)
		{
            printf("Error: Argument %d no és un enter positiu vàlid.\n", i);
            return (1);
        }
		i++;
    }

    // Comprovem que si es passa el número de vegades que cada filòsof ha de menjar, és un enter positiu
    if (argc == 6)
	{
		arg = ft_strtol(argv[5], &endptr, 10);
        
        if (*endptr != '\0' || arg <= 0 || arg > INT_MAX)
		{
            printf("Error: Argument opcional no és un enter positiu vàlid.\n");
            return (1);
        }
    }

    return (0); // Si tot és correcte, retornem 0
}


int	main(int argc, char **argv)
{
	t_env *env; // Declarem el punter a la nostra estructura d'entorn

    env = malloc(sizeof(t_env));  // Assignem memòria per a l'entorn
    if (!env)
	{
        printf("Error en la creació de l'entorn\n");
        return (1);
    }
	printf("INICIANDO PROYECTO 3, 2, 1 ...\n");
	if (ft_check_args(argc, argv))
		return (1);
	ft_init_environment(env, argc, argv);
	ft_print_environment(env);

}