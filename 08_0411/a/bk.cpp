#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int mat[49][49];
int main()
{
	freopen("bk.out","r",stdin);
	freopen("bk.in","w",stdout);
	for(int i=1,a,b,c;i<=5*40;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		mat[a][b]=c;
	}
	for(int i=1;i<=5;i++)
	{
		printf("{");
		for(int j=1;j<=40;j++)
		{
			printf("%d",mat[i][j]);
			if(j<40)
				printf(",");
		}
		printf("},\n");
	}
	return 0;
}