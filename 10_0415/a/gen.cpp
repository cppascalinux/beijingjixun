#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
#include<ctime>
using namespace std;
int main()
{
	freopen("a.in","w",stdout);
	mt19937 rnd(time(0));
	int n=500;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			printf("%d ",rnd()%2000000000-1000000000);
		printf("\n");
	}
	return 0;
}