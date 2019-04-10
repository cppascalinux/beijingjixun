#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define ll long long
#define mod 998244353
using namespace std;
int n,k,s;
ll ans;
int v[1000009];
int pre[1009][1009];
int st[10];
int gcd(int a,int b)
{
	return !b?a:gcd(b,a%b);
}
int get(int a,int b)
{
	if(a<=1000&&b<=1000)
		return pre[a][b];
	return !b?a:gcd(b,a%b);
}
void dfs(int d,int sm,int lst,int g)
{
	if(d>k)
	{
		// printf("%d %d g:%d\n",st[1],st[2],g);
		if(sm==s)
			ans+=g;
		return;
	}
	for(int i=lst+1;i<=n;i++)
		dfs(d+1,sm^v[i],i,g?get(g,v[i]):v[i]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&k,&s);
	for(int i=1;i<=n;i++)
		scanf("%d",v+i);
	for(int i=1;i<=1000;i++)
		for(int j=i;j<=1000;j++)
			pre[i][j]=pre[j][i]=gcd(i,j);
	dfs(1,0,0,0);
	printf("%lld",ans%mod);
	cerr<<clock();
	return 0;
}