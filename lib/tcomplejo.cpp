#include "tcomplejo.h"

TComplejo::TComplejo() {
	re = 0;
	im = 0;
}

TComplejo::TComplejo(double re) {
	this->re = re;
	im = 0;
}

TComplejo::TComplejo(double re, double im) {
	this->re = re;
	this->im = im;
}

TComplejo::TComplejo(const TComplejo &complejo) {
	re = complejo.re;
	im = complejo.im;
}

TComplejo::~TComplejo() {
	re = 0;
	im = 0;
}

TComplejo &TComplejo::operator=(const TComplejo &complejo) {
	if (this != &complejo) {
		this->~TComplejo();

		re = complejo.re;
		im = complejo.im;
	}

	return *this;
}

TComplejo TComplejo::operator+(const TComplejo &complejo) const {
	TComplejo aux;

	aux.re = re + complejo.re;
	aux.im = im + complejo.im;

	return aux;
}

TComplejo TComplejo::operator-(const TComplejo &complejo) const {
	TComplejo aux;

	aux.re = re - complejo.re;
	aux.im = im - complejo.im;

	return aux;
}

TComplejo TComplejo::operator*(const TComplejo &complejo) const {
	TComplejo aux;

	aux.re = (re * complejo.re) - (im * complejo.im);
	aux.im = (re * complejo.im) + (im * complejo.re);

	return aux;
}

TComplejo TComplejo::operator+(double numero) const {
	TComplejo complejo = TComplejo(numero);

	return *this + complejo;
}

TComplejo TComplejo::operator-(double numero) const {
	TComplejo complejo = TComplejo(numero);

	return *this - complejo;
}

TComplejo TComplejo::operator*(double numero) const {
	TComplejo complejo = TComplejo(numero);

	return *this * complejo;
}

TComplejo operator+(double real, const TComplejo &complejo) {
	TComplejo aux(real);

	return aux + complejo;
}

TComplejo operator-(double real, const TComplejo &complejo) {
	TComplejo aux(real);

	return aux - complejo;
}

TComplejo operator*(double real, const TComplejo &complejo) {
	TComplejo aux(real);

	return aux * complejo;
}

bool TComplejo::operator==(const TComplejo &complejo) const {
	if (this->re == complejo.re && this->im == complejo.im)
		return true;
	else
		return false;
}

bool TComplejo::operator!=(const TComplejo &complejo) const {
	return !(*this == complejo);
}

double TComplejo::Re() const {
	return re;
}

double TComplejo::Im() const {
	return im;
}

void TComplejo::Re(double real) {
	re = real;
}
void TComplejo::Im(double imaginario) {
	im = imaginario;
}

void TComplejo::Vaciar() {
	this->Re(0);
	this->Im(0);
}

double TComplejo::Arg(void) const {
	return atan2(im, re);
}

double TComplejo::Mod(void) const {
	double resultado;

	resultado = pow(Re(), 2);
	resultado += pow(Im(), 2);

	resultado = sqrt(resultado);

	return resultado;
}

bool TComplejo::esVacio() const {
	if (re == 0 && im == 0)
		return true;
	else
		return false;
}

ostream & operator<<(ostream &salida, const TComplejo &complejo) {
	salida << "(";
	salida << complejo.Re();
	salida << " ";
	salida << complejo.Im();
	salida << ")";

	return salida;
}
