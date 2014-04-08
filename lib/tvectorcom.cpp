#include "tvectorcom.h"

TVectorCom::TVectorCom() {
	this->c = NULL;
	tamano = 0;
}

TVectorCom::TVectorCom(int newtam) {
	if (newtam < 0) {
		this->c = NULL;
		this->tamano = 0;
	} else {
		this->tamano = newtam;
		c = new TComplejo[this->tamano];

		if (!c)
			cout << "Error" << endl;
	}
}

TVectorCom::TVectorCom(const TVectorCom &vector) {
	this->tamano = vector.tamano;
	this->c = new TComplejo[this->tamano];

	if (!c)
		cout << "Error" << endl;
	else {
		for (int i = 0; i < tamano; i++) {
			this->c[i] = vector.c[i];
		}
	}
}

TVectorCom::~TVectorCom() {
	if (c) {
		tamano = 0;
		delete[] c;
		c = NULL;
	}
}

TVectorCom & TVectorCom::operator=(const TVectorCom &vector) {
	if (this != &vector) {
		this->~TVectorCom();

		this->tamano = vector.tamano;
		this->c = new TComplejo[vector.tamano];

		if (!c)
			cout << "Error" << endl;
		else {
			for (int i = 0; i < tamano; i++) {
				c[i] = vector.c[i];
			}
		}
	}

	return *this;
}

bool TVectorCom::operator==(const TVectorCom &vector) const {
	bool iguales = true;

	if (this->tamano == vector.tamano) {
		for (int i = 0; i < this->tamano; i++) {
			if (this->c[i] != vector.c[i])
				iguales = false;
		}
	} else
		iguales = false;

	return iguales;
}

bool TVectorCom::operator!=(const TVectorCom &vector) const {
	return !(*this == vector);
}

TComplejo & TVectorCom::operator[](int pos) {
	if (pos < 1 || pos > this->tamano) {
		error.Vaciar();
		return error;
	} else {
		return this->c[pos - 1];
	}
}

TComplejo TVectorCom::operator[](int pos) const {
	TComplejo aux;

	if (pos < 1 || pos > this->tamano) {
		aux.Vaciar();
		return aux;
	} else
		return this->c[pos - 1];
}

int TVectorCom::Tamano() const {
	return tamano;
}

int TVectorCom::Ocupadas() const {
	int ocupadas = 0;

	TComplejo comp;

	for (int i = 0; i < this->tamano; i++) {
		if ((this->c[i] != comp) && !(this->c[i].esVacio()))
			ocupadas++;
	}

	return ocupadas;
}

bool TVectorCom::ExisteCom(const TComplejo &comp) const {
	bool encontrado = false;

	for (int i = 0; (i < this->tamano) && (encontrado == false); i++) {
		if (this->c[i] == comp)
			encontrado = true;
	}

	return encontrado;
}

void TVectorCom::MostrarComplejos(double valor) const {
	int cuantos = 0;

	for (int i = 0; i < this->tamano; i++) {
		if (this->c[i].Re() >= valor) {
			cuantos++;
		}
	}

	cout << "[";

	for (int i = 0; i < this->tamano; i++) {
		if (this->c[i].Re() >= valor && cuantos > 1) {
			cout << this->c[i] << ", ";
			cuantos--;
		}
		else {
			if (this->c[i].Re() >= valor) {
				cout << this->c[i];
			}
		}
	}

	cout << "]";
}

bool TVectorCom::Redimensionar(int newtam) {
	if (newtam <= 0)
		return false;
	else {
		if (newtam == this->tamano)//El nuevo tamaño es igual
			return false;
		else {
			if (newtam > 0 && newtam > this->tamano) {//Nuevo tamaño mayor al que tenemos
				TVectorCom aux(*this);
				this->~TVectorCom();
				this->tamano = newtam;
				this->c = new TComplejo[newtam];
				for (int i = 0; i < aux.tamano; i++) {
					this->c[i] = aux.c[i];
				}

				return true;

			} else {
				if (newtam > 0 && newtam < this->tamano) {//Nuevo tamaño menor al que tenemos
					TVectorCom aux(*this);
					this->~TVectorCom();
					this->tamano = newtam;
					this->c = new TComplejo[newtam];
					for (int i = 0; i < newtam; i++) {
						this->c[i] = aux.c[i];
					}
				}

				return true;
			}
		}
	}
}

ostream & operator<<(ostream &salida, const TVectorCom &vector) {
	salida << "[";

	if (vector.tamano == 0) {
		salida << "]";
	} else {
		for (int i = 0; i < vector.tamano - 1; i++) {
			salida << "(" << i + 1 << ") ";
			salida << vector.c[i];
			salida << ", ";
		}
		salida << "(" << vector.tamano << ") ";
		salida << vector.c[vector.tamano - 1];
		salida << "]";
	}

	return salida;
}
