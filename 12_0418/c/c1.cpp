//2019.04.18
//ezoj1590 Problem C: Cherry 后缀数组+二分
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int typ,n,m,q,len;
char s[1000009];
pii op[500009];
int sa[1000009],t1[1000009],t2[1000009],h[1000009],rnk[1000009],c[1000009];
int lg[1000009],mn[21][1000009];
int sm[1000009];
int lp[1000009],rp[1000009],st[1000009],lens[1000009];
int vis[1000009];
void getsa()
{
	int m=27,*x=t1,*y=t2;
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
		memset(c+1,0,m<<2);
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
	int j=0;
	for(int i=1;i<=n;i++)
	{
		if(j)
			j--;
		int np=sa[rnk[i]-1];
		while(s[i+j]==s[np+j])
			j++;
		h[rnk[i]]=j;
	}
}
void initlcp()
{
	for(int i=1;i<=n;i++)
		mn[0][i]=h[i];
	for(int k=1;k<=19;k++)
		for(int i=1;i<=n-(1<<k)+1;i++)
			mn[k][i]=min(mn[k-1][i],mn[k-1][i+(1<<(k-1))]);
	for(int i=2;i<=n;i++)
		lg[i]=lg[i>>1]+1;
}
int getlcp(int a,int b)
{
	if(a==b)
		return n-sa[a]+1;
	if(a>b)
		swap(a,b);
	a++;
	int k=lg[b-a+1];
	return min(mn[k][a],mn[k][b-(1<<k)+1]);
}
pii cal(int la,int ra,int lb,int rb,int lena)
{
	pii ans;
	int l=la,r=ra+1;
	while(l<r)
	{
		int mid=(l+r)>>1;
		int np=sa[mid]+lena;
		if(np<=n&&rnk[np]>=lb)
			r=mid;
		else
			l=mid+1;
	}
	ans.fi=l;
	l=la-1,r=ra;
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		int np=sa[mid]+lena;
		if(np>n||rnk[np]<=rb)
			l=mid;
		else
			r=mid-1;
	}
	ans.se=l;
	return ans;
}
pii get(int pos,int len)
{
	pii ans;
	int l=1,r=pos;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(getlcp(mid,pos)>=len)
			r=mid;
		else
			l=mid+1;
	}
	ans.fi=l;
	l=pos,r=n;
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		if(getlcp(mid,pos)>=len)
			l=mid;
		else
			r=mid-1;
	}
	ans.se=l;
	return ans;
}
void solve()
{
	int cur=len+1;
	for(int i=1;i<=m;i++)
		lp[i]=1,rp[i]=n;
	for(int i=1;i<=q;i++)
	{
		if(op[i].fi==1)
		{
			int id=op[i].se;
			if(vis[id])
			{
				vis[id]=0;
				if(cur>=st[id]&&lp[id]<=rp[id])
				{
					pii lst=get(rnk[st[id]],cur-st[id]+1);
					pii t=cal(lp[id],rp[id],lst.fi,lst.se,lens[id]);
					lens[id]+=cur-st[id]+1;
					lp[id]=t.fi;
					rp[id]=t.se;
				}
			}
			else
			{
				vis[id]=1;
				st[id]=cur+1;
			}
		}
		else if(op[i].fi==2)
			cur++;
		else
		{
			int id=op[i].se;
			if(!vis[id])
			{
				if(!lens[id]||lp[id]>rp[id])
					printf("0\n");
				else
					printf("%d\n",max(0,sm[rp[id]]-sm[lp[id]-1]));
				continue;
			}
			if((!lens[id]&&cur<st[id])||lp[id]>rp[id])
			{
				printf("0\n");
				continue;
			}
			// printf("i:%d id:%d\n",i,id);
			pii lst=get(rnk[st[id]],cur-st[id]+1);
			pii t=cal(lp[id],rp[id],lst.fi,lst.se,lens[id]);
			// printf("lstl:%d lstr:%d tl:%d tr:%d\n",lst.fi,lst.se,t.fi,t.se);
			printf("%d\n",max(0,sm[t.se]-sm[t.fi-1]));
		}
		// printf("i:%d cur:%d lp:%d rp:%d lens:%d st:%d\n",i,cur,lp[1],rp[1],lens[1],st[1]);
	}
}
void dbg()
{
	for(int i=1;i<=n;i++)
		printf("i:%d sa:%d h:%d\n",i,sa[i],h[i]);
	for(int i=1;i<=q;i++)
		printf("i:%d fi:%d se:%d\n",i,op[i].fi,op[i].se);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c1.out","w",stdout);
#endif
	scanf("%d%d%d%d",&typ,&n,&m,&q);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
		s[i]-='a'-1;
	len=n;
	s[++n]=27;
	for(int i=1,a,b;i<=q;i++)
	{
		char c[2];
		scanf("%d",&a);
		if(a==1||a==3)
		{
			scanf("%d",&b);
			op[i]=pii(a,b);
		}
		else
		{
			scanf("%s",c);
			c[0]-='a'-1;
			s[++n]=c[0];
			op[i]=pii(a,n);
		}
	}
	getsa();
	geth();
	initlcp();
	// dbg();
	for(int i=1;i<=len;i++)
		sm[rnk[i]]=1;
	for(int i=1;i<=n;i++)
		sm[i]+=sm[i-1];
	solve();
	return 0;
}