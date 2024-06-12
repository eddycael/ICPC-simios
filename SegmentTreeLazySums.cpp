#include <iostream>
using namespace std;
struct Nodo {
	long long suma;
	bool lazy;
	long long p;
	int hijos;
	Nodo() {}

	Nodo(int z) {
		suma = z;
		lazy = false;
		p = 0;
		hijos = 1;
	}
	void unir(Nodo a, Nodo b) {
		suma = a.suma + b.suma;
		hijos = a.hijos + b.hijos;
		lazy = 0;
		p = 0;
	}
	void update(int v) {
		suma += 1LL * v * hijos;
		p += v;
		lazy = true;
		// hijos no se modifica 
	}
	void split(Nodo &a, Nodo &b) {
		a.update(p);
		b.update(p);
		lazy = 0;
		p = 0;
	}
};
int a[10];
Nodo T[16];
void init(int N, int L, int R) {
	if(L == R)
		T[N] = Nodo(a[L]);	
	else {
		int A = N << 1, M = (L + R) >> 1;
		init(A, L, M);
		init(A | 1, M+1, R);
		T[N].unir(T[A], T[A|1]);
	}
}
int I, J;
Nodo query(int N, int L, int R) {
	if(I <= L && R <= J)
		return T[N];	
	else {
		int A = N << 1, M = (L + R) >> 1;
		if(T[N].lazy)
			T[N].split(T[A], T[A|1]);
		if(I > M) return query(A | 1, M+1, R);
		else if(J <= M) return query(A, L, M);
		else {
			Nodo ans;
			ans.unir(query(A, L, M) , 
			query(A | 1, M+1, R));
			return ans;
		}
	}
}
int V;
void update(int N, int L, int R) {
	if(I <= L && R <= J)
		T[N].update(V);	
	else {
		int A = N << 1, M = (L + R) >> 1;
		if(I > M) update(A | 1, M+1, R);
		else if(J <= M) update(A, L, M);
		else {
			update(A, L, M);
			update(A | 1, M+1, R);
		}
		T[N].unir(T[A], T[A|1]);
	}
}
void ver() {
	for(int i = 1; i < 16; ++i) {
		cout << "Nodo " << i << "  suma " << T[i].suma
		<< "   lazy = " << T[i].lazy << "   P = " 
		<< T[i].p << endl;
	}

}
int main() {
	int n, q;
	scanf("%d %d", &n, &q);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	init(1, 0, n-1);
	//ver();
	int tipo;
	Nodo ans; 
	for(int i=0;i<q; ++i) {
		//cout << "Consulta " << (i+1) << endl;
		scanf("%d %d %d", &tipo, &I, &J);
		I--;
		J--;
		if(tipo == 1) {
			ans = query(1, 0, n-1);
			//printf("%lld\n", ans.suma);
			cout << ans.suma << endl;
		}
		else {
			scanf("%d", &V);
			update(1, 0, n-1);			
		}
		//ver();
	}
}