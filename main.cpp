#include "mainwindow.h"
#include <QApplication>
#include "complexnumberadapter.h"
#include <iostream>

using namespace std::complex_literals;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //-------------------------------------------------------------------------------------------------------------------------------------
                                                                                                                //TEST ComplexNumberAdapter

//    ComplexNumberAdapter generalForm(1.f - 2if);
//    ComplexNumberAdapter exponentialForm = exp(generalForm);

//    std::cout << "general\t" << generalForm.real() << "\t," << generalForm.imag() << std::endl;
//    std::cout << "exp\t" << exponentialForm.real() << "\t," << exponentialForm.imag() << std::endl;

//    ComplexNumberAdapter newEx = generalForm.toExponentialForm();
//    ComplexNumberAdapter newGen = exponentialForm.toGeneralForm();

//    std::cout << "newGen\t" << newGen.real() << "\t," << newGen.imag() << std::endl;
//    std::cout << "newEx\t" << newEx.real() << "\t," << newEx.imag() << std::endl;

    std::string inputDataGeneral{"-5.3-j3.778"};
    std::string inputDataExp{"-5.4*e^-j23.235"};

    ComplexNumberAdapter inputNumberGen = ComplexNumberAdapter::parseNumberFromString(inputDataGeneral);
    ComplexNumberAdapter inputNumberExp = ComplexNumberAdapter::parseNumberFromString(inputDataExp);

    std::cout << "input\t" << inputNumberGen << "\t" << (ComplexNumberAdapter::parseFormFromString(inputDataGeneral) ? "exp" : "gen") << std::endl;
    std::cout << "input\t" << inputNumberExp <<  "\t" << (ComplexNumberAdapter::parseFormFromString(inputDataExp) ? "exp" : "gen") << std::endl;

    //--------------------------------------------------------------------------------------------------------------------------------------
    return a.exec();
}
