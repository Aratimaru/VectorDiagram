#include "dynamiclayoutholder.h"

void DynamicLayoutsHolder::addLayoutForElement(const QString &elementName) {
  DynamicLayoutsPerElement *currentLayout = new DynamicLayoutsPerElement;
  currentLayout->elementName = elementName;
  if (elementName.first(1) == "v") {
    currentLayout->U = LayoutGenerator::createParameterLayout("U", elementName);
    currentLayout->I = nullptr;
    currentLayout->R = nullptr;
  } else if (elementName.first(1) == "i") {
    currentLayout->U = nullptr;
    currentLayout->I = nullptr;
    currentLayout->R = LayoutGenerator::createParameterLayout("R", elementName);
  } else {
    currentLayout->U = nullptr;
    currentLayout->I = nullptr;
    currentLayout->R = LayoutGenerator::createParameterLayout("R", elementName);
  }
  _dynamicLayouts.push_back(currentLayout);
}

void DynamicLayoutsHolder::push_back(DynamicLayoutsPerElement &el) {
  _dynamicLayouts.push_back(&el);
}

void DynamicLayoutsHolder::pop_back() { _dynamicLayouts.pop_back(); }

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
