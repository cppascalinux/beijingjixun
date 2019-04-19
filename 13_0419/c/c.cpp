#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<ctime>
#define ll long long
#define mod 998244353
#define inf 0x7F7F7F7F
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,tot,mn,rt;
int pm[100009],vis[100009],mu[100009],phi[100009];
int g[100009];
int hd[100009],eg[200009],nxt[200009];
int sz[100009],f[100009];
vector<int> dis[100009];
int ad1[100009],ad2[100009],rm1[100009],rm2[100009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void init()
{
	int tp=0;
	phi[1]=mu[1]=vis[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!vis[i])
		{
			pm[++tp]=i;
			mu[i]=-1;
			phi[i]=i-1;
		}
		for(int j=1;j<=tp&&i*pm[j]<=n;j++)
		{
			vis[i*pm[j]]=1;
			if(i%pm[j]==0)
			{
				mu[i*pm[j]]=0;
				phi[i*pm[j]]=phi[i]*pm[j];
				break;
			}
			mu[i*pm[j]]=-mu[i];
			phi[i*pm[j]]=phi[i]*(pm[j]-1);
		}
	}
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d vis:%d phi:%d mu:%d\n",i,vis[i],phi[i],mu[i]);
}
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)
			ans=(ll)ans*a%mod;
	return ans;
}
void initg()
{
	for(int i=1;i<=n;i++)
		for(int j=i,k=1;j<=n;j+=i,k++)
			g[j]=(g[j]+(ll)i*qpow(phi[i],mod-2)%mod*(mod+mu[k]))%mod;
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d g:%d\n",i,g[i]);
}
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void getrt(int x,int fa,int siz)
{
	sz[x]=1;
	int mx=0;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa&&!vis[eg[i]])
		{
			getrt(eg[i],x,siz);
			sz[x]+=sz[eg[i]];
			mx=max(mx,sz[eg[i]]);
		}
	mx=max(mx,siz-sz[x]);
	if(mx<mn)
	{
		mn=mx;
		rt=x;
	}
}
void dfs(int x,int fa,int d)
{
	dis[x].push_back(d);
	for(int i=hd[x];i;i=nxt[i])
		if(!vis[eg[i]]&&eg[i]!=fa)
			dfs(eg[i],x,d+1);
}
void build(int x,int siz)
{
	vis[x]=1;
	dfs(x,0,0);
	for(int i=hd[x];i;i=nxt[i])
		if(!vis[eg[i]])
		{
			int nsz=sz[eg[i]]>sz[x]?siz-sz[x]:sz[eg[i]];
			mn=inf;
			getrt(eg[i],0,nsz);
			f[rt]=x;
			build(rt,nsz);
		}
}
int cal(int x)
{
	int cur=x,lst=0,ans=0,pi=phi[x];
	for(int i=0;i<(int)dis[x].size();i++)
	{
		int d=dis[x][i];
		ans=(ans+(ll)pi*d%mod*ad1[cur])%mod;
		ans=(ans+(ll)pi*ad2[cur])%mod;
		ad1[cur]=(ad1[cur]+pi)%mod;
		ad2[cur]=(ad2[cur]+(ll)d*pi)%mod;
		// printf("cur:%d ans;%d\n",cur,ans);
		if(lst)
		{
			ans=(ans-(ll)pi*d%mod*rm1[lst]%mod+mod)%mod;
			ans=(ans-(ll)pi*rm2[lst]%mod+mod)%mod;
			rm1[lst]=(rm1[lst]+pi)%mod;
			rm2[lst]=(rm2[lst]+(ll)d*pi)%mod;
		}
		lst=cur;
		cur=f[cur];
	}
	return ans*2%mod;
}
void cln(int x)
{
	int cur=x,lst=0;
	for(int i=0;i<(int)dis[x].size();i++)
	{
		ad1[cur]=0;
		ad2[cur]=0;
		rm1[lst]=0;
		rm2[lst]=0;
		lst=cur;
		cur=f[cur];
	}
}
void solve()
{
	int ans=0;
	for(int i=1;i<=n;i++)
		if(g[i])
		{
			int tmp=0;
			for(int j=i;j<=n;j+=i)
				tmp=(tmp+cal(j))%mod;
			// printf("i:%d tmp;%d\n",i,tmp);
			ans=(ans+(ll)tmp*g[i])%mod;
			for(int j=i;j<=n;j+=i)
				cln(j);
		}
	printf("%d",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	rd(n);
	init();
	initg();
	for(int i=1,a,b;i<=n-1;i++)
	{
		rd(a),rd(b);
		ins(a,b);
		ins(b,a);
	}
	memset(vis,0,sizeof(vis));
	mn=inf;
	getrt(1,0,n);
	build(rt,n);
	// for(int i=1;i<=n;i++)
		// printf("i:%d f:%d\n",i,f[i]);
	for(int i=1;i<=n;i++)
		reverse(dis[i].begin(),dis[i].end());
	// for(int i=1;i<=n;i++)
	// {
	// 	for(int j=0;j<(int)dis[i].size();j++)
	// 		printf("%d ",dis[i][j]);
	// 	printf("\n");
	// }
	solve();
	// cerr<<clock();
	return 0;
}