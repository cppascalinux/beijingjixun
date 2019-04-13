#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cassert>
#define db long double
#define eps 1e-8
#define pi 3.14159265358979323846
using namespace std;
int sgn(db x)
{
	return x<-eps?-1:(x>eps?1:0);
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
	db getl(){return sqrt(x*x+y*y+z*z);}
};
struct ln
{
	pt p,q;
	ln(){}
	ln(pt a,pt b){p=a,q=b;}
};
int m;
pt vt[5];
ln pln[5];
pt cross(pt o,pt a,pt b)
{
	return (a-o)^(b-o);
}
db dot(pt o,pt a,pt b)
{
	return (a-o)*(b-o);
}
void init()
{
	pt tmp=cross(vt[2],vt[3],vt[4]);
	if(tmp*(vt[1]-vt[2])<0)
		swap(vt[3],vt[4]);
	pln[1]=ln(vt[2],vt[2]+cross(vt[2],vt[3],vt[4]));//bcd
	pln[2]=ln(vt[1],vt[1]+cross(vt[1],vt[4],vt[3]));//acd
	pln[3]=ln(vt[1],vt[1]+cross(vt[1],vt[2],vt[4]));//abd
	pln[4]=ln(vt[1],vt[1]+cross(vt[1],vt[3],vt[2]));//abc
	// printf("vt1:%Lf %Lf %Lf\n",vt[1].x,vt[1].y,vt[1].z);
	// printf("vt2:%Lf %Lf %Lf\n",vt[2].x,vt[2].y,vt[2].z);
	// printf("vt3:%Lf %Lf %Lf\n",vt[3].x,vt[3].y,vt[3].z);
	// printf("vt4:%Lf %Lf %Lf\n",vt[4].x,vt[4].y,vt[4].z);
}
pt sh(pt g,ln l)
{
	db dp=dot(l.p,g,l.q);
	db dq=dot(l.q,g,l.p);
	pt h;
	if(!sgn(dp+dq))
		h=l.p;
	else
		h=(l.p*dq+l.q*dp)/(dp+dq);
	return l.p+g-h;
}
db geth(pt o,pt a,pt b)
{
	return cross(o,a,b).getl()/(a-b).getl();
}
db calc(pt o,db r,pt a,pt b)
{
	db t=acos((a-o)*(b-o)/(a-o).getl()/(b-o).getl());
	// printf("t:%Lf\n",t/pi*180);
	return t*r*r/2;
}
db gts(pt o,db r,pt a,pt b)
{
	db l1=(a-o).getl(),l2=(b-o).getl(),l3=(a-b).getl();
	if(!sgn(l1)||!sgn(l2)||!sgn(l3))
		return 0;
	// printf("l1:%Lf l2:%Lf l3:%Lf\n",l1,l2,l3);
	// printf("axppp:%Lf ayppp:%Lf azppp:%Lf\n",a.x,a.y,a.z);
	// printf("bxppp:%Lf byppp:%Lf bzppp:%Lf\n",b.x,b.y,b.z);
	// // printf("cx:%Lf cy:%Lf cz:%Lf\n",c.x,c.y,c.z);
	// printf("ox:%Lf oy:%Lf oz:%Lf\n",o.x,o.y,o.z);
	db h=geth(o,a,b);
	if(l1<l2)//l1>l2
		swap(l1,l2),swap(a,b);
	if(l1<=r&&l2<=r)
	{
		// printf("1\n");
		return cross(o,a,b).getl()/2;
	}
	if(l2<=r)
	{
		db la=sqrt(l1*l1-h*h)-sqrt(r*r-h*h);
		pt p=a+(b-a)/l3*la;
		pt m=o+(a-o)/l1*r;
		// printf("2\n");
		return cross(o,p,b).getl()/2+calc(o,r,m,p);
	}
	db l=sqrt(r*r-h*h);
	db la=sqrt(l1*l1-h*h)-l;
	db lb=sqrt(l2*l2-h*h)-l;
	pt hx=a+(b-a)/l3*(la+l);
	pt pa=a+(b-a)/l3*la;
	pt pb=b+(a-b)/l3*lb;
	if(h>r||sgn(dot(hx,a,b))>=0)
	{
		// pt ma=o+(a-o)/l1*r;
		// pt mb=o+(b-o)/l2*r;
		// printf("3\n");
		return calc(o,r,a,b);
	}
	// printf("4\n");
	// return 0;
	return calc(o,r,pa,a)+cross(o,pa,pb).getl()/2+calc(o,r,pb,b);
}
db cal(pt o,db r,pt a,pt b,pt c)
{
	// printf("r:%Lf\n",r);
	// printf("ax:%Lf ay:%Lf az:%Lf\n",a.x,a.y,a.z);
	// printf("bx:%Lf by:%Lf bz:%Lf\n",b.x,b.y,b.z);
	// printf("cx:%Lf cy:%Lf cz:%Lf\n",c.x,c.y,c.z);
	// printf("ox:%Lf oy:%Lf oz:%Lf\n",o.x,o.y,o.z);
	// fflush(stdout);
	pt t=cross(o,a,b);
	if(!sgn(t.getl()))
		t=cross(o,b,c);
	if(!sgn(t.getl()))
		t=cross(o,c,a);
	// printf("tx:%Lf ty:%Lf tz:%Lf\n",t.x,t.y,t.z);
	// fflush(stdout);
	// assert(sgn(t.getl())!=0);
	// assert(sgn(cross(o,a,b)*t)!=0);
	// assert(sgn(cross(o,b,c)*t)!=0);
	// assert(sgn(cross(o,c,a)*t)!=0);
	// printf("%d %d %d\n",sgn(cross(o,a,b)*t),sgn(cross(o,b,c)*t),sgn(cross(o,c,a)*t));
	return fabsl((sgn(cross(o,a,b)*t))*gts(o,r,a,b)+(sgn(cross(o,b,c)*t))*gts(o,r,b,c)+(sgn(cross(o,c,a)*t))*gts(o,r,a,c));
}
db solve(pt st,pt ed,db r)
{
	ln at=ln(st,ed);
	pt atv=ed-st;
	pt pv[5];
	pv[1]=pln[1].q-pln[1].p;
	pv[2]=pln[2].q-pln[2].p;
	pv[3]=pln[3].q-pln[3].p;
	pv[4]=pln[4].q-pln[4].p;
	db ans=0;
	if(sgn(atv*pv[1])>0)//bcd
	{
		// printf("bcd\n");
		db co=atv*pv[1]/atv.getl()/pv[1].getl();
		assert(sgn(co)!=0);
		ans+=cal(st,r,sh(vt[2],at),sh(vt[3],at),sh(vt[4],at))/co;
	}
	// printf("ans1:%Lf\n",ans);
	if(sgn(atv*pv[2])>0)//acd
	{
		// printf("acd\n");
		db co=atv*pv[2]/atv.getl()/pv[2].getl();
		assert(sgn(co)!=0);
		ans+=cal(st,r,sh(vt[1],at),sh(vt[3],at),sh(vt[4],at))/co;
	}
	// printf("ans2:%Lf\n",ans);
	if(sgn(atv*pv[3])>0)//abd
	{
		// printf("abd\n");
		db co=atv*pv[3]/atv.getl()/pv[3].getl();
		assert(sgn(co)!=0);
		ans+=cal(st,r,sh(vt[1],at),sh(vt[2],at),sh(vt[4],at))/co;
	}
	// printf("ans3:%Lf\n",ans);
	if(sgn(atv*pv[4])>0)//abc
	{
		// printf("abc\n");
		db co=atv*pv[4]/atv.getl()/pv[4].getl();
		assert(sgn(co)!=0);
		ans+=cal(st,r,sh(vt[1],at),sh(vt[2],at),sh(vt[3],at))/co;
	}
	// printf("ans4:%Lf\n",ans);
	return ans;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	for(int i=1;i<=4;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		vt[i]=pt(a,b,c);
	}
	init();
	scanf("%d",&m);
	while(m--)
	{
		int t;
		pt p,q;
		scanf("%d",&t);
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		// printf("%d %d %d ",a,b,c);
		p=pt(a,b,c);
		scanf("%d%d%d",&a,&b,&c);
		// printf("%d %d %d ",a,b,c);
		q=pt(a,b,c);
		int r;
		scanf("%d",&r);
		// assert(r>=0);
		// printf("r:%d\n",r);
		printf("%.10lf\n",(double)solve(p,q,r));
	}
	return 0;
}