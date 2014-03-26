#ifndef _TCOMPLEJO_
#define _TCOMPLEJO_

#include <iostream>
#include <cmath>

using namespace std;

class TComplejo {
	friend TComplejo operator+(double, const TComplejo &);
	friend TComplejo operator-(double, const TComplejo &);
	friend TComplejo operator*(double, const TComplejo &);
	friend ostream & operator<<(ostream &, const TComplejo &);

public:
	TComplejo();
	TComplejo(double);
	TComplejo(double, double);
	TComplejo(const TComplejo &);
	~TComplejo();
	TComplejo & operator=(const TComplejo &);

	TComplejo operator+(const TComplejo &) const;
	TComplejo operator-(const TComplejo &) const;
	TComplejo operator*(const TComplejo &) const;
	TComplejo operator+(double) const;
	TComplejo operator-(double) const;
	TComplejo operator*(double) const;

	bool operator==(const TComplejo &) const;
	bool operator!=(const TComplejo &) const;
	double Re() const;
	double Im() const;
	void Re(double);
	void Im(double);
	double Arg() const;
	double Mod() const;
	bool esVacio() const;
	void Vaciar();

private:
	double re;
	double im;
};

#endif
