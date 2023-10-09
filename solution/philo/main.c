/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 13:47:52 by dkolodze      #+#    #+#                 */
/*   Updated: 2023/10/09 10:22:43 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void ph_set_strategy(t_simulation *sim)
{
	int i;

	if (sim->args.n_philos == 1)
		sim->philos[0].routine = ph_lonely_routine;
	else
	{
		i = 0;
		while (i < sim->args.n_philos - 1)
		{
			sim->philos[i++].routine = ph_left_to_right_routine;
		}
		sim->philos[sim->args.n_philos - 1].routine = ph_right_to_left_routine;
	}
}

int	main(int argc, char **argv)
{
	int				i;
	t_simulation	simulation;

	if (ph_parse_all_params(argc, argv, &(simulation.args)) != PH_SUCCESS)
		return (1);
	if (ph_init_data(&simulation) != PH_SUCCESS)
		return (2);
	ph_set_strategy(&simulation);
	pthread_mutex_lock(&(simulation.mutex));
	i = 0;
	while (i < simulation.args.n_philos)
	{
		pthread_create(&(simulation.philos[i].thread), \
			NULL, simulation.philos[i].routine, simulation.philos + i);
		i += 1;
	}
	pthread_mutex_unlock(&(simulation.mutex));
	ph_monitor(&simulation);
	ph_cleanup_data(&simulation);
	return (0);
}
