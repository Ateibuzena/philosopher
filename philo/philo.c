/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:55 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/07 12:44:43 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philoft.h"

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

    return (0);
}


int	main(int argc, char **argv)
{
	t_env     *env;
    pthread_t monitor;
 
	//printf("INICIANDO PROYECTO 3, 2, 1 ...\n");
    env = malloc(sizeof(t_env));
    if (!env)
	{
        printf("Error en la creació de l'entorn\n");
        return (1);
    }
	if (ft_check_args(argc, argv))
		return (1);
	if (ft_init_environment(env, argc, argv))
    {
        ft_clean_up(env);
        return (1);
    }
	//ft_print_environment(env);
    if (ft_create_threads(env))
    {
        ft_clean_up(env);
        return (1);
    }
    if (pthread_create(&monitor, NULL, ft_monitoring, env) != 0)
    {
        printf("Error al crear el fil de monitorització.\n");
        ft_clean_up(env);
        return (1);
    }
    // Esperar que el fil monitor acabi
    if (pthread_join(monitor, NULL) != 0)
    {
        ft_clean_up(env);
        return (1);
    }/*
    // Esperar que tots els fils dels filòsofs acabin
    for (int i = 0; i < env->num_philos; i++)
    {
        if (pthread_join(env->philos[i].thread, NULL) != 0)
        {
            ft_clean_up(env);
            return (1);
        }
    }*/
    ft_clean_up(env);
    return (0);
}