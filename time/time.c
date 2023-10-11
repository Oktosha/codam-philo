#include "philo.h"

int main()
{
	struct timeval	val;

	gettimeofday(&val, NULL);
	printf("%ld %ld\n", val.tv_sec, val.tv_usec);
	t_ph_time timestamp = ph_time_us();
	printf("%lld\n", timestamp);
	timestamp = ph_time_us();
	printf("%lld\n", timestamp);
	usleep(1000);
	timestamp = ph_time_us();
	printf("%lld\n", timestamp);
	gettimeofday(&val, NULL);
	printf("%ld %ld\n", val.tv_sec, val.tv_usec);
	return 0;
}