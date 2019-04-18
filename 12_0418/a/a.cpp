#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define db long double
using namespace std;
int n,m,x,y,tot;
db mul[109][109][209],mat[209][209];
int py[109],px[109];
void getmul()
{
	for(int i=1;i<=m-1;i++)
		if(n!=x||i!=y)
		{
			py[i]=++tot;
			mul[n][i][tot]=1;
		}
	for(int i=1;i<=n-1;i++)
		if(i!=x||m!=y)
		{
			px[i]=++tot;
			mul[i][m][tot]=1;
		}
	for(int i=n-1;i>=1;i--)
		for(int j=m-1;j>=1;j--)
			if(i!=x||j!=y)
			{
				mul[i][j][tot+1]=1;
				for(int k=1;k<=tot+1;k++)
					mul[i][j][k]+=(mul[i+1][j][k]+mul[i][j+1][k])/2;
			}
	if(n!=x||m!=y)
	{
		mul[n][m][tot+1]=1;
		for(int k=1;k<=tot+1;k++)
			mul[n][m][k]+=(mul[n][1][k]+mul[1][m][k])/2;
	}
}
void init()
{
	for(int i=1;i<=m-1;i++)
		if(n!=x||i!=y)
		{
			int p=py[i];
			for(int k=1;k<=tot+1;k++)
				mat[p][k]+=(mul[1][i][k]+mul[n][i+1][k])/2;
			mat[p][p]-=1;
			mat[p][tot+1]=-mat[p][tot+1]-1;
		}
	for(int i=1;i<=n-1;i++)
		if(i!=x||m!=y)
		{
			int p=px[i];
			for(int k=1;k<=tot+1;k++)
				mat[p][k]+=(mul[i][1][k]+mul[i+1][m][k])/2;
			mat[p][p]-=1;
			mat[p][tot+1]=-mat[p][tot+1]-1;
		}
}
void solve()
{
	// for(int i=1;i<=tot;i++)
	// {
	// 	for(int j=1;j<=tot+1;j++)
	// 		printf("%1.3lf ",(double)mat[i][j]);
	// 	printf("\n");
	// }
	for(int i=1;i<=tot;i++)
	{
		int t=i;
		for(int j=i+1;j<=tot;j++)
			if(fabsl(mat[j][i])>fabsl(mat[i][i]))
				t=j;
		for(int k=1;k<=tot+1;k++)
			swap(mat[i][k],mat[t][k]);
		for(int k=tot+1;k>=i;k--)
			mat[i][k]/=mat[i][i];
		for(int j=i+1;j<=tot;j++)
			for(int k=tot+1;k>=i;k--)
				mat[j][k]-=mat[i][k]*mat[j][i];
	}
	for(int i=tot;i>=1;i--)
		for(int j=i+1;j<=tot;j++)
			mat[i][tot+1]-=mat[j][tot+1]*mat[i][j];
	// for(int i=1;i<=tot;i++)
	// {
	// 	for(int j=1;j<=tot+1;j++)
	// 		printf("%1.3lf ",(double)mat[i][j]);
	// 	printf("\n");
	// }
	db ans=mul[1][1][tot+1];
	// db ans=0;
	for(int i=1;i<=tot;i++)
		ans+=mul[1][1][i]*mat[i][tot+1];
	printf("%.6lf",(double)ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d%d%d%d",&n,&m,&x,&y);
	x++,y++;
	getmul();
	init();
	solve();
	return 0;
}