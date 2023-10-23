#include "customvlayout.h"

CustomVLayout::CustomVLayout() {}

void CustomVLayout::constructOuterLayout() {
  addStretch(1);
  addStretch(0);
  addStretch(5);
  addStretch(0);
  addStretch(5);
  addStretch(0);
}
