/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 13:47:52 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/10/03 13:06:53 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	simulation;

	if (parse_all_params(argc, argv, &(simulation.params)) != SUCCESS)
		return (1);
	return (0);
}
