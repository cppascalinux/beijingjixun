#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
struct pt
{
	int x,y;
	pt(){}
	pt(int a,int b){x=a,y=b;}
	pt operator +(pt p){return pt(x+p.x,y+p.y);}
	pt operator -(pt p){return pt(x-p.x,y-p.y);}
	ll operator ^(pt p){return (ll)x*p.y-(ll)y*p.x;}
	bool operator <(const pt &p) const{return x<p.x||(x==p.x&&y<p.y);}
};
int q,n,tp;
pt s[200009],cv[200009];
int vis[200009];
void solve1()
{
	for(int i=1,a,b,c;i<=q;i++)
	{
		scanf("%d",&a);
		if(a==1)
		{
			scanf("%d%d",&b,&c);
			s[++n]=pt(b,c);
		}
		else if(a==2)
		{
			scanf("%d",&b);
			vis[b]=1;
		}
		else if(a==3)
		{
			scanf("%d%d",&b,&c);
			ll ans=-1;
			for(int i=1;i<=n;i++)
				if(!vis[i]&&s[i].x<=b&&s[i].y>=c)
					ans=max(ans,(ll)(b-s[i].x)*(s[i].y-c));
			printf("%lld\n",ans);
		}
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%d",&q);
	solve1();
	return 0;
}