#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int T[16];
int a[16];
void init(int N, int L, int R) {
	if(L == R)
		T[N] = a[L] == 5;
	else {
		int M, A;
		A = N << 1;
		M = (L + R) >> 1;
		init(A, L, M);
		init(A | 1, M + 1, R);
		T[N] = T[A] + T[A | 1];
	}
}
int I, J;
int IC, JC;
int contar(int N, int L, int R) {
	if(L == R)
		return a[L] == 5;
	else {
		int M, A;
		A = N << 1;
		M = (L + R) >> 1;
		if( IC > M)
			return contar(A | 1, M+1, R);
		else if (JC <=M) return contar(A, L, M);
		else {
			return contar(A, L, M)
			+ contar(A | 1, M+1, R);
		}
	}
}
int query(int N, int L, int R, int K) {
	if(L == R)
		return L;
	else {
		int M, A;
		A = N << 1;
		M = (L + R) >> 1;
		if( T[A] >= K)
			return query(A, L, M, K);
		else return query(A | 1, M+1, R, K - T[A]);
	}
}
void update(int N, int L, int R) {
	if(L == R) {
		a[L] = J;
		T[N] = J == 5;
	} 
	else {
		int M, A;
		A = N << 1;
		M = (L + R) >> 1;
		if( I <= M)
			update(A, L, M);
		else 
			update(A | 1, M+1, R);
		T[N] = T[A] + T[A|1];	
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
    	printf("%d ", T[i]);
    putchar(10);
    int res, K;
	scanf("%d", &q);
	for(int i = 0; i < q; ++i) {
		scanf("%s", op);
		if(op[0] == 'Q') {
		    scanf("%d %d %d", &I, &J, &K);
		    I--;
			J--;
			IC = I;
			JC = J;
			res = contar(1, 0, n-1);
			if(res >= K) {
				if(I > 0) {
					IC = 0;
					JC = I - 1;
					K += contar(1, 0, n-1);
				}
				res = query(1, 0, n-1, K);
				printf("%d\n", res + 1);
			}
			else puts("-1");
		}
		else {
		    scanf("%d %d", &I, &J);
			I--;
			update(1, 0, n-1);
		}
	}
	return 0;
}