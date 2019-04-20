//2019.04.19
//ezoj1590 Problem B: Banana 线段树分治+凸包+高精度小数
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
#include<cmath>
#include<ctime>
#define li long long
#define i128 __int128
#define f128 __float128
#define pii pair<int,int>
#define pti pair<pt,int>
#define fi first
#define se second
#define pb push_back
#define ldb long double
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
struct pt
{
	li x,y;
	pt(){}
	pt(li a,li b){x=a,y=b;}
	bool operator <(const pt &p) const{return x<p.x||(x==p.x&&y<p.y);}
	pt operator +(pt p){return pt(x+p.x,y+p.y);}
	pt operator -(pt p){return pt(x-p.x,y-p.y);}
	i128 operator ^(pt p){return (i128)x*p.y-(i128)y*p.x;}
};
char *p1,*p2,buffer[10000009];
int n,c,smp;
pt p[1000009];
int lb[1000009],rb[1000009],typ[1000009];
pti ts[1000009];
int seq[1000009],st[1000009];
char vis0[4000009],vis1[4000009];
vector<int> vp[4000009];
li ansx,ansy=-1;
int anslb,ansrb,anspl,anspr,anslx,ansrx;
f128 ansv=-1e300;
template<class T>
void rd(T &x)
{
	char c=0,inv=0;
	x=0;
	while(c<'0'||c>'9')
		c=gc(),c=='-'&&(inv=1);
	while(c>='0'&&c<='9')
		x=x*10+(c&15),c=gc();
	inv&&(x=-x);
}
// void build(int a,int ll,int rr)
// {
// 	l[a]=ll;
// 	r[a]=rr;
// 	if(ll<rr)
// 	{
// 		int mid=(ll+rr)>>1;
// 		build(a<<1,ll,mid);
// 		build(a<<1|1,mid+1,rr);
// 	}
// }
void add0(int a,int l,int r,int ll,int rr,int val)
{
	if(l>rr||r<ll)
		return;
	if(l>=ll&&r<=rr)
	{
		vp[a].pb(val);
		vis0[a]=1;
		return;
	}
	int mid=(l+r)>>1;
	add0(a<<1,l,mid,ll,rr,val);
	add0(a<<1|1,mid+1,r,ll,rr,val);
}
void add1(int a,int l,int r,int pos,int val)
{
	vp[a].pb(val);
	vis1[a]=1;
	if(l<r)
	{
		int mid=(l+r)>>1;
		if(pos<=mid)
			add1(a<<1,l,mid,pos,val);
		else
			add1(a<<1|1,mid+1,r,pos,val);
	}
}
void input()
{
	int tmp;
	rd(tmp),rd(n),rd(c);
	map<pt,int> mp;
	for(int i=1,a;i<=n;i++)
	{
		li x,y;
		rd(a),rd(x),rd(y);
		if(a==1)
		{
			p[++smp]=pt(x,y);
			lb[smp]=i;
			// mp[p[smp]]=smp;
		}
		else if(a==2)
		{
			int l=mp[pt(x,y)];
			rb[l]=i-1;
		}
		else
		{
			p[++smp]=pt(x,y);
			lb[smp]=rb[smp]=i;
			typ[smp]=1;
		}
	}
	for(int i=1;i<=smp;i++)
		if(!rb[i])
			rb[i]=n;
}
// bool cmp(int a,int b)
// {
// 	return ;
// }
void init()
{
	// build(1,1,n);
	// for(int i=1;i<=smp;i++)
	// 	seq[i]=i;
	for(int i=1;i<=smp;i++)
		ts[i]=pti(p[i],i);
	sort(ts+1,ts+smp+1);
	for(int i=1;i<=smp;i++)
		seq[i]=ts[i].se;
	// sort(seq+1,seq+smp+1,cmp);
	for(int i=1;i<=smp;i++)
	{
		int k=seq[i];
		if(!typ[k])
			add0(1,1,n,lb[k],rb[k],k);
		else
			add1(1,1,n,lb[k],k);
	}
	// for(int i=1;i<=smp;i++)
	// 	printf("i:%d x:%lld y:%lld lb:%d rb:%d typ:%d\n",i,p[i].x,p[i].y,lb[i],rb[i],typ[i]);
}
int cross(pt o,pt a,pt b)
{
	return ((a-o)^(b-o))>0;
}
f128 cal(pt a,pt b)
{
	return (f128)(a.y-b.y)/(a.x-b.x);
}
void solve(int x)
{
	int tp=0,cur=1;
	// printf("x:%d\n",x);
	// for(int i=0;i<=vp[x].size();i++)
	// 	printf("i:%d ")
	for(int i=0;i<(int)vp[x].size();i++)
	{
		int t=vp[x][i];
		if(!typ[t])
		{
			while(tp>cur&&!cross(p[st[tp-1]],p[st[tp]],p[t]))
				tp--;
			cur=min(cur,tp);
			cur=max(cur,1);
			st[++tp]=t;
		}
		else
		{
			if(!tp)
				continue;
			while(cur<tp&&cross(p[st[cur]],p[st[cur+1]],p[t]))
				cur++;
			if(p[t].x==p[st[cur]].x)
			{
				if(p[t].y>=p[st[cur]].y)
					ansv=1e300,ansx=0,ansy=1;
			}
			f128 v=cal(p[t],p[st[cur]]);
			if(v>ansv)
			{
				ansv=v;
				ansx=p[t].x-p[st[cur]].x;
				ansy=p[t].y-p[st[cur]].y;
				// anslb=lb[st[cur]];
				// ansrb=rb[st[cur]];
				// anspl=lb[t];
				// anspr=rb[t];
				// anslx=l[x],ansrx=r[x];
			}
		}
	}
}
f128 sqt(f128 x)
{
	f128 ans=1;
	for(int i=1;i<=1000000;i++)
		ans=(ans*ans+x)/ans/2;
	return ans;
}
void output()
{
	// if(p[1].x==39324375589412510LL&&p[1].y==26154726069715217LL)
	// printf("ansx:%lld ansy:%lld lb:%d rb:%d pl:%d lx:%d rx:%d\n",ansx,ansy,anslb,ansrb,anspl,anslx,ansrx);
	// if(ansx<0)
	// 	ansx=-ansx,ansy=-ansy;
	// printf("%.6Lf",(ldb)ansy/sqrt((ldb)ansx*ansx+(ldb)ansy*ansy));
	if(!ansx)
	{
		if(ansy<0)
			printf("-");
		printf("1.");
		for(int i=1;i<=c;i++)
			printf("0");
		printf("\n");
		return;
	}
	if(!ansy)
	{
		printf("0.");
		for(int i=1;i<=c;i++)
			printf("0");
		printf("\n");
		return;
	}
	f128 ans=sqt(1+(f128)ansx/ansy*ansx/ansy);
	ans=1/ans;
	if(ansy<0)
		printf("-");
	// printf("ans:%lf",(double)ans);
	printf("0.");
	f128 fix=0.5;
	for(int i=1;i<=c;i++)
		fix/=10;
	ans+=fix;
	for(int i=1;i<=c;i++)
	{
		ans*=10;
		printf("%d",(int)((i128)ans%10));
	}
	printf("\n");
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	input();
	init();
	for(int i=1;i<=4*n;i++)
		if(vis1[i]&&vis0[i]&&vp[i].size())
			solve(i);
	output();
	// cerr<<clock();
	return 0;
}