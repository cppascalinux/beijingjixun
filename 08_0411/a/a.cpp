#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 1000000007
#define ll long long
using namespace std;
int tot,lst,n,k;
int o[89][49],len[89],lnk[89];
int st[49];
void add(int c)
{
	lnk[0]=-1;
	int cur=++tot,p;
	len[cur]=len[lst]+1;
	for(p=lst;p!=-1&&!o[p][c];p=lnk[p])
		o[p][c]=cur;
	if(p!=-1)
	{
		int q=o[p][c];
		if(len[q]==len[p]+1)
			lnk[cur]=q;
		else
		{
			int cln=++tot;
			len[cln]=len[p]+1;
			lnk[cln]=lnk[q];
			memcpy(o[cln],o[q],27<<2);
			for(;p!=-1&&o[p][c]==q;p=lnk[p])
				o[p][c]=cur;
			lnk[cur]=lnk[q]=cln;
		}
	}
	lst=cur;
}
void dfs(int d,ll &ans)
{
	if(d>n)
	{
		memset(o,0,sizeof(o));
		memset(len,0,sizeof(len));
		memset(lnk,0,sizeof(lnk));
		tot=lst=0;
		for(int i=1;i<=n;i++)
			add(st[i]);
		ans=(ans+tot+1)%mod;
		return;
	}
	for(int i=1;i<=k;i++)
	{
		st[d]=i;
		dfs(d+1,ans);
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a4.out","w",stdout);
#endif
	for(int i=7;i<=40;i++)
		for(int j=1;j<=40;j++)
		{
			n=i,k=j;
			ll ans=0;
			dfs(1,ans);
			printf("%d %d %lld\n",n,k,ans);
			fflush(stdout);
		}
	return 0;
}