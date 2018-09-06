/* ���Դ��룺 
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
/* 

/*
Andrew�㷨����ˮƽ����͹��
����������p����ĸ���n����������Ϊ1��ʾ�㲻��������͹����ĸ�����͹���ĵ����ch������
ֱ���ϵĵ�ҲҪ��Ļ���������<=�ĳ�< 
����Ҫ���ʱ����ʹ����̬����
warning���±��0��ʼ
warning: ����������ֱ���ϵĶ���㣬ͬʱ���Ի����˻�����εĻ������������һ���汾 
*/
int convexHull(Point* p,bool* check,int n,Point* ch,Polygon& poly){
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
	if(m > 1) m--;
	poly.size = m;
	for(int i = 0;i < m;i++) poly.ps.pb(ch[i]);
	return m;
}
/*
�汾2�����ڴ������������
�����������Ҫ����ֱ���ϵĵ㣬ͬʱ���ܻ����˻���ֱ�ߵĶ���� 
*/ 
int convexHull(Point* p,bool* check,int n,Point* ch,Polygon& poly){
	sort(p,p+n);
	int m = 0,st = n;
	bool vis[n] = {0};
	for(int i = 0;i < n;i++){
		if(check[p[i].id]) continue;
		st = min(st,i); 
		while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) vis[ch[--m].id] = false;
		vis[p[i].id] = true;
		ch[m++] = p[i];
	}
	int k = m;
	for(int i = n-2;i >= 0;i--){
		if(check[p[i].id]) continue;
		if(i != st && vis[p[i].id]) continue;
		while(m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
		ch[m++] = p[i];
	}
	if(m > 1) m--;
	poly.size = m;
	for(int i = 0;i < m;i++) poly.ps.pb(ch[i]);
	return m;
}
