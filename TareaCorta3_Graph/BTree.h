#include <iostream>
#include "TKey.h"
using namespace std;

//Factor del BTree
const short int T = 5;
//Maxima cantidad de llaves por pagina del BTree
const short int M = 2 * T - 1;
struct BTreePage {
	//Estructura de una pagina o nodo del BTree
	//de orden T con M llaves y M+1 punteros
	//pIndex addr; //Direccion de la pagina en disco
	short int n; //Cantidad de llaves
	TKey key[M]; //Llaves
	//pIndex tp[M + 1]; //Punteros
	int t = 5;
	bool isLeaf; //Indica si es una hoja
	bool isDel; //Indica si la pagina fue borrada
	bool lleno = false;
	//Constructores
	void insertarLlave(TKey llave) {
		for (int i = 0; i < M;i++) {
			if (key[i].valor == 0) {
				key[i] = llave;
				cout << "Meti una llave en la posicion: "<<i<<endl;
				break;
			}
			if (key[M-1].distancia != 0) {
				cout << "Se lleno " << endl;
				lleno = true;
			}
		}
	}
	bool vacia() {
		return (key[0].valor != 0 ? false : true);
	}
	void showKeys() {
		for (int i = 0; i < M; i++) {
			cout << "Llave: " << key[i].valor << endl;
		}
	
	}
	BTreePage(){
		for (int i = 0; i < M; i++) {
			TKey llave{};
			key[i] = llave;
		}
	}
	/*BTreePage(TKey k, pIndex izq, pIndex der) {
		addr = 0;
		n = 1;
		isLeaf = false;
		isDel = false;
		key[0] = k;
		tp[0] = izq;
		tp[1] = der;
	}*/
};