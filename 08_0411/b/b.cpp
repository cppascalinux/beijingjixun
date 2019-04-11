#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<ctime>
#define ch(x) ((x)<=0?(x)+n:((x)>n?(x)-n:(x)))
#define ll long long
#define mod 1000000007
using namespace std;
int n;
ll ans=0;
int f[1050009];
vector<int> v[29];
void init()
{
	for(int i=0;i<1<<n;i++)
	{
		int sm=0;
		for(int j=0;j<n;j++)
			if(i&(1<<j))
				sm++;
		v[sm].push_back(i);
	}
}
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)
			ans=(ll)ans*a%mod;
	return ans;
}
void dp(int sm,int s)
{
	f[s]=1;
	int invn=qpow(n,mod-2);
	for(int i=1;i<=n;i++)
		if(!(s&(1<<(i-1))))
		{
			int l=ch(i-1),r=ch(i+1);
			if((s&(1<<(l-1)))&&(s&(1<<(r-1))))
				return;
		}
	for(int i=1;i<=n;i++)
		if(!(s&(1<<(i-1))))
		{
			int t=s|(1<<(i-1));
			// printf("t:%d\n",t);
			int l1=ch(i-1),l2=ch(i-2),r1=ch(i+1),r2=ch(i+2);
			// printf("i:%d l1:%d l2:%d r1:%d r2:%d\n",i,l1,l2,r1,r2);
			if(t&(1<<(l2-1)))
				t|=1<<(l1-1);
			if(t&(1<<(r2-1)))
				t|=1<<(r1-1);
			f[s]=(f[s]+(ll)invn*f[t])%mod;
		}
	int invs=qpow(n-sm,mod-2);
	f[s]=(ll)f[s]*n%mod*invs%mod;
	// printf("s:%d f:%d\n",s,f[s]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%d",&n);
	init();
	for(int i=n-1;i>=0;i--)
		for(int j=0;j<(int)v[i].size();j++)
			dp(i,v[i][j]);
	printf("%d",f[0]);
	cerr<<clock()<<endl;
	return 0;
}