/*
 * tavlcom.cpp
 *
 *  Created on: 06/05/2014
 *      Author: jorge
 */

#include "tavlcom.h"

////////////
//TNODOAVL//
////////////

TNodoAVL::TNodoAVL() {
	fe = 0;
}

void TNodoAVL::copiarNodo(const TNodoAVL &nodo) {
	this->item = nodo.item;
	this->iz = nodo.iz;
	this->de = nodo.de;
	this->fe = nodo.fe;
}

TNodoAVL::TNodoAVL(const TNodoAVL &nodo) {
	copiarNodo(nodo);
}

TNodoAVL::~TNodoAVL() {
	fe = 0;
}

TNodoAVL & TNodoAVL::operator=(const TNodoAVL &nodo) {
	if (this != &nodo) {
		this->~TNodoAVL();

		copiarNodo(nodo);
	}

	return *this;
}

///////////
//TAVLCOM//
///////////

TAVLCom::TAVLCom() {
	this->raiz = NULL;
}

void TAVLCom::copiarArbol(const TAVLCom &arbol) {
	if (!arbol.EsVacio()) {
		this->raiz = new TNodoAVL();
		this->raiz->item = arbol.raiz->item;
		this->raiz->iz.copiarArbol(arbol.raiz->iz);
		this->raiz->de.copiarArbol(arbol.raiz->de);
	} else
		this->raiz = NULL;
}

TAVLCom::TAVLCom(const TAVLCom &arbol) {
	this->copiarArbol(arbol);
}

TAVLCom::~TAVLCom() {
	while (!this->EsVacio()) {
		TNodoAVL *aux = new TNodoAVL();
		aux = this->raiz;

		this->raiz->iz.~TAVLCom();
		this->raiz->de.~TAVLCom();

		delete this->raiz;
		this->raiz = NULL;
	}
}

TAVLCom & TAVLCom::operator=(const TAVLCom &arbol) {
	if(this != &arbol){
		this->~TAVLCom();

		this->copiarArbol(arbol);
	}

	return *this;
}

bool TAVLCom::operator==(const TAVLCom &arbol) const {
	if(this->Inorden() == arbol.Inorden())
		return true;
	else
		return false;
}

bool TAVLCom::operator!=(const TAVLCom &arbol) const {
	return !this->operator ==(arbol);
}

bool TAVLCom::EsVacio() const {
	if(this->raiz)
		return false;
	else
		return true;
}

bool TAVLCom::Insertar(const TComplejo &) {

}

bool TAVLCom::Buscar(const TComplejo &) const {

}

bool TAVLCom::Borrar(const TComplejo &) {

}

int TAVLCom::Altura() const {

}

int TAVLCom::Nodos() const {

}

int TAVLCom::NodosHoja() const {

}

TVectorCom TAVLCom::Inorden() const {
	int pos = 1;
	TVectorCom v(this->Nodos());

	this->InordenAux(v, pos);

	return v;
}

TVectorCom TAVLCom::Preorden() const {
	int pos = 1;
	TVectorCom v(this->Nodos());

	this->PreordenAux(v, pos);

	return v;
}

TVectorCom TAVLCom::Postorden() const {
	int pos = 1;
	TVectorCom v(this->Nodos());

	this->PostordenAux(v, pos);

	return v;
}

TComplejo TAVLCom::Raiz() const {
	if(this->EsVacio())
		return TComplejo();
	else
		return this->raiz->item;
}

void TAVLCom::InordenAux(TVectorCom &, int &) const{

}

void TAVLCom::PreordenAux(TVectorCom &, int &) const{

}

void TAVLCom::PostordenAux(TVectorCom &, int &) const{

}

ostream & operator<<(ostream &salida, TAVLCom &arbol) {
	salida << arbol.Inorden();

	return salida;
}
