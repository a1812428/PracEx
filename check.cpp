#include<bits/stdc++.h>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
//pbds *st.find_by_order(k) or kth largest element in log(n) and 
//st.order_of_key(k) will return number of elements lesser than k in O(logn)
#define ll long long
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> pbds; 
#define ld long double
#define loop(i,a,b) for(ll i=a;i<b;i++)
#define mod 1000000007
#define pb push_back
#define pob pop_back
struct Trie{    
    Trie *nxt[26];
    bool ended;
};
struct Trie *getNode(void){ 
    struct Trie *pNode =  new Trie;
    pNode->ended = false; 
    loop(i,0,26)
        pNode->nxt[i] = NULL;
    return pNode; 
}
void insert(struct Trie *root, string key){ 
    struct Trie *pCrawl = root;
    loop(i,0,key.size()){
        ll index = key[i]-'a';
        if(!pCrawl->nxt[index]) 
            pCrawl->nxt[index] = getNode();
        pCrawl = pCrawl->nxt[index]; 
    }
    pCrawl->ended = true; 
}
bool search(struct Trie *root, string key){ 
    struct Trie *pCrawl = root; 
    loop(i,0,key.size()){
        ll index = key[i]-'a'; 
        if(!pCrawl->nxt[index]) 
            return false;
        pCrawl = pCrawl->nxt[index]; 
    }
    return (pCrawl!=NULL && pCrawl->ended); 
} 
ll gcd(ll a, ll b){
    if (b == 0)
        return a;
    return gcd(b, a % b); 
     
}

ll ceil(ll a, ll b) {
    if (a == 0) 
        return 0ll;
    return (a - 1)/b + 1;
}

pair<ll, ll> Egcd(ll x, ll y)
{
    if(x==0)
        return make_pair(0,1);
    pair<ll, ll> t = Egcd(y % x, x);
    return make_pair(t.second-t.first*(y/x), t.first);
}
ll powerm(ll x, ll y, ll m){
    ll ans=1, r=1;
    x%=m;
    while(r>0&&r<=y){
        if(r&y){
            ans*=x;
            ans%=m;
        }
        r<<=1;
        x*=x;
        x%=m;
    }
    return ans;
}
ll lcm(ll a, ll b){
    return a*b/gcd(a, b);
}
ll power(ll x, ll n){
    if(n==0)
        return 1;
    ll pow = power(x, n/2);
    if(n & 1)
        return x*pow*pow;
    return pow*pow;
}
ll floor_sqrt(ll x){     
    // Base cases 
    if (x == 0 || x == 1)  
       return x; 
    // Do Binary Search for floor(sqrt(x)) 
    ll start = 1, end = x, ans;    
    while(start <= end){         
        int mid = (start + end) / 2;
        // If x is a perfect square 
        if (mid*mid == x) 
            return mid;
        // Since we need floor, we update answer when mid*mid is  
        // smaller than x, and move closer to sqrt(x) 
        if (mid*mid < x){ 
            start = mid + 1; 
            ans = mid; 
        }  
        else // If mid*mid is greater than x 
            end = mid-1;         
    } 
    return ans; 
} 
vector<ll> prime_sieve(ll n){
    vector<ll> p(n+1, 0);
    for(ll i=3; i<=n; i+=2){
        p[i] = 1;
    }
    for(ll i=3; i<=n; i+=2){
        if(p[i] == 1){
            for(ll j=i*i; j<=n; j+=i){
                p[j] = 0;
            }
        }
    }
    p[1] = p[0] = 0;
    p[2] = 1;
    return p;
}
vector<ll> prime_numbers(ll n){
    vector<ll> primes = prime_sieve(n);
    vector<ll> prime_array(n,0);
    ll count = 0;
    for(ll i=2; i<=n; i++){
        if(primes[i]==1){
            prime_array[count] = i;
            count++;
        }
    }
    prime_array.resize(count);
    return prime_array;
}
vector<ll> factorize(ll m){
    vector<ll> factors;
    ll num = floor_sqrt(m)+2;
    vector<ll> primes = prime_numbers(num);
    factors.clear();
    ll i = 0;
    ll p = primes[0];
    while(p*p <= m){
        if(m%p == 0){
            while(m%p == 0){
                factors.push_back(p);
                m = m/p;
            }
        }
        i++;
        p = primes[i];
    }
    if(m != 1){
        factors.push_back(m);
    }
    return factors;
}
ll no_of_divisors(ll m){
    ll num = floor_sqrt(m)+2;
    vector<ll> primes = prime_numbers(num);
    ll i = 0;
    ll p = primes[0];
    ll ans = 1;

    while(p*p <= m){
        if(m%p == 0){
            ll count = 0;
            while(m%p == 0){
                count++;
                m = m/p;
            }
            ans = ans*(count + 1);
        }
        i++;
        p = primes[i];
    }
    if(m != 1){
        ans = ans * 2;
    }
    return ans;
}
vector<ll> build_segment_tree(vector<ll> &arr){
    ll n = arr.size();
    vector<ll> tree(4*n);
    // insert leaf nodes in tree 
    loop(i,0,n)    
        tree[n+i] = arr[i];
    // build the tree by calculating parents 
    for(ll i=n-1;i>0;--i)      
        tree[i] = tree[i<<1] + tree[i<<1 | 1];  
    //equivalent to tree[i]=tree[2*i]+tree[2*i+1]
    return tree;
}
void update_segment_tree(vector<ll> &tree, ll p, ll value){  
    // set value at position p
    ll n = tree.size()/4;
    tree[p+n] = value; 
    p = p+n;
    // move upward and update parents 
    for(ll i=p; i>1; i>>=1) 
        tree[i>>1] = tree[i] + tree[i^1]; 
}
ll query_segment_tree(vector<ll> &tree, ll l, ll r){  
    ll n = tree.size()/4;
    ll res = 0;
    // loop to find the sum in the range 
    for(l += n, r += n; l < r; l >>= 1, r >>= 1){ 
        if (l&1)
            res += tree[l++]; 
        if (r&1)  
            res += tree[--r]; 
    }
    return res; 
}

template<typename T>
class Graph{
    public:
        unordered_map<T, list<T>> adj;
        unordered_map<T, bool> visited;
        Graph(){

        }
        void addEdge(T n1, T n2, bool bidir=true){
            adj[n1].pb(n2);
            if(bidir){
                adj[n2].pb(n1);
            }
        }
        void print(){
            for(auto row: this->adj){
                cout << row.first << "-->";
                for(T el: row.second){
                    cout << el << ",";
                }
                cout << "\n";
            }
        }
        void bfs(T src){
            queue<T> q;
            q.push(src);
            this->visited[src] = true;

            while(!q.empty()){
                T node = q.front();
                q.pop();
                cout << node << " ";
                for(int nbr: this->adj[node]){
                    if(!this->visited[nbr]){
                        q.push(nbr);
                        //mark that nbr as visited
                        this->visited[nbr] = true;
                    }
                }
            }
        }
        void dfs(T src){
            this->visited[src] = true;
            cout << src << " ";
            for(T neighbour: this->adj[src]){
                if(!this->visited[neighbour]){
                    dfs(neighbour);
                }
            }
        }
        ll connectedComponent(T v){
            ll count = 0;
            for(ll i=1; i<v; i++){
                if(!this->visited[i]){
                    this->dfs(i);
                    cout << "\n";
                    count++;
                }
            }
            return count;
        }
        T singleSourceShortestPath(T src, T dest){
            //Traverse all the nodes of the graph
            queue<T> q;
            unordered_map<T, T> distance;
            unordered_map<T, T> parent;
            distance[src] = 0;
            parent[src] = src;
             q.push(src);
             this->visited[src] = true;

            while(!q.empty()){
                ll node = q.front();
                q.pop();
                for(T neighbour: this->adj[node]){
                    if(!this->visited[neighbour]){
                        q.push(neighbour);
                        this->visited[neighbour] = true;
                        distance[neighbour] = distance[node]+1;
                        parent[neighbour] = node;
                    }
                }
            }
            return distance[dest];
        }
};
void FasIO(){  
    // #ifndef ONLINE_JUDGE 
    // freopen("input.txt", "r", stdin); 
    // freopen("output.txt", "w", stdout); 
    // #endif 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}


int main()
{
    FasIO();
    ll t = 1;
    // cin >> t;
    loop(test,1,t+1){
        
    }
    return 0;
}