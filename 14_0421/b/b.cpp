#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define mod 998244353
using namespace std;
int m;
int f[52509][4][16];
int inv[100009];
void dp()
{
	int n=52501;
	f[0][0][0]=1;
	// f[1][0][0]=1;
	// printf("m:%d\n",m);
	for(int i=1;i<=n;i++)
	{
		for(int k=0;k<1<<(m+1);k++)
			if(!(k&1))
				f[i][0][k]=f[i-1][m][k>>1];
		for(int j=1;j<=m;j++)
		{
			for(int k=0;k<1<<(m+1);k++)
			{
				int pl=k&(1<<(j-1)),pr=k&(1<<j);
				int np=k;
				if(!pl&&!pr)
				{
					// printf("f:%d\n",f[i][j-1][k]);
					int p1=k|(1<<(j-1)),p2=k|(1<<j);
					f[i][j][p1]=(f[i][j][p1]+f[i][j-1][k])%mod;
					f[i][j][p2]=(f[i][j][p2]+f[i][j-1][k])%mod;
					continue;
				}
				else if(pl&&!pr)
					np^=1<<(j-1);
				else if(!pl&&pr)
					np^=1<<j;
				else
					np=-1;
				if(np>0)
					f[i][j][np]=(f[i][j][np]+f[i][j-1][k])%mod;
			}
		}
	}
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d f:%d\n",i,f[i][m][0]);
}
void initinv()
{
	inv[1]=1;
	for(int i=2;i<=100000;i++)
		inv[i]=(ll)(mod-mod/i)*inv[mod%i]%mod;
}
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)
			ans=(ll)ans*a%mod;
	return 0;
}
int cb(int a,int b)
{
	int ans=1;
	for(int i=1;i<=b;i++)
		ans=(ll)ans*(a-i+1)%mod*inv[i]%mod;
	return ans;
}
void solve(int l,int r,int k)
{
	int ans=0;
	for(int i=l;i<=r;i++)
		ans=(ans+cb(f[i][m][0],k))%mod;
	ans=(ll)ans*qpow(r-l+1,mod-2)%mod;
	printf("%d\n",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	int t;
	initinv();
	scanf("%d%d",&t,&m);
	dp();
	while(t--)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		solve(a,b,c);
	}
	return 0;
}