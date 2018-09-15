struct Point{
	double x,y;ll id; 
	Point(double _x = 0,double _y = 0):x(_x),y(_y){}
};
typedef vector<Point> polygon;
bool operator<(const Point& a,const Point& b){
	return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}
int dcmp(double x){
	if(fabs(x) < eps) return 0;else return x < 0 ? -1 : 1;
}
bool operator==(const Point& a,const Point& b){
	return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}
Point operator-(Point a,Point b){
	return Point(a.x-b.x, a.y-b.y);
}
Point operator+(Point a,Point b){
	return Point(a.x+b.x, a.y+b.y);
}
double operator*(Point a,Point b){
	return a.x*b.x + a.y*b.y;
}
Point operator*(Point a,double b){
	return Vector(a.x*b, a.y*b);
}
inline double Cross(Point a,Point b){
	return a.x*b.y - a.y*b.x;
}
inline double Length(Vector a){
	return sqrt(a.x*a.x + a.y*a.y);
}
inline double Length2(Vector a){
	return a.x*a.x + a.y*a.y;
}
//单位化向量 ，若是零向量直接返回 
Point unit(Point a){
	double l = Length(a); 
	if(l < eps) return a;
	return Point(a.x/l,a.y/l);
}
inline double Angle(Point a,Point b){
	return acos(a * b / Length(a) / Length(b));
}
//有向面积 
double Area2(Point a,Point b,Point c){
	return Cross(b-a,c-a);
}
Point rotate(Point a,double rad){
	return Point(a.x*cos(rad)-a.y*sin(rad), a.x*sin(rad)+a.y*cos(rad));
}
//求向量A的左转法向量 
Point normal(Point a){
	return Point(-a.y,a.x);
}
//求单位左转法向量，调用前请保证A不是零向量 
Point unitNormal(Point a){
	double l = Length(a);
	return Point(-a.y/l,a.x/l);
}
//不损失精度判断线段规范相交(不含端点)
bool isSegmentsIntersection(Point A,Point B,Point C,Point D){
	//跨立试验 
	if(Cross(C-A,D-A) * Cross(C-B,D-B) >= 0) return false;
	if(Cross(A-C,B-C) * Cross(A-D,B-D) >= 0) return false;
	//快速排斥试验 
	if(min(max(A.x,B.x),max(C.x,D.x)) < max(min(A.x,B.x),min(C.x,D.x))) return false;
	if(min(max(A.y,B.y),max(C.y,D.y)) < max(min(A.y,B.y),min(C.y,D.y))) return false;
	return true;
}
//点在线段上(//不含端点)
bool isPointOnSegment(Point P,Point a,Point b){
	if(P == a || P == b) return true;
	//if(p == a || p == b) return false;
	return dcmp(Cross(a-P,b-P)) == 0 && dcmp((a-P)*(b-P)) < 0;
} 
//判断两条线段是否有公共点 
bool isSegmengtsCrash(Point A,Point B,Point C,Point D){
	if( isPointOnSegment(A,C,D) || isPointOnSegment(B,C,D) ||
		isPointOnSegment(C,A,B) || isPointOnSegment(D,A,B)) return true;
	if(dcmp(Cross(B-A,D-C)) == 0) return false;//共线 
	return isSegmentsIntersection(A,B,C,D);//判断线段规范相交 
}
Point midPoint(Point a,Point b){
	return Point((a.x+b.x)*0.5,(a.y+b.y)*0.5);
} 
//------------------线段相关内容-------------------- 
//有向直线 
struct Line{
	Point p1,p2;//直线上两点，从p1到p2，左边是半平面 
	double ang;//极角，从x正半轴转到v所需的角(弧度) 
	Line(){}
	Line(Point p1, Point p2):p1(p1),p2(p2){
		ang = atan2(p2.y-p1.y, p2.x-p1.x);
	}
	bool operator < (const Line& L) const{ //半平面交需要的排序函数 
		return ang < L.ang;
	}
};
//直线相交，使用前保证有唯一交点，cross(v,w)非0
Point getLineIntersection(Line L1, Line L2){
	Point u = L1.P - L2.P;
	double t = Cross(L2.v, u) / Cross(L1.v, L2.v);
	return L1.P + L1.v*t; 
}
//点到直线距离
double distanceToLine(Point P,Line L){
	Point v1 = L.v, v2 = P - L.P;
	return fabs(Cross(v1,v2)) / Length(v1);//不取绝对值就是有向距离 
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
	//使用前请保证ps内按逆时针顺序存放，且为凸多边形 
	bool pointInPloygon(Point a){
		for(int i = 0;i < size;i++){
			if(Cross(ps[i]-a,ps[(i+1)%size]-a) < 0) return false;
		} 
		return true;
	}
	//TODO:实现判断点在凹多边形内 
};
//-----------------圆相关内容-----------------------
struct Circle{
	Point o;
	double r;
	Circle(Point o,double r):o(o),r(r){}
	Point point(double rad){
		return Point(o.x+cos(rad)*r,o.y+sin(rad)*r);
	}
};
//给定两点作为直径获取圆
Circle getCircle(Point a,Point b){
	return Circle((a+b)*0.5,Length(a-b)*0.5);
} 
//通过三个点来确定一个圆,若三点共线，将最远的两个点作为直径 
Circle getCircle(Point a, Point b, Point c){
	if(dcmp(Cross(b-a,c-a)) == 0){
		//三点共线
		if (dcmp(Length(a-b)+Length(b-c)-Length(a-c))==0) return getCircle(a,c);
        if (dcmp(Length(b-a)+Length(a-c)-Length(b-c))==0) return getCircle(b,c);
        if (dcmp(Length(a-c)+Length(c-b)-Length(a-b))==0) return getCircle(a,b);
	} else{
		Line L1 = Line(midPoint(a,b),normal(b-a));
		Line L2 = Line(midPoint(a,c),normal(c-a));
		Point o = getLineIntersection(L1,L2);
		return Circle(o,Length(a-o));
	}
}
//通过三个点得到最小圆
Circle getMinCircle(Point a,Point b,Point c){
	if(dcmp(Cross(b-a,c-a)) == 0){
		//三点共线
		if (dcmp(Length(a-b)+Length(b-c)-Length(a-c))==0) return getCircle(a,c);
        if (dcmp(Length(b-a)+Length(a-c)-Length(b-c))==0) return getCircle(b,c);
        if (dcmp(Length(a-c)+Length(c-b)-Length(a-b))==0) return getCircle(a,b);
	} else{
		if((b-a)*(c-a) <= 0) return getCircle(b,c);
		if((a-b)*(c-b) <= 0) return getCircle(a,c);
		if((a-c)*(b-c) <= 0) return getCircle(a,b);
		Line L1 = Line(midPoint(a,b),normal(b-a));
		Line L2 = Line(midPoint(a,c),normal(c-a));
		Point o = getLineIntersection(L1,L2);
		return Circle(o,Length(a-o));
	}
}
//点在圆内(不含边界是<)
bool pointInCircle(Point a,Circle c){
	return dcmp(Length2(a-c.o)-c.r*c.r) <= 0;
}
*/ 
