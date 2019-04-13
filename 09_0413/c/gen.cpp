#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<random>
using namespace std;
int main()
{
	freopen("c.in","w",stdout);
	mt19937 rnd(time(0));
	printf("0 0 -1\n");
	for(int i=1;i<=3;i++)
		printf("%d %d %d\n",rnd()%15-7,rnd()%15-7,0);
	int n=10;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d %d %d %d %d %d %d %d\n",2,0,0,1,0,0,0,i);
	return 0;
}