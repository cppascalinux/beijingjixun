#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<random>
#define mx 10LL
using namespace std;
int n,c;
int main()
{
	freopen("b.in","w",stdout);
	mt19937_64 rnd(time(0));
	n=10,c=30;
	printf("1\n%d %d\n",n,c);
	for(int i=1;i<=n-1;i++)
		printf("%lld %lld %lld\n",rnd()%2*2+1,rnd()%(2*mx)-mx,rnd()%(2*mx)-mx);
	printf("%lld %lld %lld\n",3LL,rnd()%(2*mx)-mx,rnd()%(2*mx)-mx);
	return 0;
}