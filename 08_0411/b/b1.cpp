#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ch(x) ((x)<=0?(x)+n:((x)>n?(x)-n:x))
#define ll long long
#define mod 1000000007
#define bse 10000019
using namespace std;
int n,tot,invn;
int hd[bse],f[120000000],nxt[120000000];
ll eg[120000000];
void clr()
{
	memset(hd,0,sizeof(hd));
	tot=0;
}
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)
			ans=(ll)ans*a%mod;
	return ans;
}
int fnd(ll s)
{
	int x=s%bse;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]==s)
			return i;
	return 0;
}
void add(ll s,int val)
{
	int x=s%bse;
	eg[++tot]=s;
	f[tot]=val;
	nxt[tot]=hd[x];
	hd[x]=tot;
}
int dfs(ll s)
{
	int lst=fnd(s);
	if(lst)
		return f[lst];
	int fs=1;
	for(int i=1;i<=n;i++)
		if(!(s&(1LL<<(i-1))))
		{
			int l1=ch(i-1),l2=ch(i-2),r1=ch(i+1),r2=ch(i+2);
			int t=s|(1<<(i-1));
			if(t&(1<<(l2-1)))
				t|=1<<(l1-1);
			if(t&(1<<(r2-1)))
				t|=1<<(r1-1);
			int ft=dfs(t);
			fs=(fs+(ll)invn*ft)%mod;
		}
	int sm=0;
	for(int i=1;i<=n;i++)
		if(s&(1LL<<(i-1)))
			sm++;
	int invs=qpow(n-sm,mod-2);
	fs=(ll)fs*n%mod*invs%mod;
	add(s,fs);
	return fs;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b1.out","w",stdout);
#endif
	scanf("%d",&n);
	// for(n=33;n<=40;n++)
	// {
		invn=qpow(n,mod-2);
		add((1LL<<n)-1,0);
		printf("%d",n,dfs(0));
	// 	cerr<<n<<" "<<tot<<endl;
	// 	fflush(stdout);
	// 	clr();
	// }
	return 0;
}