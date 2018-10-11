//TODO:���lower_bound�汾��֧��һ�²����İ��� 
/*
ֻ���ؽ��ֵ����Ҫ���������ֵ�߶��� + ��ɢ��
���޸�ת�Ʒ��̣�ʵ��������������к�
*/
ll LIS(int* f,int len){
	ll ret = 0;
	//��ɢ���������ڽ��������ڽ���һ�� 
	discretize(f,len);
	memset(seg,0,sizeof(seg));
	for(int i = 1;i <= len;i++){
		//�����ϸ�С����Ҫ�޸�ѯ�ʣ����̿�����Ҫ�޸� 
		ll tmp = query(1,1,_cnt,1,get_id(f[i])-1) + 1;
		add(1,1,_cnt,get_id(f[i]),tmp);
		ret = max(ret,tmp);
	}
	return ret;
}
/*
�����ϵĻ������������
�����߶����ϵĽڵ���һ��pll�����޸��߶�����֤����ֵ�����С����
����ֵ�����С������pair�����second��������ȡ������������ֱ�Ӷ�pairȡmax������ȡmin�ȣ����޸�
*/
int last[maxn];
vi LIS(int* f,int len){
	ll ret = 0,mark;
	discretize(f,len);
	memset(seg,0,sizeof(seg));
	for(int i = 1;i <= len;i++){
		//�����ϸ�С����Ҫ�޸�ѯ�ʣ����̿�����Ҫ�޸� 
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
//TODO:����ģ�廹δ���Թ� 
/*
�����ݽ��д���֮��ѡȡȨֵ����ֵ�����С��x1 < x2��y1 < y2�����з������
����x1 <= x2����������ԼΪ������LIS 
x��y��Ҫ��ȫ�ֱ�������СΪlen���±��1��ʼ 
*/
int ord[maxn],last[maxn];
bool cmp(int a,int b){
	return x[a] < x[b];
}
//�߶����е�first��val��second�Ǳ��ȡ�� 
vi LIS(int len){
	//xȡֵ������-1ʱ��Ҫ�޸� 
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
�����Ǹ�ռ�ռ�̫����,̫���ӣ�дһ�����������ֻ����𰸵İ汾 
*/
int ord[maxn];
bool cmp(int a,int b){
	return x[a] < x[b];
}
ll LIS(int len){
	//xȡֵ������-1ʱ��Ҫ�޸� 
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
ģ���˻�����1��
��n�����ÿ������ϵ��һ���㹻���������ϡ�ÿ���������϶��´��������ϵĶ���Ȼ��ϵ��һ��ͼ��X�����ǹ��������ᡣ
������������ȫ���Եģ��������������ʧ���������㹻�ߣ�������ﲻ�ᴹ�����ϣ����Һ������е�Ħ����
������X����ƽ���ںδ���

��ֱ�����ѡ�㣬ÿ�������ķ����ƶ�
Ҳ�ɸ���������������ÿ����������ܺ���С 

ע�ⲻͬ����Ŀ������T��������Ҫ��������ж� 
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
ģ���˻�����2��
��С�����
���Ȳ��ܴﵽ�ܸ� 
*/
const double delta = 0.98;
//Ѱ���뵱ǰԲ����Զ�ĵ� 
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
//�˴�t�ĳ�ʼֵ��Ϊ1�ܹ�����Ϊ0.5��WA��Ŀǰ�����Ǻܶ� 
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
