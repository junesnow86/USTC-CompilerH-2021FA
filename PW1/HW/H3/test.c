int ccp(int z, int n)
{
    int y = z;
    int x = 1;
    while (n--)
    {
        if (y != z)
        {
            x = 2;
        }
        x = 2 - x;
        if (x != 1)
        {
            y = 2;
        }
    }
    return x;
}