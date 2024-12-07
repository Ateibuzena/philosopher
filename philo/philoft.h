/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoft.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:10:55 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/07 10:26:26 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOFT_H
#define PHILOFT_H

# include "/sgoinfre/students/azubieta/azubieta/Utils/libft/libft.h"
# include <pthread.h>
# include <stdlib.h>
# include <string.h> //Para memset
# include <stdio.h>
# include <sys/time.h> //gettimeofday
# define INT_MAX 214748364

typedef struct s_philo
{
    int             id;
    int             left_fork;
    int             right_fork;
    pthread_t 		thread;  // Hilo que representará al filósofo
	long 			last_meal_time;
    int 			meals_eaten;
    pthread_mutex_t meal_lock;
	struct s_env 	*env;
} t_philo;

typedef struct s_env
{
    int 			num_philos;
    int 			time_to_die;
    int 			time_to_eat;
    int 			time_to_sleep;
    int 			meals_required;
    pthread_mutex_t *forks;  // Array de mutex per als tenedors
    pthread_mutex_t print_lock;  // Mutex per evitar logs solapats
    pthread_mutex_t simulation_lock;
    t_philo 		*philos;  // Array de filòsofs
    long int        start_time;
    int 			simulation_running;  // Estat de la simulació
} t_env;

/*philo_init.c*/
int     ft_init_environment(t_env *env, int argc, char **argv);

/*philo_clean.c*/
void    ft_clean_up(t_env *env);

/*philo_threads.c*/
int     ft_create_threads(t_env *env);

/*philo_lifestyle.c*/
void    *ft_lifecycle(void *arg);

/*philo_utils.c*/
void        ft_print_environment(t_env *env);
long int    ft_get_time();
void        *ft_monitoring(void *arg);

#endif