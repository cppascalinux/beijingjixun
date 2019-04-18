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
	int typ=0,n=1000,m=1000,q=1000;
	printf("%d\n%d %d %d\n",typ,n,m,q);
	for(int i=1;i<=n;i++)
		printf("%c",rnd()%26+'a');
	printf("\n");
	for(int i=1;i<=n;i++)
	{
		int a=rnd()%3+1;
		if(a==1)
			printf("%d %d\n",a,rnd()%m+1);
		else if(a==2)
			printf("%d %c\n",a,rnd()%26+'a');
		else
			printf("%d %d\n",a,rnd()%m+1);
	}
	return 0;
}