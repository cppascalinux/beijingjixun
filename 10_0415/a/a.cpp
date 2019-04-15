#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define ll long long
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define db long double
#define pil pair<int,ll>
#define fi first
#define se second
#define cross(a,b) (a.fi*b.se-a.se*b.fi)
using namespace std;
char *p1,*p2,buffer[10000009];
int n;
int v[509][509];
ll w[509],sm[509];
pil st[509];
db ans;
int sx1,sy1,sx2,sy2;
pil operator -(pil a,pil b){return pil(a.fi-b.fi,a.se-b.se);}
void rd(int &x)
{
	char ch=0,inv=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc(),ch=='-'&&(inv=1);
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
	inv&&(x=-x);
}
int bin(int l,int r,pil np)
{
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		if(cross((st[mid]-st[mid-1]),(np-st[mid-1]))>=0)
			l=mid;
		else
			r=mid-1;
	}
	return st[l].fi;
}
void solve(int up,int dn,int h)
{
	int tp=0;
	st[++tp]=pil(0,0);
	for(int i=1;i<=n;i++)
	{
		int p=bin(1,tp,pil(i+h,sm[i]));
		db cur=(db)(sm[i]-sm[p])/(2*(i+h-p));
		// printf("i:%d p:%d cur:%Lf\n",i,p,cur);
		if(cur>ans)
		{
			ans=cur;
			sx1=up,sy1=p+1,sx2=dn,sy2=i;
		}
		pil nxt(i,sm[i]);
		while(tp>1&&cross((st[tp]-st[tp-1]),(nxt-st[tp-1]))<=0)
			tp--;
		st[++tp]=nxt;
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	rd(n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			rd(v[i][j]);
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			for(int k=1;k<=n;k++)
				w[k]+=v[j][k];
			for(int k=1;k<=n;k++)
				sm[k]=sm[k-1]+w[k];
			solve(i,j,j-i+1);
		}
		memset(w,0,sizeof(w));
	}
	printf("%.10lf\n",(double)ans);
	printf("%d %d\n%d %d",sx1,sy1,sx2,sy2);
	cerr<<clock();
	return 0;
}