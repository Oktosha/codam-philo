/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 12:52:52 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/10/05 13:25:16 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_sleep(t_simulation *simulation, int alarm_time)
{
	int	current_time;
	int	time_left_to_sleep;
	int	simulation_is_running;

	current_time = ph_time(simulation->start_time);
	while (current_time < alarm_time)
	{
		pthread_mutex_lock(&(simulation->mutex));
		if (simulation->status != SIM_RUN)
			simulation_is_running = PH_FALSE;
		pthread_mutex_unlock(&(simulation->mutex));
		if (!simulation_is_running)
			break ;
		current_time = ph_time(simulation->start_time);
		time_left_to_sleep = alarm_time - current_time;
		if (time_left_to_sleep < PH_PHILO_USLEEP_TIME)
			usleep(time_left_to_sleep);
		else
			usleep(PH_PHILO_USLEEP_TIME);
		current_time = ph_time(simulation->start_time);
	}
}
