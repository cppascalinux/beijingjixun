#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long
using namespace std;
int n,m,tot;
int hd[120009],eg[240009],nxt[240009];
int dis[120009],sz[120009],vis[120009];
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs(int x,int fa,ll &ans)
{
	sz[x]=1;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			dfs(eg[i],x,ans);
			sz[x]+=sz[eg[i]];
		}
	ans+=(ll)sz[x]*(n-sz[x]);
}
void solve0()
{
	ll ans=0;
	dfs(1,0,ans);
	printf("%lld",ans);
}
ll bfs(int s)
{
	memset(vis,0,(n+1)<<2);
	queue<int> q;
	q.push(s);
	vis[s]=1;
	dis[s]=0;
	ll ans=0;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=hd[x];i;i=nxt[i])
			if(!vis[eg[i]])
			{
				vis[eg[i]]=1;
				dis[eg[i]]=dis[x]+1;
				ans+=dis[eg[i]];
				q.push(eg[i]);
			}
	}
	// printf("x:%d ===================\n",x);
	// for(int i=1;i<=n;i++)
	// 	printf("%d ",dis[i]);
	// printf("\n");
	return ans;
}
void solve1()
{
	ll ans=0;
	for(int i=1;i<=n;i++)
		ans+=bfs(i);
	printf("%lld",ans>>1);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		ins(a,b);
		ins(b,a);
	}
	if(m==n-1)
		solve0();
	else
		solve1();
	return 0;
}