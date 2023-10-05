/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 13:47:52 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/10/05 14:25:02 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	simulation;

	if (ph_parse_all_params(argc, argv, &(simulation.args)) != PH_SUCCESS)
		return (1);
	if (ph_init_data(&simulation) != PH_SUCCESS)
		return (2);
	ph_cleanup_data(&simulation);
	return (0);
}
