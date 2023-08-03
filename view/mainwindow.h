#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

#include "model/vectordiagrammodel.h"
#include "view/diagramview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void resizeEvent(QResizeEvent *e);

private slots:
  void on_ConfirmButton_clicked();

  void on_ClearButton_clicked();

private:
  Ui::MainWindow *ui;
  std::shared_ptr<VectorDiagramModel> _model;
};
#endif // MAINWINDOW_H
