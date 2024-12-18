/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:55 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/18 01:06:27 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philoft.h"

static int	ft_check_args(int argc, char **argv)
{
	int			i;
	long int	arg;
	char		*endptr;

	if (argc < 5 || argc > 6)
		return (printf("Error: Incorrect number of arguments.\n"));
	i = 1;
	while (i < argc)
	{
		arg = strtol(argv[i], &endptr, 10);
		if (*endptr != '\0' || arg <= 0 || arg > INT_MAX)
			return (printf("Error: %s is not a valid argument.\n", argv[i]));
		i++;
	}
	if (argc == 6)
	{
		arg = strtol(argv[5], &endptr, 10);
		if (*endptr != '\0' || arg <= 0 || arg > INT_MAX)
			return (printf("Error: %s is not a valid argument.\n", argv[5]));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
	{
		printf("Error: Creating environment\n");
		return (1);
	}
	if (ft_check_args(argc, argv))
		return (1);
	if (ft_init_environment(env, argc, argv))
	{
		ft_clean_up(env);
		return (1);
	}
	if (ft_create_threads(env))
	{
		ft_clean_up(env);
		return (1);
	}
	ft_clean_up(env);
	return (0);
}
