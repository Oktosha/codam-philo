/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   announce.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 13:12:15 by codespace     #+#    #+#                 */
/*   Updated: 2023/10/04 14:16:42 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_announce(t_simulation *simulation, int philo, t_event event)
{
	t_relative_time	timestamp;

	pthread_mutex_lock(&(simulation->mutex));
	timestamp = ph_time(simulation);
	ph_update_status(simulation, timestamp);
	if (simulation->status != SIM_RUN)
		return ;
	printf("%d ")
}