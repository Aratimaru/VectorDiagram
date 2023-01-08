#include "mainwindow.h"
#include <QApplication>
#include <iostream>

#include "complexnumberadapter.h"
#include "vectorparameterscalculator.h"

using namespace std::complex_literals;

int main(int argc, char *argv[])        //TODO: add units MV, MA, kA, kV...
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.show();

    std::cout << "-------------------------------------------------------------------------------------------------------------------------"
              << std::endl;
    std::cout << "                                                                                              //TEST ComplexNumberAdapter"
              << std::endl;
    std::cout << "                                                                                              //Form conversion"
              << std::endl;

    ComplexNumberAdapter generalForm(5.f-1if);
    std::cout << "general\t" << generalForm << std::endl;
    ComplexNumberAdapter newEx = generalForm.toExponentialForm();
    std::cout << "newEx\t" << newEx << std::endl;


    ComplexNumberAdapter exponentialForm(40.7f, 98.2f);
    std::cout << "exp\t" << exponentialForm << std::endl;
    ComplexNumberAdapter newGen = exponentialForm.toGeneralForm();
    std::cout << "newGen\t" << newGen << std::endl;


    std::cout << "-------------------------------------------------------------------------------------------------------------------------"
              << std::endl;
    std::cout << "                                                                                              //TEST ComplexNumberAdapter"
              << std::endl;
    std::cout << "                                                                                              //Parse from string"
              << std::endl;

    std::string inputDataGeneral{"-5-j3"};
    std::string inputDataExp{"3.16*e^j18.4"};

    ComplexNumberAdapter inputNumberGen;
    inputNumberGen.parseNumberFromString(inputDataGeneral);
    ComplexNumberAdapter inputNumberExp;
    inputNumberExp.parseNumberFromString(inputDataExp);

    std::cout << "inputNumberGen\t" << inputNumberGen << "\t" << (inputNumberGen.getForm() ? "exp" : "gen") << std::endl;
    std::cout << "inputNumberExp\t" << inputNumberExp <<  "\t" << (inputNumberExp.getForm() ? "exp" : "gen") << std::endl;


    std::cout << "-------------------------------------------------------------------------------------------------------------------------"
              << std::endl;
    std::cout << "                                                                                              //TEST ComplexNumberAdapter"
              << std::endl;
    std::cout << "                                                                                              //operations"
              << std::endl;

    ComplexNumberAdapter resultGen = inputNumberGen+inputNumberGen;
    std::cout << "general add\t" << resultGen << std::endl;
    resultGen = inputNumberGen-inputNumberGen;
    std::cout << "general substract\t" << resultGen << std::endl;
    resultGen = inputNumberGen*inputNumberGen;
    std::cout << "general multiply\t" << resultGen << std::endl;
    resultGen = inputNumberGen/inputNumberGen;
    std::cout << "general divide\t" << resultGen << std::endl;

    ComplexNumberAdapter inputNumberExp1{3.5f, 22.4f};
    ComplexNumberAdapter inputNumberExp2{0.58f, 31.f};
    ComplexNumberAdapter resultExp = multExp(inputNumberExp1, inputNumberExp2);
    std::cout << "exp multiply\t" << resultExp << std::endl;
    resultExp = divideExp(resultExp, inputNumberExp);
    std::cout << "exp divide\t" << resultExp << std::endl;


    std::cout << "-------------------------------------------------------------------------------------------------------------------------"
              << std::endl;
    std::cout << "                                                                                              //TEST VectorParametersCalculator"
              << std::endl;
    std::cout << "                                                                                              //evaluate circuit"
              << std::endl;

    VectorParametersCalculator calculator;
    ComplexNumberAdapter calculatorAdapterResistence {0.58f, 31.f};
    ComplexNumberAdapter calculatorAdapterCurrent {3.5f, 22.4f};
    ComplexNumberAdapter calculatorAdapterVoltage {40.7f, 98.2f};
    calculatorAdapterCurrent = calculatorAdapterCurrent.toGeneralForm();

    calculator.setResistence(calculatorAdapterResistence);
    calculator.setCurrent(calculatorAdapterCurrent);
    calculator.setVoltage(calculatorAdapterVoltage);
    calculator.calculate();

    std::cout << "Voltage\t" << calculator.getVoltage() << std::endl;
    std::cout << "Current\t" << calculator.getCurrent() << std::endl;
    std::cout << "Resistence\t" << calculator.getResistence() << std::endl;


    std::cout << "-------------------------------------------------------------------------------------------------------------------------"
              << std::endl;
    std::cout << "                                                                                              //TEST PhaseVector"
              << std::endl;
    std::cout << "                                                                                              //send results"
              << std::endl;

    PhaseVector currentVector;
    PhaseVector voltageVector;

    calculator.sentResults(currentVector, voltageVector);

    std::cout << "currentVector\t" << currentVector.getCoordinates().second << std::endl;
    std::cout << "voltageVector\t" << voltageVector.getCoordinates().second << std::endl;


    return a.exec();
}
