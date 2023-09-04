#ifndef DIAGRAMWINDOW_H
#define DIAGRAMWINDOW_H

#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui {
class DiagramWindow;
}
QT_END_NAMESPACE

class DiagramWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit DiagramWindow(QWidget *parent = nullptr);
  ~DiagramWindow();

private:
  Ui::DiagramWindow *ui;
};

#endif // DIAGRAMWINDOW_H
