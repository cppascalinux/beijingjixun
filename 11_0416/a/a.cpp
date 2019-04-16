#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define ll long long
#define mod 998244353
using namespace std;
int n,k;
int mul[13];
int prb[13][13];
int tmp[13][4109],ip[4109][4109];
int to3[4109];
int f[13][540009];
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
	for(int i=0;i<n;i++)
		for(int s=1;s<1<<n;s++)
			if(!(s&1<<i))
			{
				int tp=1;
				for(int j=0;j<n;j++)
					if(s&1<<j)
						tp=(ll)tp*(mod+1-prb[j][i])%mod;
				tmp[i][s]=(mod+1-tp)%mod;
			}
	for(int s=1;s<1<<n;s++)
	{
		int u=(1<<n)-1^s;
		for(int t=u;t;t=(t-1)&u)
		{
			ip[s][t]=1;
			for(int i=0;i<n;i++)
				if(s&1<<i)
					ip[s][t]=(ll)ip[s][t]*tmp[i][t]%mod;
		}
	}
	mul[0]=1;
	for(int i=1;i<=n;i++)
		mul[i]=mul[i-1]*3;
	for(int s=1;s<1<<n;s++)
		for(int i=0;i<n;i++)
			if(s&1<<i)
				to3[s]+=mul[i];
}
void dbg()
{
	for(int i=1;i<=k;i++)
	{
		for(int s=1;s<1<<n;s++)
		{
			int tmp=0;
			for(int t=s;t;t=(t-1)&s)
				printf("d:%d s:%d t:%d f:%d\n",i,s,t,f[i][to3[s]+to3[t]]);
		}
	}
	for(int s=1;s<1<<n;s++)
	{
		int u=(1<<n)-1^s;
		for(int t=u;t;t=(t-1)&u)
			printf("s:%d t:%d ip:%d\n",s,t,ip[s][t]);
	}
	for(int i=0;i<n;i++)
		for(int s=1;s<1<<n;s++)
			printf("i:%d s:%d tmp:%d\n",i,s,tmp[i][s]);
}
void dp()
{
	f[0][2]=1;
	for(int d=0;d<=k-1;d++)
	{
		for(int s=1;s<1<<n;s++)
			if(s&1)
			{
				int u=(1<<n)-1^s;
				for(int t=s;t;t=(t-1)&s)
				{
					int now=to3[s]+to3[t];
					for(int v=u;v;v=(v-1)&u)
					{
						int nxt=to3[s|v]+to3[v];
						int pu=(ll)f[d][now]*ip[v][t]%mod;
						if(!pu)
							break;
						// f[d+1][nxt]=(f[d+1][nxt]+(ll)f[d][now]*ip[v][t]%mod*)%mod;
						for(int i=0;i<n;i++)
							if(v&1<<i)
								pu=(ll)pu*(mod+1-tmp[i][s^t])%mod;
						f[d+1][nxt]=(f[d+1][nxt]+pu)%mod;
					}
				}
			}
	}
	// dbg();
	int ans=0;
	for(int d=1;d<=k;d++)
	{
		int tmp=0;
		for(int s=1;s<1<<n;s++)
		{
			int now=to3[(1<<n)-1]+to3[s];
			ans=(ans+f[d][now])%mod;
			tmp=(tmp+f[d][now])%mod;
		}
		// printf("d:%d tmp:%d\n",d,tmp);
	}
	printf("%d",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d%d",&n,&k);
	// printf("n:%d\n",n);
	for(int i=1,a,b,c,d;i<=n*(n-1);i++)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		prb[a-1][b-1]=(ll)c*qpow(d,mod-2)%mod;
	}
	// for(int i=0;i<n;i++)
	// 	for(int j=0;j<n;j++)
	// 		printf("i:%d j:%d prb:%d\n",i,j,prb[i][j]);
	init();
	dp();
	// cerr<<clock();
	return 0;
}
/*3 2
1 2 1 2
2 1 1 2
1 3 1 2
3 1 1 2
2 3 1 2
3 2 1 3
207967574*/