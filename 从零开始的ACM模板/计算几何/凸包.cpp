#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point{
	ll x,y,id;
	Point(ll _x = 0,ll _y = 0):x(_x),y(_y){}
};
bool operator<(const Point& a,const Point& b){
	return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}
Point operator-(Point a,Point b){
	return Point(a.x-b.x, a.y-b.y);
}
inline ll Cross(Point a,Point b){
	return a.x*b.y - a.y*b.x;
}
/*
Andrew算法基于水平序求凸包
输入点的数组p，点的个数n，布尔数组为1表示点不被；返回凸包点的个数，凸包的点存在ch数组里
如果凸包边上的点不计算，把两个<=改成<
精度要求高时建议使用三态函数
warning：下标从0开始 
*/
int convexHull(Point* p,bool* check,int n,Point* ch){
	sort(p,p+n);
	int m = 0;
	for(int i = 0;i < n;i++){
		if(check[p[i].id]) continue; 
		while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
		ch[m++] = p[i];
	}
	int k = m;
	for(int i = n-2;i >= 0;i--){
		if(check[p[i].id]) continue;
		while(m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
		ch[m++] = p[i];
	}
	if(n > 1) m--;
	return m;
}
const int maxn = 3e5+10;
Point data[maxn],ch[maxn];
bool vis1[maxn],vis2[maxn],vis3[maxn];

ll gcd(ll a,ll b){
	return b == 0 ? a : gcd(b,a%b);
}

int main(){
	ios::sync_with_stdio(false);
	//freopen("average.in","r",stdin);
	//freopen("average.out","w",stdout);
	ll n;
	cin>>n;
	for(int i = 0;i < n;i++){
		cin>>data[i].x>>data[i].y;
		data[i].id = i;
	}
	int len = convexHull(data,vis1,n,ch);
	ll ans = n * len;
	vis1[ch[0].id] = true;
	for(int i = 1;i < len;i += 2) vis2[ch[i].id] = true;
	for(int i = 2;i < len;i += 2) vis3[ch[i].id] = true;
	ans += convexHull(data,vis1,n,ch) - len;
	ans += convexHull(data,vis2,n,ch) - len;
	ans += convexHull(data,vis3,n,ch) - len;
	ll d = gcd(ans,n);ans/=d;n/=d;
	cout<<ans<<"/"<<n<<endl;
	return 0;
}
