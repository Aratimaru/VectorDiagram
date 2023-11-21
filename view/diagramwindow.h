#ifndef DIAGRAMWINDOW_H
#define DIAGRAMWINDOW_H

#include <QMainWindow>

#include "dynamic_layouts/dynamiclayoutholder.h"
#include "qscrollarea.h"
#include <model/vectordiagrammodel.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class DiagramWindow;
}
QT_END_NAMESPACE

class DiagramWindow : public QMainWindow {
  Q_OBJECT

private slots:
  void onClearBtnClicked();
  void onDrawBtnClicked();

  void onChooseImageButtonClicked();

  void onStartGenXEditTextEdited();
  void onStartGenYEditTextEdited();
  void onStartExpAEditTextEdited();
  void onStartExpUEditTextEdited();

  void onEndGenXEditTextEdited();
  void onEndGenYEditTextEdited();
  void onEndExpAEditTextEdited();
  void onEndExpUEditTextEdited();

private:
  bool validateInputParameters();
  PhaseVectorPhase getCurrentPhase();
  QMap<QPair<PhaseVectorPhase, PhaseVectorType>, PhaseVector>
  getParametersFromUi();
  void setupWindow(QMainWindow *DiagramWindow);
  QVector<QString> getElementsFromImage();
  void connectDynamicSlots();

public:
  explicit DiagramWindow(QWidget *parent = nullptr);
  ~DiagramWindow();
  QString createCircuitElementsRecognizerProcess(const QString &imagePath);
  void createDynamicLayouts();

private:
  Ui::DiagramWindow *ui;
  std::shared_ptr<VectorDiagramModel> _model;
  DynamicLayoutsHolder _dynamicLayoutsHolder;
  QVBoxLayout *_mainDynamicLayout;
  std::unique_ptr<QWidget> _dynamicLayoutWidget;
  QScrollArea *_scrollArea;
  FieldsAddresses _fieldsAddress;
};

#endif // DIAGRAMWINDOW_H
