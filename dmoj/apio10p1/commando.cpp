#include <bits/stdc++.h>
using namespace std;


const long long INF = (long long)1e18;

class linear_function // y = mx+b
{
	private:
		long long m, b; 
	public:
		linear_function(){
			/*
				Sometimes is usefull to start with a function y = -INF 
				in MAXimization problems or y = +INF in MINimization problems.
			*/
			this->b = INF;
		}
		linear_function(long long _m, long long _b){
			this->m = _m;
			this->b = _b;
		}
		long long eval(long long x) const{
			if(b==abs(INF))
				return b; //return +INF (or -INF) if y = +INF (or y = -INF)
			return m*x+b; //evaluate the function in the given x coordinate.
		}
};
class Node //LiChaoTree node
{
	public:
		Node * l, * r;
		linear_function f;
		
		Node(linear_function _f){
			this->f = _f;
			this->l = this->r = NULL;
		}
		
};
class LiChaoTree
{
	private:
		Node * root;
		long long min_x, max_x; //the range of the queries (i.e. "domain" of the functions [min_x,max_x])
		
		Node * add_aux(long long l, long long r, Node * cur, linear_function f){
			if(l>r)return NULL;
			if(cur==NULL)return new Node(f);// Create a new node.
				
			long long m = l+(r-l)/2;
			
			/* 
				Check if the intersection point lies on the left or 
				on the right of the middle (m) point. If it lies on 
				the left, progate the update on the left side using
				the worst function, otherwise do it on the right side.
				
				(>) : for MAXimization problems;
				(<) : for MINimization problems.
			*/
			auto a = cur->f.eval(l) > f.eval(l);
			auto b = cur->f.eval(m) > f.eval(m);
			
			/*
				If the new function gives a better answer swap it 
				with the current function in the node.
			*/
			if(!b)swap(cur->f, f);
			
			if(l==r)return cur;
				
			/*
				If a==b then the intersection lies on the right side.
				Otherwise, it lies on the left. This came from fact 
				that if a==b then one of the functions is dominant in 
				the left side ([l,m]). Thereby, propage the update 
				with the worst function.
			*/
			if(a==b)cur->r = add_aux(m+1, r, cur->r, f);
			else cur->l = add_aux(l, m, cur->l, f); 
			
			return cur;
		}
		
		long long get_aux(long long l, long long r, Node * cur, long long x){
			/*
				If we reach a NULL node or an invalid range is given
				return -INF in MAXimization and +INF in MINimization 
				problems.
			*/
			if(l>r)return -INF;
			if(cur==NULL)return -INF;
			
			/*
				Evaluate the (best) function for this range in the
				given x coordinate.
			*/
			auto ans = cur->f.eval(x);
			
			if(l==r)return ans;
				
			long long m = l+(r-l)/2;
		
			/*
				MAXimize the answer through the path of the given x.
				DON'T FORGET to CHANGE the max function to min in a
				MINimization problem.
			*/
			if(x<m)ans = max(ans, get_aux(l, m, cur->l, x));
			else ans = max(ans, get_aux(m+1, r, cur->r, x));
			
			return ans;
		}
		
	public:
		/*
			Initialize with the min and max value of x that can be queried,
			so that the tree can be able to answer what is the MAX value
			(or MIN, depending on the problem) for any of the functions (y=mx+b) 
			previously added, in a given "x" that lies in the range [min_x, max_x].
			
			For example: maximize dp[i] = i*dp[j]+b[j]^2 for i<=j<=n.
			In this case, it's sufficient to have min_x=1 and max_x=n, 
			because x values are indices of a (1-indexed) array.
		*/
		LiChaoTree(long long _min_x,long long _max_x){
			root = NULL;
			this->min_x = _min_x;
			this->max_x = _max_x;
		}
		void add(linear_function f){ //O(logN)
			root = this->add_aux(min_x, max_x, root, f);
		}
		long long get(long long x){ //O(logN)
			return this->get_aux(min_x, max_x, root, x);	
		}
};

constexpr int64_t MAX_SUM = int64_t(1e8);
LiChaoTree lct(1, MAX_SUM);

void solve() {
    int n;
    int64_t a, b, c;
    cin >> n >> a >> b >> c;
    vector<int> x(n + 1);
    for (int i = 1; i <= n; i++) cin >> x[i];
    vector<int64_t> p(n + 1);
    for (int i = 1; i <= n; i++) p[i] = p[i - 1] + x[i];

    // since "a" is always negative, we have increasing queries, increasing slopes
    lct.add(linear_function(0, 0));
    vector<int64_t> dp(n + 1);
    for (int i = 1; i <= n; i++) {
        int64_t out = c + b * p[i] + a * p[i] * p[i];
        dp[i] = lct.get(p[i]) + out;
        lct.add(linear_function(-2*a*p[i], dp[i] - b * p[i] + a * p[i] * p[i]));
    }
    cout << dp[n] << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
