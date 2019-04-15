//2019.04.15
//ezoj1588 子矩阵 斜率优化+二分(也可以直接用类似于01分数规划的方法二分)+随机打乱优化
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<vector>
#define ll long long
#define db long double
using namespace std;
struct pt
{
	int x;
	ll y;
	pt(){}
	pt(int a,ll b){x=a,y=b;}
	pt operator +(pt p){return pt(x+p.x,y+p.y);}
	pt operator -(pt p){return pt(x-p.x,y-p.y);}
	ll operator ^(pt p){return x*p.y-y*p.x;}
};
struct node
{
	int hei,up,dn;
	ll s[509];
};
ll cross(pt o,pt a,pt b)
{
	return (a-o)^(b-o);
}
int n,tp,sx1,sy1,sx2,sy2;
db ans;
int w[509][509];
node p[126009];
int seq[126009];
db tmp[509],mn[509];
pt st[509];
int bin(int l,int r,pt p)
{
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		if(cross(st[mid-1],st[mid],p)>=0)
			l=mid;
		else
			r=mid-1;
	}
	return st[l].x;
}
void solve(int x)
{
	ll *sm=p[x].s;
	int h=p[x].hei;
	db mn=0;
	int fg=0;
	for(int i=1;i<=n;i++)
	{
		tmp[i]=sm[i]-2*ans*i;
		if(tmp[i]-mn>2*ans*h)
		{
			fg=1;
			break;
		}
		mn=min(mn,tmp[i]);
	}
	if(!fg)
		return;
	int tpc=0;
	st[++tpc]=pt(0,0);
	for(int i=1;i<=n;i++)
	{
		int q=bin(1,tpc,pt(i+h,sm[i]));
		db cur=(db)(sm[i]-sm[q])/(i+h-q)/2;
		// printf("x:%d h:%d i:%d q:%d cur:%Lf smi:%lld smq:%lld\n",x,h,i,q,cur,sm[i],sm[q]);
		if(cur>ans)
		{
			ans=cur;
			sx1=p[x].up,sy1=q+1,sx2=p[x].dn,sy2=i;
		}
		pt nxt(i,sm[i]);
		while(tpc>1&&cross(st[tpc-1],st[tpc],nxt)<=0)
			tpc--;
		st[++tpc]=nxt;
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a1.out","w",stdout);
#endif
	srand(20020618+20030619);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",w[i]+j);
	for(int i=1;i<=n;i++)
	{
		tp++;
		for(int k=1;k<=n;k++)
			p[tp].s[k]=w[i][k];
		p[tp].hei=1;
		p[tp].up=p[tp].dn=i;
		for(int j=i+1;j<=n;j++)
		{
			tp++;
			for(int k=1;k<=n;k++)
				p[tp].s[k]=p[tp-1].s[k]+w[j][k];
			p[tp].hei=j-i+1;
			p[tp].up=i;
			p[tp].dn=j;
		}
	}
	for(int i=1;i<=tp;i++)
		for(int j=1;j<=n;j++)
			p[i].s[j]+=p[i].s[j-1];
	// printf("tp:%d\n",tp);
	// for(int i=1;i<=tp;i++)
	// 	for(int j=1;j<=n;j++)
	// 		printf("i:%d j:%d p:%lld\n",i,j,p[i].s[j]);
	for(int i=1;i<=tp;i++)
		seq[i]=i;
	random_shuffle(seq+1,seq+tp+1);
	for(int i=1;i<=tp;i++)
		solve(seq[i]);
	if(!sx1)
	{
		ans=-1e300;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				db cur=(db)w[i][j]/4;
				if(ans<cur)
				{
					ans=cur;
					sx1=sx2=i;
					sy1=sy2=j;
				}
			}
	}
	printf("%.10lf\n",(double)ans);
	printf("%d %d\n%d %d",sx1,sy1,sx2,sy2);	
	cerr<<clock();
	return 0;
}