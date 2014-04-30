/*
 * tabbcom.cpp
 *
 *  Created on: 25/03/2014
 *      Author: jorge
 */

#include "tabbcom.h"

////////////
//TNODOABB//
////////////

TNodoABB::TNodoABB() {
	//No hay que hacer nada, no hay punteros en la clase.
}

TNodoABB::TNodoABB(const TNodoABB &nodo) {
	item = nodo.item;
	iz = nodo.iz;
	de = nodo.de;
}

TNodoABB::~TNodoABB() {
	//No hay que hacer nada, no hay punteros en la clase.
}

TNodoABB & TNodoABB::operator=(const TNodoABB &nodo) {
	if (this != &nodo) {
		this->~TNodoABB();

		this->item = nodo.item;
		this->de = nodo.de;
		this->iz = nodo.iz;
	}

	return *this;
}

///////////
//TABBCOM//
///////////

TABBCom::TABBCom() {
	this->nodo = NULL;
}

TABBCom::TABBCom(const TABBCom &origen) {
	Copiar(origen);
}

TABBCom::~TABBCom() {
	while (!this->EsVacio()) {
		TNodoABB *aux = new TNodoABB();
		aux = this->nodo;

		this->nodo->iz.~TABBCom();
		this->nodo->de.~TABBCom();

		delete this->nodo;
		this->nodo = NULL;


	}
}

TABBCom & TABBCom::operator=(const TABBCom &origen) {
	if (this != &origen) {
		this->~TABBCom();
		this->Copiar(origen);
	}

	return *this;
}

void TABBCom::Copiar(const TABBCom &origen) {
	if (!origen.EsVacio()) {
		this->nodo = new TNodoABB();
		this->nodo->item = origen.nodo->item;
		this->nodo->iz.Copiar(origen.nodo->iz);
		this->nodo->de.Copiar(origen.nodo->de);
	} else
		this->nodo = NULL;
}

bool TABBCom::operator==(const TABBCom &arbol) const {
	if (this->Inorden() == arbol.Inorden())
		return true;
	else
		return false;
}

bool TABBCom::EsVacio() const {
	if (this->nodo)
		return false;
	else
		return true;
}

bool TABBCom::Buscar(const TComplejo &complejo) const {
	if (!EsVacio()) {
		if (this->nodo->item == complejo)
			return true;
		else {
			if (this->nodo->iz.Buscar(complejo)
					|| this->nodo->de.Buscar(complejo))
				return true;
			else
				return false;
		}
	}

	return false;
}

bool TABBCom::Insertar(const TComplejo &complejo) {
	bool insertado = false;

	if(this->EsVacio()){
		TNodoABB *aux = new TNodoABB();
		aux->item = complejo;
		this->nodo = aux;

		insertado = true;
	}
	else{
		if(!this->Buscar(complejo)){
			if(this->mayor(complejo))
				insertado = this->nodo->de.Insertar(complejo);
			else
				insertado = this->nodo->iz.Insertar(complejo);
		}
	}

	return insertado;
}

bool TABBCom::mayor(TComplejo complejo) const {
	bool may = false;

	if (complejo.Mod() == this->nodo->item.Mod()) {
		if (complejo.Re() == this->nodo->item.Re()) {
			if (complejo.Im() == this->nodo->item.Im()) //si mod, re e im son iguales -> false
				may = false;
			else {
				if (complejo.Im() < this->nodo->item.Im())
					may = false;
				if (complejo.Im() > this->nodo->item.Im())
					may = true;;
			}
		} else {
			if (complejo.Re() < this->nodo->item.Re())
				may = false;
			if (complejo.Re() > this->nodo->item.Re())
				may = true;
		}
	} else {
		if (complejo.Mod() < this->nodo->item.Mod())
			may = false;
		if (complejo.Mod() > this->nodo->item.Mod())
			may = true;
	}

	return may;
}

bool TABBCom::Borrar(const TComplejo &complejo) {
	bool borrado = false;

	if (this->Buscar(complejo)) {
		if (this->nodo->item == complejo) {
			if (this->esHoja()) {
				delete nodo;
				nodo = NULL;

				borrado = true;
			} else {
				if (this->nodo->iz.EsVacio() || this->nodo->de.EsVacio()) {
					if (this->nodo->iz.EsVacio()) { //Sin subarbol izq
						TNodoABB *aux;

						aux = nodo;
						nodo = nodo->de.nodo;
						aux->de.nodo = NULL;
						delete aux;
						aux = NULL;

						borrado = true;
					} else { //Sin subarbol der
						TNodoABB *aux;

						aux = nodo;
						nodo = nodo->iz.nodo;
						aux->iz.nodo = NULL;
						delete aux;
						aux = NULL;

						borrado = true;
					}
				} else { //Cuando tiene dos subarboles hijo.
					this->Sustituir();

					borrado = true;
				}
			}

			borrado = true;
		} else {
			if (this->mayor(complejo))
				borrado = this->nodo->de.Borrar(complejo);
			else
				borrado = this->nodo->iz.Borrar(complejo);
		}
	}

	return borrado;
}

void TABBCom::Sustituir() {
	TNodoABB *anterior, *posterior, *actual;

	actual = this->nodo;
	posterior = this->nodo->iz.nodo; //Tenemos que sustituir por algun nodo del subarbol iz
	anterior = this->nodo;

	if (posterior->de.EsVacio()) { //No hay subarbol der por lo tanto este es el mayor.
		actual->item = posterior->item;
		actual->iz.nodo = posterior->iz.nodo;
	} else { //Buscamos iterativamente el mayor de la ezquierda (estara en una hoja lo mas a la derecha posible).
		while (!posterior->de.EsVacio()) {
			anterior = posterior;
			posterior = posterior->de.nodo;
		}

		anterior->de.nodo = posterior->iz.nodo;
		actual->item = posterior->item;
	}
}

bool TABBCom::esHoja() const {
	if (this->nodo->de.EsVacio() && this->nodo->iz.EsVacio())
		return true;
	else
		return false;
}

TComplejo TABBCom::Raiz() const {
	if (this->EsVacio())
		return TComplejo();
	else
		return nodo->item;
}

int TABBCom::Altura() const {
	if (!EsVacio()) {
		return 1 + max(nodo->de.Altura(), nodo->iz.Altura());
	} else
		return 0;
}

int TABBCom::Nodos() const {
	if (!EsVacio()) {
		return 1 + nodo->de.Nodos() + nodo->iz.Nodos();
	} else
		return 0;
}

int TABBCom::NodosHoja() const {
	if (!EsVacio()) {
		if (!nodo->iz.EsVacio() || !nodo->de.EsVacio()) {
			return nodo->iz.NodosHoja() + nodo->de.NodosHoja();
		} else
			return 1;
	} else
		return 0;
}

TVectorCom TABBCom::Inorden() const {
	int posicion = 1;
	TVectorCom v(this->Nodos());
	this->InordenAux(v, posicion);

	return v;
}

TVectorCom TABBCom::Preorden() const {
	int posicion = 1;
	TVectorCom v(this->Nodos());
	this->PreordenAux(v, posicion);

	return v;
}

TVectorCom TABBCom::Postorden() const {
	int posicion = 1;
	TVectorCom v(this->Nodos());
	this->PostordenAux(v, posicion);

	return v;
}

TVectorCom TABBCom::Niveles() const {
	TVectorCom v(this->Nodos());
	int posicion = 1;

	NivAux(v, posicion);

	return v;
}

void TABBCom::NivAux(TVectorCom &v, int &pos) const {
	if(!this->EsVacio()){
		std::queue<TNodoABB*> mycola;
		TNodoABB *aux = this->nodo;
		mycola.push(aux);

		while(!mycola.empty()){
			TNodoABB *temp = mycola.front();
			v[pos] = (*temp).item;
			pos++;

			mycola.pop();

			if(!(*temp).iz.EsVacio()){
				mycola.push((*temp).iz.nodo);
			}
			if(!(*temp).de.EsVacio()){
				mycola.push((*temp).de.nodo);
			}
		}
	}
}

void TABBCom::InordenAux(TVectorCom &v, int &x) const {
	if (!this->EsVacio()) {
		if (this->esHoja()){//Es un nodo hoja
			//Lo añado al vector y acabo recur
			v[x] = this->nodo->item;
			x++;
		} else {
			this->nodo->iz.InordenAux(v, x);
			v[x] = this->nodo->item;
			x++;
			this->nodo->de.InordenAux(v, x);
		}
	}
}

void TABBCom::PreordenAux(TVectorCom &v, int &x) const {
	if (!this->EsVacio()) {
		if (this->esHoja()) {			//Es un nodo hoja
			//Lo añado al vector y acabo recur
			v[x] = this->nodo->item;
			x++;
		} else {
			v[x] = this->nodo->item;
			x++;
			this->nodo->iz.PreordenAux(v, x);
			this->nodo->de.PreordenAux(v, x);
		}
	}
}

void TABBCom::PostordenAux(TVectorCom &v, int &x) const {
	if (!this->EsVacio()) {
		if (this->esHoja()) {				//Es un nodo hoja
			//Lo añado al vector y acabo recur
			v[x] = this->nodo->item;
			x++;
		} else {
			this->nodo->iz.PostordenAux(v, x);
			this->nodo->de.PostordenAux(v, x);
			v[x] = this->nodo->item;
			x++;
		}
	}
}

ostream & operator<<(ostream &salida, const TABBCom &arbol){
	salida << arbol.Niveles();

	return salida;
}
