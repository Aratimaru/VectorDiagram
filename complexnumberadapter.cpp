#include "complexnumberadapter.h"

ComplexNumberAdapter::ComplexNumberAdapter()  : std::complex <float>(){
    setForm(false);
}

ComplexNumberAdapter::ComplexNumberAdapter(std::complex <float> a) : std::complex <float>(a){
    setForm(false);
}

ComplexNumberAdapter::ComplexNumberAdapter(float r, float i) : std::complex <float> (r, i){
    setForm(true);
}

ComplexNumberAdapter ComplexNumberAdapter::toGeneralForm(){
    ComplexNumberAdapter result;
    result.m_Form = false;

    result.real(this->real()*(std::cos(this->imag()*(std::atan(1.0f)*4/180.f))));
    result.imag(this->real()*(std::sin(this->imag()*(std::atan(1.0f)*4/180.f))));
    return result;
}

ComplexNumberAdapter ComplexNumberAdapter::toExponentialForm(){
    ComplexNumberAdapter result;
    result.m_Form = true;

    result.real(std::sqrt(std::pow(this->real(),2) + std::pow(this->imag(),2)));
    result.imag(std::atan(this->imag()/this->real()) * 180.f/(std::atan(1.0f)*4.f));     //std::atan(1.0)*4 = PI
    return result;
}

void ComplexNumberAdapter::parseNumberFromString(const std::string &s)
{
    std::string sReal{}, sImag{};
    int jIndex = 0;         //delimiter to separate real and imag parts

    for (int i=0;i<s.length();i++){
        if (isDigit(s.at(i))){
            sReal += s.at(i);
        }else {
            if (s.at(i) == 'j'){
                jIndex = i;
                break;
            }
        }
    }
    if(sReal.at(sReal.length()-1 == '-')){
        sReal.erase(sReal.length()-1);
    }

    for (int i=jIndex-1;i<s.length();i++){
        if (isDigit(s.at(i))){
            sImag += s.at(i);
        }
    }

    this->real(std::stof(sReal));
    this->imag(std::stof(sImag));
    parseFormFromString(s);
}

void ComplexNumberAdapter::parseFormFromString(const std::string &s)
{
    for (const auto& c : s){
        if (c == 'e'){
            m_Form = true;
            return;
        }
    }
    m_Form = false;
}

bool ComplexNumberAdapter::getForm()
{
    return m_Form;
}

void ComplexNumberAdapter::setForm(bool f)
{
    m_Form = f;
}

bool ComplexNumberAdapter::isDigit(const char& c){
    return ((c>47 && c<58) || c == '.' || c == '-');
}

ComplexNumberAdapter multExp(ComplexNumberAdapter c1, const ComplexNumberAdapter& c2){
    ComplexNumberAdapter result;

    float real = c1.real()*c2.real();
    float imag = c1.imag()+c2.imag();

    result.real(real); result.imag(imag);
    return result;
}

ComplexNumberAdapter divideExp(ComplexNumberAdapter c1, const ComplexNumberAdapter& c2){
    ComplexNumberAdapter result;

    if(c2.real() == NULL_COMPLEX_NUMBER)
        return ComplexNumberAdapter (NULL_COMPLEX_NUMBER);

    float real = c1.real()/c2.real();
    float imag = c1.imag()-c2.imag();

    result.real(real); result.imag(imag);
    return result;
}
