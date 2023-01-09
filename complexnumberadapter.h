#ifndef COMPLEXNUMBERADAPTER_H
#define COMPLEXNUMBERADAPTER_H
#include <complex>
#include <string>

#define UNDEFINED_COMPLEX_NUMBER (FLT_MAX, FLT_MAX)
#define NULL_COMPLEX_NUMBER (0.f, 0.f)

class ComplexNumberAdapter : public std::complex <float>
{
public:
    ComplexNumberAdapter();
    ComplexNumberAdapter(std::complex <float>);
    ComplexNumberAdapter(float r, float i);
    ComplexNumberAdapter toGeneralForm();   //returns pair of real and imaginary values
    ComplexNumberAdapter toExponentialForm();   //returns pair of coefficient and exponent power values

                                                                                                  //TODO: add multiplexion and division for exp form

    friend ComplexNumberAdapter multExp(ComplexNumberAdapter c1, const ComplexNumberAdapter& c2);   //operations methods for exponential form
    friend ComplexNumberAdapter divideExp(ComplexNumberAdapter c1, const ComplexNumberAdapter& c2);
    bool getForm();
    void setForm(bool f);
private:
    static bool isDigit(const char& c);
    bool m_Form;        //0 - gen, 1 -exp
};

#endif // COMPLEXNUMBERADAPTER_H
