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
        pre = max_dis;
    }
    return res;
} 
//�˴�t�ĳ�ʼֵ��Ϊ1�ܹ�����Ϊ0.5��WA��Ŀǰ�����Ǻܶ� 
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
