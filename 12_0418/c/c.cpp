#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define pii pair<int,int>
#define fi first
#define se second
#define ll long long
#define bse 619
#define mod1 1000000007
#define mod2 1000000009
#define mod3 1000003
using namespace std;
int typ,n,m,q;
char s[500009];
namespace solve1
{
	int lst=1,tot=1,sme;
	int o[1000009][27],lnk[1000009],len[1000009],sm[1000009];
	int hd[1000009],eg[1000009],nxt[1000009];
	int pos[500009],vis[500009];
	void add(int c)
	{
		int cur=++tot,p;
		sm[cur]=1;
		len[cur]=len[lst]+1;
		for(p=lst;p&&!o[p][c];p=lnk[p])
			o[p][c]=cur;
		if(!p)
			lnk[cur]=1;
		else
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
				for(;p&&o[p][c]==q;p=lnk[p])
					o[p][c]=cln;
				lnk[cur]=lnk[q]=cln;
			}
		}
		lst=cur;
	}
	void ins(int a,int b)
	{
		eg[++sme]=b;
		nxt[sme]=hd[a];
		hd[a]=sme;
	}
	void dfs(int x)
	{
		for(int i=hd[x];i;i=nxt[i])
		{
			dfs(eg[i]);
			sm[x]+=sm[eg[i]];
		}
	}
	void solve()
	{
		for(int i=1;i<=n;i++)
			add(s[i]-'a'+1);
		for(int i=2;i<=tot;i++)
			ins(lnk[i],i);
		dfs(1);
		// for(int i=1;i<=tot;i++)
		// 	printf("i:%d lnk:%d len:%d sm:%d\n",i,lnk[i],len[i],sm[i]);
		for(int i=1;i<=m;i++)
			pos[i]=1;
		for(int i=1,a,b;i<=q;i++)
		{
			scanf("%d",&a);
			if(a==1)
			{
				scanf("%d",&b);
				vis[b]^=1;
			}
			else if(a==2)
			{
				char c[2];
				scanf("%s",c);
				c[0]-='a'-1;
				for(int j=1;j<=m;j++)
					if(vis[j])
					{
						pos[j]=o[pos[j]][c[0]];
						if(!pos[j])
							pos[j]=1;
					}
			}
			else if(a==3)
			{
				scanf("%d",&b);
				if(pos[b]==1)
					printf("0\n");
				else
					printf("%d\n",sm[pos[b]]);
			}
		}
	}
}
namespace solve2
{
	int tot;
	int hd[1000003],nxt[3001009],sm[3001009];
	pii hs[3001009];
	int vis[200009];
	pii hsm[200009];
	int qpow1(int a,int b)
	{
		int ans=1;
		for(;b;b>>=1,a=(ll)a*a%mod1)
			if(b&1)
				ans=(ll)ans*a%mod1;
		return ans;
	}
	int qpow2(int a,int b)
	{
		int ans=1;
		for(;b;b>>=1,a=(ll)a*a%mod2)
			if(b&1)
				ans=(ll)ans*a%mod2;
		return ans;
	}
	void ins(int a,pii b)
	{
		hs[++tot]=b;
		sm[tot]=1;
		nxt[tot]=hd[a];
		hd[a]=tot;
	}
	void add(pii val)
	{
		int st=val.fi%mod3;
		for(int i=hd[st];i;i=nxt[i])
			if(hs[i]==val)
			{
				sm[i]++;
				return;
			}
		ins(st,val);
	}
	int ask(pii val)
	{
		int st=val.fi%mod3;
		for(int i=hd[st];i;i=nxt[i])
			if(hs[i]==val)
				return sm[i];
		return 0;
	}
	pii cal(pii p,int ml,int ad)
	{
		p.fi=((ll)p.fi*ml+ad)%mod1;
		p.se=((ll)p.se*ml+ad)%mod2;
		return p;
	}
	pii cal(pii p,pii ml,pii ad)
	{
		p.fi=((ll)p.fi*ml.fi+ad.fi)%mod1;
		p.se=((ll)p.se*ml.se+ad.se)%mod2;
		return p;
	}
	void solve()
	{
		for(int i=1;i<=n;i++)
		{
			pii tsh=pii(0,0);
			for(int j=i;j<=n;j++)
			{
				tsh=cal(tsh,bse,s[j]);
				add(tsh);
			}
		}
		pii ml=pii(1,1),ad=pii(0,0);
		for(int i=1,a,b;i<=q;i++)
		{
			scanf("%d",&a);
			if(a==1)
			{
				scanf("%d",&b);
				if(vis[b])
				{
					vis[b]=0;
					hsm[b]=cal(hsm[b],ml,ad);
				}
				else
				{
					vis[b]=1;
					printf("fi:%d se:%d\n",hsm[b].fi,hsm[b].se);
					hsm[b].fi=(hsm[b].fi-ad.fi+mod1)%mod1;
					hsm[b].se=(hsm[b].se-ad.se+mod2)%mod2;
					hsm[b].fi=(ll)hsm[b].fi*qpow1(ml.fi,mod1-2)%mod1;
					hsm[b].se=(ll)hsm[b].se*qpow2(ml.se,mod2-2)%mod2;
					printf("fi:%d se:%d\n",cal(hsm[b],ml,ad).fi,cal(hsm[b],ml,ad).se);
				}
			}
			else if(a==2)
			{
				char c[2];
				scanf("%s",c);
				ml=cal(ml,bse,0);
				ad=cal(ad,bse,c[0]);
			}
			else
			{
				scanf("%d",&b);
				pii p=hsm[b];
				if(vis[b])
					p=cal(p,ml,ad);
				printf("%d\n",ask(p));
			}
		}
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%d%d%d%d",&typ,&n,&m,&q);
	scanf("%s",s+1);
	if(typ<=2)
		solve1::solve();
	else
		solve2::solve();
	return 0;
}