/**************************************************************
    Problem: 3470
    User: 2019bj01
    Language: C++
    Result: Accepted
    Time:667 ms
    Memory:158044 kb
****************************************************************/
 
 
#include<bits/stdc++.h>
using namespace std;
#define li long long
char cc[100000],*dd = cc + 100000;
#define gc ((dd == cc + 100000 ? (fread(cc,1,100000,stdin),dd = cc) : 0),*(dd++))
//#define gc getchar()
#define pc putchar
inline li read(){
    li x = 0,y = 0,c = gc;
    while(!isdigit(c)) y = c,c = gc;
    while(isdigit(c)) x = x * 10 + c - '0',c = gc;
    return y == '-' ? -x : x;
}
inline void print(li q){
    if(q < 0) pc('-'),q = -q;
    if(q >= 10) print(q / 10);
    pc(q % 10 + '0');
}
int n,m,q,tot;
struct qy{
    int op,x,l,r;
}b[500010];
struct nd{
    int l,r,len;
    nd(int _l = 0,int _r = 0,int _len = 0){l = _l;r = _r;len = _len;}
}p[500010];
char s[2000010];
int sm[2000010];
int sa[2000010],rk[2000010],js[2000010],tp[2000010],ht[2000010],bj[2000010],lgo[1000010];
int st[21][1000010];
inline nd wk(nd u,nd v){
    if(u.l == -1 || v.l == -1) return nd(-1,-1,-1);
    if(!u.len) return v;
    if(!v.len) return u;
    nd as;as.len = u.len + v.len;
    int l,r,mid,ans;
    l = u.l;r = u.r;ans = u.r + 1;
    while(l <= r){
        mid = l + r >> 1;
        if(rk[sa[mid] + u.len] >= v.l) ans = mid,r = mid - 1;
        else l = mid + 1;
    }
    as.l = ans;
    l = u.l;r = u.r;ans = u.l - 1;
    while(l <= r){
        mid = l + r >> 1;
        if(rk[sa[mid] + u.len] <= v.r) ans = mid,l = mid + 1;
        else r = mid - 1;
    }
    as.r = ans;
    if(as.l > as.r) return nd(-1,-1,-1);
    return as;
}
inline int qy(int l,int r){
    --r;
    int x = lgo[r - l + 1];
    return min(st[x][l],st[x][r - (1 << x) + 1]);
}
inline nd wk2(int u,int v){
    if(u > v) return nd(1,tot,0);
    nd as;as.len = v - u + 1;
    int l,r,mid,ans;
    as.l = as.r = rk[u];
    l = 1;r = rk[u] - 1;ans = rk[u];
    while(l <= r){
        mid = l + r >> 1;
        if(qy(mid,rk[u]) >= v - u + 1) ans = mid,r = mid - 1;
        else l = mid + 1;
    }
    as.l = ans;
    l = rk[u] + 1;r = tot;ans = rk[u];
    while(l <= r){
        mid = l + r >> 1;
        if(qy(rk[u],mid) >= v - u + 1) ans = mid,l = mid + 1;
        else r = mid - 1;
    }
    as.r = ans;
    if(as.l > as.r) return nd(-1,-1,-1);
    return as;
}
int main(){
    freopen("c.in","r",stdin);
    freopen("c.out","w",stdout);
    register int i,j;
    read();n = tot = read();m = read();q = read();for(i = 1;i <= n;++i) s[i] = gc;
    for(i = 1;i <= n;++i) s[i] -= 'a' - 1;s[++tot] = 27;
    for(i = 1;i <= q;++i){
        b[i].op = read();
        if(b[i].op == 1){
            b[i].x = read();
            if(bj[b[i].x]){
                b[i].l = bj[b[i].x];b[i].r = tot;bj[b[i].x] = 0;
            }
            else bj[b[i].x] = tot + 1;
        }
        else if(b[i].op == 2){
            b[i].x = gc;while(b[i].x < 'a' || b[i].x > 'z') b[i].x = gc;
            b[i].x -= 'a' - 1;
            s[++tot] = b[i].x;
        }
        else{
            b[i].x = read();
            if(bj[b[i].x]){
                b[i].l = bj[b[i].x];b[i].r = tot;bj[b[i].x] = tot + 1;
            }
        }
    }
    for(i = 1;i <= m;++i) p[i].l = 1,p[i].r = tot,p[i].len = 0;
    for(i = 1;i <= tot;++i) ++js[s[i]];
    for(i = 1;i <= 27;++i) js[i] += js[i - 1];
    for(i = 1;i <= tot;++i) sa[js[s[i]]--] = i;
    for(i = 1;i <= tot;++i) rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
    for(i = 1;i <= 27;++i) js[i] = 0;
    for(i = 0;i < 20;++i){
        for(j = 0;j <= tot;++j) js[j] = 0;
        for(j = 1;j <= tot;++j) ++js[rk[j + (1 << i)]];
        for(j = 1;j <= tot;++j) js[j] += js[j - 1];
        for(j = 1;j <= tot;++j) tp[js[rk[j + (1 << i)]]--] = j;
        for(j = 0;j <= tot;++j) js[j] = 0;
        for(j = 1;j <= tot;++j) ++js[rk[j]];
        for(j = 1;j <= tot;++j) js[j] += js[j - 1];
        for(j = tot;j;--j) sa[js[rk[tp[j]]]--] = tp[j];
        for(j = 1;j <= tot;++j) tp[sa[j]] = tp[sa[j - 1]] + (rk[sa[j]] != rk[sa[j - 1]] || rk[sa[j] + (1 << i)] != rk[sa[j - 1] + (1 << i)]);
        for(j = 1;j <= tot;++j) rk[j] = tp[j];
        if(rk[sa[tot]] == tot) break;
    }
    for(i = 1;i <= tot;++i) if(rk[i] != tot) for(ht[rk[i]] = max(0,ht[rk[i - 1]] - 1);s[i + ht[rk[i]]] == s[sa[rk[i] + 1] + ht[rk[i]]];++ht[rk[i]]);
    for(i = 1;i <= tot;++i) sm[i] = sm[i - 1] + (sa[i] <= n);
    for(i = 1;i < tot;++i) st[0][i] = ht[i];
    for(i = 1;i < 20;++i){
        for(j = 1;j + (1 << i) - 1 <= tot;++j) st[i][j] = min(st[i - 1][j],st[i - 1][j + (1 << i - 1)]);
    }
    for(i = 2;i <= tot;++i) lgo[i] = lgo[i >> 1] + 1;
    int tc = 0;
    for(i = 1;i <= q;++i){
        if(b[i].l){
            p[b[i].x] = wk(p[b[i].x],wk2(b[i].l,b[i].r));
        } 
        if(b[i].op == 3){
            if(!p[b[i].x].len || p[b[i].x].l == -1) pc('0');
            else print(sm[p[b[i].x].r] - sm[p[b[i].x].l - 1]);
            pc('\n');
        } 
    }
    return 0;
}