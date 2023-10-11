/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/29 15:21:31 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/10/11 16:16:14 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PH_NOT_FOUND -1
# define PH_NOT_STARTED 0
# define PH_TINY_SLEEP_TIME_US 8

struct					s_philosopher;
typedef pthread_mutex_t	t_fork;
typedef long long int	t_ph_time;

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

typedef enum e_time_action {
	PH_TIME_SET,
	PH_TIME_GET
}	t_ph_time_action;

typedef struct s_sim_args {
	int			n_philos;
	int			time_to_die_ms;
	int			time_to_eat_ms;
	int			time_to_sleep_ms;
	int			times_each_eats;
}	t_sim_args;

typedef struct s_simulation {
	t_sim_args				args;
	struct s_philosopher	*philos;
	t_fork					*forks;
	pthread_mutex_t			mutex;
	t_sim_status			status;
}	t_simulation;

typedef struct s_philosopher {
	int				name;
	pthread_t		thread;
	void			*(*routine)(void *);
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				eaten_meals;
	t_ph_time		death_time_us;
	t_simulation	*sim;
}	t_philo;

// announce.c
void		ph_announce(t_ph_time timestamp_us, t_philo *philo, char *message);

// data.c
t_status	ph_init_data(t_simulation *simulation);
void		ph_cleanup_data(t_simulation *simulation);

// error.c
t_status	ph_error(char *s);

// monitor.c
void		ph_monitor(t_simulation *simulation);
void		ph_update_status(t_simulation *simulation, t_ph_time timestamp_us);

// parse.c
t_status	ph_parse_all_args(int argc, char **argv, t_sim_args *args);

// routine.c
void		*ph_left_to_right_routine(void *arg);
void		*ph_right_to_left_routine(void *arg);
void		*ph_lonely_routine(void *arg);

// sleep.c
void		ph_aware_sleep_till(t_ph_time alarm_time_us, t_simulation *sim);

// time.c
t_ph_time	ph_time_us(t_ph_time_action action);
t_ph_time	ph_time_to_eat_us(t_simulation *sim);
t_ph_time	ph_time_to_die_us(t_simulation *sim);
t_ph_time	ph_time_to_sleep_us(t_simulation *sim);

#endif
