#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
#include<ctime>
using namespace std;
int main()
{
	freopen("b.in","w",stdout);
	mt19937 rnd(time(0));
	int n=1000,k=3,s=500;
	printf("%d %d %d\n",n,k,s);
	for(int i=1;i<=n;i++)
		printf("%d ",rnd()%1000);
	return 0;
}