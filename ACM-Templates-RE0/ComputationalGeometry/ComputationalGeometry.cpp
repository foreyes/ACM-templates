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
	return sqrt(a*a);
}
inline double Angle(Vector a,Vector b){
	return acos(a * b / Length(a) / Length(b));
}
int dcmp(double x){
	if(fab(x) < eps) return 0;else return x < 0 ? -1 : 1;
}
bool operator==(const Point& a,const Point& b){
	return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}
double Area2(Point a,Point b,Point c){
	return Cross(b-a,c-a);
}
Vector rotate(Vector a,double rad){
	return Vector(a.x*cos(rad)-a.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}
//使用前保证A不是零向量 
Vector normal(Vector a){
	double L = Length(a);
	return Vector(A.x/L,A.y/L);
}

