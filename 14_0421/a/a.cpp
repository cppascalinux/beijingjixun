#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<cassert>
#include<climits>
#define pii pair<int,int>
#define fi first
#define se second
#define db double
#define ldb double
#define eps 1e-9
using namespace std;
int n,m,tot;
db str;
char s[1509],t[1509],out[1509];
int o[1509][11],fail[1509];
int sz[1509];
db smv[1509];
db f[1509][1509],g[1509];
int pre0[1509][1509],pre1[1509][1509];
void add(int x)
{
	int l=strlen(t+1);
	for(int i=1;i<=l;i++)
		t[i]-='0'-1;
	int cur=0;
	for(int i=1;i<=l;i++)
	{
		if(!o[cur][t[i]])
			o[cur][t[i]]=++tot;
		cur=o[cur][t[i]];
	}
	sz[cur]+=1;
	smv[cur]+=log((db)x);
	str=max(str,smv[cur]);
	// printf("cur:%d sz:%d smv:%Lf\n",cur,sz[cur],smv[cur]);
}
void getfail()
{
	queue<int> q;
	q.push(0);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		sz[x]+=sz[fail[x]],smv[x]+=smv[fail[x]];
		for(int i=1;i<=10;i++)
			if(o[x][i])
			{
				if(x)
					fail[o[x][i]]=o[fail[x]][i];
				q.push(o[x][i]);
			}
			else
				o[x][i]=o[fail[x]][i];
	}
	// for(int i=1;i<=tot;i++)
	// 	printf("i:%d fail:%d\n",i,fail[i]);
}
int dp(ldb val)
{
	for(int i=0;i<=n;i++)
		for(int j=0;j<=tot;j++)
			f[i][j]=-1e100,pre0[i][j]=pre1[i][j]=0;
	for(int j=0;j<=tot;j++)
		g[j]=smv[j]-val*(db)sz[j];
	f[0][0]=0;
	// for(int j=0;j<=tot;j++)
	// 	f[0][j]=0;
	for(int i=1;i<=n;i++)
	{
		db *lf=f[i-1],*nf=f[i];
		int *tp0=pre0[i],*tp1=pre1[i];
		for(int j=0;j<=tot;j++)
			if(lf[j]>-1e99)
			{
				int *no=o[j];
				if(s[i]>=1&&s[i]<=10)
				{
					int nxt=no[s[i]];
					// printf("nxt:%d\n",nxt);
					db nv=lf[j]+g[nxt];
					// printf("nv:%Lf\n",nv);
					if(nv>nf[nxt])
					{
						nf[nxt]=nv;
						tp0[nxt]=s[i];
						tp1[nxt]=j;
					}
				}
				else
				{
					for(int k=1;k<=10;k++)
					{
						int nxt=no[k];
						// printf("nxt:%d\n",nxt);
						db nv=lf[j]+g[nxt];
						// printf("nv:%Lf\n",nv);
						if(nv>nf[nxt])
						{
							nf[nxt]=nv;
							tp0[nxt]=k;
							tp1[nxt]=j;
						}
					}
				}
			}
	}
	db ans=-1;
	// printf("val:%Lf---------------\n",val);
	// for(int j=0;j<=tot;j++)
	// 	printf("j:%d f:%Lf\n",j,f[n][j]);
	for(int j=0;j<=tot;j++)
		ans=max(ans,f[n][j]);
	return ans>0;
}
void getans()
{
	db ans=-1;
	int cur=0;
	for(int j=0;j<=tot;j++)
		if(f[n][j]>ans)
			ans=f[n][j],cur=j;
	for(int i=n;i>=1;i--)
	{
		out[i]=pre0[i][cur];
		cur=pre1[i][cur];
		assert(out[i]>0);
	}
	for(int i=1;i<=n;i++)
		printf("%d",out[i]-1);
}
void bin()
{
	ldb l=0,r=log((db)INT_MAX);
	dp(0);
	for(int k=1;k<=20;k++)
	// while(r-l>eps)
	{
		ldb mid=(l+r)/2;
		if(dp(mid))
			l=mid;
		else
			r=mid;
	}
	// if(l<0)
	// 	dp(0);
	dp(l);
	// printf("l:%Lf\n",l);
	getans();
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
		s[i]-='0'-1;
	for(int i=1,a;i<=m;i++)
	{
		scanf("%s%d",t+1,&a);
		add(a);
	}
	getfail();
	bin();
	return 0;
}