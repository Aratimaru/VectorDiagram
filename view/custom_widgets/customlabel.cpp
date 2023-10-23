#include "customlabel.h"

CustomLabel::CustomLabel(QWidget *parent) { this->setParent(parent); }

/*
 *            <widget class="QLabel" name="V1EndGenYLabel">
               <property name="sizePolicy">
                <sizepolicy hsizetype="Preferred" vsizetype="Fixed">
                 <horstretch>0</horstretch>
                 <verstretch>0</verstretch>
                </sizepolicy>
               </property>
               <property name="maximumSize">
                <size>
                 <width>30</width>
                 <height>16777215</height>
                </size>
               </property>
               <property name="font">
                <font>
                 <pointsize>13</pointsize>
                </font>
               </property>
               <property name="frameShape">
                <enum>QFrame::NoFrame</enum>
               </property>
               <property name="frameShadow">
                <enum>QFrame::Plain</enum>
               </property>
               <property name="text">
                <string>+iy</string>
               </property>
              </widget>

 * */

void CustomLabel::constructEndGenYlabel(const QString &parameterName,
                                        QWidget *parent) {
  this->setParent(parent);
  this->setObjectName(QString(parameterName + "Label"));
  this->setSizePolicy(QSizePolicy::Policy::Preferred,
                      QSizePolicy::Policy::Fixed);
  this->setMaximumSize(30, 2000);

  QFont font{};
  font.setPointSize(13);

  this->setFont(font);
  this->setFrameShape(QFrame::NoFrame);
  this->setFrameShadow(QFrame::Plain);
  this->setText("+iy");
}
