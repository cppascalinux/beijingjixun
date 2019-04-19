//2019.04.19
//ezoj1591 Problem B: 分组(fz) 矩阵优化dp+矩阵求逆+前缀和
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define mod 998244353
#define o 998244352
using namespace std;
struct node
{
	int w[4][4];
	node(){memset(w,0,sizeof(w));}
	node(int p[4][4])
	{
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				w[i][j]=p[i][j];
	}
	node operator *(node p)
	{
		node ans;
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				for(int k=0;k<4;k++)
					ans.w[i][j]=(ans.w[i][j]+(ll)w[i][k]*p.w[k][j])%mod;
		return ans;
	}
	void output()
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
				printf("%d ",w[i][j]);
			printf("\n");
		}
	}
};
int n,q;
char s[1000009];
int id1[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
int mul1[4][4]={{1,0,0,0},{1,1,0,0},{1,0,1,0},{1,1,1,1}};
int mul2[4][4]={{1,0,0,1},{1,1,0,1},{1,0,1,1},{1,1,1,2}};
int inv1[4][4]={{1,0,0,0},{o,1,0,0},{o,0,1,0},{1,o,o,1}};
int inv2[4][4]={{0,1,1,o},{o,1,0,0},{o,0,1,0},{1,o,o,1}};
node ml[1000009],ip[1000009];
void init()
{
	ml[0]=ip[0]=node(id1);
	node ml1=node(mul1),ml2=node(mul2),iv1=node(inv1),iv2=node(inv2);
	for(int i=1;i<=n;i++)
	{
		// printf("i:%d---------\n",i);
		if(s[i])
		{
			// printf("1wwww\n");
			ml[i]=ml[i-1]*ml1;
			ip[i]=iv1*ip[i-1];
		}
		else
		{
			// printf("2eeee\n");
			ml[i]=ml[i-1]*ml2;
			ip[i]=iv2*ip[i-1];
		}
		// ml[i].output();
		// printf("ip:\n");
		// ip[i].output();
		// (ml[i]*ip[i]).output();
	}
	// printf("sngoiashvuioasdbilghediasu\n");
	// (ip[n-1]*ml[n]).output();
	// (ml1*iv1).output();
	// (ml2*iv2).output();
}
int solve(int l,int r)
{
	node t=ip[l]*ml[r];
	int ans=0;
	for(int i=0;i<4;i++)
		ans=(ans+t.w[3][i])%mod;
	// printf("ans:%d 0:%d 1:%d 2:%d 3:%d\n",ans,t.w[3][0],t.w[3][1],t.w[3][2],t.w[3][3]);
	return ans;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%d%d",&n,&q);
	scanf("%s",s+2);
	for(int i=2;i<=n;i++)
		s[i]-='0';
	init();
	int a,b,c,d;
	scanf("%d%d%d%d",&a,&b,&c,&d);
	int ans=0;
	for(int i=1;i<=q;i++)
	{
		int l=min(a,b),r=max(a,b);
		// printf("l:%d r:%d\n",l,r);
		a=((a^i)+c)%n+1,b=((b^i)+d)%n+1;
		ans^=solve(l,r);
	}
	printf("%d",ans);
	return 0;
}