#include "mainwindow.h"
#include <QApplication>
#include <iostream>

#include "complexnumberadapter.h"
#include "vectorparameterscalculator.h"

using namespace std::complex_literals;

int main(int argc, char *argv[])        //TODO: add units MV, MA, kA, kV...
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    //-------------------------------------------------------------------------------------------------------------------------------------
                                                                                                                //TEST ComplexNumberAdapter
                                                                                                                //Form conversion

//    ComplexNumberAdapter generalForm(5.f-1if);
//    std::cout << "general\t" << generalForm << std::endl;
//    ComplexNumberAdapter newEx = generalForm.toExponentialForm();
//    std::cout << "newEx\t" << newEx << std::endl;


//    ComplexNumberAdapter exponentialForm(5.1f, 11.3f);
//    std::cout << "exp\t" << exponentialForm << std::endl;
//    ComplexNumberAdapter newGen = exponentialForm.toGeneralForm();
//    std::cout << "newGen\t" << newGen << std::endl;

    //-------------------------------------------------------------------------------------------------------------------------------------
                                                                                                                //TEST ComplexNumberAdapter
                                                                                                                //Parse from string

//    std::string inputDataGeneral{"-5-j3"};
//    std::string inputDataExp{"3.16*e^j18.4"};

//    ComplexNumberAdapter inputNumberGen = ComplexNumberAdapter::parseNumberFromString(inputDataGeneral);
//    ComplexNumberAdapter inputNumberExp = ComplexNumberAdapter::parseNumberFromString(inputDataExp);

//    std::cout << "inputNumberGen\t" << inputNumberGen << "\t" << (ComplexNumberAdapter::parseFormFromString(inputDataGeneral) ? "exp" : "gen") << std::endl;
//    std::cout << "inputNumberExp\t" << inputNumberExp <<  "\t" << (ComplexNumberAdapter::parseFormFromString(inputDataExp) ? "exp" : "gen") << std::endl;

    //-------------------------------------------------------------------------------------------------------------------------------------
                                                                                                                //TEST ComplexNumberAdapter
                                                                                                                //operations

//    ComplexNumberAdapter resultGen = inputNumberGen+inputNumberGen;
//    std::cout << "general add\t" << resultGen << std::endl;
//    resultGen = inputNumberGen-inputNumberGen;
//    std::cout << "general substract\t" << resultGen << std::endl;
//    resultGen = inputNumberGen*inputNumberGen;
//    std::cout << "general multiply\t" << resultGen << std::endl;
//    resultGen = inputNumberGen/inputNumberGen;
//    std::cout << "general divide\t" << resultGen << std::endl;

//    ComplexNumberAdapter inputNumberExp1{3.5f, 22.4f};
//    ComplexNumberAdapter inputNumberExp2{0.58f, 31.f};
//    ComplexNumberAdapter resultExp = multExp(inputNumberExp1, inputNumberExp2);
//    std::cout << "exp multiply\t" << resultExp << std::endl;
//    resultExp = divideExp(resultExp, inputNumberExp);
//    std::cout << "exp multiply\t" << resultExp << std::endl;


    //--------------------------------------------------------------------------------------------------------------------------------------


    //-------------------------------------------------------------------------------------------------------------------------------------
                                                                                                                //TEST VectorParametersCalculator
                                                                                                                //evaluate circuit

    VectorParametersCalculator calculator;
    calculator.setResistence(120.f);
    calculator.setVoltage(0.f);
    calculator.evaluateCircuit();

    std::cout << "Voltage\t" << calculator.getVoltage() << std::endl;
    std::cout << "Current\t" << calculator.getCurrent() << std::endl;
    std::cout << "Resistence\t" << calculator.getResistence() << std::endl;

    return a.exec();
}
