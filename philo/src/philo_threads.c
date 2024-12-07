/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:40 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/06 19:02:26 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

int ft_create_threads(t_env *env)
{
	int i;

	i = 0;
    while (i < env->num_philos)
	{
        if (pthread_create(&env->philos[i].thread, NULL,
                ft_lifecycle, &env->philos[i]) != 0)
        {
            printf("Error creant el filòsof %d\n", i + 1);
            return (1);
        }
		i++;
    }
    return (0);
}