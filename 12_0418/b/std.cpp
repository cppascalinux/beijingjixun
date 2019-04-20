#include <cstdio>
#include <algorithm>
#include <vector>
 
using std::max;
using std::sort;
using std::vector;
 
typedef long long LL;
typedef long double LD;
typedef __float128 F128;
typedef __int128 I128;
 
const double DINF=1e40;
const int N=1000000+10;
 
F128 sqr(F128 x){
    return x*x;
}
F128 sqrt(F128 x){
    F128 l=0,r=x,mid;
    for(int i=0;i<100000;i++){
        mid=(l+r)*0.5;
        if(sqr(mid)<x)
            l=mid;
        else
            r=mid;
    }
    return l;
}
 
int n,m,c;
struct Point{
    LL x,y;
    static LD Slope(const Point &a,const Point &b){
        if(a.x==b.x)
            return a.y<=b.y?+DINF:-DINF;
        return LD(b.y-a.y)/(b.x-a.x);
    }
}ans1,ans2;
LD ans;
 
Point ptr[N],que[N];
namespace IO{/*{{{*/
    const int LEN=10000000;
    char *inBuf,*inPtr;
    char *outBuf,*outPtr;
    void Init(){
        inBuf=new char[LEN];
        outBuf=outPtr=new char[LEN];
    }
    void Load(){
        fread(inBuf,1,LEN,stdin);
        inPtr=inBuf;
    }
    void Flush(){
        fwrite(outBuf,1,outPtr-outBuf,stdout);
    }
    char GetChar(){
        char res=*(inPtr++);
        if(inPtr-inBuf==LEN)
            Load();
        return res;
    }
    void PutChar(char c){
        *(outPtr++)=c;
    }
    LL GetInt(){
        LL x=0,f=1;
        char c=GetChar();
        while(c<'0'||c>'9'){if(c=='-')f=-1;c=GetChar();}
        while('0'<=c&&c<='9'){x=x*10+c-'0';c=GetChar();}
        return x*f;
    }
    void PutI128(I128 x){
        if(x==0){
            PutChar('0');
        }else{
            if(x<0){
                PutChar('-');
                x=-x;
            }
            static int digit[1000],len;
            for(len=0;x;x/=10) digit[++len]=x%10;
            for(;len;len--) PutChar('0'+digit[len]);
        }
    }
    void PutF128(F128 x,char end='\n'){
        if(x<0){
            PutChar('-');
            x=-x;
        }
        PutI128(I128(x));
        PutChar('.');
        x=x-I128(x);
        for(int i=1;i<c;i++){
            x=x*10;
            PutChar('0'+int(x));
            x-=int(x);
        }
        x=x*10;
        int y=int(x);
        x-=int(x);
        if(x>=0.499999)
            y++;
        PutChar('0'+y);
    }
}/*}}}*/
namespace Scan{/*{{{*/
    struct Event{
        int type;
        Point p;
    }e[N];
    int ecnt;
    bool Legal(Point &a,Point &b,Point &c){
        //  (b.y-a.y)/(b.x-a.x)<(c.y-b.y)/(c.x-b.x)
        return 1.0*(b.y-a.y)*(c.x-b.x)<1.0*(c.y-b.y)*(b.x-a.x);
    }
    void Init(vector<Point> &a,vector<Point> &b){
        ecnt=0;
        int i=0,j=0;
        while(i<int(a.size())||j<int(b.size())){
            if(i<int(a.size())&&(j==int(b.size())||a[i].x<=b[j].x))
                e[ecnt++]=(Event){0,a[i++]};
            else
                e[ecnt++]=(Event){1,b[j++]};
        }
    }
    void Run(){
        static int que[N],head,tail;
        head=1; tail=0;
        for(int i=0;i<ecnt;i++){
            Point p=e[i].p;
            if(e[i].type==0){
                while(tail-head+1>=2&&!Legal(e[que[tail-1]].p,e[que[tail]].p,p))
                    tail--;
                que[++tail]=i;
            }else{
                while(tail-head+1>=2&&Point::Slope(e[que[head]].p,e[que[head+1]].p)<ans)
                    head++;
                if(head<=tail){
                    LD k=Point::Slope(e[que[head]].p,p);
                    if(k>ans){
                        ans=k;
                        ans1=e[que[head]].p;
                        ans2=p;
                    }
                }
            }
        }
    }
}/*}}}*/
namespace Seg{/*{{{*/
    const int SIZE=(::N)*2;
    struct LinkNode{
        int id;
        int nex;
    }ln[(::N)*36];
    int lnCnt;
    struct Node{
        int ch[2];
        int ha,hb,ea,eb;
    }a[SIZE];
    int nodeCnt;
    int rt;
    void Build(int &u,int l,int r){
        u=++nodeCnt;
        if(l==r)
            return;
        int mid=(l+r)>>1;
        Build(a[u].ch[0],l,mid);
        Build(a[u].ch[1],mid+1,r);
    }
    void InsertPtr(int u,int l,int r,int ml,int mr,int id){
        if(ml<=l&&r<=mr){
            if(a[u].ha==0){
                a[u].ha=a[u].ea=++lnCnt;
                ln[lnCnt]=(LinkNode){id,0};
            }else{
                ln[a[u].ea].nex=++lnCnt;
                ln[lnCnt].id=id;
                a[u].ea=lnCnt;
            }
            return;
        }
        int mid=(l+r)>>1;
        if(mr<=mid){
            InsertPtr(a[u].ch[0],l,mid,ml,mr,id);
        }else if(mid<ml){
            InsertPtr(a[u].ch[1],mid+1,r,ml,mr,id);
        }else{
            InsertPtr(a[u].ch[0],l,mid,ml,mid,id);
            InsertPtr(a[u].ch[1],mid+1,r,mid+1,mr,id);
        }
    }
    void InsertQue(int u,int l,int r,int pos,int id){
        if(a[u].hb==0){
            a[u].hb=a[u].eb=++lnCnt;
            ln[lnCnt]=(LinkNode){id,0};
        }else{
            ln[a[u].eb].nex=++lnCnt;
            ln[lnCnt].id=id;
            a[u].eb=lnCnt;
        }
        if(l==r)
            return;
        int mid=(l+r)>>1;
        if(pos<=mid)
            InsertQue(a[u].ch[0],l,mid,pos,id);
        else
            InsertQue(a[u].ch[1],mid+1,r,pos,id);
    }
    void Calc(int u,int l,int r){
        if(a[u].ha&&a[u].hb){
            vector<Point> ta,tb;
            for(int x=a[u].ha;x;x=ln[x].nex)
                ta.push_back(ptr[ln[x].id]);
            for(int x=a[u].hb;x;x=ln[x].nex)
                tb.push_back(que[ln[x].id]);
            Scan::Init(ta,tb);
            Scan::Run();
        }
        if(l==r)
            return;
        int mid=(l+r)>>1;
        Calc(a[u].ch[0],l,mid);
        Calc(a[u].ch[1],mid+1,r);
    }
}/*}}}*/
namespace Hash{/*{{{*/
    const int M=9875321;
    const int N=(::N);
    int head[M];
    struct Node{
        LL k1,k2;
        int v1,v2;
        int nex;
    }a[N];
    int nodeCnt;
    int GetVal(LL x,LL y){
        return (1ll*(x%M)*(y%M)%M+M)%M;
    }
    void Insert(LL k1,LL k2,int y1,int y2){
        int p=GetVal(k1,k2);
        a[++nodeCnt]=(Node){k1,k2,y1,y2,head[p]};
        head[p]=nodeCnt;
    }
    int Query(LL k1,LL k2){
        int p=GetVal(k1,k2);
        int u;
        for(u=head[p];u&&!(a[u].k1==k1&&a[u].k2==k2);u=a[u].nex);
        if(u&&a[u].k1==k1&&a[u].k2==k2)
            return u;
        else
            return -1;
    }
}/*}}}*/
bool Cmp1(const int &x,const int &y){
    if(ptr[x].x!=ptr[y].x)
        return ptr[x].x<ptr[y].x;
    return ptr[x].y<ptr[y].y;
}
bool Cmp2(const int &x,const int &y){
    if(que[x].x!=que[y].x)
        return que[x].x<que[y].x;
    return que[x].y<que[y].y;
}
void ReadData(){/*{{{*/
    using IO::GetInt;
    GetInt();
    n=GetInt(); c=GetInt();
    static int start[N],end[N];
    static int qt[N];
    int qcnt=0;
    for(int i=1;i<=n;i++){
        int opt;
        LL x,y;
        opt=GetInt(); x=GetInt(); y=GetInt();
        switch(opt){
            case 1:{
                       int u=Hash::Query(x,y);
                       if(u==-1){
                           Hash::Insert(x,y,0,0);
                           u=Hash::nodeCnt;
                       }
                       Hash::a[u].v2++;
                       if(Hash::a[u].v2>1)
                           break;
                       m++;
                       start[m]=i;
                       ptr[m].x=x; ptr[m].y=y;
                       Hash::a[u].v1=m;
                       break;
                   }
            case 2:{
                       int u=Hash::Query(x,y);
                       Hash::a[u].v2--;
                       if(Hash::a[u].v2>0)
                           break;
                       int z=Hash::a[u].v1;
                       end[z]=i-1;
                       break;
                   }
            case 3: que[++qcnt]=(Point){x,y};
                    qt[qcnt]=i;
                    break;
        }
    }
    for(int i=1;i<=m;i++)
        if(Hash::a[Hash::Query(ptr[i].x,ptr[i].y)].v2>0)
            end[i]=n;
    static int a[N],b[N];
    for(int i=1;i<=m;i++) a[i]=i;
    for(int i=1;i<=qcnt;i++) b[i]=i;
    sort(a+1,a+m+1,Cmp1);
    sort(b+1,b+qcnt+1,Cmp2);
    Seg::Build(Seg::rt,1,n);
    for(int i=1;i<=m;i++){
        int j=a[i];
        Seg::InsertPtr(Seg::rt,1,n,start[j],end[j],j);
    }
    for(int i=1;i<=qcnt;i++){
        int j=b[i];
        Seg::InsertQue(Seg::rt,1,n,qt[j],j);
    }
}/*}}}*/
int main(){
    freopen("b.in","r",stdin);
    freopen("std.out","w",stdout);
    IO::Init();
    IO::Load();
    ReadData();
    ans=-DINF;
    Seg::Calc(Seg::rt,1,n);
    if(ans==-DINF){
        printf("-1.");
        for(int i=1;i<=c;i++) putchar('0');
    }else if(ans==+DINF){
        printf("1.");
        for(int i=1;i<=c;i++) putchar('0');
    }else{
        F128 edge=sqrt(sqr(ans2.y-ans1.y)+sqr(ans2.x-ans1.x));
        F128 result=F128(ans2.y-ans1.y)/edge;
        IO::PutF128(result);
    }
    IO::Flush();
    puts("");
    return 0;
}