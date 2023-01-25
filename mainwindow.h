#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

#include "phasevector.h"
#include "vectordiagrammodel.h"

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

private slots:
  void on_ConfirmButton_clicked();

  void fillModel(const std::vector<PhaseVector> &allPhases);

private:
  Ui::MainWindow *ui;
  std::shared_ptr<VectorDiagramModel> _model;
};
#endif // MAINWINDOW_H
