//#include <stdio.h>
//#include <time.h>
//#include<string>
//using namespace std;
//int main()
//{
//	time_t curtime;
//
//	time(&curtime);
//
//	string registration_time(ctime(&curtime));
//	printf(registration_time.c_str());
//
//	return(0);
//	
//}


//#include <windows.h>
//#include <stdio.h>
//#include <string>
//#include <iostream>
//using namespace std;
//int main(void)
//{
//	SYSTEMTIME sys;
//	GetLocalTime(&sys);
//	string daytime = to_string(sys.wYear) + "-" + to_string(sys.wMonth) + "-" + to_string(sys.wDay) + 
//		" " + to_string(sys.wHour) + ":" + to_string(sys.wMinute) + ":" + to_string(sys.wSecond) + ":" + to_string(sys.wMilliseconds);
//	cout << daytime << endl;
//	printf("%4d-%02d-%02d %02d:%02d:%02d.%03d\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
//	return 0;
//}


#include <windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

int main() {
	string a = "12345";
	string b = a.substr(2, a.length() - 2);
	cout << b << endl;
}





