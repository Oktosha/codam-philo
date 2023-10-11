/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 14:05:45 by codespace     #+#    #+#                 */
/*   Updated: 2023/10/11 13:17:58 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_ph_time	ph_absolute_time_us(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t_ph_time)(t.tv_sec)) * 1000000ll + (t_ph_time)(t.tv_usec);

}

t_ph_time	ph_time_us(void)
{
	static t_ph_time	start_time = PH_NOT_STARTED;
	t_ph_time			t;

	t = ph_absolute_time_us();
	if (start_time == PH_NOT_STARTED)
	{
		start_time = t;
		return (0);
	}
	return (t - start_time);
}

t_ph_time	ph_time_to_eat_us(t_simulation *sim)
{
	return (((t_ph_time)(sim->args.time_to_eat_ms)) * 1000ll);
}

t_ph_time	ph_time_to_die_us(t_simulation *sim)
{
	return (((t_ph_time)(sim->args.time_to_die_ms)) * 1000ll);
}

t_ph_time	ph_time_to_sleep_us(t_simulation *sim)
{
	return (((t_ph_time)(sim->args.time_to_sleep_ms)) * 1000ll);
}
