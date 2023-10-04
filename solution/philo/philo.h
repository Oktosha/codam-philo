/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/29 15:21:31 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/10/04 14:13:56 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

# define PH_NOT_FOUND -1

struct					s_philosopher;
typedef pthread_mutex_t	t_fork;
typedef int				t_relative_time;
typedef int				t_absolute_time;

typedef enum e_ph_bool {
	PH_FALSE = 0,
	PH_TRUE = 1
}	t_ph_bool;

typedef enum e_status {
	PH_SUCCESS = 0,
	PH_ERROR = 1
}	t_status;

typedef enum e_sim_status {
	SIM_INIT = -1,
	SIM_RUN = 0,
	SIM_END = 1
}	t_sim_status;

typedef struct s_sim_params {
	int	n_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_each_eats;
}	t_sim_params;

typedef struct s_simulation {
	t_sim_params			params;
	struct s_philosopher	*philos;
	t_fork					*forks;
	pthread_mutex_t			mutex;
	t_sim_status			status;
	t_absolute_time			start_time;
}	t_simulation;

typedef struct s_philosopher {
	int				name;
	pthread_t		thread;
	void			(*routine)(void *);
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				eaten_meals;
	t_relative_time	death_time;
	t_simulation	*simulation;
}	t_philo;

// data.c
t_status	ph_init_data(t_simulation *simulation);
void		ph_cleanup_data(t_simulation *simulation);

// error.c
t_status	ph_error(char *s);

// monitor.c
void		ph_update_status(t_simulation *simulation, int timestamp);

// parse.c
t_status	ph_parse_all_params(int argc, char **argv, t_sim_params *params);

// time.c
int			ph_time(t_simulation *simulation);

#endif
