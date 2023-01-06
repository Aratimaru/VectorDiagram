#include "complexnumberadapter.h"

ComplexNumberAdapter::ComplexNumberAdapter()
{

}

std::complex<float> ComplexNumberAdapter::toGeneralForm(std::complex<float> const &exponentialExpression){
    return log(exponentialExpression);
}

std::complex<float> ComplexNumberAdapter::toExponentialForm(std::complex<float> const &generalExpression){
    return exp(generalExpression);
}

std::pair <std::complex<float>, bool> ComplexNumberAdapter::parseFromString(const std::string& s){    //TODO: add float support
    float real =0, imag = 0;
    std::string sReal{}, sImag{};
    char sign = '0';
    bool form = false;      //0 - general, 1 - exp

    if(s.at(0) == '-'){     //set '-' sign to real
        sReal += s.at(0);
    }

    for (int i=0;i<s.length();i++){
        if (isDigit(s.at(i))){      //find real and imag part
            if(real == 0){
                sReal += s.at(i);
            }else{

                if(imag == 0){
                    sImag += s.at(i);

                    if(i == s.length() -1){
                        imag = std::stof(sImag);

                        if(sign == '-'){
                            imag = -imag;
                        }
                    }
                }
            }
        }else{

            if(real == 0 && i>0){
                real = std::stof(sReal);
            }

            if(sign == '0'){        //find sign
                if(s.at(i) =='-' || s.at(i) == '+'){
                    sign = s.at(i);
                }
            }

            if(s.at(i) == 'e'){     //exp form detected
                form = true;
            }
        }
    }

    std::complex <float> result;

    result.real(real);
    result.imag(imag);

    return {result, form};
}

bool ComplexNumberAdapter::isDigit(const char& c){
    return ((c>47 && c<58) || c == '.');
}
