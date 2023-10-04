/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 11:59:24 by codespace     #+#    #+#                 */
/*   Updated: 2023/10/04 13:59:13 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	ph_init_mutexes(t_simulation *simulation)
{
	int	status;
	int	i;
	int	j;

	i = 0;
	while (i < simulation->params.n_philos)
	{
		status = pthread_mutex_init(simulation->forks + i, NULL);
		if (status)
		{
			j = 0;
			while (j < i)
				pthread_mutex_destroy(&(simulation->forks[j++]));
			printf("couldn't init fork mutex %d\n", i);
			return (PH_ERROR);
		}
	}
	status = pthread_mutex_init(&(simulation->mutex), NULL);
	if (status)
		return (ph_error("Couln't init simulation mutex"));
	return (PH_SUCCESS);
}

// must be called after the philos array is allocated
static void	ph_init_philos(t_simulation *simulation)
{
	int	i;
	int	left_fork_i;
	int	right_fork_i;

	i = 0;
	while (i < simulation->params.n_philos)
	{
		left_fork_i = i;
		right_fork_i = (i + 1) % simulation->params.n_philos;
		simulation->philos[i].name = i + 1;
		simulation->philos[i].left_fork = simulation->forks + left_fork_i;
		simulation->philos[i].right_fork = simulation->forks + right_fork_i;
		simulation->philos[i].eaten_meals = 0;
		simulation->philos[i].death_time = simulation->params.time_to_die;
		simulation->philos[i].simulation = simulation;
		i += 1;
	}
}

t_status	ph_init_data(t_simulation *simulation)
{
	simulation->status = SIM_INIT;
	simulation->philos = malloc(sizeof(t_philo) * simulation->params.n_philos);
	simulation->forks = malloc(sizeof(t_fork) * simulation->params.n_philos);
	if (simulation->philos == NULL || simulation->forks == NULL)
		return (ph_error("Couldn't allocate memory"));
	if (ph_init_mutexes(simulation) != PH_SUCCESS)
	{
		free(simulation->philos);
		free(simulation->forks);
		return (PH_ERROR);
	}
	ph_init_philos(simulation);
	return (PH_SUCCESS);
}

void	ph_cleanup_data(t_simulation *simulation)
{
	int	i;
	int	status;

	i = 0;
	while (i < simulation->params.n_philos)
	{
		status = pthread_mutex_destroy(&(simulation->forks[i]));
		if (status)
			printf("warning: problem destroying fork mutex %d\n", i);
		++i;
	}
	status = pthread_mutex_destroy(&(simulation->mutex));
	if (status)
		printf("warning: problem destroying simulation mutex\n");
	free(simulation->forks);
	free(simulation->philos);
}
