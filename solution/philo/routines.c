/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routines.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 13:00:32 by codespace     #+#    #+#                 */
/*   Updated: 2023/10/04 14:16:40 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ph_lonely_routine(void	*arg)
{
	t_philo	*self;

	self = arg;
	pthread_mutex_lock(self->left_fork);
	
}