#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Operations.h>

#include <QMainWindow>
#include <QDesktopWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Operations operations;


    QVector <int> vecA;
    QVector <int> vecB;
    bool boolPositiveResult = true; // по дефолту результат должен быть положительным числом
    QString strPositiveNegativeVecA = "";// по дефолту число vecA является положительным
    QString strOperation;
    bool boolComaVecA = false; // по дефолту число без плавающей точки
    bool boolComaVecB = false; // по дефолту число без плавающей точки
    bool boolForProcessEvents = false;// Отслеживания выполняение цикла где присутствует QApplication::processEvents
    bool boolClose = false; // для отслеживания закрытия приложения


    void setupFront();
    void setupConnections();

public:
    void showResult(const QVector <int> &vec);
    void refreshFlags(bool positiveVecA = true, bool positiveResult = true, bool comaVecA = false,
                      bool comaVecB = false, bool strOperationClear = true, bool forProcessEvents = false,
                      bool vecAClear = false, bool vecBClear = false, bool close = false);
    void showInformations(const QString str);
    int fromStepWriteSeparator(const QVector<int> &vec);
    QString labelOperation(int number);
    QString labelNameNumber(int number);
    QString labelInformation(int number);
    QString labelInformationText(int number, bool boolVec);

    void operationPlus(QVector <int> &vecAA, QVector <int> &vecBB);
    void operationMinus(QVector <int> &vecAA, QVector <int> &vecBB);
    void operationMultiply (QVector <int> &vecAA, QVector<int> &vecBB);
    void operationDivide(QVector <int> &vecAA, QVector <int> &vecBB);
    void operationElevate(QVector <int> &vecAA, QVector <int> &vecBB);


protected:
    virtual void closeEvent(QCloseEvent *event);

public slots:
    void slotClickedOnNumbers();
    void slotOnPushButtonMultiplyDivide();
    void slotOnPushButtonPlusMinus();
    void slotOnPushButton_Elevate();
    void slotOnPushButton_comma();
    void slotOnPushButton_equally();
    void slotOnPushButton_remove();
    void slotOnPushButton_clear();

    void slotShowElevate(int numeralElevate);
signals:
    void signalClose();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
