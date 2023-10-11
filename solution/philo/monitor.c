/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 13:31:00 by codespace     #+#    #+#                 */
/*   Updated: 2023/10/11 12:59:54 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_get_index_of_earliest_dead(t_simulation *sim, t_ph_time time_us)
{
	int	i;
	int	ans_i;

	ans_i = 0;
	i = 1;
	while (i < sim->args.n_philos)
	{
		if (sim->philos[i].death_time_us < sim->philos[ans_i].death_time_us)
			ans_i = i;
	}
	if (sim->philos[ans_i].death_time_us <= time_us)
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

void	ph_update_status(t_simulation *simulation, t_ph_time timestamp_us)
{
	int			dead_i;
	int			dead_name;
	t_ph_time	death_time;

	if (simulation->status != SIM_RUN)
		return ;
	dead_i = ph_get_index_of_earliest_dead(simulation, timestamp_us);
	if (dead_i != PH_NOT_FOUND)
	{
		dead_name = simulation->philos[dead_i].name;
		death_time = simulation->philos[dead_i].death_time_us / 1000ll;
		printf("%lld %d died\n", death_time, dead_name);
		simulation->status = SIM_END;
		return ;
	}
	if (simulation->args.times_each_eats != -1 && ph_all_are_full(simulation))
		simulation->status = SIM_END;
}

void	ph_monitor(t_simulation *simulation)
{
	int			should_monitor;
	t_ph_time	timestamp;

	should_monitor = PH_TRUE;
	while (should_monitor)
	{
		pthread_mutex_lock(&(simulation->mutex));
		timestamp = ph_time_us();
		ph_update_status(simulation, timestamp);
		if (simulation->status != SIM_RUN)
			should_monitor = PH_FALSE;
		pthread_mutex_unlock(&(simulation->mutex));
		usleep(PH_TINY_SLEEP_TIME_US);
	}
}
