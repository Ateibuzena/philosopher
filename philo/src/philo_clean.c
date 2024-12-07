/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:02:32 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/06 19:12:44 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philoft.h"

void ft_clean_up(t_env *env)
{
	int i;

	i = 0;
    while (i < env->num_philos)
    {
        pthread_mutex_destroy(&env->forks[i]);  // Destruïm els mutex dels tenedors
        i++;
    }
    pthread_mutex_destroy(&env->print_lock);  // Destruïm el mutex de la impressió
    free(env->forks);  // Alliberem la memòria per als mutex
    free(env->philos);  // Alliberem la memòria per als filòsofs
}