#ifdef NEG
#define M -4
#else
#define M 4
#endif
int main()
{
    int a = M;
    if (a)
        a = a + 4;
    else
        a = a * 4;
    return 0;
}
