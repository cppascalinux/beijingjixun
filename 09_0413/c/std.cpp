#include <bits/stdc++.h>
#define DB long double
#define MAXN 100010
using namespace std;
 
const DB eps=1e-5;
 
int read(){
    char c;
    while(((c=getchar())<'0' || c>'9') && c!='-');
    int res=c-'0',flag=1;
    if(c=='-') res=0,flag=-1;
    while((c=getchar())>='0' && c<='9') res=res*10+c-'0';
    return res*flag;
}
 
namespace G2D{
    struct vec{
        DB x,y;
        vec(DB _x=0,DB _y=0):x(_x),y(_y){}
        vec operator+(vec p){ return vec(x+p.x,y+p.y); }
        vec operator-(vec p){ return vec(x-p.x,y-p.y); }
        vec operator*(DB k){ return vec(x*k,y*k); }
        vec operator/(DB k){ return vec(x/k,y/k); }
        friend DB dot(vec x,vec y){ return x.x*y.x+x.y*y.y; }
        friend DB cross(vec x,vec y){ return x.x*y.y-x.y*y.x; }
    };
 
    vec get_p(vec x,vec a,vec b){
        vec d=b-a;
        DB lambda=dot(d,x-a)/dot(d,d);
        return a+d*lambda;
    }
 
    DB dis2(vec x,vec y){ return dot(y-x,y-x); } 
    DB dis_pp(vec x,vec y){ return sqrt(dot(y-x,y-x)); } 
    DB dis_pl(vec x,vec a,vec b){ return abs(cross(b-a,x-a)/dis_pp(a,b)); }
 
    DB get_s_tri(vec a,vec b,vec c){ return abs(cross(c-a,b-a))/2; }
    DB get_s_cir(DB r){ return r*r*M_PI; }
 
    DB get_s_sec(vec a,vec b,vec p,DB r){
        DB angle=acos(dot(a-p,b-p)/(r*r));
        return angle*r*r/2;
    }
 
    DB get_s_seg(vec p,vec a,vec b,vec c){
        DB r=dis_pp(a,p);
        DB s=get_s_sec(a,b,p,r)-get_s_tri(p,a,b);
        if(cross(c-a,b-a)*cross(p-a,b-a)<0) s=get_s_cir(r)-s;
        return s;
    }
 
    pair<vec,vec> get_p2(vec a,vec b,vec p,DB r){
        vec t=get_p(p,a,b);
        vec d=b-a;
        d=d/dis_pp(a,b);
        DB l=sqrt(max(r*r-dis2(p,t),(DB)0));
        return make_pair(t-d*l,t+d*l);
    }
 
    bool check(vec a,vec b,vec p,DB r){
        if(dis_pl(p,a,b)>r) return 0;
        vec c=get_p2(a,b,p,r).first;
        return dot(c-a,c-b)<0;
    }
 
    DB get_s(vec p,DB r,vec a,vec b,vec c){
        DB r2=r*r;
        if(dis2(a,p)>r2+eps && dis2(b,p)<r2+eps) swap(a,b);
        if(dis2(b,p)>r2+eps && dis2(c,p)<r2+eps) swap(b,c);
        if(dis2(a,p)>r2+eps && dis2(b,p)<r2+eps) swap(a,b);
        if(dis2(c,p)<r2+eps) return get_s_tri(a,b,c);
        if(dis2(b,p)<r2+eps){
            vec t1=get_p2(a,c,p,r).second,t2=get_p2(b,c,p,r).second;
            return get_s_tri(a,b,c)-get_s_tri(t1,t2,c)+get_s_seg(p,t1,t2,p);
        }
        if(dis2(a,p)<r2+eps){
            vec t1=get_p2(a,b,p,r).second,t2=get_p2(a,c,p,r).second;
            DB s=get_s_tri(a,t1,t2)+get_s_seg(p,t1,t2,a);
            if(check(b,c,p,r)){
                pair<vec,vec> temp=get_p2(b,c,p,r);
                s-=get_s_seg(p,temp.first,temp.second,a);
            }
            return s;
        }
        DB s=get_s_cir(r);
        bool flag=0;
        if(check(a,b,p,r)){
            pair<vec,vec> temp=get_p2(a,b,p,r);
            flag=1,s-=get_s_seg(p,temp.first,temp.second,c);
        }
        if(check(a,c,p,r)){
            pair<vec,vec> temp=get_p2(a,c,p,r);
            flag=1,s-=get_s_seg(p,temp.first,temp.second,b);
        }
        if(check(c,b,p,r)){
            pair<vec,vec> temp=get_p2(c,b,p,r);
            flag=1,s-=get_s_seg(p,temp.first,temp.second,a);
        }
        if(flag) return s;
        if(cross(b-a,c-a)*cross(b-a,p-a)>0 && 
           cross(c-a,b-a)*cross(c-a,p-a)>0 && 
           cross(c-b,a-b)*cross(c-b,p-b)>0)
            return get_s_cir(r);
        return 0;
    }
}
 
typedef G2D::vec vec2;
 
namespace G3D{
    struct vec{
        DB x,y,z;
        vec(DB _x=0,DB _y=0,DB _z=0):x(_x),y(_y),z(_z){}
        friend vec operator+(vec x,vec y){ return vec(x.x+y.x,x.y+y.y,x.z+y.z); }
        friend vec operator-(vec x,vec y){ return vec(x.x-y.x,x.y-y.y,x.z-y.z); }
        friend vec operator*(vec x,DB y){ return vec(x.x*y,x.y*y,x.z*y); }
        friend vec operator/(vec x,DB y){ return vec(x.x/y,x.y/y,x.z/y); }
        friend DB dot(vec x,vec y){ return x.x*y.x+x.y*y.y+x.z*y.z; }
        friend vec cross(vec x,vec y){ return vec(x.y*y.z-x.z*y.y,x.z*y.x-x.x*y.z,x.x*y.y-x.y*y.x); }
    }p[MAXN];
 
    struct face{
        int e1,e2,e3;
        vec normal;
    }f[MAXN];
 
    struct edge{
        int u,v;
        int e2;
    }e[MAXN];
 
    void calc_normal(int x){
        vec a=p[e[f[x].e1].u],b=p[e[f[x].e2].u],c=p[e[f[x].e3].u];
        f[x].normal=cross(b-a,c-a);
    }
 
    int n,ne,nf;
    bool tage[MAXN],tagf[MAXN];
    int pe[MAXN],tr[MAXN];
 
    DB calc_len(vec x){
        return sqrt(x.x*x.x+x.y*x.y+x.z*x.z);
    }
 
    void init(vec v1,vec v2,vec v3,vec v4){
        if(dot(cross(v4-v3,v1-v3),v2-v3)<0) swap(v3,v4);
        n=nf=4; ne=12;
        p[1]=v1; p[2]=v2; p[3]=v3; p[4]=v4;
        e[1]=(edge){1,2,4}; e[2]=(edge){2,4,12}; e[3]=(edge){4,1,9};
        e[4]=(edge){2,1,1}; e[5]=(edge){3,2,11}; e[6]=(edge){1,3,8};
        e[7]=(edge){4,3,10}; e[8]=(edge){3,1,6}; e[9]=(edge){1,4,3};
        e[10]=(edge){3,4,7}; e[11]=(edge){2,3,5}; e[12]=(edge){4,2,2};
        f[1].e1=1; f[1].e2=2; f[1].e3=3; calc_normal(1);
        f[2].e1=5; f[2].e2=4; f[2].e3=6; calc_normal(2);
        f[3].e1=8; f[3].e2=9; f[3].e3=7; calc_normal(3);
        f[4].e1=10; f[4].e2=12; f[4].e3=11; calc_normal(4);
    }
 
    void insert(vec np){
        memset(tagf+1,0,sizeof(bool)*nf);
        memset(tage+1,0,sizeof(bool)*ne);
        bool flag=0;
        for(int i=1;i<=nf;i++)
            if(dot(np-p[e[f[i].e1].u],f[i].normal)>eps){
                tagf[i]=1;
                tage[f[i].e1]^=1;
                tage[f[i].e2]^=1;
                tage[f[i].e3]^=1;
                flag=1;
            }
        if(!flag) return;
        int nf0=nf; nf=0;
        for(int i=1;i<=nf0;i++) if(!tagf[i]) f[++nf]=f[i];
        int ne0=ne,st;
        for(int i=1;i<=ne0;i++)
            if(!tage[i] && tage[e[i].e2]){
                tage[++ne]=0;
                e[e[ne].e2=i].e2=ne;
                e[ne].u=e[i].v;
                e[ne].v=e[i].u;
                pe[st=e[ne].u]=ne;
            }
        p[++n]=np;
        int cur=st,laste=0,f0=nf+1;
        do{
            int eid=pe[cur],nxt=e[eid].v;
            e[++ne]=(edge){n,cur,laste};
            if(laste) e[laste].e2=ne;
            e[laste=++ne]=(edge){nxt,n,0};
            cur=nxt;
            f[++nf]=(face){eid,ne,ne-1};
            tage[ne-1]=tage[ne]=0;
            calc_normal(nf);
        }while(cur!=st);
        e[laste].e2=f[f0].e3;
        e[f[f0].e3].e2=laste;
        ne0=ne; ne=0;
        for(int i=1;i<=ne0;i++)
            if(!tage[i]){
                e[++ne]=e[i];
                tr[i]=ne;
            }
        for(int i=1;i<=ne;i++) e[i].e2=tr[e[i].e2];
        for(int i=1;i<=nf;i++) f[i].e1=tr[f[i].e1],f[i].e2=tr[f[i].e2],f[i].e3=tr[f[i].e3];
    }
 
    DB query(vec a,vec b,DB r){
        vec d=b-a;
        d=d/sqrt(dot(d,d));
        vec d2(d.x,d.z,-d.y);
        vec u=cross(d,d2),v=cross(d,u);
        u=u/sqrt(dot(u,u));
        v=v/sqrt(dot(v,v));
        DB s=0;
        for(int i=1;i<=nf;i++)
            if(dot(f[i].normal,vec()-d)>eps){
                vec v1=p[e[f[i].e1].u],v2=p[e[f[i].e2].u],v3=p[e[f[i].e3].u];
                vec2 w1(dot(v1-a,u),dot(v1-a,v));
                vec2 w2(dot(v2-a,u),dot(v2-a,v));
                vec2 w3(dot(v3-a,u),dot(v3-a,v));
                DB s0=G2D::get_s(vec2(),r,w1,w2,w3),k=sqrt(dot(f[i].normal,f[i].normal))/dot(f[i].normal,vec()-d);
                s+=s0*k;
            }
        return s;
    }
}
 
typedef G3D::vec vec3;
 
vec3 readp(){
    vec3 x;
    x.x=read(); x.y=read(); x.z=read();
    return x;
}
 
void init(){
    vec3 v1=readp(),v2=readp(),v3=readp(),v4=readp();
    G3D::init(v1,v2,v3,v4);
}
 
int main(){
	freopen("c.in","r",stdin);
	freopen("std.out","w",stdout);
    init();
    int m=read();
    while(m--){
        if(read()==1) G3D::insert(readp());
        else{
            vec3 v1=readp(),v2=readp();
            printf("%.10f\n",(double)G3D::query(v1,v2,read()));
        }
    }
    return 0;
}