/*
 * tabbcom.cpp
 *
 *  Created on: 25/03/2014
 *      Author: jorge
 */

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

bool TABBCom::operator==(TABBCom &);
bool TABBCom::EsVacio();
bool TABBCom::Insertar(TComplejo &);
bool TABBCom::Borrar(TComplejo &);
bool TABBCom::Buscar(TComplejo &);
TComplejo TABBCom::Raiz();
int TABBCom::Altura();
int TABBCom::Nodos();
int TABBCom::NodosHoja();
TVectorCom TABBCom::Inorden();
TVectorCom TABBCom::Preorden();
TVectorCom TABBCom::Postorden();
TVectorCom TABBCom::Niveles();
void TABBCom::InordenAux(TVectorCom &, int &);
void TABBCom::PreordenAux(TVectorCom &, int &);
void TABBCom::PostordenAux(TVectorCom &, int &);
