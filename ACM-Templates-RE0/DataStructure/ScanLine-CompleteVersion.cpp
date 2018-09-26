#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+10;
typedef long long ll;
ll lazy[maxn*4];
double seg[maxn*4],weight[maxn*4],num[maxn*4],len[maxn*4];

int _cnt;
double idx[maxn*4],tmp_id[maxn*4];
void discretize(double *f,int size){
	_cnt = 0;
	int tmp = 0;
	for(int i = 1;i <= size;i++) tmp_id[++tmp] = f[i];
	sort(tmp_id+1,tmp_id+tmp+1);
	for(int i = 1;i <= tmp;i++){
		if(i == 1 || tmp_id[i] != tmp_id[i-1]) idx[++_cnt] = tmp_id[i];
	}
}
int get_id(double x){
	return lower_bound(idx+1,idx+_cnt+1,x) - idx;
}
ll build(int o,int l,int r){
	if(l == r) return weight[o] = len[l];
	int mid = (l + r) >> 1;
	build(o<<1,l,mid);build(o<<1|1,mid+1,r);
	weight[o] = weight[o<<1] + weight[o<<1|1];
}
ll addLazy(int,int,int,ll);
void push_down(int o,int l,int r){
	int mid = (l + r) >> 1;
	addLazy(o<<1,l,mid,lazy[o]);
	addLazy(o<<1|1,mid+1,r,lazy[o]);
	lazy[o] = 0;
}
ll addLazy(int o,int l,int r,ll k){
	lazy[o] += k;
	if(lazy[o] > 0) return seg[o] = weight[o];
	if(l == r) return seg[o] = 0;
	if(lazy[o] < 0) push_down(o,l,r);
	seg[o] = seg[o<<1] + seg[o<<1|1];
}
ll add(int o,int l,int r,int L,int R,ll k){
	if(L > R) return 0;
	if(l >= L && r <= R) return addLazy(o,l,r,k);
	if(lazy[o] != 0) push_down(o,l,r);
	int mid = (l + r) >> 1;
	if(L <= mid) add(o<<1,l,mid,L,R,k);
	if(R > mid) add(o<<1|1,mid+1,r,L,R,k);
	seg[o] = seg[o<<1] + seg[o<<1|1];
}
double query(int o,int l,int r,int L,int R){
	if(l >= L && r <= R) return seg[o];
	if(lazy[o] != 0) push_down(o,l,r);
	int mid = (l + r) >> 1;
	double ans = 0;
	if(L <= mid) ans += query(o<<1,l,mid,L,R);
	if(R > mid) ans += query(o<<1|1,mid+1,r,L,R);
	return ans;
}
struct Line{
	double x,y1,y2;
	ll k;
	bool operator<(const Line& tar)const{
		if(x != tar.x) return x < tar.x;
		return k < tar.k;
	}
}lines[maxn*2];

int main(){
	int n;
	while(cin>>n){
		if(n == 0) break;
		memset(lazy,0,sizeof(lazy));
		memset(seg,0,sizeof(seg));
		int tot = 0,cnt = 0;
		for(int i = 0;i < n;i++){
			double x1,y1,x2,y2;
			cin>>x1>>y1>>x2>>y2;
			num[++cnt] = y1, num[++cnt] = y2;
			lines[tot].x = x1, lines[tot].y1 = y1, lines[tot].y2 = y2, lines[tot++].k = 1;
			lines[tot].x = x2, lines[tot].y1 = y1, lines[tot].y2 = y2, lines[tot++].k = -1;
		}
		discretize(num,cnt);
		for(int i = 1;i < _cnt;i++) len[i] = idx[i+1] - idx[i];
		len[_cnt] = 0;
		build(1,1,_cnt);
		sort(lines,lines+tot);
		double ans = 0, pre = 0;
		for(int i = 0;i < tot;i++){
			double tmp = query(1,1,_cnt,1,_cnt);
			ans += tmp * (lines[i].x - pre);
			add(1,1,_cnt,get_id(lines[i].y1),get_id(lines[i].y2)-1,lines[i].k);
			pre = lines[i].x;
		}
		printf("%.2f\n",ans); 
	}
}
