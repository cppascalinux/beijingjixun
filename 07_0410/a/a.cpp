#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<ctime>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define ll long long
#define mod 998244353
#define vi vector<int>
#define pvv pair<vi,vi>
#define fi first
#define se second
using namespace std;
char *p1,*p2,buffer[10000009];
int n,len;
int p[100009],q[100009];
int rt[2][270009],mp[270009];
int mul[100009],inv[100009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
template<class T>
void clr(vector<T> &v)
{
	vector<T> tmp;
	tmp.swap(v);
}
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)
			ans=(ll)ans*a%mod;
	return ans;
}
void initm()
{
	mul[0]=1;
	for(int i=1;i<=n;i++)
		mul[i]=(ll)mul[i-1]*i%mod;
	inv[n]=qpow(mul[n],mod-2);
	for(int i=n-1;i>=0;i--)
		inv[i]=(ll)inv[i+1]*(i+1)%mod;
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d mul:%d inv:%d\n",i,mul[i],inv[i]);
}
void init(int l)
{
	int bit=0;
	while(1<<bit<l)
		bit++;
	len=1<<bit;
	rt[0][0]=rt[1][0]=1;
	rt[0][1]=qpow(3,(mod-1)/len);
	for(int i=2;i<len;i++)
		rt[0][i]=(ll)rt[0][i-1]*rt[0][1]%mod;
	for(int i=1;i<len;i++)
		rt[1][i]=rt[0][len-i];
	for(int i=1;i<len;i++)
		mp[i]=(mp[i>>1]>>1)|((i&1)<<(bit-1));
}
void fft(vi &s,int c)
{
	s.resize(len);
	for(int i=0;i<len;i++)
		if(i<mp[i])
			swap(s[i],s[mp[i]]);
	for(int l=2;l<=len;l<<=1)
	{
		int sp=len/l,d=l>>1;
		for(int j=0;j<len;j+=l)
			for(int i=0;i<d;i++)
			{
				int t=(ll)rt[c][sp*i]*s[i+j+d]%mod;
				s[i+j+d]=(s[i+j]-t+mod)%mod;
				s[i+j]=(s[i+j]+t)%mod;
			}
	}
	if(c)
	{
		int inv=qpow(len,mod-2);
		for(int i=0;i<len;i++)
			s[i]=(ll)s[i]*inv%mod;
	}
}
pvv solve(int l,int r)
{
	if(l==r)
	{
		vi s1,s2;
		s2.push_back(1);
		s2.push_back(p[l]);
		s1.push_back(q[l]);
		return pvv(s1,s2);
	}
	int mid=(l+r)>>1;
	pvv pl=solve(l,mid),pr=solve(mid+1,r);
	vi s1,s2;
	int sz=r-l+2;
	init(sz);
	fft(pl.fi,0);
	fft(pl.se,0);
	fft(pr.fi,0);
	fft(pr.se,0);
	s1.resize(len);
	s2.resize(len);
	for(int i=0;i<len;i++)
		s2[i]=(ll)pl.se[i]*pr.se[i]%mod;
	for(int i=0;i<len;i++)
		s1[i]=((ll)pl.fi[i]*pr.se[i]+(ll)pl.se[i]*pr.fi[i])%mod;
	fft(s1,1);
	fft(s2,1);
	// for(int i=sz-1;i<(int)s1.size();i++)
	// 	if(s1[i])
	// 		cerr<<"error1";
	// for(int i=sz;i<(int)s2.size();i++)
	// 	if(s2[i])
	// 		cerr<<"error2";
	s1.resize(sz-1);
	s2.resize(sz);
	return pvv(s1,s2);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	rd(n);
	initm();
	for(int i=1,a,b,c;i<=n;i++)
	{
		rd(a),rd(b),rd(c);
		p[i]=((ll)a+c-(ll)a*c%mod+mod)%mod;
		q[i]=(ll)a*b%mod;
	}
	int ans=0;
	vi s=solve(1,n).fi;
	// for(int i=0;i<(int)s.size();i++)
	// 	printf("i:%d s:%d\n",i,s[i]);
	// for(int i=0;i<(int)s.size();i++)
	// 	ans=(ans+(ll)s[i]*mul[i+1]%mod*mul[n-i-1]%mod*inv[n])%mod;
	// printf("sz:%d\n",(int)s.size());
	for(int i=0;i<(int)s.size();i++)
		ans=(ans+(ll)s[i]*mul[i]%mod*mul[n-1-i]%mod*inv[n])%mod;
	printf("%d",ans);
	cerr<<clock()<<endl;
	return 0;
}