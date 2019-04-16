//2019.04.16
//ezoj1589 故障电灯(light) 贪心+二分图最大匹配+dinic
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define inf 0x7F7F7F7F
using namespace std;
int n,tot=1,st,ed,smv;
int vis[10000009],pm[10000009];
int dis[10000009];
int s[109];
int stv[209];
int hd[209],eg[100009],nxt[100009],cap[100009];
int dep[209],cur[209];
void clr()
{
	for(int i=1;i<=smv;i++)
		dis[stv[i]]=0;
	memset(hd,0,sizeof(hd));
	tot=1;
	smv=0;
}
void init()
{
	int tot=0,m=10000007;
	vis[0]=1;
	vis[1]=1;
	for(int i=2;i<=m;i++)
	{
		if(!vis[i])
			pm[++tot]=i;
		for(int j=1;j<=tot&&i*pm[j]<=m;j++)
		{
			vis[i*pm[j]]=1;
			if(i%pm[j]==0)
				break;
		}
	}
	vis[2]=1;
}
void ins(int a,int b,int c)
{
	eg[++tot]=b;
	cap[tot]=c;
	nxt[tot]=hd[a];
	hd[a]=tot;
	eg[++tot]=a;
	cap[tot]=0;
	nxt[tot]=hd[b];
	hd[b]=tot;
}
int bfs()
{
	queue<int> q;
	memset(dep,0,sizeof(dep));
	dep[st]=1;
	q.push(st);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=hd[x];i;i=nxt[i])
			if(cap[i]&&!dep[eg[i]])
			{
				dep[eg[i]]=dep[x]+1;
				q.push(eg[i]);
			}
	}
	return dep[ed];
}
int dfs(int x,int a)
{
	if(x==ed||!a)
		return a;
	int f,totf=0;
	for(int &i=cur[x];i;i=nxt[i])
		if(cap[i]&&dep[eg[i]]==dep[x]+1&&(f=dfs(eg[i],min(a,cap[i]))))
		{
			cap[i]-=f;
			cap[i^1]+=f;
			a-=f;
			totf+=f;
			if(!a)
				break;
		}
	return totf;
}
int flow()
{
	int totf=0;
	while(bfs())
	{
		for(int i=1;i<=smv+2;i++)
			cur[i]=hd[i];
		totf+=dfs(st,inf);
	}
	return totf;
}
void solve()
{
	int s1=0,s2=0;
	for(int i=1;i<=n;i++)
		dis[s[i]]^=1,dis[s[i]+1]^=1;
	for(int i=1;i<=n;i++)
	{
		if(dis[s[i]])
			stv[++smv]=s[i];
		if(dis[s[i]+1])
			stv[++smv]=s[i]+1;
	}
	st=smv+1,ed=smv+2;
	for(int i=1;i<=smv;i++)
	{
		if(stv[i]&1)
		{
			s1++;
			ins(st,i,1);
			for(int j=1;j<=smv;j++)
				if(!vis[abs(stv[i]-stv[j])])
					ins(i,j,1);
		}
		else
		{
			s2++;
			ins(i,ed,1);
		}
	}
	int k=flow();
	printf("%d\n",k+(s1-k)/2*2+(s2-k)/2*2+((s1-k)&1)*3);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	init();
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",s+i);
		solve();
		clr();
	}
	return 0;
}