//2019.04.09
//ezoj1586 Problem C: 法 乱搞+缩图+预处理前缀和+bfs
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define pii pair<int,int>
#define fi first
#define se second
#define ll long long
using namespace std;
int n,m,tot,smp,sm2;
ll ans;
int hd1[120009],eg1[240009],nxt1[240009];
int hd2[120009],eg2[240009],nxt2[240009];
int deg[120009],sz[120009],mp[120009];
int sp[509],pos[120009];
int dis[509][120009],vis[120009];
int f[120009],gl[120009],gr[120009];
int smd[120009];
vector<int> v[1009],sm0[1009],sm1[1009];
pii e[1009];
void ins(int a,int b,int *hd,int *eg,int *nxt)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void init()
{
	queue<int> q;
	for(int i=1;i<=n;i++)
	{
		if(deg[i]==1)
			q.push(i);
		sz[i]=1;
	}
	while(!q.empty())
	{
		int x=q.front();
		ans+=2LL*sz[x]*(n-sz[x]);
		q.pop();
		for(int i=hd1[x];i;i=nxt1[i])
			if(deg[eg1[i]]>1)
			{
				sz[eg1[i]]+=sz[x];
				if(--deg[eg1[i]]<=1)
					q.push(eg1[i]);
			}
	}
}
void rebuild()
{
	int n1=0;
	for(int i=1;i<=n;i++)
		if(deg[i]>1)
			mp[i]=++n1;
	tot=0;
	for(int i=1;i<=n;i++)
		if(deg[i]>1)
			for(int j=hd1[i];j;j=nxt1[j])
				if(deg[eg1[j]]>1)
					ins(mp[i],mp[eg1[j]],hd2,eg2,nxt2);
	for(int i=1;i<=n;i++)
		if(deg[i]>1)
			deg[mp[i]]=deg[i];
	n=n1;
	for(int i=1;i<=n;i++)
		if(deg[i]>=3)
		{
			sp[++smp]=i;
			pos[i]=smp;
		}
}
void bfs(int s)
{
	memset(vis,0,sizeof(vis));
	queue<int> q;
	vis[s]=1;
	q.push(s);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=hd2[x];i;i=nxt2[i])
			if(!vis[eg2[i]])
			{
				dis[s][eg2[i]]=dis[s][x]+1;
				vis[eg2[i]]=1;
				q.push(eg2[i]);
			}
	}
}
int fnd(int x)
{
	return x==f[x]?x:f[x]=fnd(f[x]);
}
void gete()
{
	for(int i=1;i<=n;i++)
		f[i]=i;
	for(int i=1;i<=n;i++)
		if(deg[i]==2)
			for(int j=hd2[i];j;j=nxt2[j])
				if(deg[eg2[j]]>=3)
					gl[i]=eg2[j];
	for(int i=1;i<=n;i++)
		if(deg[i]==2)
			for(int j=hd2[i];j;j=nxt2[j])
				if(deg[eg2[j]]==2)
				{
					int fx=fnd(i),fy=fnd(eg2[j]);
					if(fx==fy)
						continue;
					if(gl[fx]&&gl[fy])
						gr[fx]=gl[fy];
					else
						gl[fx]=gl[fx]|gl[fy];
					f[fy]=fx;
				}
	for(int i=1;i<=n;i++)
		if(deg[i]==2&&f[i]==i)
		{
			sm2++;
			e[sm2]=pii(gl[i],gr[i]);
			
		}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c1.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		ins(a,b,hd1,eg1,nxt1),ins(b,a,hd1,eg1,nxt1);
		deg[a]++,deg[b]++;
	}
	init();
	rebuild();
	for(int i=1;i<=smp;i++)
		bfs(sp[i]);
	gete();
	return 0;
}