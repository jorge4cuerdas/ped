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

TABBCom::TABBCom(const TABBCom &){
    
}

TABBCom::~TABBCom(){
    
}

TABBCom & TABBCom::operator=(TABBCom &){
    
}

void TABBCom::Copiar(const TABBCom){
    
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
