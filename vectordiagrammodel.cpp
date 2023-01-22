#include "vectordiagrammodel.h"

VectorDiagramModel::VectorDiagramModel(QObject *parent)
    : QAbstractTableModel{parent}
{

}

int VectorDiagramModel::rowCount(const QModelIndex & /*parent*/) const
{return _instances.size();
}

int VectorDiagramModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 3;//
}

QVariant VectorDiagramModel::data(const QModelIndex &index, int role) const
{
    //! \todo add the sanity check

    const TableOfPhases *holderStruct {&_instances[index.row()]};

    switch (index.column()) {
    case 0:
        return QVariant::fromValue(holderStruct->phaseA);
    case 1:
        return QVariant::fromValue(holderStruct->phaseB);
    case 2:
        return QVariant::fromValue(holderStruct->phaseC);
    default:
        Q_ASSERT(false);
        break;
    }

}

bool VectorDiagramModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.column() >= columnCount() || index.row() >= _instances.size() )
        return false;

    if (!value.canConvert<QPair<double, double>>())
        return false; // conversion may not succeed

    //! \todo intermediary calculations

    auto dataPair = value.value<QPair<double, double>>();
    TableOfPhases *holderStruct;
    holderStruct = &_instances[index.row()];

    switch (index.column()) {
    case 0:
        holderStruct->phaseA = dataPair;
        break;
    case 1:
        holderStruct->phaseB = dataPair;
        break;
    case 2:
        holderStruct->phaseC= dataPair;
        break;
    default:
        Q_ASSERT(false);
        break;
    }
}
