#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<random>
#define mod 998244353
using namespace std;
int main()
{
	freopen("a.in","w",stdout);
	mt19937 rnd(time(0));
	int n=100000;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d %d %d\n",rnd()%mod,rnd()%mod,rnd()%mod);
	return 0;
}