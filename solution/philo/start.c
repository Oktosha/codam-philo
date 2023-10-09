/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 14:12:04 by codespace     #+#    #+#                 */
/*   Updated: 2023/10/09 10:04:09 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_wait_for_the_start(t_philo *philo)
{
	int	should_wait;

	should_wait = PH_TRUE;
	while (should_wait)
	{
		pthread_mutex_lock(&(philo->sim->mutex));
		if (philo->sim->status != SIM_INIT)
			should_wait = PH_FALSE;
		pthread_mutex_unlock(&(philo->sim->mutex));
	}
}
