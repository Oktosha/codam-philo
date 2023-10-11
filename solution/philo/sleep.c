/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 12:52:52 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/10/11 15:54:27 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_aware_sleep_till(t_ph_time alarm_time_us, t_simulation *sim)
{
	t_ph_time	current_time_us;
	t_ph_time	time_left_to_sleep_us;
	t_ph_bool	simulation_is_running;

	simulation_is_running = PH_TRUE;
	current_time_us = ph_time_us(PH_TIME_GET);
	while (current_time_us < alarm_time_us)
	{
		pthread_mutex_lock(&(sim->mutex));
		if (sim->status != SIM_RUN)
			simulation_is_running = PH_FALSE;
		pthread_mutex_unlock(&(sim->mutex));
		if (!simulation_is_running)
			break ;
		current_time_us = ph_time_us(PH_TIME_GET);
		time_left_to_sleep_us = alarm_time_us - current_time_us;
		if (time_left_to_sleep_us < PH_TINY_SLEEP_TIME_US)
			usleep(time_left_to_sleep_us);
		else
			usleep(PH_TINY_SLEEP_TIME_US);
		current_time_us = ph_time_us(PH_TIME_GET);
	}
}
