//
//  tlistacom.cpp
//  
//
//  Created by Jorge Amat Soler on 05/03/14.
//
//

#include "tlistacom.h"

//////////////////////////////////////////////////
////////////////////TLISTANODO////////////////////
//////////////////////////////////////////////////

TListaNodo::TListaNodo():e()
{
    anterior = NULL;
    siguiente = NULL;
}
    
TListaNodo::TListaNodo(const TListaNodo &nodo):e(nodo.e)
{
    anterior = nodo.anterior;
    siguiente = nodo.siguiente;
}
    
TListaNodo::~TListaNodo()
{
    siguiente = NULL;
    anterior = NULL;
}

TListaNodo & TListaNodo::operator=(const TListaNodo &nodo)
{
	if(this != &nodo){
		this->~TListaNodo();

		e = nodo.e;
		anterior = nodo.anterior;
		siguiente = nodo.siguiente;
	}

	return *this;
}

/////////////////////////////////////////////////
////////////////////TLISTAPOS////////////////////
/////////////////////////////////////////////////

TListaPos::TListaPos()
{
    pos = NULL;
}

TListaPos::TListaPos(const TListaPos &pos)
{
    this->pos = pos.pos;
}

TListaPos::~TListaPos()
{
    pos = NULL;
}

TListaPos & TListaPos::operator=(const TListaPos &pos)
{
    if(this != &pos)
        this->pos = pos.pos;

    return *this;
}

bool TListaPos::operator==(const TListaPos &pos) const
{
    if(this->pos == pos.pos)
        return true;
    else
        return false;
}

bool TListaPos::operator!=(const TListaPos &pos) const
{
    if(this->pos == pos.pos)
        return false;
    else
        return true;
}

TListaPos TListaPos::Anterior() const
{
    if(this->EsVacia() || pos->anterior == NULL)
    	return TListaPos();
	else {
		TListaPos aux;

		aux.pos = this->pos->anterior;

		return aux;
	}
}

TListaPos TListaPos::Siguiente() const
{
    if(this->EsVacia() || pos->siguiente == NULL)
    	return TListaPos();
	else {
		TListaPos aux;

		aux.pos = this->pos->siguiente;

		return aux;
	}
}

bool TListaPos::EsVacia() const
{
    if(pos == NULL)
        return true;
    else
        return false;
}

/////////////////////////////////////////////////
////////////////////TLISTACOM////////////////////
/////////////////////////////////////////////////

TListaCom::TListaCom()
{
    primero = NULL;
    ultimo = NULL;
}

TListaCom::TListaCom(const TListaCom &lista)
{
	primero = ultimo = NULL;
	TListaPos pos = lista.Ultima();

	while(!pos.EsVacia()){
		this->InsCabeza(pos.pos->e);
		pos = pos.Anterior();
	}
}

TListaCom::~TListaCom()
{
	TListaPos borrar = this->Primera();
	TListaPos aux = borrar.Siguiente();

	do{
		delete borrar.pos;
		borrar = aux;
		aux = borrar.Siguiente();
	}while(!aux.EsVacia());

	this->primero = NULL;
	this->ultimo = NULL;
}

TListaCom & TListaCom::operator=(const TListaCom &lista)
{
		if(this != &lista){
			this->~TListaCom();

			primero = ultimo = NULL;
			TListaPos pos = lista.Ultima();

			while(!pos.EsVacia()){
				this->InsCabeza(pos.pos->e);
				pos = pos.Anterior();
			}
		}

		return *this;
}

bool TListaCom::operator==(const TListaCom &lista) const
{
    bool iguales = true;

    TListaPos mipos = this->Primera();
    TListaPos lpos = lista.Primera();

    if(this->Longitud() == lista.Longitud()){
    	do{
    		if(!mipos.EsVacia() && !lpos.EsVacia()){
    			if(mipos.pos->e != lpos.pos->e)
    				iguales = false;
    		}

    		mipos = mipos.Siguiente();
    		lpos = lpos.Siguiente();
    	}while(!mipos.EsVacia());
    }
    else{
    	iguales = false;
    }
    
    return iguales;
}

bool TListaCom::operator!=(const TListaCom &lista) const
{
    return !this->operator==(lista);
}

TListaCom TListaCom::operator+(const TListaCom &lista) const
{
    TListaCom res(lista);
    TListaPos pos = this->Ultima();

    if(!pos.EsVacia()){
    	res.InsCabeza(pos.pos->e);
    }

    while(!pos.Anterior().EsVacia()){
    	pos = pos.Anterior();
    	res.InsCabeza(pos.pos->e);
    }
    
    return res;
}

TListaCom TListaCom::operator-(const TListaCom &lista) const {
	TListaCom res;
	TListaPos pos = this->Ultima();

	if (lista.EsVacia()) {
		res = *this;
	} else {
		if (!pos.EsVacia()) {
			if (!lista.Buscar(pos.pos->e)) {
				res.InsCabeza(pos.pos->e);
			}
		}

		while (!pos.Anterior().EsVacia()) {
			pos = pos.Anterior();

			if (!lista.Buscar(pos.pos->e)) {
				res.InsCabeza(pos.pos->e);
			}
		}
	}

	return res;
}

bool TListaCom::EsVacia() const
{
    if(this->primero == NULL || this->ultimo == NULL)
    	return true;
    return false;
}

bool TListaCom::InsCabeza(const TComplejo &complejo)
{
    TListaNodo *nuevo = new TListaNodo();
    
    if(nuevo){
    	nuevo->e = complejo;

        if(this->EsVacia()){//La lista esta vacia.
           	nuevo->anterior = NULL;
       	   	nuevo->siguiente = NULL;
       	   	this->ultimo = nuevo;
       	   	this->primero = nuevo;

       	    return true;
        }
        else{//La lista contiene nodos.
            TListaPos aux = this->Primera();

        	nuevo->anterior = NULL;
        	nuevo->siguiente = aux.pos;
        	aux.pos->anterior = nuevo;
        	this->primero = nuevo;

        	return true;
        }
    }
    else
    	return false;
}

bool TListaCom::InsertarI(const TComplejo &complejo, const TListaPos &posicion)
{
	if(!posicion.EsVacia()){
		if(this->Longitud() == 1){//La lista tiene un elemento
			this->InsCabeza(complejo);

			return true;
		}
		else{//La lista contiene mas de un elemento.
			if(posicion == this->Primera()){
				this->InsCabeza(complejo);

				return true;
			}
			else{
				TListaPos aux = posicion.Anterior();
				TListaNodo *nodo = new TListaNodo();
				nodo->e = complejo;

				nodo->anterior = aux.pos;
				nodo->siguiente = posicion.pos;
				aux.pos->siguiente = nodo;
				posicion.pos->anterior = nodo;

				return true;
			}
		}
	}
	else{
		if(this->EsVacia()){
			this->InsCabeza(complejo);

			return true;
		}
	}

	return false;
}

bool TListaCom::InsertarD(const TComplejo &complejo, const TListaPos &posicion)
{
	if(!posicion.EsVacia()){
		if(this->Longitud() == 1 || posicion == this->Ultima()){//La lista solo tiene un elemento.
			TListaNodo *nodo = new TListaNodo();
			nodo->e = complejo;

			nodo->anterior = posicion.pos;
			nodo->siguiente = NULL;
			this->ultimo = nodo;
			posicion.pos->siguiente = nodo;

			return true;
		}
		else{//Lista con mas de un elemento.
			TListaPos aux = posicion.Siguiente();
			TListaNodo *nodo = new TListaNodo();
			nodo->e = complejo;

			nodo->anterior = posicion.pos;
			nodo->siguiente = aux.pos;
			posicion.pos->siguiente = nodo;
			aux.pos->anterior = nodo;

			return true;
		}
	}
	else{
		if(this->EsVacia()){
			this->InsCabeza(complejo);

			return true;
		}
	}

	return false;
}

bool TListaCom::Borrar(const TComplejo &complejo)
{
	if(!this->EsVacia() && this->Buscar(complejo)) {
		TListaPos aux = this->Primera();

		if(aux.pos->e == complejo){//Complejo en primera posicion.
			if(this->Longitud() == 1){//Lista de un elemento
				this->~TListaCom();

				return true;
			}
			else{//Lista con mas de 1 elemento.
				TListaPos pos = aux.Siguiente();
				aux.pos->~TListaNodo();
				this->primero = pos.pos;
				pos.pos->anterior = NULL;

				return true;
			}
		}

		while (!aux.Siguiente().EsVacia()) {
			aux.pos = aux.pos->siguiente;

			if(aux == this->Ultima() && aux.pos->e == complejo){//Si hemos llegado al ultimo nodo...
				TListaPos pos = aux.Anterior();
				aux.pos->~TListaNodo();
				pos.pos->siguiente = NULL;
				this->ultimo = pos.pos;

				return true;
			}
			else{
				if(aux.pos->e == complejo){
					TListaPos pre = aux.Anterior(), post = aux.Siguiente();
					aux.pos->~TListaNodo();
					pre.pos->siguiente = post.pos;
					post.pos->anterior = pre.pos;

					return true;
				}
			}
		}
	}
    
    return false;
}

bool TListaCom::BorrarTodos(const TComplejo &complejo)
{
    if(!this->EsVacia() && this->Buscar(complejo)){

    	do{
    		this->Borrar(complejo);
    	}while(this->Buscar(complejo));

    	return true;
    }
    
    return false;
}

bool TListaCom::Borrar(const TListaPos &pos)
{
    if(!this->EsVacia() && !pos.EsVacia()){
    	if(this->Buscar(pos.pos->e)){
    		this->Borrar(pos.pos->e);
    		pos.~TListaPos();

    		return true;
    	}

    	return false;
    }
    
    return false;
}

TComplejo TListaCom::Obtener(const TListaPos &posicion) const
{
    TListaPos aux = this->Primera();
    bool encontrado = false;

	if (!this->EsVacia() && !posicion.EsVacia()) {
		while (!aux.EsVacia() && encontrado == false) {
			if (aux == posicion) {
				encontrado = true;
				return aux.pos->e;
			}

			aux = aux.Siguiente();
		}
	}

	return TComplejo();
}

bool TListaCom::Buscar(const TComplejo &complejo) const
{
    bool encontrado = false;
    TListaPos pos = this->Primera();

	if (pos.pos->e == complejo)
		encontrado = true;

    while(!pos.Siguiente().EsVacia() && encontrado == false){
    	pos = pos.Siguiente();

    	if(pos.pos->e == complejo)
    		encontrado = true;
    }
    
    return encontrado;
}

int TListaCom::Longitud() const
{
    int tam = 0;
    TListaPos aux = this->Primera();

    if(aux.pos)
    	tam++;

    while(!aux.Siguiente().EsVacia()){
    	tam++;
    	aux.pos = aux.pos->siguiente;
    }
    
    return tam;
}

TListaPos TListaCom::Primera() const
{
	TListaPos aux;

	if(this->EsVacia())
		return TListaPos();
	else{
		aux.pos = this->primero;
		return aux;
	}
}

TListaPos TListaCom::Ultima() const
{
    TListaPos aux;
    
    if(this->EsVacia())
    	return aux;
    else{
    	aux.pos = this->ultimo;
    	return aux;
    }
}

ostream & operator<<(ostream &salida, const TListaCom &lista)
{
    salida << "{";

    if(lista.EsVacia()) //Lista vacia.
    	salida << "}";
    else{
    	TListaPos pos = lista.Primera();

    	if(pos.Siguiente().EsVacia())//Solo un elemento;
    		salida << lista.Obtener(pos) << "}";
    	else{//Mas de un elemento.
    		salida << lista.Obtener(pos);
    		salida << " ";

    		while(!pos.Siguiente().EsVacia() && pos.Siguiente() != lista.Ultima()){
    			pos = pos.Siguiente();
    			salida << lista.Obtener(pos) << " ";
    		}

    		pos = pos.Siguiente();
    		salida << lista.Obtener(pos);
    		salida << "}";
    	}
    }
    
    return salida;
}
