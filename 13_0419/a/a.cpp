#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<ctime>
#define ll long long
#define mod 998244353
using namespace std;
ll n;
map<ll,int> lc,rc,sm;
void solve(ll x)
{
	// printf("x:%lld\n",x);
	// fflush(stdout);
	if(!x||sm[x])
		return;
	ll mid=x>>1;
	solve(mid),solve(x-mid);
	int rcl=rc[mid],sml=sm[mid];
	int lcr=lc[x-mid],smr=sm[x-mid];
	int nsm=(sml+smr+1)%mod;
	nsm=(nsm+(ll)rcl*((x-mid)%mod))%mod;
	nsm=(nsm+(ll)lcr*(mid%mod))%mod;
	nsm=(nsm+x-2)%mod;
	sm[x]=nsm;
	lc[x]=((ll)lc[mid]+lc[x-mid]+(x-mid)%mod)%mod;
	rc[x]=((ll)rc[mid]+rc[x-mid]+mid%mod)%mod;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%lld",&n);
	sm[0]=0,sm[1]=1;
	solve(n);
	// for(ll i=1;i<=n;i++)
	// 	printf("i:%lld lc:%d rc:%d sm:%d\n",i,lc[i],rc[i],sm[i]);
	printf("%d",sm[n]);
	// cerr<<clock();
	return 0;
}