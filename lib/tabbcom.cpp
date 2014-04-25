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
;

TNodoABB::TNodoABB(const TNodoABB &nodo) {
    item = nodo.item;
    iz = nodo.item;
    de = nodo.item;
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
}

///////////
//TABBCOM//
///////////

TABBCom::TABBCom(){
    nodo = NULL;
}

TABBCom::TABBCom(const TABBCom &origen){
    Copiar(origen);
}

TABBCom::~TABBCom(){
    if(nodo != NULL){
    	delete nodo;
    	nodo == NULL;
    }
}

TABBCom & TABBCom::operator=(const TABBCom &origen){
    this->~TABBCom();
    Copiar(origen);
    
    return * this;
}

void TABBCom::Copiar(const TABBCom &origen){
    if(origen.nodo != NULL){
    	TNodoABB *nodo = new TNodoABB();
    	nodo->item = origen.nodo->item;
    	this->nodo = nodo;
    	(nodo->iz).Copiar(origen.nodo->iz);
    	(nodo->de).Copiar(origen.nodo->de);
    }
    else
    	nodo = NULL;
}

bool TABBCom::operator==(const TABBCom &arbol) const{
	if(this->Nodos() == arbol.Nodos()){
		bool iguales = true;


	}
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

	if(!this->Buscar(complejo)){
		if(this->nodo->de.EsVacio() && this->nodo->iz.EsVacio()){
			TNodoABB *aux = new TNodoABB();
			aux->item = complejo;

			if(complejo > this->nodo->item)
				this->nodo->de.nodo = aux;
			else
				this->nodo->iz.nodo = aux;

			insertado = true;
		}
		else{
			if(complejo > this->nodo->item)
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
				//Cuando el elemento a borrar solo sea una hoja
			}
			else{
				if(this->nodo->iz.EsVacio() || this->nodo->de.EsVacio()){
					//Cuando solo tiene un subarbol hijo
				}
				else{
					//Cuando tiene dos subarboles hijo.
				}
			}

			borrado = true;
		}
		else{
			if(complejo > this->nodo->item)
				this->nodo->de.Borrar(complejo);
			else
				this->nodo->iz.Borrar(complejo);
		}
	}

	return borrado;
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
		return new TComplejo();
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

TVectorCom TABBCom::Inorden();
TVectorCom TABBCom::Preorden();
TVectorCom TABBCom::Postorden();
TVectorCom TABBCom::Niveles();
void TABBCom::InordenAux(TVectorCom &, int &);
void TABBCom::PreordenAux(TVectorCom &, int &);
void TABBCom::PostordenAux(TVectorCom &, int &);
