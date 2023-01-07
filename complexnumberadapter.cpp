#include "complexnumberadapter.h"

ComplexNumberAdapter::ComplexNumberAdapter()  : std::complex <float>(){

}

ComplexNumberAdapter::ComplexNumberAdapter(std::complex <float> a) : std::complex <float>(a){

}

ComplexNumberAdapter ComplexNumberAdapter::toGeneralForm(){
    return log(*this);
}

ComplexNumberAdapter ComplexNumberAdapter::toExponentialForm(){
    return exp(*this);
}

ComplexNumberAdapter ComplexNumberAdapter::parseNumberFromString(const std::string &s)
{
    std::string sReal{}, sImag{};
    int jIndex = 0;         //delimeter to separate real and imag parts

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

    std::complex <float> result;
    result.real(std::stof(sReal));
    result.imag(std::stof(sImag));

    return result;
}

bool ComplexNumberAdapter::parseFormFromString(const std::string &s)
{
    for (const auto& c : s){
        if (c == 'e'){
            return true;
        }
    }
    return false;
}

bool ComplexNumberAdapter::isDigit(const char& c){
    return ((c>47 && c<58) || c == '.' || c == '-');
}
