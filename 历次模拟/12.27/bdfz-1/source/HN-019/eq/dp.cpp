#include<iostream>
#include<cstdio>
using namespace std;
int T=100000;
int main()
{
	while (T--)
	{
		system("./rd2");
		system("./eq");
		system("./ps");
		if (system("diff eq.out eq.ans"))
		{
			puts("WA");
			return 0;
		}
		else puts("AC");
	}
	return 0;
}
