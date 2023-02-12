int main()
{
    clock_t start, ed;
    start = clock();
    /// code
    /// code end
    ed = clock();
    double time_elapsed = (double)(ed - start) / CLOCKS_PER_SEC;
    fprintf(stderr, "%.3f s\n", time_elapsed);
    return 0;
}
