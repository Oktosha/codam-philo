/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   announce.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 13:54:56 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/10/11 16:07:14 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_announce(t_ph_time timestamp_us, t_philo *philo, char *message)
{
	t_ph_time	timestamp_ms;

	timestamp_ms = timestamp_us / 1000ll;
	pthread_mutex_lock(&(philo->sim->mutex));
	ph_update_status(philo->sim, timestamp_us);
	printf("%lld %d %s; status = %d\n", timestamp_ms, philo->name, message, philo->sim->status);
	pthread_mutex_unlock(&(philo->sim->mutex));
}
