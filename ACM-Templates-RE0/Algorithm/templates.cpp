//TODO:添加lower_bound版本的支持一下操作的板子 
/*
只返回结果值，需要区间求最大值线段树 + 离散化
可修改转移方程，实现求最大上升序列和
*/
ll LIS(int* f,int len){
	ll ret = 0;
	//离散化，可以在仅主函数内进行一次 
	discretize(f,len);
	memset(seg,0,sizeof(seg));
	for(int i = 1;i <= len;i++){
		//不是严格小于需要修改询问，方程可能需要修改 
		ll tmp = query(1,1,_cnt,1,get_id(f[i])-1) + 1;
		add(1,1,_cnt,get_id(f[i]),tmp);
		ret = max(ret,tmp);
	}
	return ret;
}
/*
在以上的基础上输出方案
由于线段树上的节点是一个pll，需修改线段树保证输出字典序最小方案
输出字典序最小方案，pair里面的second存的是序号取负，这样可以直接对pair取max，若是取min等，需修改
*/
int last[maxn];
vi LIS(int* f,int len){
	ll ret = 0,mark;
	discretize(f,len);
	memset(seg,0,sizeof(seg));
	for(int i = 1;i <= len;i++){
		//不是严格小于需要修改询问，方程可能需要修改 
		pll tmp = query(1,1,_cnt,1,get_id(f[i])-1);
		ll val = tmp.fi + 1;
		last[i] = -tmp.se;
		add(1,1,_cnt,get_id(f[i]),mp(val,-i));
		if(val > ret){
			ret = val;
			mark = i;
		}
	}
	stack<int> s;
	while(mark != 0){
		s.push(mark);
		mark = last[mark];
	}
	vi retv;
	while(!s.empty()){
		retv.pb(s.top());
		s.pop();
	}
	return retv;
}
//TODO:以下模板还未测试过 
/*
对数据进行处理之后，选取权值最大字典序最小的x1 < x2，y1 < y2的序列方案输出
若是x1 <= x2，可排序后归约为正常的LIS 
x和y需要是全局变量，大小为len，下标从1开始 
*/
int ord[maxn],last[maxn];
bool cmp(int a,int b){
	return x[a] < x[b];
}
//线段树中的first是val，second是编号取负 
vi LIS(int len){
	//x取值可能是-1时需要修改 
	ll ret = 0,mark,lastx = -1;
	for(int i = 1;i <= len;i++) ord[i] = i;
	sort(ord+1,ord+len+1,cmp);
	discretize(y,len);
	memset(seg,0,sizeof(seg));
	queue<pair<ll,pll> > q;
	for(int i = 1;i <= len;i++){
		if(lastx != x[ord[i]]){
			while(!q.empty()){
				add(1,1,_cnt,q.front().fi,q.front().se);
				q.pop();
			}
			lastx = x[ord[i]];
		}
		pll tmp = query(1,1,_cnt,1,get_id(y[ord[i]])-1);
		ll val = tmp.fi + 1;
		last[i] = -tmp.se;
		q.push(mp(get_id(y[ord[i]]), mp(val,-ord[i])));
		if(val > ret){
			ret = val;
			mark = ord[i];
		}
	}
	stack<int> s;
	while(mark != 0){
		s.push(mark);
		mark = last[mark];
	}
	vi retv;
	while(!s.empty()){
		retv.pb(s.top());
		s.pop();
	}
	return retv;
}
/*
上面那个占空间太大了,太复杂，写一个不输出方案只输出答案的版本 
*/
int ord[maxn];
bool cmp(int a,int b){
	return x[a] < x[b];
}
ll LIS(int len){
	//x取值可能是-1时需要修改 
	ll ret = 0,lastx = -1;
	for(int i = 1;i <= len;i++) ord[i] = i;
	sort(ord+1,ord+len+1,cmp);
	discretize(y,len);
	memset(seg,0,sizeof(seg));
	queue<pll> q;
	for(int i = 1;i <= len;i++){
		if(lastx != x[ord[i]]){
			while(!q.empty()){
				add(1,1,_cnt,q.front().fi,q.front().se);
				q.pop();
			}
			lastx = x[ord[i]];
		}
		ll tmp = query(1,1,_cnt,1,get_id(y[ord[i]])-1) + 1;
		q.push(mp(get_id(y[ord[i]]),tmp));
		ret = max(ret,tmp);
	}
	return ret;
}
typedef long long ll;
const ll MOD = 1e9+7;

struct Mat{
	int size;
	vector<vector<ll> > a;
	Mat(int size = 3):size(size){}
	void setZero(){
		for(int i = 0;i < size;i++){
			vector<ll> tmp(size);
			for(int j = 0;j < size;j++){
				tmp[j] = 0;
			}
			a.push_back(tmp);
		}
	}
	void setUnit(){
		setZero();
		for(int i = 0;i < size;i++) a[i][i] = 1;
	}
	vector<ll>& operator[](size_t n){
		return a[n];
	} 
	Mat operator*(Mat& tar){
		Mat ret(size);
		ret.setZero();
		for(int i = 0;i < size;i++){
			for(int j = 0;j < size;j++){
				for(int k = 0;k < size;k++){
					ret[i][j] = (ret[i][j] + a[i][k] * tar[k][j])%MOD;
				}
			}
		}
		return ret;
	}
};
Mat matPow(Mat a,ll b){
	Mat ret(a.size);
	ret.setUnit();
	while(b){
		if(b & 1) ret = ret * a;
		a = a * a;
		b >>= 1;
	}
	return ret;
}
/*
模拟退火例题1：
有n个重物，每个重物系在一条足够长的绳子上。每条绳子自上而下穿过桌面上的洞，然后系在一起。图中X处就是公共的绳结。
假设绳子是完全弹性的（不会造成能量损失），桌子足够高（因而重物不会垂到地上），且忽略所有的摩擦。
问绳结X最终平衡于何处。

可直接随机选点，每次往力的方向移动
也可根据评估函数，让每个物体的势能和最小 

注意不同的题目，参数T的设置需要根据情况判断 
*/ 
const double delta = 0.99;
Vector getNext(Point *p,Point now,int n){
	Vector ret = Point(0,0);
	for(int i = 0;i < n;i++){
		ret = ret + unit(p[i]-now)*w[i];
	}
	return ret;
}
Point work(Point* p,int n){
	double t = 1,min_dis = 1e18;
	Point now = p[0],ans = p[0];
	while(t > eps){
		Vector dv = getNext(p,now,n);
		double l = Length(dv);
		if(min_dis > l){
			min_dis = l;
			ans = now;
		}
		now.x = now.x + dv.x * t;
		now.y = now.y + dv.y * t;
		t *= delta;
	}
	return ans;
}
/*
模拟退火例题2：
最小球包含
精度不能达到很高 
*/
const double delta = 0.98;
//寻找离当前圆心最远的点 
int getPoint(Point *p,Point now,int n){
	int res = -1;
    double max_dis = 0,pre= 0;
    for(int i = 0;i < n;i++){
        max_dis = max(max_dis,Length(p[i]-now));
        if(max_dis != pre) res = i;
        pre = max_d;
    }
    return res;
} 
//此处t的初始值设为1能过，设为0.5就WA，目前还不是很懂 
Point work(Point* p,int n){
    double t = 1,min_r = 1e18;
    Point now = p[0],ans = p[0];
    while(t > eps){
        int i = getPoint(p,now,n);
        now.x = now.x + (p[i].x - now.x) * t;
        now.y = now.y + (p[i].y - now.y) * t;
        now.z = now.z + (p[i].z - now.z) * t; 
        if(min_dis > r){
            min_dis = r;
            ans = now;
        }
        t *= delta;
    }
    return ans;
} 
