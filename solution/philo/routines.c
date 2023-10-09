/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routines.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 13:00:32 by codespace     #+#    #+#                 */
/*   Updated: 2023/10/09 11:29:15 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ph_act( \
	t_philo *philo, t_fork *first_fork, t_fork *second_fork)
{
	int	timestamp;

	pthread_mutex_lock(first_fork);
	timestamp = ph_time(philo->sim->start_time);
	ph_announce(timestamp, philo, "has taken a fork");
	pthread_mutex_lock(second_fork);
	timestamp = ph_time(philo->sim->start_time);
	pthread_mutex_lock(&(philo->sim->mutex));
	philo->death_time = timestamp + philo->sim->args.time_to_die;
	pthread_mutex_unlock(&(philo->sim->mutex));
	ph_announce(timestamp, philo, "has taken a fork");
	ph_announce(timestamp, philo, "is eating");
	ph_sleep(philo->sim, timestamp + philo->sim->args.time_to_eat);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	timestamp = ph_time(philo->sim->start_time);
	pthread_mutex_lock(&(philo->sim->mutex));
	philo->eaten_meals += 1;
	pthread_mutex_unlock(&(philo->sim->mutex));
	ph_announce(timestamp, philo, "is sleeping");
	ph_sleep(philo->sim, timestamp + philo->sim->args.time_to_sleep);
	timestamp = ph_time(philo->sim->start_time);
	ph_announce(timestamp, philo, "is thinking");
}

static void	ph_loop(t_philo *philo, t_fork *first_fork, t_fork *second_fork)
{
	int	sim_is_running;

	pthread_mutex_lock(&(philo->sim->mutex));
	pthread_mutex_unlock(&(philo->sim->mutex));
	sim_is_running = PH_TRUE;
	while (sim_is_running)
	{
		ph_act(philo, first_fork, second_fork);
		pthread_mutex_lock(&(philo->sim->mutex));
		sim_is_running = philo->sim->status == SIM_RUN;
		pthread_mutex_unlock(&(philo->sim->mutex));
	}
}

void	*ph_left_to_right_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	ph_loop(philo, philo->left_fork, philo->right_fork);
	return (NULL);
}

void	*ph_right_to_left_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	ph_loop(philo, philo->right_fork, philo->left_fork);
	return (NULL);
}

void	*ph_lonely_routine(void	*arg)
{
	t_philo	*philo;
	int		timestamp;

	philo = arg;
	pthread_mutex_lock(&(philo->sim->mutex));
	pthread_mutex_unlock(&(philo->sim->mutex));
	pthread_mutex_lock(philo->left_fork);
	timestamp = ph_time(philo->sim->start_time);
	ph_announce(timestamp, philo, "has taken a fork");
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}
