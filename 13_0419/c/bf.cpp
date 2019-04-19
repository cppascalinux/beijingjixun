#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<ctime>
#include<queue>
#define ll long long
#define mod 998244353
using namespace std;
int n,tot;
ll ans;
int hd[100009],eg[200009],nxt[200009];
int vis[25000009],pm[10000009],phi[25000009];
int dis[100009];
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void init()
{
	int m=25000000,sm=0;
	for(int i=2;i<=m;i++)
	{
		if(!vis[i])
		{
			pm[++sm]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=sm&&i*pm[j]<=m;j++)
		{
			vis[i*pm[j]]=1;
			if(i%pm[j]==0)
			{
				phi[i*pm[j]]=phi[i]*pm[j];
				break;
			}
			phi[i*pm[j]]=phi[i]*(pm[j]-1);
		}
	}
}
void bfs(int s)
{
	memset(dis+1,0,n<<2);
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=hd[x];i;i=nxt[i])
			if(!dis[eg[i]]&&eg[i]!=s)
			{
				dis[eg[i]]=dis[x]+1;
				q.push(eg[i]);
			}
	}
	for(int i=1;i<=n;i++)
		ans+=(ll)phi[i*s]*dis[i];
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("bf.out","w",stdout);
#endif
	init();
	scanf("%d",&n);
	for(int i=1,a,b;i<=n-1;i++)
	{
		scanf("%d%d",&a,&b);
		ins(a,b);
		ins(b,a);
	}
	for(int i=1;i<=n;i++)
	{
		bfs(i);
		ans%=mod;
	}
	printf("%lld",ans);
	cerr<<clock();
	return 0;
}