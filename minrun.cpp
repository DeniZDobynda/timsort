int getMinrun(int n)
{
    int r = 0;

    while ( n >= 64 )
    {
        r |= n & 1;
        n >>= 1;
    }

    return n+r;
}
