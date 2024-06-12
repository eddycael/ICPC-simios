#include <iostream>
#include <cstdio>
using namespace std;
int T[16];
int a[16];
void init(int N, int L, int R) {
	if(L == R)
		T[N] = a[L];
	else {
		int M, A;
		A = N << 1;
		M = (L + R) >> 1;
		init(A, L, M);
		init(A | 1, M + 1, R);
		T[N] = T[A] * T[A | 1];
	}
}
int I, J;
int query(int N, int L, int R) {
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
		    return query(A, L, M) * query(A | 1, M+1, R);
	}
}
void update(int N, int L, int R) {
	if(L == R) {
		a[L] = J;
		T[N] = J;
	} 
	else {
		int M, A;
		A = N << 1;
		M = (L + R) >> 1;
		if( I <= M)
			update(A, L, M);
		else 
			update(A | 1, M+1, R);
		T[N] = T[A] * T[A|1];	
	}
}
int main(int argc, char const *argv[]) {
	int n, q;
	char op[2];
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
        scanf("%d", a + i);
    init(1, 0, n-1);
    scanf("%d", &q);
	for(int i = 0; i < q; ++i) {
		scanf("%s %d %d", op, &I, &J);
		if(op[0] == 'Q') {
		    I--;
			J--;
			printf("es %d\n", query(1, 0, n-1));	
		}
		else {
			scanf("%s",&V);
			update(1, 0, n-1);
		}
	}
	return 0;
}