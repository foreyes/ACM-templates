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
        pre = max_dis;
    }
    return res;
} 
//此处t的初始值设为1能过，设为0.5就WA，目前还不是很懂 
Point work(Point* p,int n){
    double t = 1,min_r = 1e18;
    Point now = p[0],ans = p[0];
    while(t > eps){
        int i = getPoint(p,now,n);
        double r = Length(p[i] - now);
        if(min_r > r){
        	min_r = r;
        	ans = now;
		}
        now.x = now.x + (p[i].x - now.x) * t;
        now.y = now.y + (p[i].y - now.y) * t;
        now.z = now.z + (p[i].z - now.z) * t; 
        t *= delta;
    }
    return ans;
} 
