/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   announce.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 13:54:56 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/10/05 14:23:34 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_announce(int timestamp, t_philo *philo, char *message)
{
	pthread_mutex_lock(&(philo->sim->mutex));
	ph_update_status(philo->sim, timestamp);
	if (philo->sim->status == SIM_RUN)
		printf("%d %d %s\n", timestamp, philo->name, message);
	pthread_mutex_unlock(&(philo->sim->mutex));
}
