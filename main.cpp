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

    ComplexNumberAdapter complexAdapter;
    std::complex <float> generalForm = 1.f - 2if;
    std::complex <float> exponentialForm = exp(generalForm);

    std::cout << "general\t" << generalForm.real() << "\t," << generalForm.imag() << std::endl;
    std::cout << "exp\t" << exponentialForm.real() << "\t," << exponentialForm.imag() << std::endl;

    std::complex <float> newEx = complexAdapter.toExponentialForm(generalForm);
    std::complex <float> newGen = complexAdapter.toGeneralForm(exponentialForm);

    std::cout << "newGen\t" << newGen.real() << "\t," << newGen.imag() << std::endl;
    std::cout << "newEx\t" << newEx.real() << "\t," << newEx.imag() << std::endl;

    std::complex <float> input = complexAdapter.parseFromString("-5.4*e^j-23.235").first;

    std::cout << "input\t" << input.real() << "\t" << input.imag() << std::endl;


    //--------------------------------------------------------------------------------------------------------------------------------------
    return a.exec();
}
