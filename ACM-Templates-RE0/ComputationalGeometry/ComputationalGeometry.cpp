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
//求向量A的单位左转法向量，使用前保证A不是零向量 
Vector Normal(Vector a){
	double L = Length(a);
	return Vector(-a.y/L,a.x/L);
}
//------------------线段相关内容--------------------
//有向直线 
struct Line{
	Point P;//直线上任意一点 
	Vector v;//方向向量，左边为半平面 
	double ang;//极角，从x正半轴转到v所需的角(弧度) 
	Line(){}
	Line(Point P, Vector v):P(P),v(v){
		ang = atan2(v.y, v.x);
	}
	bool operator < (const Line& L) const{ //半平面交需要的排序函数 
		return ang < L.ang;
	}
};
//直线相交，使用前保证有唯一交点，cross(v,w)非0
Point getLineIntersection(Line L1, Line L2){
	Vector u = L1.P - L2.P;
	double t = Cross(L2.v, u) / Cross(L1.v, L2.v);
	return L1.P + L1.v*t; 
}
//点到直线距离
double distanceToLine(Point P,Line L){
	Vector v1 = L.v, v2 = P - L.P;
	return fabs(Cross(v1,v2)) / Length(v1);//不取绝对值就是有向距离 
}
//点在线段上(不含端点)
bool pointOnSegment(Point P,Point a,Point b){
	return dcmp(Cross(a-P,b-P)) == 0 && dcmp((a-P)*(b-P)) < 0;
} 
//----------------多边形相关内容----------------------
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
	//仅适用于凸多边形 
	bool pointInPloygon(Point a){
		for(int i = 0;i < size;i++){
			if(Cross(ps[i]-a,ps[(i+1)%size]-a) < 0) return false;
		} 
		return true;
	}
	//TODO:实现判断点在凹多边形内 
};
