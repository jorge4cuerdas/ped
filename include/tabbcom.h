/*
 * tabbcom.h
 *
 *  Created on: 25/03/2014
 *      Author: Jorge Amat Soler
 */

#ifndef TABBCOM_CPP_
#define TABBCOM_CPP_

#include<iostream>

#include "tvectorcom.h"

using namespace std;

class TABBCom;

class TNodoABB {
	friend class TABBCom;

public:
	TNodoABB();
	TNodoABB(const TNodoABB &);
	~TNodoABB();
	TNodoABB & operator=(const TNodoABB &);

private:
	TComplejo item;
	TABBCom iz, de;
};

class TABBCom {
	friend class TNodoABB;
	friend ostream & operator<<(ostream &, const TABBCom &);

public:
	TABBCom();
	TABBCom(const TABBCom &);
	~TABBCom();
	TABBCom & operator=(const TABBCom &);

	bool operator==(Tconst ABBCom &);
	bool EsVacio();
	bool Insertar(const TComplejo &);
	bool Borrar(const TComplejo &);
	bool Buscar(const TComplejo &);
	TComplejo Raiz();
	int Altura();
	int Nodos();
	int NodosHoja();
	TVectorCom Inorden();
	TVectorCom Preorden();
	TVectorCom Postorden();
	TVectorCom Niveles();
	void InordenAux(const TVectorCom &, int &);
	void PreordenAux(const TVectorCom &, int &);
	void PostordenAux(const TVectorCom &, int &);

private:
	TNodoABB *nodo;
};

#endif /* TABBCOM_CPP_ */
