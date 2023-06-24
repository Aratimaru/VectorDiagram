#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

#include "model/modelupdater.h"
#include "view/viewupdater.h"

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

private:
  Ui::MainWindow *ui;
  std::shared_ptr<ModelUpdater> _modelUpdater;
  std::shared_ptr<ViewUpdater> _viewUpdater;
};
#endif // MAINWINDOW_H
