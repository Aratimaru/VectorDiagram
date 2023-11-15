#include "dynamiclayoutholder.h"

void DynamicLayoutsHolder::addLayoutForElement(const QString &elementName) {
  DynamicLayoutsPerElement *currentLayout = new DynamicLayoutsPerElement;
  currentLayout->elementName = elementName;
  currentLayout->I = LayoutGenerator::createParameterLayout("I" + elementName);
  currentLayout->U = LayoutGenerator::createParameterLayout("U" + elementName);
  currentLayout->R = LayoutGenerator::createParameterLayout("R" + elementName);
  _dynamicLayouts.push_back(currentLayout);
}

int DynamicLayoutsHolder::size() { return _dynamicLayouts.size(); }

const DynamicLayoutsPerElement &
DynamicLayoutsHolder::operator[](int index) const {
  if (index >= _dynamicLayouts.size()) {
    throw std::out_of_range(Q_FUNC_INFO);
  }
  return *_dynamicLayouts[index];
}

DynamicLayoutsPerElement &DynamicLayoutsHolder::operator[](int index) {
  if (index >= _dynamicLayouts.size()) {
    throw std::out_of_range(Q_FUNC_INFO);
  }
  return *_dynamicLayouts[index];
}
