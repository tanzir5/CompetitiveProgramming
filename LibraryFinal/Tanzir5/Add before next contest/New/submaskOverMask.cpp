///O(3^n)
// iterate over all the masks
for (int mask = 0; mask < (1<<n); mask++){
    // iterate over all the subsets of the mask except for 0. Handle 0 manually
    for(int i = mask; i > 0; i = (i-1) & mask)
    {
        ??
    }
}
