#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
struct Nodo {
    int prod, suma, mn, mx, mcd;
	void init(int v) {
	   prod = v;
	   suma = v;
	   mn = v;
	   mx = v;
	   mcd = v; 
	}
};
Nodo merge(Nodo a, Nodo b) {
	Nodo res;
	res.suma = a.suma + b. suma;
	res.prod = a.prod * b. prod;
	res.mn = min(a.mn, b. mn);
	res.mx = max(a.mx, b. mx);
	res.mcd = __gcd(a.mcd, b.mcd);
	return res;
}
Nodo T[16];
int a[16];
void init(int N, int L, int R) {
	if(L == R)
		T[N].init(a[L]);
	else {
		int M, A;
		A = N << 1;
		M = (L + R) >> 1;
		init(A, L, M);
		init(A | 1, M + 1, R);
		T[N] = merge(T[A], T[A | 1]);
	}
}
int I, J;
Nodo query(int N, int L, int R) {
	if(I <= L && R <= J)
		return T[N];
	else {
		int M, A;
		A = N << 1;
		M = (L + R) >> 1;
		if( J <= M)
			return query(A, L, M);
		else if (I > M)
			return query(A | 1, M+1, R);
		else 
		    return merge(query(A, L, M), query(A | 1, M+1, R));
	}
}
void update(int N, int L, int R) {
	if(L == R) {
		a[L] = J;
		T[N].init(J);
	} 
	else {
		int M, A;
		A = N << 1;
		M = (L + R) >> 1;
		if( I <= M)
			update(A, L, M);
		else 
			update(A | 1, M+1, R);
		T[N] = merge(T[A], T[A|1]);	
	}
}
int main(int argc, char const *argv[]) {
	int n, q;
	char op[2];
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
        scanf("%d", a + i);
    init(1, 0, n-1);
    for(int i = 1; i < 16; ++i)
    	printf("%d ", T[i].suma);
    putchar(10);
    for(int i = 1; i < 16; ++i)
    	printf("%d ", T[i].prod);
    putchar(10);
	Nodo res;
	scanf("%d", &q);
	for(int i = 0; i < q; ++i) {
		scanf("%s %d %d", op, &I, &J);
		if(op[0] == 'Q') {
		    I--;
			J--;
			res = query(1, 0, n-1);
			printf("es %d %d %d %d %d\n", res.suma, res.prod, res.mn, res.mx, res.mcd);	
		}
		else {
			I--;
			update(1, 0, n-1);
		}
	}
	return 0;
}