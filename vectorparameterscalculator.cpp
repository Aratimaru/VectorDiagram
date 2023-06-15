#include "VectorParametersCalculator.h"

VectorParametersCalculator::VectorParametersCalculator()
{

}

std::vector<PhaseVector> VectorParametersCalculator::calculate(PhaseParametersStorage &data){
    std::vector <PhaseVector> phaseVectors;

    if(data.getVoltage().parameter == UNDEFINED_COMPLEX_NUMBER &&   //calculate voltage if it is unknown
            data.getCurrent().parameter != UNDEFINED_COMPLEX_NUMBER &&
            data.getResistence().parameter != UNDEFINED_COMPLEX_NUMBER){
        if(!necessaryParametersFound(data, VOLTAGE)){
            return phaseVectors;
        }

        if(data.getCurrent().parameter.getForm() == false){         //transform to exp form
            Parameter current;
            current.parameter = data.getCurrent().parameter.toExponentialForm();
            data.setCurrent(current);
        }
        if(data.getResistence().parameter.getForm() == false){      //transform to exp form
            Parameter resistence;
            resistence.parameter = data.getResistence().parameter.toExponentialForm();
            data.setResistence(resistence);
        }

        Parameter voltage;
        voltage.parameter = multExp(data.getCurrent().parameter, data.getResistence().parameter);
        voltage.parameter.setForm(true);
        data.setVoltage(voltage);
    }

    if(data.getCurrent().parameter == UNDEFINED_COMPLEX_NUMBER &&   //calculate current if it is unknown
            data.getVoltage().parameter != UNDEFINED_COMPLEX_NUMBER &&
            data.getResistence().parameter != UNDEFINED_COMPLEX_NUMBER){
        if(!necessaryParametersFound(data, CURRENT)){
            return phaseVectors;
        }

        if(data.getVoltage().parameter.getForm() == false){         //transform to exp form
            Parameter voltage;
            voltage.parameter = data.getVoltage().parameter.toExponentialForm();
            data.setVoltage(voltage);
        }
        if(data.getResistence().parameter.getForm() == false){      //transform to exp form
            Parameter resistence;
            resistence.parameter = data.getResistence().parameter.toExponentialForm();
            data.setResistence(resistence);
        }

        Parameter current;
        current.parameter = divideExp(data.getVoltage().parameter, data.getResistence().parameter);
        current.parameter.setForm(true);
        data.setCurrent(current);
    }

    if(data.getCurrent().parameter != UNDEFINED_COMPLEX_NUMBER &&
            data.getVoltage().parameter != UNDEFINED_COMPLEX_NUMBER){
        if(data.getVoltage().parameter.getForm() == true){         //transform to gen form
            Parameter voltage;
            voltage.parameter = data.getVoltage().parameter.toGeneralForm();
            data.setVoltage(voltage);
        }

        if(data.getCurrent().parameter.getForm() == true){         //transform to gen form
            Parameter current;
            current.parameter = data.getCurrent().parameter.toGeneralForm();
            data.setCurrent(current);
        }
    }else{
        return phaseVectors;
    }

    PhaseVector currentVector;
    currentVector.setCoodinates(Coordinates {data.getCurrent().parameter.real(), data.getCurrent().parameter.imag()});
    currentVector.setLabel(CURRENT);
    PhaseVector voltageVector;
    voltageVector.setCoodinates(Coordinates {data.getVoltage().parameter.real(), data.getVoltage().parameter.imag()});
    voltageVector.setLabel(VOLTAGE);

    phaseVectors.push_back(voltageVector);
    phaseVectors.push_back(currentVector);
    return phaseVectors;
}


//void VectorParametersCalculator::sentResults(PhaseVector& currentVector, PhaseVector& voltageVector)
//{
//    ComplexNumberAdapter voltage = _Voltage.parameter.toGeneralForm();
//    ComplexNumberAdapter current = _Current.parameter.toGeneralForm();

//    currentVector.setCoodinates({current.real(), current.imag()});
//    voltageVector.setCoodinates({voltage.real(), voltage.imag()});
//}

bool VectorParametersCalculator::necessaryParametersFound(PhaseParametersStorage &data, VectorLabel value){
    switch (value){
    case VOLTAGE:
    {
        return (data.getCurrent().parameter!=UNDEFINED_COMPLEX_NUMBER &&
                data.getResistence().parameter!=UNDEFINED_COMPLEX_NUMBER);
        break;
    }
    case CURRENT:
    {
        return (data.getVoltage().parameter!=UNDEFINED_COMPLEX_NUMBER &&
                data.getResistence().parameter!=UNDEFINED_COMPLEX_NUMBER &&
                data.getResistence().parameter!=NULL_COMPLEX_NUMBER);
        break;
    }
    case RESISTENCE:
    {
        return (data.getCurrent().parameter!=UNDEFINED_COMPLEX_NUMBER &&
                data.getVoltage().parameter!=UNDEFINED_COMPLEX_NUMBER);
        break;
    }
    default:
    {
        return false;
    }
    }
}

//void VectorParametersCalculator::convertToUnit(Parameters p, const UnitPrefix u)
//{
//    switch (p) {
//    case CURRENT:
//    {
//        if(_Current.parameter.getForm() == false){     //only for exp form
//            return;
//        }
//        _Current.parameter.real(_Current.parameter.real() * pow(10, (int)_Current.prefix - (int)u));
//        _Current.prefix = u;
//        break;
//    }
//    case VOLTAGE:
//    {
//        if(_Voltage.parameter.getForm() == false){     //only for exp form
//            return;
//        }
//        _Voltage.parameter.real(_Voltage.parameter.real() * pow(10, (int)_Voltage.prefix - (int)u));
//        _Voltage.prefix = u;
//        break;
//    }
//    case RESISTENCE:
//    {
//        if(_Resistence.parameter.getForm() == false){     //only for exp form
//            return;
//        }
//        _Resistence.parameter.real(_Resistence.parameter.real() * pow(10, (int)_Resistence.prefix - (int)u));
//        _Resistence.prefix = u;
//        break;
//    }
//    default:
//        break;
//    }
//}

//void VectorParametersCalculator::convertToUnit(Parameter &p, const UnitPrefix u)
//{
//    if(p.parameter.getForm() == false){     //only for exp form
//        return;
//    }
//    p.parameter.real(p.parameter.real() * pow(10, ((int)p.prefix - (int)u)));
//    p.prefix = u;
//}

//void VectorParametersCalculator::convertToSmallerUnit(Parameter &p1, Parameter &p2)
//{

//}
