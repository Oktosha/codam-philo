/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 14:05:45 by codespace     #+#    #+#                 */
/*   Updated: 2023/10/05 14:37:04 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_time(int	offset)
{
	struct timeval	timeval_time;
	int				absolute_time;

	if (offset == PH_NOT_STARTED)
		printf("BUG: attempt to get the time with the offset PH_NOT_STARTED\n");
	if (offset < 0)
		printf("BUG: attempt to get the time with offset %d < 0\n", offset);
	gettimeofday(&timeval_time, NULL);
	absolute_time = timeval_time.tv_sec * 1000 + (timeval_time.tv_usec / 1000);
	return (absolute_time - offset);
}
