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
int n,m,tot,smp,cnt;
ll ans;
int hd1[120009],eg1[240009],nxt1[240009];
int hd2[120009],eg2[240009],nxt2[240009];
int deg[120009],sz[120009],mp[120009];
int sp[509],pos[120009];
int dis[509][120009],vis[120009];
int gl[120009],gr[120009];
int seq[120009];
vector<int> v[1009];
vector<ll> sm1[1009],sm0[1009];
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
	int t=m;
	while(!q.empty())
	{
		int x=q.front();
		if(t)
			ans+=2LL*sz[x]*(n-sz[x]);
		t--;
		// printf("x:%d sz:%d ans:%d\n",x,sz[x],ans);
		q.pop();
		for(int i=hd1[x];i;i=nxt1[i])
			if(deg[eg1[i]]>1)
			{
				sz[eg1[i]]+=sz[x];
				if(--deg[eg1[i]]<=1)
					q.push(eg1[i]);
			}
	}
	// printf("ans:%I64d\n",ans);
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
			sz[mp[i]]=sz[i];
	n=n1;
	for(int i=1;i<=n;i++)
	{
		deg[i]=0;
		for(int j=hd2[i];j;j=nxt2[j])
			deg[i]++;
	}
	for(int i=1;i<=n;i++)
		if(deg[i]>=3)
		{
			sp[++smp]=i;
			pos[i]=smp;
		}
	if(!smp)
	{
		sp[++smp]=1;
		pos[1]=smp;
		deg[1]++;
	}
	// for(int i=1;i<=n;i++)
		// printf("i:%d sz:%d deg:%d pos:%d\n",i,sz[i],deg[i],pos[i]);
}
void bfs(int s,int *dis)
{
	memset(vis,0,sizeof(vis));
	queue<int> q;
	vis[s]=1;
	dis[s]=0;
	q.push(s);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=hd2[x];i;i=nxt2[i])
			if(!vis[eg2[i]])
			{
				dis[eg2[i]]=dis[x]+1;
				vis[eg2[i]]=1;
				q.push(eg2[i]);
			}
	}
}
void dfs(int x,int fa,int lp)
{
	v[cnt].push_back(x);
	seq[x]=v[cnt].size()-1;
	vis[x]=cnt;
	// if(gr[x])
	// {
	// 	e[cnt]=pii(lp,gr[x]?gr[x]:gl[x]);
	// 	return;
	// }
	int ch=0;
	for(int i=hd2[x];i;i=nxt2[i])
		if(deg[eg2[i]]==2&&eg2[i]!=fa)
		{
			ch=1;
			dfs(eg2[i],x,lp);
		}
	if(!ch)
		e[cnt]=pii(lp,gr[x]?gr[x]:gl[x]);
}
void gete()
{
	for(int i=1;i<=n;i++)
		if(deg[i]==2)
			for(int j=hd2[i];j;j=nxt2[j])
				if(deg[eg2[j]]>=3)
				{
					if(gl[i])
						gr[i]=eg2[j];
					else
						gl[i]=eg2[j];
				}
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
		if(deg[i]==2&&!vis[i]&&gl[i])
		{
			cnt++;
			dfs(i,0,gl[i]);
		}
	for(int i=1;i<=cnt;i++)
	{
		sm0[i].resize(v[i].size());
		sm1[i].resize(v[i].size());
		sm0[i][0]=sm1[i][0]=sz[v[i][0]];
		for(int j=1;j<(int)v[i].size();j++)
		{
			sm0[i][j]=sm0[i][j-1]+sz[v[i][j]];
			sm1[i][j]=sm1[i][j-1]+(ll)(j+1)*sz[v[i][j]];
		}
	}
}
void solve()
{
	for(int i=1;i<=n;i++)
	{
		if(pos[i])
		{
			for(int j=1;j<=n;j++)
				ans+=(ll)sz[i]*sz[j]*dis[pos[i]][j];
		}
		else
		{
			ll tsm=0;
			for(int j=1;j<=smp;j++)
			{
				tsm+=(ll)sz[sp[j]]*dis[j][i];
				// printf("i:%d tsm:%I64d\n",i,tsm);
			}
			for(int j=1;j<=cnt;j++)
				if(j!=vis[i])
				{
					int disl=dis[pos[e[j].fi]][i],disr=dis[pos[e[j].se]][i];
					int len=v[j].size();
					int mid=disr-disl+len-1;
					if(mid!=-1)
						mid/=2;
					// printf("\ti:%d j:%d mid:%d disl:%d disr:%d\n",i,j,mid,disl,disr);
					mid=max(mid,-1);
					mid=min(mid,len-1);
					ll t=tsm;
					if(mid>-1)
						tsm+=(ll)sm0[j][mid]*disl+sm1[j][mid];
					if(mid<len-1)
						tsm+=(ll)(sm0[j][len-1]-(mid>-1?sm0[j][mid]:0))*disr+(sm0[j][len-1]-(mid>-1?sm0[j][mid]:0))*(len+1)-(sm1[j][len-1]-(mid>-1?sm1[j][mid]:0));
					// printf("\tadd:%I64d\n",tsm-t);
				}
			// printf("i:%d tsm2:%I64d\n",i,tsm);
			int p=seq[i],id=vis[i],lsp=pos[e[id].fi],rsp=pos[e[id].se],len=v[id].size();
			int midl=p-1-dis[lsp][i];
			if(midl!=-1)
				midl/=2;
			int midr=(len+dis[rsp][i]+p+1)/2;
			midl=max(midl,-1);
			midl=min(midl,p-1);
			midr=max(midr,p+1);
			midr=min(midr,len);
			// printf("len:%d midl:%d midr:%d\n",len,midl,midr);
			if(midl>-1)
				tsm+=(ll)sm0[id][midl]*dis[lsp][i]+sm1[id][midl];
			if(midl<p-1)
				tsm+=(ll)(sm0[id][p-1]-(midl>-1?sm0[id][midl]:0))*p-(sm1[id][p-1]-(midl>-1?sm1[id][midl]:0));
			if(midr>p+1)
				tsm+=(sm1[id][midr-1]-sm1[id][p])-(ll)(sm0[id][midr-1]-sm0[id][p])*p;
			if(midr<len)
				tsm+=(ll)(sm0[id][len-1]-(midr>0?sm0[id][midr-1]:0))*dis[rsp][i]+(ll)(sm0[id][len-1]-(midr>0?sm0[id][midr-1]:0))*(len+1)-(sm1[id][len-1]-(midr>0?sm1[id][midr-1]:0));
			ans+=tsm*sz[i];
		}
		// printf("i:%d ans:%I64d\n",i,ans);
	}
	printf("%I64d",ans>>1);
}
void dbg()
{
	for(int i=1;i<=smp;i++)
	{
		for(int j=1;j<=n;j++)
			printf("%d ",dis[i][j]);
		printf("\n");
	}
	for(int i=1;i<=n;i++)
		printf("i:%d gl:%d gr:%d\n",i,gl[i],gr[i]);
	for(int i=1;i<=cnt;i++)
	{
		printf("i:%d l:%d r:%d====================\n",i,e[i].fi,e[i].se);
		for(int j=0;j<(int)v[i].size();j++)
			printf("\tj:%d v:%d sm0:%d sm1:%I64d\n",j,v[i][j],sm0[i][j],sm1[i][j]);
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
		bfs(sp[i],dis[i]);
	gete();
	// dbg();
	solve();
	return 0;
}