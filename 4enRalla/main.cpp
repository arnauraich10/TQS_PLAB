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

void inicializartablero(tablero tab[7][7]) {
	//Poner los valores del tablero a "_" y vaciar las posiciones (Inicializacion del tablero)
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 7; j++){
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

void meterficha(tablero tab[7][7],bool turno) {
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
				if (turno==true)
				{
					tab[6][posicion - 1].valor = 'X';
				}else{
					tab[6][posicion - 1].valor = 'O';
				}
			}
			else {
				int fila = 7;
				do
				{
					fila = fila - 1;
				}while (tab[fila][posicion - 1].ocupado == true);
				tab[fila][posicion - 1].ocupado = true;
				if (turno == true)				{
					tab[fila][posicion - 1].valor = 'X';
				}
				else{
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
//____________________________CODI DE TESTS___________________________________

void testFicha() {
	tablero uno;
	uno.ocupado = false;
	uno.valor = 'O';
	assert(uno.ocupado==false);
	assert(uno.valor == 'O');
}

void testCreartablero() {
	tablero testablero[7][7];
	assert(testablero != NULL);
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 7; j++){
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
		if (tab[0][pos].ocupado==false)
		{
			tab[0][pos].ocupado = true;
			tab[0][pos].valor = 'X';
			metido = true;
		}
		else {
			pos +=1;
		}
	} while (metido == false);
}

void testmeterficha() {
	tablero tabtestmeterficha[7][7];
	assert(tabtestmeterficha != NULL);
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 7; j++){
			tabtestmeterficha[i][j].ocupado = false;
			tabtestmeterficha[i][j].valor = '_';
		}
	}
	testinsertar(tabtestmeterficha);
	assert(tabtestmeterficha[0][0].ocupado == true);
	assert(tabtestmeterficha[0][0].valor == 'X');
}

void tests() {
	testFicha();
	testCreartablero();
	testmeterficha();
	cout << "Los tests han ido bien"<<endl;
	cout << "Introduzca su nombre para empezar la partida" << endl;
	string enter;	
	cin >> enter;
}
//______________________________MAIN___________________________________________
int main(){
	tests();
	string respuesta = "";
	tablero tab[7][7];
	inicializartablero(tab);
	bool partida = true;
	bool turno = true;
	do
	{
		if (turno==true){
			cout << "Turno del jugador X" << "\n";
		}else{
			cout << "Turno del jugador O" << "\n";
		}
		mostrartablero(tab);
		meterficha(tab,turno);
		std::cout << "\x1B[2J\x1B[H";
		
		if (comprobarGanador(tab)) {
			if (turno == true) {
				cout << "Jugador X ha ganado" << endl;
			}
			else {
				cout << "Jugador O ha ganado" << endl;
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
