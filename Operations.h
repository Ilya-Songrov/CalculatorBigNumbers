#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "QVector"
#include "qDebug"
#include "QObject"


class Operations : public QObject
{
    Q_OBJECT
public:
    Operations();

    bool boolClose = false; // для отслеживания закрытия приложения
private:
public: // после удалить
    void clearZero(QVector <int> &vec);
    void fillZeroToEndVectors(QVector <int> &vec1, QVector <int> &vec2, bool boolCommaVecA, bool boolCommaVecB);
    QString compareVectors(QVector <int> &vec1, QVector <int> &vec2);
    QString compareVectorsWithComma(QVector<int> &vec1, QVector<int> &vec2, bool boolCommaVecA, bool boolCommaVecB);
    int findComma(const QVector <int> &vec);
    QVector <int> toVectorNumberOfTen(int numeral);
    void slotClose() { boolClose = true; }
public:
    void plus(QVector<int> vecA, QVector<int> vecB, QVector <int> &vecResult);
    void minus(QVector <int> vecA, QVector<int> vecB, QVector <int> &vecResult);
    void multiply (QVector <int> vecA, QVector<int> vecB, QVector <int> &vecResult);
    void divide(QVector<int> vecA, QVector <int> vecB, QVector <int> &vecResult);
    void divideNumberOfTen(const QVector<int> vecA, QVector<int> vecB, QVector <int> &vecResult);
    void elevate(const QVector <int> &vecA, QVector <int> &vecB, QVector <int> &vecResult);
        void plusWithComma(QVector<int> vecA, QVector<int> vecB, QVector <int> &vecResult);
        void minusWithComma(QVector <int> vecA, QVector<int> vecB, QVector <int> &vecResult);
        void multiplyWithComma (QVector <int> vecA, QVector<int> vecB, QVector <int> &vecResult);
        void divideWithComma(QVector<int> vecA, QVector <int> vecB, QVector <int> &vecResult);

signals:
        void signalElevate(int numeralElevate);
};

#endif // OPERATIONS_H
