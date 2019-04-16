//2019.04.16
//ezoj1589 重复子串(string) 后缀数组+启发式合并+贪心+扫描线+主席树+二分答案
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<set>
#include<vector>
#define pii pair<int,int>
#define fi first
#define se second
#define si set<int>::iterator
using namespace std;
int n,m,smpt,tot;
char s[100009];
int sa[100009],c[100009],t1[100009],t2[100009],rnk[100009],h[100009];
pii st[100009];
int f[100009];
set<int> vp[100009];
vector<pii> pt[100009];
int rt[4000009],lp[80000009],rp[80000009],mx[80000009];
void getsa()
{
	int *x=t1,*y=t2,m=26;
	for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
	for(int i=1;i<=m;i++) c[i]+=c[i-1];
	for(int i=1;i<=n;i++) sa[c[x[i]]--]=i;
	for(int k=1;k<=n;k<<=1)
	{
		int p=0;
		for(int i=n-k+1;i<=n;i++)
			y[++p]=i;
		for(int i=1;i<=n;i++)
			if(sa[i]>k)
				y[++p]=sa[i]-k;
		memset(c,0,(m+1)<<2);
		for(int i=1;i<=n;i++) c[x[i]]++;
		for(int i=1;i<=m;i++) c[i]+=c[i-1];
		for(int i=n;i>=1;i--) sa[c[x[y[i]]]--]=y[i];
		p=0;
		for(int i=1;i<=n;i++)
			y[sa[i]]=x[sa[i]]==x[sa[i-1]]&&x[sa[i]+k]==x[sa[i-1]+k]?p:++p;
		swap(x,y);
		if((m=p)>=n)
			break;
	}
}
void geth()
{
	for(int i=1;i<=n;i++)
		rnk[sa[i]]=i;
	int p=0;
	for(int i=1;i<=n;i++)
	{
		if(p)
			p--;
		int np=sa[rnk[i]-1];
		while(s[i+p]==s[np+p])
			p++;
		h[rnk[i]]=p;
	}
}
int fnd(int x)
{
	return x==f[x]?x:f[x]=fnd(f[x]);
}
void init()
{
	for(int i=1;i<=n;i++)
	{
		f[i]=i;
		vp[i].insert(i);
	}
	for(int i=2;i<=n;i++)
		st[i-1]=pii(h[i],i);
	sort(st+1,st+n);
	for(int i=n-1;i>=1;i--)
	{
		int a=fnd(sa[st[i].se-1]),b=fnd(sa[st[i].se]);
		if(vp[a].size()<vp[b].size())
			swap(a,b);
		si it;
		for(it=vp[b].begin();it!=vp[b].end();it++)
		{
			si pl=vp[a].lower_bound(*it),pr=vp[a].upper_bound(*it);
			if(pl!=vp[a].begin())
			{
				pl--;
				int pa=*it,pb=*pl;
				if(pa>pb)
					swap(pa,pb);
				pt[pa].push_back(pii(pb,st[i].fi));
			}
			if(pr!=vp[a].end())
			{
				int pa=*it,pb=*pr;
				if(pa>pb)
					swap(pa,pb);
				pt[pa].push_back(pii(pb,st[i].fi));
			}
		}
		vp[a].insert(vp[b].begin(),vp[b].end());
		f[b]=a;
	}
}
void add(int &a,int l,int r,int pos,int val,int lst)
{
	if(a<=lst)
	{
		int p=a;
		a=++tot;
		lp[a]=lp[p],rp[a]=rp[p],mx[a]=mx[p];
	}
	mx[a]=max(mx[a],val);
	// printf("mxa:%d\n",mx[a]);
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		add(lp[a],l,mid,pos,val,lst);
	else
		add(rp[a],mid+1,r,pos,val,lst);
}
int ask(int a,int l,int r,int askl,int askr)
{
	if(l>askr||r<askl)
		return 0;
	if(l>=askl&&r<=askr)
		return mx[a];
	int mid=(l+r)>>1;
	return max(ask(lp[a],l,mid,askl,askr),ask(rp[a],mid+1,r,askl,askr));
}
void gett()
{
	for(int i=n;i>=1;i--)
	{
		int lst=tot;
		rt[i]=rt[i+1];
		for(int j=0;j<(int)pt[i].size();j++)
			add(rt[i],1,n,pt[i][j].fi,pt[i][j].se,lst);
		// printf("i:%d---------------\n",i);
		// for(int j=0;j<(int)pt[i].size();j++)
		// 	printf("\tx:%d y:%d h:%d\n",i,pt[i][j].fi,pt[i][j].se);
	}
}
int cal(int l,int r)
{
	// printf("l:%d r:%d ans:%d\n",l,r,ask(rt[l],1,n,1,r));
	return ask(rt[l],1,n,1,r);
}
int solve(int lp,int rp)
{
	int l=0,r=rp-lp+1;
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		if(cal(lp,rp-mid+1)>=mid)
			l=mid;
		else
			r=mid-1;
	}
	return l;
}
void dbg()
{
	for(int i=1;i<=n;i++)
		printf("i:%d sa:%d h:%d\n",i,sa[i],h[i]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
		s[i]-='a'-1;
	getsa();
	geth();
	// dbg();
	init();
	gett();
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		printf("%d\n",solve(a,b));
	}
	return 0;
}