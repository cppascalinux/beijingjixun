#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define mod 998244353
using namespace std;
int a,n;
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)
			ans=(ll)ans*a%mod;
	return ans;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d%d",&a,&n);
	int ans=(mod+1-(ll)(n-1)*qpow((ll)qpow(360-a,mod-2)*(180-a)%mod,n-2)%mod)%mod;
	printf("%d",ans);
	return 0;
}