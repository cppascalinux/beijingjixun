//2019.04.11
//ezoj1586 树 概率+期望+组合数
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define mod 1000000007
#define cb(a,b) (b<0||b>a?0:(ll)mul[a]*inv[b]%mod*inv[a-(b)]%mod)
using namespace std;
int n;
int mul[10000009],inv[10000009];
int f[10000009];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)
			ans=(ll)ans*a%mod;
	return ans;
}
void init()
{
	mul[0]=1;
	for(int i=1;i<=n;i++)
		mul[i]=(ll)mul[i-1]*i%mod;
	inv[n]=qpow(mul[n],mod-2);
	for(int i=n-1;i>=0;i--)
		inv[i]=(ll)inv[i+1]*(i+1)%mod;
}
void getf()
{
	for(int i=0;i<=n-1;i++)
		f[i]=(ll)cb(i,n-i)*mul[n-i]%mod*mul[i-1]%mod*inv[n-1]%mod;
}
void solve()
{
	int ans=0;
	for(int i=0;i<=n-1;i++)
		ans=(ans+(ll)n*inv[n-i]%mod*mul[n-i-1]%mod*(mod+1-f[i]))%mod;
	printf("%d",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b2.out","w",stdout);
#endif
	scanf("%d",&n);
	init();
	getf();
	solve();
	return 0;
}