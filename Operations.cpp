#include "Operations.h"

Operations::Operations()
{
    // Здесь производятся операции над 2-мя числами, которые храняться в векторе. Результат вывовидться по ссылке
    // чтобы не копировать громадное число.
}

void Operations::clearZero(QVector<int> &vec)
{
    if(vec.isEmpty()){
        return;
    }
    for (;;) // удаляется перед числом ноль, если он есть.
    {
        if(vec.size() >= 2 && vec[0] == 0 && vec[1] == -1){
            break; // Выходим если это ноль целых 0,.....
        }
        /* vec[0] == 0 && vec.size() != 1 На тот случай если результат одна только цифра ноль, ее нельзя удалять*/
        if(!vec.isEmpty() && vec[0] == 0 && vec.size() != 1){
            vec.pop_front();
        }
        if(!vec.isEmpty() && (vec[0] != 0 || vec.size() == 1)){
            break;// Выходим если число 1,234
        }
    }
    bool boolComma = false;
    for (int var = 0; var < vec.size(); ++var) {// Обходим вектор чтоб узнать есть ли запятая
        if(vec[var] == -1){
            boolComma = true;
        }
    }
    if(!boolComma){
        return; // Выходим поскольку число без запятой и удалять нули в конце нельзя.
    }
    for (;;) // удаляется в конце числа ноль если это число с запятой.
    {
        /* На тот случай если результат одна только цифра ноль, ее нельзя удалять*/
        if(!vec.isEmpty() && vec[vec.size() - 1] == 0 && vec.size() != 1){
            vec.pop_back();
        }
        if(!vec.isEmpty() && (vec[vec.size() - 1] != 0 || vec.size() == 1)){
            break;// Выходим если число 1,234
        }
    }
    if(vec[vec.size() - 1] == -1){
        vec.pop_back();// Если чило было 5.000 и осталось (5.), тогда удалим точку
    }
}

void Operations::fillZeroToEndVectors(QVector<int> &vec1, QVector<int> &vec2,
                                      bool boolCommaVecA, bool boolCommaVecB)
{
    if(vec1.size() == vec2.size()){
        return;
    }
    int size = 0;
    if(vec1.size() > vec2.size()){// Если первый вектор больше тогда мы заполним нулями второй
        size = vec1.size() - vec2.size();
        // Ставим запятую в том случае если у числа нет запятой, потом добавляем нули
            vec2.push_back(boolCommaVecB ? 0 : -1);
        for (int var = 0; var < size -1; ++var) {
            vec2.push_back(0);
        }
    }
    else{// Если второй вектор больше тогда мы заполним нулями первый
        size = vec2.size() - vec1.size();
        // Ставим запятую в том случае если у числа нет запятой, потом добавляем нули
            vec1.push_back(boolCommaVecA ? 0 : -1);
        for (int var = 0; var < size -1; ++var) {
            vec1.push_back(0);
        }
    }
    if(vec1[vec1.size() - 1] == -1 || vec2[vec2.size() - 1] == -1)
    {// Если в одном из векторов оказалась последняя цифра запятая, мы добавим туда и туда нули.
     // 3,3 и 32, превратиться в 3,30 и 32,0
        vec1.push_back(0);
        vec2.push_back(0);
    }
}

QString Operations::compareVectors(QVector<int> &vec1, QVector<int> &vec2)
{
    clearZero(vec1); // удаляется перед числом и после числа ноль, если он есть.
    clearZero(vec2); // удаляется перед числом и после числа ноль, если он есть.
    // Выравниваем числа по длине не нужно поскольку сюда не попадаем с числами с запятой.


    if(vec1.size() > vec2.size())
        return ">";
    if(vec1.size() < vec2.size())
        return "<";

    for (int var = 0; var < vec1.size(); ++var)
    {
        if(vec1[var] > vec2[var]){
            return ">";
        }
        if(vec1[var] < vec2[var]){
            return "<";
        }
    }
    return "==";
}

QString Operations::compareVectorsWithComma(QVector<int> &vec1, QVector<int> &vec2,
                                            bool boolCommaVecA, bool boolCommaVecB)
{
    clearZero(vec1); // удаляется перед числом ноль, если он есть.
    clearZero(vec2); // удаляется перед числом ноль, если он есть.
    fillZeroToEndVectors(vec1, vec2, boolCommaVecA, boolCommaVecB);// Выравниваем числа по длине

    int intCommaVec1 = 0;
    int intCommaVec2 = 0;

    for (int var = 0; var < vec1.size(); ++var)
    {// Как минимум у одно числа есть точно запятая, значит нужно найти это число - оно и будет меньшим.
     // Если у двоих чисел есть зяпятые, значит меньшее число у того у кого запятая раньше.
            if(vec1[var] == -1){// Если встречаем зяпятую, записываем в какой позиции
                intCommaVec1 = var;
            }
            if(vec2[var] == -1){// Если встречаем зяпятую, записываем в какой позиции
                intCommaVec2 = var;
            }
        if(intCommaVec1 == intCommaVec2 && intCommaVec1 != 0 && intCommaVec2 != 0){
            // В случае если запятые совпадают мы сравним числа в обычном сравнителе
            // Возможна такая ситуяция два числа 234,45 и 500,00 и в compareVectors(); они не правильно
            // сравнять из-за того что есть запятая, поэтому мы делаем числа без запятых.
            QVector <int> vecMultiplyTwoNumbers = toVectorNumberOfTen(vec1.size() - (intCommaVec1 + 1));
            QVector <int> vec1Copy = vec1;// Делаем копии чтоб не испортить оригинал
            QVector <int> vec2Copy = vec2;
            fillZeroToEndVectors(vec1Copy, vec2Copy, intCommaVec1, intCommaVec2);
            multiplyWithComma(vec1Copy, vecMultiplyTwoNumbers, vec1Copy);// Умножаем чтоб избавиться от запятой
            multiplyWithComma(vec2Copy, vecMultiplyTwoNumbers, vec2Copy);
            return compareVectors(vec1Copy, vec2Copy);
        }
        else if(intCommaVec1 != intCommaVec2){ // Запятые не совпадают. Число у которого запятая оказалась раньше
            return intCommaVec1 < intCommaVec2 ? ">" : "<"; // является меньшим числом
        }
    }
    return "==";
}

int Operations::findComma(const QVector<int> &vec)
{
    for (int var = 0; var < vec.size(); ++var)
    {
        if(vec[var] == -1){
            return var;
        }
    }
    return vec.size();// Означает запятой нет
}

QVector<int> Operations::toVectorNumberOfTen(int numeral)
{// Функция которая делает вектор в зависимости сколько указанно десятков. numeral 1 = 10; numeral 2 = 100;
 // numeral 3 = 1000; numeral 0 = 1;
    QVector <int> vec;
    vec.push_back(1);
    if(numeral == 0){
        return vec;
    }
    for (int var = 0; var < numeral; ++var) {
        vec.push_back(0);
    }
    return vec;
}


void Operations::plus(QVector<int> vecA, QVector<int> vecB, QVector<int> &vecResult)
{
    vecResult.clear();
    vecResult = vecB;

    vecA.push_front(0);
    vecResult.push_front(0);
    int intSize = vecA.size() > vecResult.size() ? vecA.size()+1 : vecResult.size()+1;

    for (int var = 1; var < intSize; ++var)
    {// это и есть цикл прибавления предыдущего числа к новому.
            if(vecA.size() < vecResult.size()){
                vecA.push_front(0);
            }
            if(vecResult.size() < vecA.size()){
                vecResult.push_front(0);
            }

        vecResult[vecResult.size() - var] += vecA[vecA.size() - var];
        if(vecResult[vecResult.size() - var] > 9) // если число больше 9, то десяток нужно перенести.
        {// перенос десятка на следующий десяток, как при решении в столбик.
            vecResult[vecResult.size() - var -1] += 1;
            vecResult[vecResult.size() - var] = vecResult[vecResult.size() - var] - 10;
        }
    }
    clearZero(vecResult);
}

void Operations::minus(QVector<int> vecA, QVector<int> vecB, QVector<int> &vecResult)
{
    vecResult.clear();
    vecResult = vecA;

    vecB.push_front(0);
    vecResult.push_front(0);
    int intSize = vecB.size() > vecResult.size() ? vecB.size()+1 : vecResult.size()+1;

    for (int var = 1; var < intSize; ++var)
    {// это и есть цикл отнятия предыдущего числа от нового.
            if(vecB.size() < vecResult.size())
                vecB.push_front(0);
            if(vecResult.size() < vecB.size())
                vecResult.push_front(0);

        vecResult[vecResult.size() - var] -= vecB[vecB.size() - var];
        //если число отрицательное, то десяток нужно взять у следующего и прибавить к этому, сделав его положительным
        if(vecResult[vecResult.size() - var] < 0/* && vecResult[0] != -1*/)
        {// перенос десятка на предыдущий десяток
            vecResult[vecResult.size() - var -1] -= 1;
            vecResult[vecResult.size() - var] = vecResult[vecResult.size() - var] + 10;
        }
    }
    clearZero(vecResult);
}

void Operations::multiply(QVector<int> vecA, QVector<int> vecB, QVector<int> &vecResult)
{
    vecResult.clear();
    vecResult.push_back(0);

    int null = 0; // для добавление нулей перед каждым новым числом.

    for (int ix = vecA.size()-1; ix > -1; ix--)
    {
        QVector <int> vecC = {0};
        for (int jx = vecB.size()-1; jx > -1; jx--)
        {// все "верхнее число" умножается на нижнюю цифру
            vecC.push_front(0);
            vecC[1] += vecA[ix] * vecB[jx];
            if(vecC[1] > 9)
            {// перенос десятка на следующий десяток, как при решении в столбик
                int ten = vecC[1] / 10;
                vecC[0] +=  ten;
                vecC[1] = vecC[1] - ten * 10;
            }
        }

        for (int var = 0; var < null; ++var)
            vecC.push_back(0); // для добавление нулей перед каждым новым числом. Потомучто числа смещаются при
                            // прибавлении, по технике в столбик.

        for (int var = 1; var < (vecC.size() > vecResult.size() ? vecC.size()+1 : vecResult.size()+1); ++var)
        {// это и есть цикл прибавления предыдущего числа к новому.
                if(vecC.size() < vecResult.size())
                    vecC.push_front(0);
                if(vecResult.size() < vecC.size())
                    vecResult.push_front(0);

            vecResult[vecResult.size() - var] += vecC[vecC.size() - var];
            if(vecResult[vecResult.size() - var] > 9)
            {// перенос десятка на следующий десяток, как при решении в столбик
                vecResult[vecResult.size() - var -1] += 1;
                vecResult[vecResult.size() - var] = vecResult[vecResult.size() - var] - 10;
            }
        }

        null++; // для добавление нулей перед каждым новым числом.
    }
    clearZero(vecResult);
}

void Operations::divide(QVector<int> vecA, QVector<int> vecB, QVector<int> &vecResult)
{
    // vecA - делимое  // vecB - делитель
     vecResult.clear();
     QVector <int> vecRemainderAA; // остаток от вычитания.
     QVector <int> vecPartResult = {0}; // число в которое после операций заносится в результат.
     int intPos = 0; // для отщитывания какую цифру прибавлять после вычитания.
     bool boolComaDivide = false;// по умолчанию запятая не поставленна.

     // благодаря compareVectors(); уничтожаются не нужные нули. Как (50/051). После проверки (50/51).
     if(compareVectors(vecA,vecB) == "<"){// если число "А" меньше "В". Делитель меньше делимого.
         // Чило "А" может быть меньше "В" как(50<51).
         // И чило "А" может быть меньше "В" как(50<515).
             vecResult.push_back(0);// и в результат сразу записываем 0 целых
             vecResult.push_back(-1);// запятая ставится только однажды после ноль целых (0,...)
             boolComaDivide = true;
         if(vecA.size() != vecB.size())
         {// если чило "А" меньше "В" как(50<515) тогда нужно установить нули;
                 vecRemainderAA = vecA; // Временно ислпользуем число А, чтоб определить добавлять "0" или нет.
             for (int var = 0; var < vecB.size() - vecA.size(); ++var)
             {// цикл прокрутиться как минимум один раз, поскольку vecA.size() != vecB.size().
                 vecRemainderAA.push_back(0);
                 // В результат сразу записываем 0 десятых, сотых, тысячных... В зависимости на сколько делитель -
                 // - больше делимого, и лишь в том случае когда число после добавления к нему "0" все-равно оказы -
                 // - вается меше делителя.
                 if(compareVectors(vecRemainderAA,vecB) == "<")
                     vecResult.push_back(0);
             }
             vecRemainderAA.clear();// очищаем вектор, поскольку мы его использовали временно. Он создан не для этого.
         }
     }

     //перекачка часть числа А в vecRemainderAA, такого размера как размер делителя(В).
     for (int var = 0; var < vecB.size(); ++var) // В самом начале vecRemainderAA это не остаток от вычитания, а -
         vecRemainderAA.push_back(var < vecA.size() ? vecA[var] : 0); // - число выкачанное из числа А.


     for(;;)// Это цикл деления.
     {
         if(compareVectors(vecRemainderAA,vecB) == "<")
         {
             // если есть еще цифры мы добавляем их, если нет цифр, значит добавляем ноль.
             vecRemainderAA.push_back(intPos+vecB.size() < vecA.size() ? vecA[intPos+vecB.size()] : 0);
             // Если цифры закончились, мы вписываем запятую. И если запятая еще не поставленна.
             if(intPos+vecB.size() == vecA.size() && !boolComaDivide){
                 vecResult.push_back(-1);// -1 это запятая. После этого начинается записываться остаток.
                 boolComaDivide = true;// отмечаем что запятая поставлена
             }
             // Если мы добавили сдедующую цифру и после этого число все-равно меньше, тогда в результат нужно вста-
             // -вить "0". А если стало больше тогда, мы не вставляем ничего, это произойдет дальше в цикле деления.
             if(compareVectors(vecRemainderAA,vecB) == "<")
                 vecResult.push_back(0);
             intPos++; // для отщитывания, какую цифру прибавлять после вычитания.
         }
         if(compareVectors(vecRemainderAA,vecB) == "==")
         {
             vecResult.push_back(1);// в результат попадает число.
             vecPartResult[0] = 0;
             vecRemainderAA = vecPartResult; // определяем остаток.
         }
         if(compareVectors(vecRemainderAA,vecB) == ">")
         {
             QVector <int> vecMultiplyBB_old;// если vecRemainderAA меньше делителя, оно будет увеличиваться.
             for (int var = 1; var < 11; ++var)// Крутим 10 раз, чтобы потом получилось vecPartResult[0]-1.
             {// определение во сколько делитель больше числа vecRemainderAA. Максимально это может быть в 9 раз.
                 vecPartResult[0] = var; // начинаем с умножения в 1 и т.д. var = 1
                 QVector <int> vecMultiplyBB;
                 multiply(vecB, vecPartResult, vecMultiplyBB);
 if(compareVectors(vecMultiplyBB,vecRemainderAA) == "<" || compareVectors(vecMultiplyBB,vecRemainderAA) == "==")
                     vecMultiplyBB_old = vecMultiplyBB; // записываем
                 else
                     break;
             }

             minus(vecRemainderAA, vecMultiplyBB_old, vecRemainderAA); // определяем остаток.
             vecResult.push_back(vecPartResult[0]-1);// в результат попадает число.
         }

         if(intPos - vecA.size() > 50)
             break; // Определять число в пероде - сложно. Поэтому выходим после 50 знаков после запятой.
         if(vecRemainderAA[0] == 0 && intPos+vecB.size() >= vecA.size())
             break; // выходим когда после многократныx вычитаний получили ноль.
     }

}

void Operations::divideNumberOfTen(const QVector<int> vecA, QVector<int> vecB, QVector<int> &vecResult)
{// Здесь происходит деление на числа у которых первая цифра 1 остальные ноль. (10000000000...)
    vecResult.clear();
    vecResult = vecA;
    if(vecResult.size() < vecB.size()){// Если делимое меньше делителя. (123 / 1000000)
    // fillZeroToEndVectors(); не подходит поскольку там во время заполнения нолями может вставиться запятая.
    // Поэтому здесь отдельно заполняются нули при необходимости, и при этом не ставиться запятая.
        int intSize = vecB.size() - vecResult.size();
        for (int var = 0; var < intSize; ++var) {
            vecResult.push_front(0);
        }
    }
    QVector <int>::iterator iteratorVecResult = vecResult.end() - (vecB.size() - 1);
    vecResult.insert(iteratorVecResult, -1);// Вставляем обратно запятую
    vecResult.push_front(0);// Вставляем вначало ноль поскольку вставка по итератору может вставить запятую
    // первым элементом. Если запятая не в первом элементе вектора, этот ноль удалиться в clearZero();
    clearZero(vecResult);
}

void Operations::elevate(const QVector<int> &vecA, QVector<int> &vecB, QVector<int> &vecResult)
{
    vecResult.clear();
    vecResult.push_back(1);
    // Для сравнения с вектором vecB, и как только эти вектора будут равны, бесконечный цикл прекращаем.
    QVector <int> vecBBfor = {0};

    int numberFor = 0;
    int intTen = 0;
    for(;;)// цикл вращается столько сколько записано в векторе vecB.
    {
        vecBBfor[vecBBfor.size()-1] = intTen;
        if(intTen == 10)// как только увеличивается до десятока, мы его переносим
        {// Вектор vecBBfor используется так, что максимальная цифра vecBBfor[0], а десяток в последнем.
            for (int var = vecBBfor.size()-1; var > -1; var--)
            {// обходим все цифры и переносим десятки. Зачем нужен цикл ярко понятно на числе 999999
                if(vecBBfor[var] == 10 && var-1 > -1){// если это десяток и не первое число.
                    vecBBfor[var] = 0;
                    vecBBfor[var-1]++;
                }
                if(vecBBfor[var] == 10 && var-1 == -1){// если это десяток и первое число.
                    vecBBfor[var] = 0;
                    vecBBfor.push_front(1);// добавляем новый десяток.
                }
            }
            intTen = 0;
        }
        if(vecBBfor.size() == vecB.size()){// сначала сравниваем размеры векторов
            if(compareVectors(vecBBfor,vecB) == "==")// если вектора равны, сравниваем их уже по качеству.
                break;
        }
        if(vecB.isEmpty() || vecA.isEmpty() || boolClose)
            return;// выходим когда нажата кнопка очистить или закрылось приложение.

        intTen++;
//--------------------------------------------------------------------------------------------
// Здесь и происходит возведение в степень.
        multiply(vecResult, vecA, vecResult);
        emit signalElevate(numberFor++);
//--------------------------------------------------------------------------------------------
    }

    clearZero(vecResult);
}

void Operations::plusWithComma(QVector<int> vecA, QVector<int> vecB, QVector<int> &vecResult)
{
    vecResult.clear();
    clearZero(vecA);
    clearZero(vecB);
    const int commaVecA = findComma(vecA);
    const int commaVecB = findComma(vecB);
    // fillZeroToEndVectors(); гарантирует что числа будут одинаковы по длине.
    fillZeroToEndVectors(vecA, vecB, commaVecA != vecA.size(), commaVecB != vecB.size());
    QVector <int> vecMultiplyTwoNumbers = {0};
    if(commaVecA <= commaVecB){// Если запятая в числе vecA встретилась раньше, тогда на сколько знаков нужно
        // перенести запятую в числе vecA столько и переноситься запятая в числе vecB
        vecMultiplyTwoNumbers = toVectorNumberOfTen(vecA.size() - (commaVecA + 1));
    }
    else{// Если запятая в числе vecB встретилась раньше, тогда на сколько знаков нужно
        // перенести запятую в числе vecB столько и переноситься запятая в числе vecA
        vecMultiplyTwoNumbers = toVectorNumberOfTen(vecB.size() - (commaVecB + 1));
    }
    multiplyWithComma(vecA, vecMultiplyTwoNumbers, vecA);// Умножаем чтоб перенести запятую, после поделим
    multiplyWithComma(vecB, vecMultiplyTwoNumbers, vecB);// Умножаем чтоб перенести запятую, после поделим
    plus(vecA, vecB, vecResult);
//    divide(vecResult, vecMultiplyTwoNumbers, vecResult);// Занимает много времени
    divideNumberOfTen(vecResult, vecMultiplyTwoNumbers, vecResult);// Занимает гараздо гараздо меньше времени
    clearZero(vecResult);
}

void Operations::minusWithComma(QVector<int> vecA, QVector<int> vecB, QVector<int> &vecResult)
{
    vecResult.clear();
    clearZero(vecA);
    clearZero(vecB);
    const int commaVecA = findComma(vecA);
    const int commaVecB = findComma(vecB);
    // fillZeroToEndVectors(); гарантирует что числа будут одинаковы по длине.
    fillZeroToEndVectors(vecA, vecB, commaVecA != vecA.size(), commaVecB != vecB.size());

    QVector <int> vecMultiplyTwoNumbers = {0};
    if(commaVecA <= commaVecB){// Если запятая в числе vecA встретилась раньше, тогда на сколько знаков нужно
        // перенести запятую в числе vecA столько и переноситься запятая в числе vecB
        vecMultiplyTwoNumbers = toVectorNumberOfTen(vecA.size() - (commaVecA + 1));
    }
    else{// Если запятая в числе vecB встретилась раньше, тогда на сколько знаков нужно
        // перенести запятую в числе vecB столько и переноситься запятая в числе vecA
        vecMultiplyTwoNumbers = toVectorNumberOfTen(vecB.size() - (commaVecB + 1));
    }
    multiplyWithComma(vecA, vecMultiplyTwoNumbers, vecA);// Умножаем чтоб перенести запятую, после поделим
    multiplyWithComma(vecB, vecMultiplyTwoNumbers, vecB);// Умножаем чтоб перенести запятую, после поделим
    minus(vecA, vecB, vecResult);
//    divide(vecResult, vecMultiplyTwoNumbers, vecResult);// Занимает много времени
    divideNumberOfTen(vecResult, vecMultiplyTwoNumbers, vecResult);// Занимает гараздо гараздо меньше времени
    clearZero(vecResult);
}

void Operations::multiplyWithComma(QVector<int> vecA, QVector<int> vecB, QVector<int> &vecResult)
{
// Калькулятор на телефоне плохо считает пример 52.6 * 52.369;
// Выравнивание 2 числа по одинаковой длине не нужно, умножение происходит и с разной длины чисел
    vecResult.clear();
    int commaVecA = findComma(vecA);
    int commaVecB = findComma(vecB);
    int moveCommaVecA = vecA.size() - commaVecA;// Вместо умножения перемещаем запятую в конец и записываем
    int moveCommaVecB = vecB.size() - commaVecB;// на сколько переместили, чтоб потом на столько поделить.
    if(commaVecA != vecA.size()){// Если зяпятая есть мы ее удалим
        vecA.remove(commaVecA);
        moveCommaVecA -= 1;// Отнимаем здесь поскольку выше неизвестно было о существовании запятой
    }
    if(commaVecB != vecB.size()){// Если зяпятая есть мы ее удалим
        vecB.remove(commaVecB);
        moveCommaVecB -= 1;// Отнимаем здесь поскольку выше неизвестно было о существовании запятой
    }
    multiply(vecA, vecB, vecResult);// Умножение чисел без запятых
    for (int var = 0; var < moveCommaVecA + moveCommaVecB; ++var) {
        vecResult.push_front(0);// Вставляем нули чтоб не было выхода за пределы вектора
    }
    QVector <int>::iterator iteratorVecResult = vecResult.end() - moveCommaVecA - moveCommaVecB;
    vecResult.insert(iteratorVecResult, -1);// Вставляем обратно запятую
    vecResult.push_front(0);// Вставляем вначало ноль поскольку вставка по итератору может вставить запятую
    // первым элементом. Если запятая не в первом элементе вектора, этот ноль удалиться в clearZero();
    clearZero(vecResult);
}

void Operations::divideWithComma(QVector<int> vecA, QVector<int> vecB, QVector<int> &vecResult)
{
    vecResult.clear();
    clearZero(vecA);
    clearZero(vecB);
    const int commaVecA = findComma(vecA);
    const int commaVecB = findComma(vecB);
    // fillZeroToEndVectors(); гарантирует что числа будут одинаковы по длине.
    fillZeroToEndVectors(vecA, vecB, commaVecA != vecA.size(), commaVecB != vecB.size());

    QVector <int> vecMultiplyTwoNumbers = {0};
    if(commaVecA <= commaVecB){// Если запятая в числе vecA встретилась раньше, тогда на сколько знаков нужно
        // перенести запятую в числе vecA столько и переноситься запятая в числе vecB
        vecMultiplyTwoNumbers = toVectorNumberOfTen(vecA.size() - (commaVecA + 1));
    }
    else{// Если запятая в числе vecB встретилась раньше, тогда на сколько знаков нужно
        // перенести запятую в числе vecB столько и переноситься запятая в числе vecA
        vecMultiplyTwoNumbers = toVectorNumberOfTen(vecB.size() - (commaVecB + 1));
    }
    multiplyWithComma(vecA, vecMultiplyTwoNumbers, vecA);// Умножаем чтоб перенести запятую, после поделим
    multiplyWithComma(vecB, vecMultiplyTwoNumbers, vecB);// Умножаем чтоб перенести запятую, после поделим
    divide(vecA, vecB, vecResult);
    clearZero(vecResult);
}
