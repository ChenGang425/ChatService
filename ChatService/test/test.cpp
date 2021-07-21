#include <stdio.h>
#include <time.h>
#include<string>
using namespace std;
int main()
{
	time_t curtime;

	time(&curtime);

	string registration_time(ctime(&curtime));
	printf(registration_time.c_str());

	return(0);
	
}
