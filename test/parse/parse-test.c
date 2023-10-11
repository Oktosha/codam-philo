#include <assert.h>
#include "philo.h"

int main(int argc, char **argv)
{
	t_sim_args	args = {};
	t_status	status;

	printf("# given args\n");
	status = ph_parse_all_args(argc, argv, &args);
	printf("¯\\_(ツ)_/¯\n\n");

	printf("# too few args\n");
	status = ph_parse_all_args(2, NULL, &args);
	assert(status == PH_ERROR);
	printf("..correct!\n\n");

	printf("# too many args\n");
	status = ph_parse_all_args(8, NULL, &args);
	assert(status == PH_ERROR);
	printf("..correct!\n\n");

	printf("# normal args\n");
	char *normal[] = {"test", "1", "12", "30", "100"};
	status = ph_parse_all_args(5, normal, &args);
	assert(status == PH_SUCCESS);
	assert(args.n_philos == 1);
	assert(args.time_to_die_ms == 12);
	assert(args.time_to_eat_ms == 30);
	assert(args.time_to_sleep_ms == 100);
	assert(args.times_each_eats == -1);
	printf("..correct!\n\n");

	printf("# optional arg\n");
	char *normal_with_optional[] = {"test", "1", "12", "30", "100", "10"};
	status = ph_parse_all_args(6, normal_with_optional, &args);
	assert(status == PH_SUCCESS);
	assert(args.n_philos == 1);
	assert(args.time_to_die_ms == 12);
	assert(args.time_to_eat_ms == 30);
	assert(args.time_to_sleep_ms == 100);
	assert(args.times_each_eats == 10);
	printf("..correct!\n\n");

	printf("# big num\n");
	char *big_num[] = {"test", "100000000", "12", "30", "100"};
	status = ph_parse_all_args(5, big_num, &args);
	assert(status == PH_ERROR);
	printf("..correct!\n\n");
	
	return 0;
}
