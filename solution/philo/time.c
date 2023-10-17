/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 14:05:45 by codespace     #+#    #+#                 */
/*   Updated: 2023/10/17 15:31:30 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "philo.h"

static t_ph_time	ph_absolute_time_us(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (((t_ph_time)(t.tv_sec)) * 1000000ll + (t_ph_time)(t.tv_usec));
}

t_ph_time	ph_time_us(t_ph_time_action action)
{
	static t_ph_time	start_time = PH_NOT_STARTED;

	if (action == PH_TIME_SET)
	{
		assert(start_time == PH_NOT_STARTED);
		start_time = ph_absolute_time_us();
		return (start_time);
	}
	if (action == PH_TIME_GET)
		return (ph_absolute_time_us() - start_time);
	printf("BUG: requesting time with wrong action constant");
	return (-100);
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
