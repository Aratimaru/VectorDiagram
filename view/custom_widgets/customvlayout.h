#ifndef CUSTOMVLAYOUT_H
#define CUSTOMVLAYOUT_H

#include <QHBoxLayout>

//<layout class="QHBoxLayout" name="V1Layout" stretch="1,0,5,0,5,0">
class CustomVLayout : public QHBoxLayout {
public:
  CustomVLayout();
  void constructOuterLayout();
};

#endif // CUSTOMVLAYOUT_H
