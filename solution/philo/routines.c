/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routines.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 13:00:32 by codespace     #+#    #+#                 */
/*   Updated: 2023/10/05 14:38:32 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_left_to_right_loop(t_philo *philo, int timestamp, int sim_is_running)
{
	while (sim_is_running)
	{
		pthread_mutex_lock(&(philo->left_fork));
		timestamp = ph_time(philo->sim->start_time);
		ph_announce(timestamp, philo, "has taken a fork");
		pthread_mutex_lock(&(philo->right_fork));
		timestamp = ph_time(philo->sim->start_time);
		ph_announce(timestamp, philo, "has taken a fork");
		ph_announce(timestamp, philo, "is eating");
		ph_sleep(philo->sim, timestamp + philo->sim->args.time_to_eat);
		pthread_mutex_unlock(&(philo->left_fork));
		pthread_mutex_unlock(&(philo->right_fork));
		timestamp = ph_time(philo->sim->start_time);
		pthread_mutex_lock(&(philo->sim->mutex));
		philo->eaten_meals += 1;
		pthread_mutex_unlock(&(philo->sim->mutex));
		ph_announce(timestamp, philo, "is sleeping");
		ph_sleep(philo->sim, timestamp + philo->sim->args.time_to_sleep);
		timestamp = ph_time(philo->sim->start_time);
		ph_announce(timestamp, philo, "is thinking");
		sim_is_running = ph_read_status_safely(philo->sim) == SIM_RUN;
	}
}

void	*ph_left_to_right_routine(void *arg)
{
	t_philo	*philo;
	int		timestamp;
	int		sim_is_running;

	philo = arg;
	timestamp = 0;
	ph_wait_for_the_start(philo);
	sim_is_running = PH_TRUE;
	ph_left_to_right_loop(philo, timestamp, sim_is_running);
	return (NULL);
}

void	ph_right_to_left_loop(t_philo *philo, int timestamp, int sim_is_running)
{
	while (sim_is_running)
	{
		pthread_mutex_lock(&(philo->right_fork));
		timestamp = ph_time(philo->sim->start_time);
		ph_announce(timestamp, philo, "has taken a fork");
		pthread_mutex_lock(&(philo->left_fork));
		timestamp = ph_time(philo->sim->start_time);
		ph_announce(timestamp, philo, "has taken a fork");
		ph_announce(timestamp, philo, "is eating");
		ph_sleep(philo->sim, timestamp + philo->sim->args.time_to_eat);
		pthread_mutex_unlock(&(philo->left_fork));
		pthread_mutex_unlock(&(philo->right_fork));
		timestamp = ph_time(philo->sim->start_time);
		pthread_mutex_lock(&(philo->sim->mutex));
		philo->eaten_meals += 1;
		pthread_mutex_unlock(&(philo->sim->mutex));
		ph_announce(timestamp, philo, "is sleeping");
		ph_sleep(philo->sim, timestamp + philo->sim->args.time_to_sleep);
		timestamp = ph_time(philo->sim->start_time);
		ph_announce(timestamp, philo, "is thinking");
		sim_is_running = ph_read_status_safely(philo->sim) == SIM_RUN;
	}
}

void	*ph_right_to_left_routine(void *arg)
{
	t_philo	*philo;
	int		timestamp;
	int		sim_is_running;

	philo = arg;
	timestamp = 0;
	ph_wait_for_the_start(philo);
	sim_is_running = PH_TRUE;
	ph_right_to_left_loop(philo, timestamp, sim_is_running);
	return (NULL);
}

void	*ph_lonely_routine(void	*arg)
{
	t_philo	*philo;
	int		timestamp;

	philo = arg;
	ph_wait_for_the_start(philo);
	pthread_mutex_lock(philo->left_fork);
	timestamp = ph_time(philo->sim->start_time);
	pthread_mutex_lock(&(philo->sim->mutex));
	ph_update_status(philo->sim, timestamp);
	if (philo->sim->status == SIM_RUN)
		printf("%d %d has taken a fork\n", timestamp, philo->name);
	pthread_mutex_unlock(&(philo->sim->mutex));
	pthread_mutex_unlock(philo->left_fork);
}
