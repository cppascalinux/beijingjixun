//2019.04.15
//ezoj1588 取石子 线段树+二分
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define la a<<1
#define ra a<<1|1
#define upd() sm[a]=sm[la]+sm[ra],mn[a]=min(mn[la],sm[la]+mn[ra]),mx[a]=max(mx[la],sm[la]+mx[ra])
#define ll long long
using namespace std;
char *p1,*p2,buffer[10000009];
int n,q,x,y;
int v[500009];
ll sm[2000009],mn[2000009],mx[2000009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void build(int a,int l,int r)
{
	if(l==r)
	{
		sm[a]=v[l];
		mn[a]=min(0,v[l]);
		mx[a]=max(0,v[l]);
		return;
	}
	int mid=(l+r)>>1;
	build(la,l,mid);
	build(ra,mid+1,r);
	upd();
}
void setv(int a,int l,int r,int x,int val)
{
	if(l==r)
	{
		sm[a]=val;
		mn[a]=min(0,val);
		mx[a]=max(0,val);
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)
		setv(la,l,mid,x,val);
	else
		setv(ra,mid+1,r,x,val);
	upd();
}
ll askv(int a,int l,int r,int maxv,int curv)
{
	if(l==r)
		return min((ll)maxv,max(sm[a]+curv,0LL));
	int mid=(l+r)>>1;
	if(mx[ra]-mn[ra]>=maxv)
		return askv(ra,mid+1,r,maxv,curv);
	ll lv=askv(la,l,mid,maxv,curv);
	if(lv+mx[ra]>=maxv)
		return maxv-(mx[ra]-sm[ra]);
	if(lv+mn[ra]<=0)
		return sm[ra]-mn[ra];
	return sm[ra]+lv;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b1.out","w",stdout);
#endif
	rd(n),rd(q),rd(x),rd(y);
	for(int i=1;i<=n;i++)
	{
		rd(v[i]);
		if(!(i&1))
			v[i]=-v[i];
	}
	build(1,1,n);
	for(int i=1,a,b,c;i<=q;i++)
	{
		rd(a),rd(b);
		if(a==1)
			x=b;
		else if(a==2)
			y=b;
		else
		{
			rd(c);
			if(!(b&1))
				c=-c;
			setv(1,1,n,b,c);
		}
		printf("%lld\n",askv(1,1,n,x+y,x));
	}
	return 0;
}