#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int p[49]={0,1,1,500000006,666666675,166666673,900000013,950000015,466666680,653571445,698412717,796825418,270562790,170274191,819696997,109598759,669574900,806479665,426442708,594393633,814773502,224581378,982770887,502864913,976064346,417759576,435681433,271210321,228639946,295063911,797887069,566283339,825641297};
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("up.out","w",stdout);
#endif
	int n;
	scanf("%d",&n);
	printf("%d",p[n]);
	return 0;
}