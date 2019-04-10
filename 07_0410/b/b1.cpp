//2019.04.09
//ezoj1585 Problem B: 选数 莫比乌斯反演+线性筛+容斥原理+FWT+meet in the middle
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define ll long long
#define mod 998244353
#define inv2 499122177
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,k,s,m,len;
int mul[10],imul[10];
int v[1000009],id[50009];
int vis[50009],pm[50009],phi[50009];
int f[50009];
int t[70009],qt[70009];
int buc1[70009],buc2[70009],out1[70009],out2[70009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1)
			ans=(ll)ans*a%mod;
	return ans;
}
void getphi()
{
	int tot=0;
	vis[1]=phi[1]=1;
	for(int i=2;i<=m;i++)
	{
		if(!vis[i])
		{
			pm[++tot]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=tot&&i*pm[j]<=m;j++)
		{
			vis[i*pm[j]]=1;
			if(i%pm[j]==0)
			{
				phi[i*pm[j]]=phi[i]*pm[j];
				break;
			}
			phi[i*pm[j]]=phi[i]*(pm[j]-1);
		}
	}
}
void fwt(int *s,int c)
{
	for(int l=2;l<=len;l<<=1)
	{
		int d=l>>1;
		for(int j=0;j<len;j+=l)
			for(int i=0;i<d;i++)
			{
				int t=s[i+j+d];
				s[i+j+d]=(s[i+j]-t+mod)%mod;
				s[i+j]=(s[i+j]+t)%mod;
				if(c)
				{
					s[i+j]=(ll)s[i+j]*inv2%mod;
					s[i+j+d]=(ll)s[i+j+d]*inv2%mod;
				}
			}
	}
}
void initm()
{
	mul[0]=1;
	for(int i=1;i<=k;i++)
		mul[i]=(ll)mul[i-1]*i%mod;
	imul[k]=qpow(mul[k],mod-2);
	for(int i=k-1;i>=0;i--)
		imul[i]=(ll)imul[i+1]*(i+1)%mod;
}
void solve()
{
	if(k==1)
		printf("%lld",(ll)id[s]*s%mod);
	else if(k==2)
	{
		
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b1.out","w",stdout);
#endif
	rd(n),rd(k),rd(s);
	initm();
	for(int i=1;i<=n;i++)
	{
		rd(v[i]);
		m=max(m,v[i]);
		id[v[i]]++;
	}
	getphi();
	solve();
	return 0;
}