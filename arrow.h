#ifndef ARROW_H
#define ARROW_H

#include <QAbstractGraphicsShapeItem>
#include <QLineF>
#include <QObject>

class Arrow : public QAbstractGraphicsShapeItem {
public:
  explicit Arrow(QAbstractGraphicsShapeItem *parent = nullptr);
  Arrow(QLineF &base, QLineF &leftSide, QLineF &rightSide);
  Arrow(QLineF &base, const float &angle = 90, const float &sideLenght = 10);

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  QRectF boundingRect() const override;

  void setArrowParameters(QLineF &base, QLineF &leftSide, QLineF &rightSide);
  void setArrowParameters(QLineF &base, const float &angle = 60,
                          const float &sideLenght = 20);

  QPointF getP1();
  QPointF getP2();

private:
  void calculateSidesByAngle();

  QLineF _base{};
  QLineF _leftSide{};
  QLineF _rightSide{};
  float _angle{};
  float _sideLenght{};
};

#endif // ARROW_H
