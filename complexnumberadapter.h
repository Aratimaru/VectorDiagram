#ifndef COMPLEXNUMBERADAPTER_H
#define COMPLEXNUMBERADAPTER_H
#include <complex>
#include <string>

class ComplexNumberAdapter
{
public:
    ComplexNumberAdapter();
    std::complex<float> toGeneralForm(std::complex<float> const &exponentialExpression);   //returns pair of real and imaginary values
    std::complex<float> toExponentialForm(std::complex<float> const &generalExpression);   //returns pair of coefficient and exponent power values
    std::pair <std::complex<float>, bool> parseFromString(const std::string& s);
private:
    bool isDigit(const char& c);
    float constructNumberFromString(const std::string& s);
};

#endif // COMPLEXNUMBERADAPTER_H
