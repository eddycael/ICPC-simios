#include <iostream>
#include <cstdio>
// Eddy Cael Mamani Canaviri
// Nunca dejes de aprender
using namespace std;
int T[16];
int a[16];
void init(int N, int L, int R) {
	if (L == R)
		T[N] = a[L];
	else {
		int M;
		M = (L + R) / 2;
		init(N * 2 ,L , M);
		init(N * 2 + 1 ,M + 1 , R);
        T[N] = T[N * 2] * T[N * 2 + 1];
	}
}
int I, J;
int query(int N, int L, int R) {
    //printf("Rango %d con %d %d\n", N ,L, R);
    if(I <= L && R <= J) {
    	//printf("Rango %d %d valido con %d\n", L, R, T[N]);
    	return T[N];
    }
    else {
    	int M;
    	M = (L + R) / 2;
    	if(J <= M) {
    		//printf("Buscare por la izquierda\n");
    		return query(N * 2, L, M);
    	}
    	else if(I > M) {
    		//printf("Buscare por la derecha\n");
    		return query(N * 2 + 1, M + 1, R);
    	}
    	else {
    		//printf("Buscare por ambos lados\n");
    		return query(N * 2, L, M) * query(N * 2 + 1, M + 1, R);
    	}	 
    }
}
int main(int argc, char const *argv[]) {
	int n, q;
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
        scanf("%d", a + i);
    init(1, 0, n-1);
    for(int i = 1; i < 16; ++i)
    	printf("%d ", T[i]);
    putchar(10);
	scanf("%d", &q);
	for(int i = 0; i < q; ++i) {
		scanf("%d %d", &I, &J);
		I--;
		J--;
		printf("es %d\n", query(1, 0, n-1));
	}
	return 0;
}
