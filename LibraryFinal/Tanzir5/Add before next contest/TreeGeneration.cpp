/// generates a random tree with 10^5 nodes under 1 second. Takes more than 6 seconds to generate random tree with 10^6 nodes
#define MAX     100000
namespace tree{
    int par[MAX+10];
    int Find(int a)
    {
        if(par[a] == a)
            return a;
        return par[a] = Find(par[a]);
    }

    bool Union(int u, int v)
    {
        int a = Find(u), b = Find(v);
        if(a == b)
            return false;
        par[a] = b;
        return true;
    }

    void generateTree(int _n)
    {
        int n = _n;
        srand(time(NULL));
        cout << n << endl;
        for(int i= 1; i<=n; i++)
            par[i] =i;
        for(int i = 1; i<n; i++)
        {
            int u = (rand()*rand())%n+1;
            int v = (rand()*rand())%n+1;
            if(Union(u,v))
                printf("%d %d\n",u,v);
            else
                i--;
        }
    }
}

int main()
{
    freopen("inputTree.txt", "w", stdout);
    tree::generateTree(MAX);
}


