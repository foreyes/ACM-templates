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
Point operator+(Point a,Point b){
	return Point(a.x+b.x, a.y+b.y);
}
ll operator*(Point a,Point b){
	return a.x*b.x + a.y*b.y;
}
Point operator*(Point a,ll b){
	return Point(a.x*b, a.y*b);
}
inline ll Cross(Point a,Point b){
	return a.x*b.y - a.y*b.x;
}
inline double Length(Point a){
	return sqrt((double)(a*a));
}
inline double Angle(Point a,Point b){
	return acos((double)(a * b) / Length(a) / Length(b));
}
//不损失精度判断线段规范相交(不含端点)
/若要判断线段是否有点在多边形内部，最好缩多边形，判任一公共点，
//或者把线段端点往里缩一下，同时取中点，check一下这三个点是不是在多边形内部 
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
	return Cross(a-P,b-P) == 0 && (a-P)*(b-P) < 0;
} 
//判断两条线段是否有公共点 
bool isSegmengtsCrash(Point A,Point B,Point C,Point D){
	if( isPointOnSegment(A,C,D) || isPointOnSegment(B,C,D) ||
		isPointOnSegment(C,A,B) || isPointOnSegment(D,A,B)) return true;
	if(Cross(B-A,D-C) == 0) return false;//共线 
	return isSegmentsIntersection(A,B,C,D);//判断线段规范相交 
}
