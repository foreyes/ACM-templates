#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-10;
const double pi = 3.1415926535897932;
const double eln = 2.718281828459045;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

string s[100] = {"UsefulTools","Algorithm","DataStructure","GraphTheory","StringAlgorithm","Math","NimGame","DynamicProgramming","ComputationalGeometry"};
int n = 9;
int main(){
    ios::sync_with_stdio(false);
	freopen("script.bat","w",stdout);
	for(int i = 0;i < n;i++){
		cout<<"cd "<<s[i]<<endl;
		cout<<"copy /b * "<<i<<".tmp"<<endl;
		cout<<"move "<<i<<".tmp ../"<<i<<".cpp"<<endl;
		cout<<"cd ../"<<endl;
	}
	//cout<<"copy /b *.tmp templates.cpp"<<endl;
	//cout<<"del *.tmp"<<endl;
	//cout<<"pause"<<endl;
    return 0;
}
