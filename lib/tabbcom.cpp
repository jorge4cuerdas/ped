/*
 * tabbcom.cpp
 *
 *  Created on: 25/03/2014
 *      Author: jorge
 */

TNodoABB::TNodoABB() {
}
;

TNodoABB::TNodoABB(TNodoABB &nodo) {

}

TNodoABB::~TNodoABB() {

}

TNodoABB & TNodoABB::operator=(TNodoABB &nodo) {
	if(this != &nodo){
		this->~TNodoABB();

		this->item = nodo.item;
		this->de = nodo.de;
		this->iz = nodo.iz;
	}
}

TABBCom::TABBCom();
TABBCom::TABBCom(TABBCom &);
TABBCom::~TABBCom();
TABBCom & TABBCom::operator=(TABBCom &);

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
