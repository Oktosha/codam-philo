/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 12:13:04 by codespace     #+#    #+#                 */
/*   Updated: 2023/10/09 11:02:06 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	ph_parse_arg(char *s, int *res)
{
	int	i;

	*res = 0;
	i = 0;
	if (s[0] == '\0')
		return (ph_error("the given number is an empty string"));
	if (s[0] == '0')
		return (ph_error("the given number starts with zero"));
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (ph_error("the given number contains non-num character"));
		*res = *res * 10 + (s[i] - '0');
		++i;
		if (i > 7)
			return (ph_error("the given number is too big"));
	}
	return (PH_SUCCESS);
}

t_status	ph_parse_all_args(int argc, char **argv, t_sim_args *args)
{
	args->times_each_eats = -1;
	if (argc < 5 || argc > 6)
		return (ph_error("invalid number of args, must be 4 or 5"));
	if (ph_parse_arg(argv[1], &(args->n_philos)) != PH_SUCCESS)
		return (ph_error("can't parse arg #1: number_of_philosophers\n" \
			"must be a positive integer without whitespaces, leading 0 or +"));
	if (ph_parse_arg(argv[2], &(args->time_to_die)) != PH_SUCCESS)
		return (ph_error("can't parse arg #2: time_to_die\n" \
			"must be a positive integer without whitespaces, leading 0 or +"));
	if (ph_parse_arg(argv[3], &(args->time_to_eat)) != PH_SUCCESS)
		return (ph_error("can't parse arg #3: time_to_eat\n" \
			"must be a positive integer without whitespaces, leading 0 or +"));
	if (ph_parse_arg(argv[4], &(args->time_to_sleep)) != PH_SUCCESS)
		return (ph_error("can't parse arg #4: time_to_sleep\n" \
			"must be a positive integer without whitespaces, leading 0 or +"));
	if (argc == 6 \
		&& ph_parse_arg(argv[5], &(args->times_each_eats)) != PH_SUCCESS)
		return (ph_error("can't parse optional arg #5: " \
			"[number_of_times_each_philosopher_must_eat]\n" \
			"must be a positive integer without whitespaces, leading 0 or +"));
	return (PH_SUCCESS);
}
