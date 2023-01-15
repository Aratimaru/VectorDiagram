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
//    ComplexNumberAdapter voltage = m_Voltage.parameter.toGeneralForm();
//    ComplexNumberAdapter current = m_Current.parameter.toGeneralForm();

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
//        if(m_Current.parameter.getForm() == false){     //only for exp form
//            return;
//        }
//        m_Current.parameter.real(m_Current.parameter.real() * pow(10, (int)m_Current.prefix - (int)u));
//        m_Current.prefix = u;
//        break;
//    }
//    case VOLTAGE:
//    {
//        if(m_Voltage.parameter.getForm() == false){     //only for exp form
//            return;
//        }
//        m_Voltage.parameter.real(m_Voltage.parameter.real() * pow(10, (int)m_Voltage.prefix - (int)u));
//        m_Voltage.prefix = u;
//        break;
//    }
//    case RESISTENCE:
//    {
//        if(m_Resistence.parameter.getForm() == false){     //only for exp form
//            return;
//        }
//        m_Resistence.parameter.real(m_Resistence.parameter.real() * pow(10, (int)m_Resistence.prefix - (int)u));
//        m_Resistence.prefix = u;
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
