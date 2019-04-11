//2019.04.09
//ezoj1585 Problem B: 选数 莫比乌斯反演+线性筛+容斥原理+FWT+meet in the middle
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
#define ll long long
#define mod 998244353
#define inv2 499122177
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,k,s,m,len;
int id[50009];
int vis[50009],pm[50009],phi[50009];
int f[50009];
int q[70009],nq[70009];
int buc1[70009],buc2[70009],st1[7000009],st2[7000009];
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
	// for(int i=1;i<=m;i++)
	// 	printf("i:%d vis:%d phi:%d\n",i,vis[i],phi[i]);
}
void fwt(int *s,int c)
{
	len=65536;
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
void dfs(int d,int mxd,int sm,int *buc,int *st,int &tp,int mul,int p)
{
	if(d>mxd)
	{
		if(mul)
		{
			buc[sm]=(buc[sm]+mul)%mod;
			st[++tp]=sm;
		}
		return;
	}
	for(int i=p;i<=m;i+=p)
		if(id[i])
			dfs(d+1,mxd,sm^i,buc,st,tp,(ll)mul*id[i]%mod,p);
}
int cal(int nk,int p)
{
	int l=sqrt(m);
	if(p<=80)
	{
		memset(q,0,sizeof(q));
		for(int i=p;i<=m;i+=p)
			q[i]=id[i];
		// for(int i=1;i<=m;i++)
		// 	printf("%d ",q[i]);
		// printf("\n");
		// fwt(q,0);
		// fwt(q,1);
		// for(int i=1;i<=m;i++)
		// 	printf("%d ",q[i]);
		// printf("\n");
		fwt(q,0);
		for(int i=0;i<len;i++)
		{
			nq[i]=1;
			for(int j=1;j<=nk;j++)
				nq[i]=(ll)nq[i]*q[i]%mod;
		}
		fwt(nq,1);
		return nq[s];
	}
	int mid=nk>>1,tp1=0,tp2=0;
	dfs(1,mid,0,buc1,st1,tp1,1,p);
	dfs(1,nk-mid,0,buc2,st2,tp2,1,p);
	int ans=0;
	for(int i=1;i<=tp1;i++)
	{
		ans=(ans+(ll)buc1[st1[i]]*buc2[s^st1[i]])%mod;
		buc1[st1[i]]=0;
	}
	for(int i=1;i<=tp2;i++)
		buc2[st2[i]]=0;
	return ans;
}
int solve(int nk,int p)
{
	if(nk==1)
	{
		return s%p==0?id[s]:0;
	}
	else if(nk==2)
		return (ll)cal(2,p)*inv2%mod;
	else if(nk==3)
	{
		int now=cal(3,p);
		int lst=solve(1,p);
		int sm=0;
		for(int i=p;i<=m;i+=p)
			sm+=id[i];
		now=(now-(ll)(3*sm-2)*lst%mod+mod)%mod;
		int inv6=qpow(6,mod-2);
		return (ll)now*inv6%mod;
	}
	int now=cal(4,p);
	int lst=solve(2,p);
	int sm=0;
	for(int i=p;i<=m;i+=p)
		sm+=id[i];
	now=(now-(ll)(12*sm-16)*lst%mod+mod)%mod;
	int inv24=qpow(24,mod-2);
	return (ll)now*inv24%mod;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b1.out","w",stdout);
#endif
	rd(n),rd(k),rd(s);
	for(int i=1,a;i<=n;i++)
	{
		rd(a);
		m=max(m,a);
		id[a]++;
	}
	getphi();
	int ans=0;
	for(int i=1;i<=m;i++)
		ans=(ans+(ll)phi[i]*solve(k,i))%mod;
	printf("%d",ans);
	cerr<<clock()<<endl;
	return 0;
}