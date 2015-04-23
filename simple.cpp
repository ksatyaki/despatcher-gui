#include <peiskernel/peiskernel_mt.h>
#include <unistd.h>

int main(int argn, char* args[])
{
	peiskmt_initialize(&argn, args);
	sleep(2);

	return 0;
}
