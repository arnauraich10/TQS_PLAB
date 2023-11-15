//Crear la tabla
//Poder insrtrarlas fichas y que "caigan"
//No poder insertar fichas donde no se pueda
//Que cada turno inserte ficha a quien le toque
//Que no se puedan insertar fichas donde la columna este completa
//Comprobar condiciones de victoria
#include <iostream>
using namespace std;
#include "tablero.h"
#include <cassert>
#include <fstream>

void inicializartablero(tablero tab[7][7]) {
	//Poner los valores del tablero a "_" y vaciar las posiciones (Inicializacion del tablero)
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			tab[i][j].ocupado = false;
			tab[i][j].valor = '_';
		}
	}
}

void mostrartablero(tablero tab[7][7]) {
	cout << "1 2 3 4 5 6 7 " << "\n";
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			cout << tab[i][j].valor << " ";
		}
		cout << "\n";
	}
}
int seleccionarposicion() {
	bool condicion = true;
	int posicion2;
	do
	{
		cout << "introduce la columna donde quieres introducir la ficha" << "\n";
		cin >> posicion2;
		switch (posicion2)
		{
		case 1:
			condicion = false;
			break;
		case 2:
			condicion = false;
			break;
		case 3:
			condicion = false;
			break;
		case 4:
			condicion = false;
			break;
		case 5:
			condicion = false;
			break;
		case 6:
			condicion = false;
			break;
		case 7:
			condicion = false;
			break;
		default:
			cout << "Esta posicion no es valida" << "\n";
			break;
		}
	} while (condicion);
	return posicion2;
}

void meterficha(tablero tab[7][7], bool turno) {
	int posicion;
	posicion = seleccionarposicion();
	bool puesta = true;
	do
	{
		if (tab[0][posicion - 1].ocupado == true)
		{
			cout << "No caben mas fichas en esta columna" << "\n";
			posicion = seleccionarposicion();
		}
		else {
			puesta = false;
			if (tab[6][posicion - 1].ocupado == false)
			{
				tab[6][posicion - 1].ocupado = true;
				if (turno == true)
				{
					tab[6][posicion - 1].valor = 'X';
				}
				else {
					tab[6][posicion - 1].valor = 'O';
				}
			}
			else {
				int fila = 7;
				do
				{
					fila = fila - 1;
				} while (tab[fila][posicion - 1].ocupado == true);
				tab[fila][posicion - 1].ocupado = true;
				if (turno == true) {
					tab[fila][posicion - 1].valor = 'X';
				}
				else {
					tab[fila][posicion - 1].valor = 'O';
				}
			}
		}
	} while (puesta);
}

bool comprobarGanador(tablero tab[7][7]) {
	// Comprobar filas
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 4; j++) {
			if (tab[i][j].ocupado &&
				tab[i][j].valor == tab[i][j + 1].valor &&
				tab[i][j].valor == tab[i][j + 2].valor &&
				tab[i][j].valor == tab[i][j + 3].valor) {
				return true;
			}
		}
	}

	// Comprobar columnas
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 7; j++) {
			if (tab[i][j].ocupado &&
				tab[i][j].valor == tab[i + 1][j].valor &&
				tab[i][j].valor == tab[i + 2][j].valor &&
				tab[i][j].valor == tab[i + 3][j].valor) {
				return true;
			}
		}
	}

	// Comprobar diagonales (de izquierda arriba a derecha abajo)
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tab[i][j].ocupado &&
				tab[i][j].valor == tab[i + 1][j + 1].valor &&
				tab[i][j].valor == tab[i + 2][j + 2].valor &&
				tab[i][j].valor == tab[i + 3][j + 3].valor) {
				return true;
			}
		}
	}

	// Comprobar diagonales (de izquierda abajo a derecha arriba)
	for (int i = 3; i < 7; i++) {
		for (int j = 0; j < 4; j++) {
			if (tab[i][j].ocupado &&
				tab[i][j].valor == tab[i - 1][j + 1].valor &&
				tab[i][j].valor == tab[i - 2][j + 2].valor &&
				tab[i][j].valor == tab[i - 3][j + 3].valor) {
				return true;
			}
		}
	}

	return false;
}

void guardarRanking(int puntosX, int puntosO) {
	ofstream archivo("ranking.txt");
	if (archivo.is_open()) {
		archivo << puntosX << " " << puntosO << endl;
		archivo.close();
	}
	else {
		cout << "No se pudo abrir el archivo de ranking." << endl;
	}
}

void cargarRanking(int& puntosX, int& puntosO) {
	ifstream archivo("ranking.txt");
	if (archivo.is_open()) {
		archivo >> puntosX >> puntosO;
		archivo.close();
	}
	else {
		cout << "No se pudo abrir el archivo de ranking." << endl;
	}
}
//____________________________CODI DE TESTS___________________________________

void testFicha() {
	tablero uno;
	uno.ocupado = false;
	uno.valor = 'O';
	assert(uno.ocupado == false);
	assert(uno.valor == 'O');
}

void testCreartablero() {
	tablero testablero[7][7];
	assert(testablero != NULL);
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			testablero[i][j].ocupado = true;
			testablero[i][j].valor = 'a';
		}
	}
	assert(testablero[1][3].ocupado == true);
	assert(testablero[1][3].valor == 'a');
}


void testinsertar(tablero tab[7][7]) {
	bool metido = false;
	int pos = 0;
	do
	{
		if (tab[0][pos].ocupado == false)
		{
			tab[0][pos].ocupado = true;
			tab[0][pos].valor = 'X';
			metido = true;
		}
		else {
			pos += 1;
		}
	} while (metido == false);
}

void testmeterficha() {
	tablero tabtestmeterficha[7][7];
	assert(tabtestmeterficha != NULL);
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			tabtestmeterficha[i][j].ocupado = false;
			tabtestmeterficha[i][j].valor = '_';
		}
	}
	testinsertar(tabtestmeterficha);
	assert(tabtestmeterficha[0][0].ocupado == true);
	assert(tabtestmeterficha[0][0].valor == 'X');
}
void testRanking() {
	int puntosX = 3;
	int puntosO = 5;

	guardarRanking(puntosX, puntosO);

	int puntosXLeidos = 0;
	int puntosOLeidos = 0;
	cargarRanking(puntosXLeidos, puntosOLeidos);

	assert(puntosXLeidos == puntosX);
	assert(puntosOLeidos == puntosO);

}

void testinsertarposicion(int posicion) {
	bool condicion = true;
	do
	{
		switch (posicion)
		{
		case 1:
			condicion = false;
			break;
		case 2:
			condicion = false;
			break;
		case 3:
			condicion = false;
			break;
		case 4:
			condicion = false;
			break;
		case 5:
			condicion = false;
			break;
		case 6:
			condicion = false;
			break;
		case 7:
			condicion = false;
			break;
		default:
			cout << "Esta posicion no es valida" << "\n";
			break;
		}
	} while (condicion);
}

void testatementcoveragemeterfichatrueuno(bool turno) {
	tablero tab[7][7];
	int posicion = 3;
	tab[0][2].ocupado = true;
	bool puesta = true;
	do{
		if (tab[0][posicion - 1].ocupado == true){
			cout << "No caben mas fichas en esta columna" << "\n";
			posicion = 4;
		}else{
			puesta = false;
			tab[6][posicion - 1].ocupado == false;
			if (tab[6][posicion - 1].ocupado == false)
			{
				tab[6][posicion - 1].ocupado = true;
				if (turno == true){
					tab[6][posicion - 1].valor = 'X';
				}else{
					tab[6][posicion - 1].valor = 'O';
				}
			}else {
				int fila = 7;
				do{
					fila = fila - 1;
				}while (tab[fila][posicion - 1].ocupado == true);
					tab[fila][posicion - 1].ocupado = true;
				if (turno == true) {
					tab[fila][posicion - 1].valor = 'X';
				}
				else {
					tab[fila][posicion - 1].valor = 'O';
				}
			}
		}
	} while (puesta);
}

void testatementcoveragemeterfichatruedos(bool turno) {
	tablero tab[7][7];
	int posicion = 3;
	tab[0][2].ocupado = false;
	bool puesta = true;
	do {
		if (tab[0][posicion - 1].ocupado == true) {
			cout << "No caben mas fichas en esta columna" << "\n";
			posicion = 4;
		}
		else {
			puesta = false;
			tab[6][posicion - 1].ocupado == true;
			if (tab[6][posicion - 1].ocupado == false)
			{
				tab[6][posicion - 1].ocupado = true;
				if (turno == true) {
					tab[6][posicion - 1].valor = 'X';
				}
				else {
					tab[6][posicion - 1].valor = 'O';
				}
			}
			else {
				int fila = 7;
				do {
					fila = fila - 1;
				} while (tab[fila][posicion - 1].ocupado == true);
				tab[fila][posicion - 1].ocupado = true;
				if (turno == true) {
					tab[fila][posicion - 1].valor = 'X';
				}
				else {
					tab[fila][posicion - 1].valor = 'O';
				}
			}
		}
	} while (puesta);
}


void tests() {
	//TDD
	testFicha();
	testCreartablero();
	testmeterficha();
	testRanking();
	//Particions equivalents i Valors limit i frontera
	/*testinsertarposicion(-10);
	testinsertarposicion(-1);
	testinsertarposicion(0);
	testinsertarposicion(1);
	testinsertarposicion(3);
	testinsertarposicion(6);
	testinsertarposicion(7);
	testinsertarposicion(8);
	testinsertarposicion(10);*/
	//Statement coverage + Condition Coverage + Decision Coverage + Path Coverage
	testatementcoveragemeterfichatrueuno(true);
	testatementcoveragemeterfichatrueuno(false);
	testatementcoveragemeterfichatruedos(true);
	testatementcoveragemeterfichatruedos(false);
	cout << "Los tests han ido bien" << endl;
	//cout << "Introduzca su nombre para empezar la partida" << endl;
	//string enter;	
	//cin >> enter;
}
//______________________________MAIN___________________________________________
int main() {
	tests();
	string respuesta = "";
	tablero tab[7][7];
	inicializartablero(tab);
	bool partida = true;
	bool turno = true;
	int puntosX = 0;
	int puntosO = 0;

	do
	{
		cargarRanking(puntosX, puntosO);
		cout << "Ranking Actual: " << endl;
		cout << "Victorias de X: " << puntosX << endl;
		cout << "Victorias de O: " << puntosO << endl;
		if (turno == true) {
			cout << "Turno del jugador X" << "\n";
		}
		else {
			cout << "Turno del jugador O" << "\n";
		}
		mostrartablero(tab);
		meterficha(tab, turno);
		std::cout << "\x1B[2J\x1B[H";

		if (comprobarGanador(tab)) {
			if (turno == true) {
				cout << "Jugador X ha ganado" << endl;
				puntosX++;
				cout << "Jugador X ya lleva " << puntosX << " partidas ganadas" << endl;
				guardarRanking(puntosX, puntosO);
			}
			else {
				cout << "Jugador O ha ganado" << endl;
				puntosO++;
				cout << "Jugador O ya lleva " << puntosO << " partidas ganadas" << endl;
				guardarRanking(puntosX, puntosO);
			}
			cout << "Quieres jugar otra partida? (s/n): " << endl;
			cin >> respuesta;
			if (respuesta == "s") {
				inicializartablero(tab);
			}
			else {
				partida = !partida;
			}
		}
		else {
			turno = !turno;
		}
	} while (partida);
}
