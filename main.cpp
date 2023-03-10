#include "mainwindow.h"
#include <QApplication>
#include <iostream>

#include "complexnumberadapter.h"
#include "phaseparametersstorage.h"
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
    std::cout << "                                                                                              //orerations"
              << std::endl;

    ComplexNumberAdapter inputNumberGen(-5.f-3if);
    ComplexNumberAdapter inputNumberExp(3.16f, 18.4f);
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
    std::cout << "                                                                                              //calculate phase vectors"
              << std::endl;

    ComplexNumberAdapter complexResistence {0.58f, 31.f};
    ComplexNumberAdapter complexCurrent {3.5f, 22.4f};
    ComplexNumberAdapter complexrVoltage {40.7f, 98.2f};

    Parameter resistence; resistence.parameter = complexResistence; resistence.prefix = MEGA;
    Parameter current; current.parameter = complexCurrent; current.prefix = KILO;
    Parameter voltage; voltage.parameter = complexrVoltage; voltage.prefix = MEGA;

    PhaseParametersStorage phaseParameterStorage;
    phaseParameterStorage.setResistence(resistence);
    phaseParameterStorage.setCurrent(current);
    phaseParameterStorage.setVoltage(voltage);

    VectorParametersCalculator calculator;
    std::vector <PhaseVector> phaseVectors;
    phaseVectors = calculator.calculate(phaseParameterStorage);

    std::cout << phaseVectors.at(0) << std::endl;
    std::cout << phaseVectors.at(1) << std::endl;


//    std::cout << "-------------------------------------------------------------------------------------------------------------------------"
//              << std::endl;
//    std::cout << "                                                                                              //TEST PhaseVector"
//              << std::endl;
//    std::cout << "                                                                                              //send results"
//              << std::endl;

//    PhaseVector currentVector;
//    PhaseVector voltageVector;

//    calculator.sentResults(currentVector, voltageVector);

//    std::cout << "currentVector\t" << currentVector.getCoordinates().second << std::endl;
//    std::cout << "voltageVector\t" << voltageVector.getCoordinates().second << std::endl;


    return a.exec();
}
