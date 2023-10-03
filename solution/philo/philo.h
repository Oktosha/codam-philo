/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/29 15:21:31 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/10/03 13:13:07 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>

struct	s_philosopher;

typedef struct s_sim_params {
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_each_philo_eats;
}	t_sim_params;

typedef struct s_simulation {
	t_sim_params		params;
	struct s_philosopher	*philosophers;
	pthread_mutex_t			*forks;
	pthread_mutex_t			mutex;
	int						is_running;
}	t_simulation;

typedef struct s_philosopher {
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				eaten_meals;
	int				latest_meal_start;
	t_simulation	*simulation;
}	t_philosopher;

typedef enum e_status {
	SUCCESS = 0,
	ERROR = 1
}	t_status;

t_status	parse_all_params(int argc, char **argv, t_sim_params *params);

#endif
