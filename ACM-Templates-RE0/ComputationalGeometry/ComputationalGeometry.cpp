struct Point{
	double x,y;ll id; 
	Point(double _x = 0,double _y = 0):x(_x),y(_y){}
};
typedef Point Vector;
bool operator<(const Point& a,const Point& b){
	return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}
Vector operator-(Point a,Point b){
	return Point(a.x-b.x, a.y-b.y);
}
Vector operator+(Point a,Point b){
	return Point(a.x+b.x, a.y+b.y);
}
double operator*(Vector a,Vector b){
	return a.x*b.x + a.y*b.y;
}
Vector operator*(Vector a,ll b){
	return Vector(a.x*b, a.y*b);
}
inline ll Cross(Point a,Point b){
	return a.x*b.y - a.y*b.x;
}
inline double Length(Vector a){
	return sqrt(a.x*a.x + a.y*a.y);
}
inline double Length2(Vector a){
	return a.x*a.x + a.y*a.y;
}
inline double Angle(Vector a,Vector b){
	return acos(a * b / Length(a) / Length(b));
}
int dcmp(double x){
	if(fabs(x) < eps) return 0;else return x < 0 ? -1 : 1;
}
bool operator==(const Point& a,const Point& b){
	return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}
double Area2(Point a,Point b,Point c){
	return Cross(b-a,c-a);
}
Vector rotate(Vector a,double rad){
	return Vector(a.x*cos(rad)-a.y*sin(rad), a.x*sin(rad)+a.y*cos(rad));
}
//������A�ĵ�λ��ת��������ʹ��ǰ��֤A���������� 
Vector Normal(Vector a){
	double L = Length(a);
	return Vector(-a.y/L,a.x/L);
}
//------------------�߶��������--------------------
//����ֱ�� 
struct Line{
	Point P;//ֱ��������һ�� 
	Vector v;//�������������Ϊ��ƽ�� 
	double ang;//���ǣ���x������ת��v����Ľ�(����) 
	Line(){}
	Line(Point P, Vector v):P(P),v(v){
		ang = atan2(v.y, v.x);
	}
	bool operator < (const Line& L) const{ //��ƽ�潻��Ҫ�������� 
		return ang < L.ang;
	}
};
//ֱ���ཻ��ʹ��ǰ��֤��Ψһ���㣬cross(v,w)��0
Point getLineIntersection(Line L1, Line L2){
	Vector u = L1.P - L2.P;
	double t = Cross(L2.v, u) / Cross(L1.v, L2.v);
	return L1.P + L1.v*t; 
}
//�㵽ֱ�߾���
double distanceToLine(Point P,Line L){
	Vector v1 = L.v, v2 = P - L.P;
	return fabs(Cross(v1,v2)) / Length(v1);//��ȡ����ֵ����������� 
}
//�����߶���(�����˵�)
bool pointOnSegment(Point P,Point a,Point b){
	return dcmp(Cross(a-P,b-P)) == 0 && dcmp((a-P)*(b-P)) < 0;
} 
//----------------������������----------------------
struct Polygon{
	int size;
	vector<Point> ps;
	vector<double> rad;
	vector<double> length;
	void getRad(){
		//TODO
	}
	double getLength(){
		double sum = 0;
		length.clear();
		for(int i = 0;i < size;i++){
			length.pb(Length(ps[i]-ps[(i+1)%size]));
			sum += length.back();
		}
		return sum;
	}
	//��������͹����� 
	bool pointInPloygon(Point a){
		for(int i = 0;i < size;i++){
			if(Cross(ps[i]-a,ps[(i+1)%size]-a) < 0) return false;
		} 
		return true;
	}
	//TODO:ʵ���жϵ��ڰ�������� 
};
