int func(int a) {
    return a + 2;
}

int main() {
    int a = 2;
    int b = 1*a;
    int c = func(b);
    int d = func(b);
    return c+d;
}