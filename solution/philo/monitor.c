/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 13:31:00 by codespace     #+#    #+#                 */
/*   Updated: 2023/10/09 10:28:59 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_get_index_of_earliest_dead(t_simulation *sim, int timestamp)
{
	int	i;
	int	ans_i;

	ans_i = 0;
	i = 1;
	while (i < sim->args.n_philos)
	{
		if (sim->philos[i].death_time < sim->philos[ans_i].death_time)
			ans_i = i;
	}
	if (sim->philos[ans_i].death_time <= timestamp)
		return (ans_i);
	return (PH_NOT_FOUND);
}

static t_ph_bool	ph_all_are_full(t_simulation *sim)
{
	int	i;
	int	n_full;

	i = 0;
	n_full = 0;
	while (i < sim->args.n_philos)
	{
		if (sim->philos[i].eaten_meals >= sim->args.times_each_eats)
			n_full += 1;
		i += 1;
	}
	if (n_full == sim->args.n_philos)
		return (PH_TRUE);
	return (PH_FALSE);
}

void	ph_update_status(t_simulation *simulation, int timestamp)
{
	int	dead_i;
	int	dead_name;
	int	death_time;

	if (simulation->status != SIM_RUN)
		return ;
	dead_i = ph_get_index_of_earliest_dead(simulation, timestamp);
	if (dead_i != PH_NOT_FOUND)
	{
		dead_name = simulation->philos[dead_i].name;
		death_time = simulation->philos[dead_i].death_time;
		printf("%d %d died\n", death_time, dead_name);
		simulation->status = SIM_END;
		return ;
	}
	if (ph_all_are_full(simulation))
		simulation->status = SIM_END;
}

void	ph_monitor(t_simulation *simulation)
{
	int	should_monitor;
	int	timestamp;

	should_monitor = PH_TRUE;
	while (should_monitor)
	{
		pthread_mutex_lock(&(simulation->mutex));
		timestamp = ph_time(simulation->start_time);
		ph_update_status(simulation, timestamp);
		if (simulation->status != SIM_RUN)
			should_monitor = PH_FALSE;
		pthread_mutex_unlock(&(simulation->mutex));
		usleep(PH_MONITOR_USLEEP_TIME);
	}
}
