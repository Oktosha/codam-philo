#include <assert.h>
#include "philo.h"

int main(int argc, char **argv)
{
	t_sim_params	params = {};
	t_status		status;

	printf("# given args\n");
	status = ph_parse_all_params(argc, argv, &params);
	printf("¯\\_(ツ)_/¯\n\n");

	printf("# too few args\n");
	status = ph_parse_all_params(2, NULL, &params);
	assert(status == PH_ERROR);
	printf("..correct!\n\n");

	printf("# too many args\n");
	status = ph_parse_all_params(8, NULL, &params);
	assert(status == PH_ERROR);
	printf("..correct!\n\n");

	printf("# normal args\n");
	char *normal[] = {"test", "1", "12", "30", "100"};
	status = ph_parse_all_params(5, normal, &params);
	assert(status == PH_SUCCESS);
	assert(params.n_philos == 1);
	assert(params.time_to_die == 12);
	assert(params.time_to_eat == 30);
	assert(params.time_to_sleep == 100);
	assert(params.times_each_eats == -1);
	printf("..correct!\n\n");

	printf("# optional arg\n");
	char *normal_with_optional[] = {"test", "1", "12", "30", "100", "10"};
	status = ph_parse_all_params(6, normal_with_optional, &params);
	assert(status == PH_SUCCESS);
	assert(params.n_philos == 1);
	assert(params.time_to_die == 12);
	assert(params.time_to_eat == 30);
	assert(params.time_to_sleep == 100);
	assert(params.times_each_eats == 10);
	printf("..correct!\n\n");

	printf("# big num\n");
	char *big_num[] = {"test", "100000000", "12", "30", "100"};
	status = ph_parse_all_params(5, big_num, &params);
	assert(status == PH_ERROR);
	printf("..correct!\n\n");
	
	return 0;
}