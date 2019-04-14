//2019.04.13
//ezoj1587 Problem C: 我做东方鬼畜音MAD，好吗？ 三维凸包+点在平面上投影+圆和多边形交
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define db long double
#define eps 1e-8
#define ln pair<pt,pt>
#define fi first
#define se second
using namespace std;
int sgn(db x)
{
	return x>eps?1:(x<-eps?-1:0);
}
struct pt
{
	db x,y,z;
	pt(){}
	pt(db a,db b,db c){x=a,y=b,z=c;}
	pt operator +(pt p){return pt(x+p.x,y+p.y,z+p.z);}
	pt operator -(pt p){return pt(x-p.x,y-p.y,z-p.z);}
	pt operator *(db v){return pt(x*v,y*v,z*v);}
	pt operator /(db v){return pt(x/v,y/v,z/v);}
	db operator *(pt p){return x*p.x+y*p.y+z*p.z;}
	pt operator ^(pt p){return pt(y*p.z-p.y*z,z*p.x-p.z*x,x*p.y-p.x*y);}
	db getl(){return sqrtl(x*x+y*y+z*z);}//the length of vector
};
struct fc
{
	int v[3];
	fc(){}
	fc(int a,int b,int c){v[0]=a,v[1]=b,v[2]=c;}
};
int m,tot,n=4;
char e[5009][5009];
pt p[5009];
fc f[10009],tmp[10009];
pt cross(pt o,pt a,pt b)
{
	return (a-o)^(b-o);
}
db crossl(pt o,pt a,pt b)
{
	return ((a-o)^(b-o)).getl();
}
db dot(pt o,pt a,pt b)
{
	return (a-o)*(b-o);
}
int in(fc f,pt q)
{
	pt np=cross(p[f.v[0]],p[f.v[1]],p[f.v[2]]);
	return sgn(np*(q-p[f.v[0]]))<0;
}
void add(int id)//add a point to the convex
{
	int ntot=0;
	for(int i=1;i<=tot;i++)
	{
		int res=in(f[i],p[id]);
		if(res)
			tmp[++ntot]=f[i];
		for(int j=0;j<=2;j++)
			e[f[i].v[j]][f[i].v[(j+1)%3]]=res;
	}
	for(int i=1;i<=tot;i++)
		for(int j=0;j<=2;j++)
		{
			int a=f[i].v[j],b=f[i].v[(j+1)%3];
			if(e[a][b]&&!e[b][a])
				tmp[++ntot]=fc(id,b,a);
		}
	for(int i=1;i<=ntot;i++)
		f[i]=tmp[i];
	tot=ntot;
}
ln getn(fc f)//get the vector of a plain
{
	pt a=p[f.v[0]],b=p[f.v[1]],c=p[f.v[2]];
	return ln(a,a+cross(a,b,c));
}
pt getsh(ln l,pt p)//get the shadow of a point on a plain
{
	db vfi=dot(l.fi,p,l.se);
	db vse=dot(l.se,p,l.fi);
	pt h=(l.fi*vse+l.se*vfi)/(vse+vfi);
	return l.fi+p-h;
}
db calcir(pt o,db r,pt a,pt b)//calculate area of part of a circle
{
	db rad=acosl(dot(o,a,b)/(a-o).getl()/(b-o).getl());//the radian
	return rad*r*r/2;
}
db geth(ln l,pt a)//calculate the height from a to l
{
	return crossl(a,l.fi,l.se)/(l.fi-l.se).getl();
}
db cala(pt o,db r,pt a,pt b)//calculate the area of a circle and a triangle
{
	db oa=(a-o).getl(),ob=(b-o).getl(),ab=(a-b).getl();
	if(!oa||!ob||!ab)
		return 0;
	db h=geth(ln(a,b),o);
	if(oa<ob)//make a longer than b
		swap(oa,ob),swap(a,b);
	if(oa<=r&&ob<=r)//triangle all in circle
		return crossl(o,a,b)/2;
	if(ob<=r)
	{
		db ap=sqrtl(oa*oa-h*h)-sqrtl(r*r-h*h);
		pt p=a+(b-a)/ab*ap;
		return crossl(o,p,b)/2+calcir(o,r,a,p);
	}
	if(h>=r)
		return calcir(o,r,a,b);
	db lap=sqrtl(oa*oa-h*h)-sqrtl(r*r-h*h);
	db lbp=sqrtl(ob*ob-h*h)-sqrtl(r*r-h*h);
	pt pa=a+(b-a)/ab*lap;
	pt pb=b+(a-b)/ab*lbp;
	if(sgn((pb-o).getl()-r)!=0||sgn((pa-o).getl()-r)!=0)
		return calcir(o,r,a,b);
	return calcir(o,r,a,pa)+calcir(o,r,b,pb)+crossl(o,pa,pb)/2;
}
db calt(pt o,db r,pt a,pt b,pt c)//calculate the area of a triangle and a circle
{
	pt std=cross(o,a,b);
	if(!sgn(std.getl()))
		std=cross(o,b,c);
	if(!sgn(std.getl()))
		std=cross(o,c,a);
	int d1=sgn(cross(o,a,b)*std);
	int d2=sgn(cross(o,b,c)*std);
	int d3=sgn(cross(o,c,a)*std);
	return fabsl(d1*cala(o,r,a,b)+d2*cala(o,r,b,c)+d3*cala(o,r,c,a));
}
db ask(ln l,db r)
{
	db ans=0;
	for(int i=1;i<=tot;i++)
	{
		pt nl=l.se-l.fi;
		ln lp=getn(f[i]);
		pt np=lp.se-lp.fi;
		if(sgn(np*nl)>0)
			continue;
		pt a=getsh(l,p[f[i].v[0]]);//get shadow
		pt b=getsh(l,p[f[i].v[1]]);
		pt c=getsh(l,p[f[i].v[2]]);
		db co=-(np*nl/np.getl()/nl.getl());//cos a
		// printf("co:%lf\n",co);
		ans+=calt(l.fi,r,a,b,c)/co;
	}
	return ans;
}
void init()
{
	f[++tot]=fc(1,2,3);
	f[++tot]=fc(1,3,2);
	add(4);
	// for(int i=1;i<=4;i++)
	// 	for(int j=0;j<=2;j++)
	// 		printf("i:%d j:%d v:%d\n",i,j,f[i].v[j]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c1.out","w",stdout);
#endif
	for(int i=1,a,b,c;i<=4;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		p[i]=pt(a,b,c);
	}
	init();
	scanf("%d",&m);
	for(int i=1,t,a,b,c,r;i<=m;i++)
	{
		scanf("%d",&t);
		if(t==1)
		{
			scanf("%d%d%d",&a,&b,&c);
			p[++n]=pt(a,b,c);
			add(n);
		}
		else
		{
			ln l;
			scanf("%d%d%d",&a,&b,&c);
			l.fi=pt(a,b,c);
			scanf("%d%d%d",&a,&b,&c);
			l.se=pt(a,b,c);
			scanf("%d",&r);
			printf("%.10lf\n",(double)ask(l,r));
		}
	}
	return 0;
}