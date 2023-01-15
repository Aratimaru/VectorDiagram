#ifndef VectorParametersCalculator_H
#define VectorParametersCalculator_H
#include "phasevector.h"
#include "phaseparametersstorage.h"
#include <vector>

class VectorParametersCalculator
{
private:
    bool necessaryParametersFound(PhaseParametersStorage &data, VectorLabel value);

public:
    VectorParametersCalculator();
    std::vector <PhaseVector> calculate(PhaseParametersStorage &data);      //empty if no enough parameters
                                                                            //returns complex numbers in general form
                                                                            //sets only vector's end coordinate
                                                                            //0 - voltage, 1 - current

//    void convertToUnit (Parameters p, const UnitPrefix u);
//    void convertToUnit (Parameter& p, const UnitPrefix u);     //TODO: change to private
//    void convertToSmallerUnit(Parameter& p1, Parameter& p2);
//    void convertToBiggerUnit(Parameter& p1, Parameter& p2);

//    void sentResults(PhaseVector& currentVector, PhaseVector& voltageVector);           //TODO: removel
};

#endif // VectorParametersCalculator_H
