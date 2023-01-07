#include "mainwindow.h"
#include <QApplication>
#include "complexnumberadapter.h"
#include <iostream>

using namespace std::complex_literals;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    //-------------------------------------------------------------------------------------------------------------------------------------
                                                                                                                //TEST ComplexNumberAdapter

//    ComplexNumberAdapter generalForm(5.f-1if);
//    std::cout << "general\t" << generalForm << std::endl;
//    ComplexNumberAdapter newEx = generalForm.toExponentialForm();
//    std::cout << "newEx\t" << newEx << std::endl;


    ComplexNumberAdapter exponentialForm(5.1f, 11.3f);  //TODO: exp form should be used
    std::cout << "exp\t" << exponentialForm << std::endl << std::endl;
    ComplexNumberAdapter newGen = exponentialForm.toGeneralForm();
    std::cout << "newGen\t" << newGen << std::endl;

//    std::string inputDataGeneral{"-5.3-j3.778"};
//    std::string inputDataExp{"-5.4*e^-j23.235"};

//    ComplexNumberAdapter inputNumberGen = ComplexNumberAdapter::parseNumberFromString(inputDataGeneral);
//    ComplexNumberAdapter inputNumberExp = ComplexNumberAdapter::parseNumberFromString(inputDataExp);

//    std::cout << "input\t" << inputNumberGen << "\t" << (ComplexNumberAdapter::parseFormFromString(inputDataGeneral) ? "exp" : "gen") << std::endl;
//    std::cout << "input\t" << inputNumberExp <<  "\t" << (ComplexNumberAdapter::parseFormFromString(inputDataExp) ? "exp" : "gen") << std::endl;

//    generalForm = inputNumberGen+inputNumberGen;
//    exponentialForm = inputNumberExp + inputNumberExp;

//    std::cout << "general add\t" << generalForm << std::endl;
//    std::cout << "exp add\t" << exponentialForm << std::endl;

    //--------------------------------------------------------------------------------------------------------------------------------------
    return a.exec();
}
