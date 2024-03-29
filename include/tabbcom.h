/*
 * tabbcom.h
 *
 *  Created on: 25/03/2014
 *      Author: Jorge Amat Soler
 */

#ifndef TABBCOM_CPP_
#define TABBCOM_CPP_

#include<iostream>
#include<queue>

#include "tvectorcom.h"

using namespace std;

class TNodoABB;

//Declaración de la clase TABBCom
class TABBCom {
	friend class TNodoABB;
	friend ostream & operator<<(ostream &, const TABBCom &);

public:
	TABBCom();
	TABBCom(const TABBCom &);
	~TABBCom();
	TABBCom & operator=(const TABBCom &);

	bool operator==(const TABBCom &) const;
	bool EsVacio() const;
	bool Insertar(const TComplejo &);
	bool Borrar(const TComplejo &);
	bool Buscar(const TComplejo &) const;
	TComplejo Raiz() const;
	int Altura() const;
	int Nodos() const;
	int NodosHoja() const;
	TVectorCom Inorden() const;
	TVectorCom Preorden() const;
	TVectorCom Postorden() const;
	TVectorCom Niveles() const;
	void InordenAux(TVectorCom &, int &) const;
	void PreordenAux(TVectorCom &, int &) const;
	void PostordenAux(TVectorCom &, int &) const;

private:
	TNodoABB *nodo;

    void Copiar(const TABBCom &);
    bool esHoja() const;
    void Sustituir();
    void NivAux(TVectorCom &, int &) const;
    bool mayor(TComplejo) const;
};

//Declaración de la clase TNodoABB
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

#endif /* TABBCOM_CPP_ */
