//Josephus [ 0 indexed ] O (n) Recursive
int josephus(int n, int k)
{
    if(n == 1) return 0;
    return (josephus(n-1, k) + k)%n;
}

//  [ 0 Indexed] O(n) Iterative
int josephus(int n,int k)
{
    int bachbe=0,first_morbe,i;
    for(i=2;i<=n;i++)
    {
        first_morbe=(k)%i;
        bachbe=(first_morbe+bachbe)%i;
    }
    return bachbe;
}
