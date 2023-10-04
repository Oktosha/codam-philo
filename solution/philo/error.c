/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 11:19:47 by codespace     #+#    #+#                 */
/*   Updated: 2023/10/04 12:15:46 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_status	ph_error(char *s)
{
	printf("%s\n", s);
	return (PH_ERROR);
}
