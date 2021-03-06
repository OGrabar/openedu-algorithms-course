#include <fstream>
#include <iostream>

int digit(int n, int k, int N, int M) {
    return (n >> (N * k) & (M - 1));
}

void radixsort(long *l, long *r, int N) {
    int k = (32 + N - 1) / N;
    int M = 1 << N;
    int sz = r - l;
    long *b = new long[sz];
    long *c = new long[M];
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < M; j++)
            c[j] = 0;
        for (long *j = l; j < r; j++)
            c[digit(*j, i, N, M)]++;
        for (int j = 1; j < M; j++)
            c[j] += c[j - 1];
        for (long *j = r - 1; j >= l; j--)
            b[--c[digit(*j, i, N, M)]] = *j;
        int cur = 0;
        for (long *j = l; j < r; j++)
            *j = b[cur++];
    }
    delete b;
    delete c;
}

int main() {
    std::ifstream in("input.txt");
    int n, m;
    in >> n >> m;
    long a[n];
    for (int i = 0; i < n; i++) in >> a[i];
    long b[m];
    for (int i = 0; i < m; i++) in >> b[i];

    int nm = n * m;
    long ab[nm];
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ab[k++] = a[i] * b[j];
        }
    }

    radixsort(ab, ab + nm, sizeof(long));

    int sum = 0;
    for (int i = 0; i < nm; i += 10)
        sum += ab[i];

    std::ofstream out("output.txt");
    out << sum;

    return 0;
}
