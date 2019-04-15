#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,q,x,y;
int s[500009];
void solve()
{
	int tx=x,ty=y;
	for(int i=1;i<=n;i++)
	{
		if(i&1)
		{
			int v=min(ty,s[i]);
			tx+=v;
			ty-=v;
		}
		else
		{
			int v=min(tx,s[i]);
			tx-=v;
			ty+=v;
		}
	}
	printf("%d\n",tx);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%d%d",&n,&q);
	scanf("%d%d",&x,&y);
	for(int i=1;i<=n;i++)
		scanf("%d",s+i);
	for(int i=1,a,b,c;i<=q;i++)
	{
		scanf("%d",&a);
		if(a==1)
		{
			scanf("%d",&b);
			x=b;
		}
		else if(a==2)
		{
			scanf("%d",&b);
			y=b;
		}
		else
		{
			scanf("%d%d",&b,&c);
			s[b]=c;
		}
		solve();
	}
	return 0;
}