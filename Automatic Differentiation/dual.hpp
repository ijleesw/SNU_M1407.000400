#ifndef DUAL_HPP_
#define DUAL_HPP_

#include <iostream>
#include <math.h>
using namespace std;


/*****************************************************
 *
 *  Macro(s) and (commented out) function prototypes
 *
 *****************************************************/

#define X(x) dual<ring>(x)
/*
[+, -, *, /] are all overloaded
dual<ring> exp(dual<ring>& x);
dual<ring> log(dual<ring>& x);
dual<ring> pow(dual<ring>& x, dual<ring>& y);
dual<ring> sin(dual<ring>& x);
dual<ring> cos(dual<ring>& x);
dual<ring> sqrt(dual<ring>& x);
*/


/*****************************************************
 *
 *  dual number for auto-differentiation
 *
 *****************************************************/

template <typename ring>
class dual
{
public:
	ring val;
	ring deriv;

	dual() {}
	dual(ring a) : val(a), deriv(1) {}
	dual(ring a, ring b) : val(a), deriv(b) {}
	~dual() {}

	dual operator+(dual& ref);
	dual operator+(ring& ref);
	dual operator-(dual& ref);
	dual operator-(ring& ref);
	dual operator*(dual& ref);
	dual operator*(ring& ref);
	dual operator/(dual& ref);
	dual operator/(ring& ref);

	dual& operator=(ring& ref);

	template <typename T>
	friend ostream& operator<<(ostream&, const dual<T>&);
};


/*****************************************************
 *
 *  Operator definitions
 *
 *****************************************************/

template <typename ring>
dual<ring> dual<ring>::operator+(dual<ring>& ref)
{
	return dual<ring>(val+ref.val, deriv+ref.deriv);
}

template <typename ring>
dual<ring> dual<ring>::operator+(ring& ref)
{
	return dual<ring>(val+ref, deriv);
}


template <typename ring>
dual<ring> dual<ring>::operator-(dual<ring>& ref)
{
	return dual<ring>(val-ref.val, deriv-ref.deriv);
}


template <typename ring>
dual<ring> dual<ring>::operator-(ring& ref)
{
	return dual<ring>(val-ref.val, deriv);
}


template <typename ring>
dual<ring> dual<ring>::operator*(dual<ring>& ref)
{
	return dual<ring>(val*ref.val, val*ref.deriv + deriv*ref.val);
}


template <typename ring>
dual<ring> dual<ring>::operator*(ring& ref)
{
	return dual<ring>(val*ref.val, deriv*ref.val);
}


template <typename ring>
dual<ring> dual<ring>::operator/(dual<ring>& ref)
{
	if (ref.val == 0) { cout << "Division by zero error.\n"; exit(-1); }
	return dual<ring>(val/ref.val, (deriv*ref.val - val*ref.deriv) / (ref.val*ref.val));
}


template <typename ring>
dual<ring> dual<ring>::operator/(ring& ref)
{
	if (ref.val == 0) { cout << "Division by zero error.\n"; exit(-1); }
	return dual<ring>(val/ref.val, deriv.ref.val);
}


template <typename ring>
dual<ring>& dual<ring>::operator=(ring& ref)
{
	val = ref; deriv = 1;
	return *this;
}


template <typename ring>
ostream& operator<<(ostream& out, const dual<ring>& x)
{
	out << x.val << "("<<x.deriv<<")";
	return out;
}


/*****************************************************
 *
 *  Additional function definitions
 *
 *****************************************************/

template <typename ring>
dual<ring> exp(dual<ring>& x)
{
	return dual<ring>(exp(x.val), exp(x.val)*x.deriv);
}


template <typename ring>
dual<ring> log(dual<ring>& x)
{
	return dual<ring>(log(x.val), (1/x.val)*x.deriv);
}


template <typename ring>
dual<ring> pow(dual<ring>& x, dual<ring>& y)
{
	dual<ring> tmp = log(x); tmp = y * tmp;
	return exp(tmp);
}


template <typename ring>
dual<ring> sin(dual<ring>& x)
{
	return dual<ring>(sin(x.val), cos(x.val)*x.deriv);
}


template <typename ring>
dual<ring> cos(dual<ring>& x)
{
	return dual<ring>(cos(x.val), (-1)*sin(x.val)*x.deriv);
}


template <typename ring>
dual<ring> sqrt(dual<ring>& x)
{
	return dual<ring>(sqrt(x.val), (0.5/sqrt(x.val))*x.deriv);
}


#endif  /* DUAL_HPP_ */