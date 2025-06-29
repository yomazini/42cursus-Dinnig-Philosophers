/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 04:52:34 by ymazini           #+#    #+#             */
/*   Updated: 2025/06/03 17:48:36 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h> 

# define MAX_PHILO 201

struct	s_table;

typedef struct s_philo
{
	int				index;
	pthread_t		philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
	int				eating_count;
	long			last_time_eat;
}	t_philo;

typedef struct s_table
{
	int				nbr_philos;
	int				time_to_eat;
	pthread_mutex_t	last_time_eat_mutex;
	int				time_to_die;
	int				all_eat;
	long			sim_start_time;
	int				nmr_time_must_eat;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				time_to_sleep;
	pthread_mutex_t	writing_mutex;
}	t_table;

int		input_validation(char **av, int arguments);
int		philo_start_simulation(t_table **table);
long	get_time(void);
void	clean_all(t_table **table, int num_philos);
int		ft_isdigit(char c);
int		initialize_mutexes(t_table **table, int number_philo);
void	ft_usleep(int timee);
int		ft_atoi(const char *str);
int		ft_fork_spliting(t_table **table, int num_philo);
void	*routine(void *philos);
void	detach_thread(t_table **table, int nmr_philos);
void	print_sleep_stats(t_philo *phil);
void	print_eating_stats(t_philo *phil);
void	print_fork_taken(t_philo *phil);
void	monitor(t_table **table, int nmr_philos);
void	update_status(t_philo **philo);
int		eating_count_check(t_philo **philo);
int		initialize_table(t_table **table, char **av);
void	print_death_status(t_table *table, int i);
void	print_thinking_stats(t_philo *phil);
int		allocate_philos_forks(t_table **table);
int		ft_validating_the_arg(char *to_check);

#endif