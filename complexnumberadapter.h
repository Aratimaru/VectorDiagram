#ifndef COMPLEXNUMBERADAPTER_H
#define COMPLEXNUMBERADAPTER_H
#include <complex>
#include <string>

class ComplexNumberAdapter : public std::complex <float>
{
public:
    ComplexNumberAdapter();
    ComplexNumberAdapter(std::complex <float>);
    ComplexNumberAdapter toGeneralForm();   //returns pair of real and imaginary values
    ComplexNumberAdapter toExponentialForm();   //returns pair of coefficient and exponent power values
    static ComplexNumberAdapter parseNumberFromString(const std::string& s);
    static bool parseFormFromString(const std::string& s);                                        //0 - general, 1 - exp
private:
    static bool isDigit(const char& c);
};

#endif // COMPLEXNUMBERADAPTER_H
