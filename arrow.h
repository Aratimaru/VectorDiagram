#ifndef ARROW_H
#define ARROW_H

#include <QLineF>
#include <QObject>

class Arrow : public QLineF {
public:
  explicit Arrow(QLineF *parent = nullptr);
};

#endif // ARROW_H
