/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 12:13:04 by codespace     #+#    #+#                 */
/*   Updated: 2023/10/03 13:29:26 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_status	parse_error(char *s)
{
	printf("%s\n", s);
	return (ERROR);
}

static t_status	parse_param(char *s, int *res)
{
	int i;

	*res = 0;
	i = 0;
	if (s[0] == '\0')
		return (parse_error("the given number is an empty string"));
	if (s[0] == '0')
		return (parse_error("the given number starts with zero"));
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (parse_error("the given number contains non-num character"));
		*res = *res * 10 + (s[i] - '0');
		++i;
		if (i > 7)
			return (parse_error("the given number is too big"));
	}
	return (SUCCESS);
}

t_status	parse_all_params(int argc, char **argv, t_sim_params *params)
{
	params->times_each_philo_eats = -1;
	if (argc < 5 || argc > 6)
		return parse_error("invalid number of args, must be 4 or 5");
	if (parse_param(argv[1], &(params->number_of_philosophers)) != SUCCESS)
		return (parse_error("can't parse arg #1: number_of_philosophers\n"
			"must be a positive integer without whitespaces, leading 0 or +"));
	if (parse_param(argv[2], &(params->time_to_die)) != SUCCESS)
		return (parse_error("can't parse arg #2: time_to_die\n"
			"must be a positive integer without whitespaces, leading 0 or +"));
	if (parse_param(argv[3], &(params->time_to_eat)) != SUCCESS)
		return (parse_error("can't parse arg #3: time_to_eat\n"
			"must be a positive integer without whitespaces, leading 0 or +"));
	if (parse_param(argv[4], &(params->time_to_sleep)) != SUCCESS)
		return (parse_error("can't parse arg #4: time_to_sleep\n"
			"must be a positive integer without whitespaces, leading 0 or +"));
	if (argc == 6 \
		&& parse_param(argv[5], &(params->times_each_philo_eats)) != SUCCESS)
		return (parse_error("can't parse optional arg #5: "
			"[number_of_times_each_philosopher_must_eat]\n"
			"must be a positive integer without whitespaces, leading 0 or +"));
	return (SUCCESS);
}