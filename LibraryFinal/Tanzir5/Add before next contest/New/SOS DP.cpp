void SOS(int N)
{
    /// base case ??
    for(int i = 0;i < N; ++i)
    {
        for(int mask = 0; mask < (1<<N); ++mask)
        {
            if(mask & (1<<i))
                F[mask] += F[mask^(1<<i)];
        }
    }
}
