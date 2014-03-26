//
//  tlistacom.h
//  
//
//  Created by Jorge Amat Soler on 05/03/14.
//
//

#ifndef ____tlistacom__
#define ____tlistacom__

#include <iostream>

#include "tcomplejo.h"

class TListaNodo {
	friend class TListaPos;
	friend class TListaCom;

public:
	TListaNodo();
	TListaNodo(const TListaNodo &);
	~TListaNodo();
	TListaNodo & operator=(const TListaNodo &);

private:
	TComplejo e;
	TListaNodo *anterior;
	TListaNodo *siguiente;

};

class TListaPos {
	friend class TListaCom;
	friend class TListaNodo;

public:
	TListaPos();
	TListaPos(const TListaPos &);
	~TListaPos();
	TListaPos & operator=(const TListaPos &);

	bool operator==(const TListaPos &) const;
	bool operator!=(const TListaPos &) const;
	TListaPos Anterior() const;
	TListaPos Siguiente() const;
	bool EsVacia() const;

private:
	TListaNodo *pos;
};

class TListaCom {
	friend class TListaNodo;
	friend class TListaPos;

	friend ostream & operator<<(ostream &, const TListaCom &);

public:
	TListaCom();
	TListaCom(const TListaCom &);
	~TListaCom();
	TListaCom & operator=(const TListaCom &);

	bool operator==(const TListaCom &) const;
	bool operator!=(const TListaCom &) const;
	TListaCom operator+(const TListaCom &) const;
	TListaCom operator-(const TListaCom &) const;
	bool EsVacia() const;
	bool InsCabeza(const TComplejo &);
	bool InsertarI(const TComplejo &, const TListaPos &);
	bool InsertarD(const TComplejo &, const TListaPos &);
	bool Borrar(const TComplejo &);
	bool BorrarTodos(const TComplejo &);
	bool Borrar(const TListaPos &);
	TComplejo Obtener(const TListaPos &) const;
	bool Buscar(const TComplejo &) const;
	int Longitud() const;
	TListaPos Primera() const;
	TListaPos Ultima() const;

private:
	TListaNodo *primero;
	TListaNodo *ultimo;
};

#endif /* defined(____tlistacom__) */
