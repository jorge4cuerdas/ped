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

TNodoABB::TNodoABB()
{
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
	if(this != &nodo){
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

TABBCom::TABBCom(){
    this->nodo = NULL;
}

TABBCom::TABBCom(const TABBCom &origen){
    Copiar(origen);
}

TABBCom::~TABBCom(){
    /*if(nodo != NULL){
    	delete nodo;
    	nodo == NULL;
    }
    */

	while(!this->EsVacio()){
		TNodoABB *aux = new TNodoABB();

		aux = this->nodo;

		delete this->nodo;
		this->nodo = NULL;

		aux->de.~TABBCom();
		aux->iz.~TABBCom();
	}
}

TABBCom & TABBCom::operator=(const TABBCom &origen){
    if(this != &origen){
    	this->~TABBCom();
    	Copiar(origen);
    }
    
    return * this;
}

void TABBCom::Copiar(const TABBCom &origen){
    if(!origen.EsVacio()){
    	TNodoABB *nodo = new TNodoABB();
    	nodo->item = origen.nodo->item;
    	this->nodo = nodo;
    	(this->nodo->iz).Copiar(origen.nodo->iz);
    	(this->nodo->de).Copiar(origen.nodo->de);
    }
    else
    	this->nodo = NULL;
}

bool TABBCom::operator==(const TABBCom &arbol) const{
	if(this->Inorden() == arbol.Inorden())
		return true;
	else
		return false;
}

bool TABBCom::EsVacio() const{
	if(nodo)
		return false;
	else
		return true;
}

bool TABBCom::Insertar(const TComplejo &complejo){
	bool insertado = false;

	if(!this->EsVacio() && !this->Buscar(complejo)){
		if(this->nodo->de.EsVacio() && this->nodo->iz.EsVacio()){
			TNodoABB *aux = new TNodoABB();
			aux->item = complejo;

			if(complejo.Re() > this->nodo->item.Re())
				this->nodo->de.nodo = aux;
			else
				this->nodo->iz.nodo = aux;

			insertado = true;
		}
		else{
			if(complejo.Re() > this->nodo->item.Re())
				this->nodo->de.Insertar(complejo);
			else
				this->nodo->iz.Insertar(complejo);
		}
	}

	return insertado;
}

bool TABBCom::Borrar(const TComplejo &complejo){
	bool borrado = false;

	if(this->Buscar(complejo)){
		if(this->nodo->item == complejo){
			if(this->esHoja()){
				delete nodo;
				nodo = NULL;

				borrado = true;
			}
			else{
				if(this->nodo->iz.EsVacio() || this->nodo->de.EsVacio()){
					if(this->nodo->iz.EsVacio()){//Sin subarbol izq
						TNodoABB *aux;

						aux = nodo;
						nodo = nodo->de.nodo;
						aux->de.nodo = NULL;
						delete aux;
						aux = NULL;

						borrado = true;
					}
					else{//Sin subarbol der
						TNodoABB *aux;

						aux = nodo;
						nodo = nodo->iz.nodo;
						aux->iz.nodo = NULL;
						delete aux;
						aux = NULL;

						borrado = true;
					}
				}
				else{//Cuando tiene dos subarboles hijo.
					this->Sustituir();

					borrado = true;
				}
			}

			borrado = true;
		}
		else{
			if(complejo.Re() > this->nodo->item.Re())
				this->nodo->de.Borrar(complejo);
			else
				this->nodo->iz.Borrar(complejo);
		}
	}

	return borrado;
}

void TABBCom::Sustituir(){
	TNodoABB *anterior, *posterior, *actual;

	actual = this->nodo;
	posterior = this->nodo->iz.nodo; //Tenemos que sustituir por algun nodo del subarbol iz
	anterior = this->nodo;

	if(posterior->de.EsVacio()){//No hay subarbol der por lo tanto este es el mayor.
		actual->item = posterior->item;
		actual->iz.nodo = posterior->iz.nodo;
	}
	else{//Buscamos iterativamente el mayor de la ezquierda (estara en una hoja lo mas a la derecha posible).
		while(!posterior->de.EsVacio()){
			anterior = posterior;
			posterior = posterior->de.nodo;
		}

		anterior->de.nodo = posterior->iz.nodo;
		actual->item = posterior->item;
	}
}

bool TABBCom::esHoja() const {
	if(this->nodo->de.EsVacio() && this->nodo->iz.EsVacio())
		return true;
	else return false;
}

bool TABBCom::Buscar(const TComplejo &complejo)const{
	if(!EsVacio()){
		if(this->nodo->item == complejo)
			return true;
		else{
			if(this->nodo->iz.Buscar(complejo) ||
					this->nodo->de.Buscar(complejo))
				return true;
			else
				return false;
		}
	}

	return false;
}

TComplejo TABBCom::Raiz() const{
	if(this->EsVacio())
		return TComplejo();
	else
		return nodo->item;
}

int TABBCom::Altura() const{
	if(!EsVacio()){
		return 1 + max(nodo->de.Altura(), nodo->iz.Altura());
	}
	else
		return 0;
}

int TABBCom::Nodos() const{
	if(!EsVacio()){
		return 1 + nodo->de.Nodos() + nodo->iz.Nodos();
	}
	else return 0;
}

int TABBCom::NodosHoja() const{
	if(!EsVacio()){
		if(!nodo->iz.EsVacio() || !nodo->de.EsVacio()){
			return nodo->iz.NodosHoja() + nodo->de.NodosHoja();
		}
		else
			return 1;
	}
	else
		return 0;
}

TVectorCom TABBCom::Inorden() const{
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

TVectorCom TABBCom::Niveles() const{
	TVectorCom v(this->Nodos());
	int posicion = 1;

	NivAux(v, posicion);

	return v;
}

void TABBCom::NivAux(TVectorCom &v, int &pos) const{
	while(!this->EsVacio()){
		v[pos] = this->nodo->item;
		pos++;
		this->nodo->iz.NivAux(v, pos);
		this->nodo->de.NivAux(v, pos);
	}
}

void TABBCom::InordenAux(TVectorCom &v, int &x) const{

}

void TABBCom::PreordenAux(TVectorCom &v, int &x) const{

}

void TABBCom::PostordenAux(TVectorCom &v, int &x) const{

}
