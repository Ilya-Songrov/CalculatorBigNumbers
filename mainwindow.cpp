
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QPainter"
#include "QPalette"
#include "QDialog"
#include "QScrollArea"
#include "QCheckBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    vecA(0),
    vecB(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupFront();
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupFront()
{

    this->setWindowIconText("Calculator Big Numbers");
    this->setWindowTitle("Calculator Big Numbers");
    this->setFixedSize(362,543);

    qApp->setStyleSheet(
                "QWidget {"
                "background-color: #a6a6f7;"
                "}"

            "QPushButton { "
            "background-color: #7dbcbc; "
            "border-width: 2px; "
            "border-color: #537d7d; "
            "border-style: solid; "
            "border-radius: 10; "
            "padding: 3px; "
            "min-width: 9ex;"
            " min-height: 2.5ex;"
            "}"
                        );
    ui->pushButton_Elevate->setIcon(QIcon(":/Picture/Elevate2.png"));
    ui->pushButton_Elevate->setIconSize(ui->pushButton_Elevate->size());
    ui->pushButton_remove->setIcon(QIcon(":/Picture/Remove2.png"));/* доделать в конце */
        ui->pushButton_remove->setIconSize(ui->pushButton_remove->size());
    ui->textEditMain->setPlaceholderText("0");
    ui->textEditMain->setTextInteractionFlags(Qt::TextSelectableByMouse);
        ui->label_operation->setText(QString::number(0) + "<sup> " + QString::number(0) + "</sup>");
        ui->label_operation->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->label_nameNumber->setText("0");
    ui->label_nameNumber->setTextInteractionFlags(Qt::TextSelectableByMouse);
        ui->label_information->setText(labelInformationText(-1,false));
        ui->label_information->setTextInteractionFlags(Qt::TextSelectableByMouse);
}

void MainWindow::setupConnections()
{


    connect(ui->pushButton_0, &QPushButton::clicked, this, &MainWindow::slotClickedOnNumbers);
    connect(ui->pushButton_1, &QPushButton::clicked, this, &MainWindow::slotClickedOnNumbers);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::slotClickedOnNumbers);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::slotClickedOnNumbers);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::slotClickedOnNumbers);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::slotClickedOnNumbers);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::slotClickedOnNumbers);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &MainWindow::slotClickedOnNumbers);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &MainWindow::slotClickedOnNumbers);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::slotClickedOnNumbers);


    connect(ui->pushButton_plus, &QPushButton::clicked, this, &MainWindow::slotOnPushButtonPlusMinus);
    connect(ui->pushButton_minus, &QPushButton::clicked, this, &MainWindow::slotOnPushButtonPlusMinus);
    connect(ui->pushButton_multiply, &QPushButton::clicked, this, &MainWindow::slotOnPushButtonMultiplyDivide);
    connect(ui->pushButton_divide, &QPushButton::clicked, this, &MainWindow::slotOnPushButtonMultiplyDivide);
    connect(ui->pushButton_Elevate, &QPushButton::clicked, this, &MainWindow::slotOnPushButton_Elevate);
    connect(ui->pushButton_comma, &QPushButton::clicked, this, &MainWindow::slotOnPushButton_comma);
    connect(ui->pushButton_equally, &QPushButton::clicked, this, &MainWindow::slotOnPushButton_equally);
    connect(ui->pushButton_remove, &QPushButton::clicked, this, &MainWindow::slotOnPushButton_remove);
    connect(ui->pushButton_clear, &QPushButton::clicked, this, &MainWindow::slotOnPushButton_clear);


    connect(this, &MainWindow::signalClose, &operations, &Operations::slotClose);
    connect(&operations, &Operations::signalElevate, this, &MainWindow::slotShowElevate);
//    connect(ui->textEditMain, &QTextEdit::, this, &MainWindow::slotShowElevate);
}

void MainWindow::slotClickedOnNumbers()
{
    QRegExp rx("pushButton_(.+)");
    QString str = "";
    if(rx.indexIn(sender()->objectName()) == -1 || boolForProcessEvents == true){
        return;// Выходим потому что не нашлось соотвецтвия или потому что где-то выполняется цикл,
        // в которой происходит какая-то операция.
    }
    rx.setMinimal(true);
    if(rx.cap(1).indexOf(QRegExp("\\d")) != -1){
        if(strOperation.isEmpty()){
            vecA.push_back(QString(rx.cap(1)).toInt());
        }
        else{
            vecB.push_back(QString(rx.cap(1)).toInt());
        }
        str = rx.cap(1);
    }

    if(strOperation == "<sup>n</sup>"){// сюда входим после того как была введена операция "n"
        // и начались вводиться цифры степени.
        if(vecB.size() == 1)// Сюда входим
        {// для того чтобы заменить символ (n) который обозначал возведение в степень цифрой степени.
            QString strTextEdit = ui->textEditMain->toPlainText().remove(QRegExp("n")) + "<sup>" + str;
            str = strTextEdit;
            ui->textEditMain->selectAll();
        }
        else
        {// Сюда входим если вписывается двухзначная или больше степень.
            str.insert(0,"</sup><sup>"); // закрываем предыдущий тег и открываем новый для тока что введенного числа
        }
    }
    showInformations(str);
}


void MainWindow::slotOnPushButton_equally()
{
    if(strOperation == "+"){
        operationPlus(vecA, vecB);
    }
    if(strOperation == "-"){
        operationMinus(vecA, vecB);
    }
    if(strOperation == "*"){
        operationMultiply(vecA, vecB);
    }
    if(strOperation == "÷"){
        operationDivide(vecA, vecB);
    }
    if(strOperation == "<sup>n</sup>"){
        operationElevate(vecA, vecB);
    }
}

void MainWindow::slotOnPushButtonMultiplyDivide()
{
    if(vecA.isEmpty()){ // не идем дальше если нажата сначала какая-то операция, когда еще цифр никаких нет
        strOperation = "";
        return;
    }
    QRegExp rx("pushButton_(.+)");
    QString str = "";
    if(rx.indexIn(sender()->objectName()) == -1 || boolForProcessEvents == true){
        return;// Выходим потому что не нашлось соотвецтвия или потому что где-то выполняется цикл,
        // в которой происходит какая-то операция.
    }
    rx.setMinimal(true);

    if(boolComaVecA || boolComaVecB){// Сюда входим для предотвращения нажатия операции после запятой.
        if(vecA[vecA.size()-1] == -1){
            return;
        }
        else if(boolComaVecB && vecB[vecB.size()-1] == -1){
            return;
        }
    }
    if(!strOperation.isEmpty() && !vecB.isEmpty()){//Если нажата вместо равно какая-то операция,
            slotOnPushButton_equally();// тогда сначала все посчитается, а потом уже продолжим.
            strOperation.clear();
    }
    if(!strOperation.isEmpty() && vecB.isEmpty()){// Если операции вводится повторно,
        ui->textEditMain->undo();// нужно удалить предыдущию операцию и ввести новую
    }
    if(rx.cap(1) == "multiply"){
        strOperation = "*";
        str = "&nbsp;*&nbsp;";
    }
    if(rx.cap(1) == "divide"){
        strOperation = "÷";
        str = "&nbsp;÷&nbsp;";
    }

    showInformations(str);
}

void MainWindow::slotOnPushButton_Elevate()
{
    if(vecA.isEmpty()){ // не идем дальше если нажата сначала какая-то операция, когда еще цифр никаких нет
        strOperation = "";
        return;
    }
    QRegExp rx("pushButton_(.+)");
    QString str = "";
    if(rx.indexIn(sender()->objectName()) == -1 || boolForProcessEvents == true){
        return;// Выходим потому что не нашлось соотвецтвия или потому что где-то выполняется цикл,
        // в которой происходит какая-то операция.
    }
    rx.setMinimal(true);

    if(!strOperation.isEmpty() && !vecB.isEmpty()){//Если нажата вместо равно какая-то операция,
            slotOnPushButton_equally();// тогда сначала все посчитается, а потом уже продолжим.
            strOperation.clear();
    }
    if(!strOperation.isEmpty() && vecB.isEmpty()){// Если операции вводится повторно,
        ui->textEditMain->undo();// нужно удалить предыдущию операцию и ввести новую
    }

    strOperation = "<sup>n</sup>";
    str = "<sup>n";

    showInformations(str);
}

void MainWindow::slotOnPushButtonPlusMinus()
{
    QRegExp rx("pushButton_(.+)");
    QString str = "";
    if(rx.indexIn(sender()->objectName()) == -1 || boolForProcessEvents == true){
        return;// Выходим потому что не нашлось соотвецтвия или потому что где-то выполняется цикл,
        // в которой происходит какая-то операция.
    }
    rx.setMinimal(true);
    if(boolComaVecA || boolComaVecB){// Сюда входим для предотвращения нажатия операции после запятой.
        if(vecA[vecA.size()-1] == -1){
            return;
        }
        else if(boolComaVecB && vecB[vecB.size()-1] == -1){
            return;
        }
    }
    if(!strOperation.isEmpty() && !vecB.isEmpty()){//Если нажата вместо равно какая-то операция,
            slotOnPushButton_equally();// тогда сначала все посчитается, а потом уже продолжим.
            strOperation.clear();
    }
    if(!strOperation.isEmpty() && vecB.isEmpty()){// Если операции вводится повторно,
        ui->textEditMain->undo();// нужно удалить предыдущию операцию и ввести новую
    }
    if(rx.cap(1) == "plus"){
        strOperation = "+";
        str = "&nbsp;+&nbsp;";
    }
    if(rx.cap(1) == "minus"){
        strOperation = "-";
        str = "&nbsp;-&nbsp;";
    }
        if(vecA.isEmpty()){// Если минус выступает не как операция а как указание что число отрицательное или
            if(!strPositiveNegativeVecA.isEmpty()){// положительное.
                ui->textEditMain->undo();// Тогда нужно удалить предыдущее указание и ввести ноый знак.
            }
            strPositiveNegativeVecA = strOperation;
            strOperation.clear();
        }
        showInformations(str);
}

void MainWindow::slotOnPushButton_comma()
{
    if(vecA.isEmpty() || strOperation == "<sup>n</sup>"){
        return;// запятую не ставим и не идем дальше когда еще цифр нет и когда введена операция степени
    }
    if(!strOperation.isEmpty() && vecB.isEmpty()){
        return;// Выходим когда введена какая-то операция и сразу после нее нельзя ставить запятую.
    }
    QRegExp rx("pushButton_(.+)");
    QString str = "";
    if(rx.indexIn(sender()->objectName()) == -1 || boolForProcessEvents == true){
        return;// Выходим потому что не нашлось соотвецтвия или потому что где-то выполняется цикл,
        // в которой происходит какая-то операция.
    }
    rx.setMinimal(true);

    if(!boolComaVecA && vecB.isEmpty()){// зпятую можно ставить только один раз. В одном из чисел.
        str = ",";
        vecA.push_back(-1);
        boolComaVecA = true; //
    }
    if(!boolComaVecB && !vecB.isEmpty()){// зпятую можно ставить только один раз. В одном из чисел.
        str = ",";
        vecB.push_back(-1);
        boolComaVecB = true; //
    }
    showInformations(str);
}

void MainWindow::slotOnPushButton_remove()
{
    if(vecA.isEmpty()){
        strPositiveNegativeVecA = "";
        boolPositiveResult = true;
        ui->textEditMain->clear(); // Для того чтобы не удалить знак равно в тех случаях когда он остается.
    }
    if(vecB.isEmpty() && strOperation.isEmpty() && !vecA.isEmpty()){
        if(vecA[vecA.size()-1] == -1){
            boolComaVecA = false;
        }
        vecA.pop_back();
    }
    if(vecB.isEmpty() && !strOperation.isEmpty()){
        strOperation.clear();
    }
    if(!vecB.isEmpty()){
        if(vecB[vecB.size()-1] == -1){
            boolComaVecB = false;
        }
        vecB.pop_back();
    }

    ui->textEditMain->undo();
    showInformations("");
}

void MainWindow::slotOnPushButton_clear()
{
    vecA.clear();
    vecB.clear();
    strOperation = "";
    boolComaVecA = false; // по дефолту число без плавающей точки
    boolComaVecB = false; // по дефолту число без плавающей точки
    boolForProcessEvents = false;
    boolPositiveResult = true;
    strPositiveNegativeVecA = "";
    boolClose = false;
    ui->textEditMain->setHtml("");
    ui->textEditMain->setPlaceholderText("0");
    ui->label_operation->setText(QString::number(0) + "<sup> " + QString::number(0) + " </sup>");
    ui->label_nameNumber->setText("0");
    ui->label_information->setText(labelInformationText(-1,false));
}

void MainWindow::slotShowElevate(int numeralElevate)
{
    ui->label_operation->setText("N<sup>"+QString::number(numeralElevate)+"</sup>");
    boolForProcessEvents = true;
    QApplication::processEvents();
}

void MainWindow::showResult(const QVector<int> &vec)
{
    ui->textEditMain->clear();// Обнуляет UndoRedo стек, чтобы мы не двигались по истории старых числе.
    QString strNumber = boolPositiveResult ? "=&nbsp;" : "=&nbsp;-&nbsp;";
    int threeSteps = fromStepWriteSeparator(vec);
    int stopNameInfo = 0;// После зяпятой информирование прекращается

    for (int var = 0; var < vec.size(); ++var)
    {
        if(threeSteps >= 3){// после прохождения 3-х чисел, вставляем разделитель.
            if(var != 0 && vec[var] != -1){
                // Если число из трех цифр, тогда перед ним не нужно ставить разделитель
                strNumber = "'";
            }
            threeSteps = 0;
        }
        // водим цифры, и если встречаем -1, тогда вместо -1 должна стоять запятая. -1 может быть только вначале
        strNumber += (vec[var] == -1) ?  "," : QString::number(vec[var]);// числа, его не заменяем.
        ui->textEditMain->insertHtml(strNumber);
        ui->textEditMain->moveCursor(QTextCursor::End);
        ui->label_operation->setText("&nbsp;≈&nbsp;" + QString::number(vec[0])+ "&nbsp;*&nbsp;" +
                        "10<sup>" + QString::number(stopNameInfo == 0 ? var : stopNameInfo) + "</sup>");
        ui->label_nameNumber->setText(labelNameNumber(stopNameInfo == 0 ? var : stopNameInfo));
        ui->label_information->setText(labelInformation(stopNameInfo == 0 ? var : stopNameInfo));
        boolForProcessEvents = true;
        QApplication::processEvents();
        if(vec[var] == -1){/*запятую -1, нельзя считать за число */ // Поэтому если встерчается запятая -1, это озна-
            threeSteps = -1;//-чает, что отсчет нужно обнулить. Ставим -1 не 0 поскольку запятую, нельзя считать за число.
            boolComaVecA = true;
            stopNameInfo = var;// Информация высвечивается только до запятой
        }
        threeSteps++;
        strNumber = "";
        if(vecB.isEmpty() || vecA.isEmpty() || boolClose)
            break;// выходим когда нажата кнопка очистить или закрылось приложение.
    }
    vecA = vec;// Результат становиться первым числом, это означает дальше можно вводить уже второе число
    boolComaVecA = operations.findComma(vecA) != vecA.size(); // узнаем есть ли запятая
    refreshFlags(boolPositiveResult, boolPositiveResult, boolComaVecA, false, true, false, false, true);
}

void MainWindow::refreshFlags(bool positiveVecA, bool positiveResult, bool comaVecA, bool comaVecB,
            bool strOperationClear, bool forProcessEvents, bool vecAClear, bool vecBClear, bool close)
{
    strPositiveNegativeVecA = positiveVecA ? "" : "-";
    boolPositiveResult = positiveResult;
    boolComaVecA = comaVecA;
    boolComaVecB = comaVecB;
    strOperation = strOperationClear ? "" : strOperation;
    boolForProcessEvents = forProcessEvents;
    if(vecAClear){
        vecA.clear();
    }
    if(vecBClear){
        vecB.clear();
    }
    boolClose = close;
}


void MainWindow::showInformations(const QString str)
{
    ui->textEditMain->insertHtml(str);
    ui->textEditMain->moveCursor(QTextCursor::End);

    ui->label_operation->setText(labelOperation(vecB.isEmpty() ? vecA.size() : vecB.size()));

    ui->label_nameNumber->setText(labelNameNumber(vecB.isEmpty() ? vecA.size() : vecB.size()));

    ui->label_information->setText(labelInformation(vecB.isEmpty() ? vecA.size() : vecB.size()));
}

int MainWindow::fromStepWriteSeparator(const QVector <int> &vec)
{// Функция нужна для того чтобы понять с какого числа выставлять разделитель по 3. Это достигаем с помощью
 // прокрутки всего вектора. Сколько цифр в конце останеться без разделителя столько и нужно будет пропустить
 // при выводе результата. Способ какой-то странный, но сработает)
    int threeSteps = 0;
    for (int var = vec.size()-1; var > -1; var--) {
        if(vec[var] == -1){/*запятую -1, нельзя считать за число */ // Поэтому если встерчается запятая -1,
            threeSteps = -1;// отсчет нужно обнулить.
        }
        threeSteps++;
        if(threeSteps == 3){
            threeSteps = 0;
        }
    }
    return 3 - threeSteps;
}

QString MainWindow::labelOperation(int number)
{
    QString str = (number == 0 ? "0" : "10"); // Если векторо пустой, уходим в дефолт
    return str + "<sup> " + QString::number(vecA.isEmpty() ? 0 : vecA.size()-1) + "</sup>&nbsp;" +
            strOperation + "&nbsp;" +
           (vecB.isEmpty() ? "" : "10<sup>" + QString::number(vecB.size()-1) + "</sup>");
}

QString MainWindow::labelNameNumber(int number)
{

    if(number == 0) // Если векторо пустой, уходим в дефолт
        return "0";
    if(number == 0 || number == 1)
        return "Цыфра";
    if(number == 2)
        return "Десяток";
    if(number == 3)
        return "Сотня";
    if(number >= 4 && number <= 6)
        return "Тысяча";
    if(number >= 10 && number <= 12) // к этoму названию не подходит окончание (иллион)
        return "Миллиард";
    if(number >= 100 && number <= 123) // к этoму названию не подходит окончание (иллион)
        return "Гугол";

    QVector <QString> vecStr = {"М","Миллиард","Тр","Квадр","Квинт","Секст","Септ","Окт","Нон","Дец","Ундец","Додец",
        "Тредец","Кваттуордец","Квиндец","Седец","Септдец","Дуодевигинт","Ундевигинт", "Вигинт","Анвигинт",
        "Дуовигинт","Тревигинт","Кватторвигинт","Квинвигинт","Секствигинт","Септемвигинт","Октовигинт","Новемвигинт",
        "Тригинт","Антригинт"};

    if(number > 6 && number < 100) // здесь обрабатываются цифры от Миллион до Гугла
    {
        int threeSteps = 1;
        int numVec = 0;
        for (int var = 7; var <= number; ++var)
        {
//            qDebug() << "Text " << number << numVec << var <<endl;
            if(var >= number && number <= var+2)
                return vecStr[numVec] + "иллион";

            if(threeSteps == 3)
            {
                threeSteps = 0; // обнуляется к нулю потомучто ниже сразу есть threeSteps++
                numVec++;
            }
            threeSteps++;
        }
    }

//--------------------------------------------------------------------------------------------------------
// здесь обрабатываются цифры после Гугла

    QVector <QString> vecStr2 = {"Квадрагинти","Квинквагинти","Секстагинти","Септуагинти","Октогинти","Нонагинти",
        "Центи","Центуни","Центдуо","Центтри","Центквадри","Центтретригинти","Дуценти","Треценти","Квадрингенти",
        "Квингенти","Сесценти","Септингенти","Окстингенти","Нонгенти","Милли","Дуомилиа","Тремиллиа","Милиамилиаи",
        "Дуомилиамилиаи","Гуголплекс"};

    QVector <long int> vecCondition = {123,152,183,213,243,273,303,306,309,312,315,402,603,903,1203,1503,1803,
                                 2103,2403,2703,3003,6003,9003,30000003,60000003,1000000000};

    for (int var = 0; var < vecCondition.size(); ++var)
    {
        if(var+1 == vecCondition.size())
            return "Гуголплекс";
        if(number >= vecCondition[var] && var<vecCondition.size() ? number<=vecCondition[var+1] : number < 60000003)
            return vecStr2[var] + "ллион";
    }

    return "";
}

QString MainWindow::labelInformation(int number)
{
    if(number == 0)
        return labelInformationText(-1, false);
    if(number == 1)// Если в векторе одно число заходим сюда. На каждую цифру есть информация.
        return labelInformationText(vecB.isEmpty() ? vecA[0] : vecB[0], false);

    if(number == 2)
        return labelInformationText(0, true);
    if(number == 3)
        return labelInformationText(1, true);
    if(number >= 4 && number <= 6)
        return labelInformationText(2, true);
    if(number >= 10 && number <= 12)
        return labelInformationText(4, true);
    if(number >= 100 && number <= 123)
        return labelInformationText(34, true);

    if(number > 6 && number < 100) // здесь обрабатываются цифры от Миллион до Гугла
    {
        int threeSteps = 1;
        int numVec = 0;
        for (int var = 7; var <= number; ++var)
        {
//            qDebug() << "Text2 " << number << numVec << var <<endl;
            if(var >= number && number <= var+2)
                return labelInformationText(numVec+3, true);

            if(threeSteps == 3)
            {
                threeSteps = 0; // обнуляется к нулю потомучто ниже сразу есть threeSteps++
                numVec++;
            }
            threeSteps++;
        }
    }

//--------------------------------------------------------------------------------------------------------
// здесь обрабатываются цифры после Гугла

    return labelInformationText(111, false); // Этому числу сложно найти применения в реальном мире."
}

void MainWindow::operationPlus(QVector<int> &vecAA, QVector<int> &vecBB)
{
    QVector <int> vecResult;

    if(!boolComaVecA && !boolComaVecB && strPositiveNegativeVecA.isEmpty()){
        // Если запятых нет и vecA положительное
        QString strCompare = operations.compareVectors(vecAA, vecBB);
        if(strCompare == ">" || strCompare == "=="){
            operations.plus(vecAA, vecBB, vecResult);
            refreshFlags(true, true, false, false, true);
        }
        else{// Число А меньше числа B, и в конечном итоге нужно получить положительное число.
            operations.plus(vecAA, vecBB, vecResult);
            refreshFlags(true, true, false, false, true);
        }
    }
    else if(!boolComaVecA && !boolComaVecB && strPositiveNegativeVecA == "-"){
        // Если заяпятых нет и первое число с минусом а операция плюс.
        QString strCompare = operations.compareVectors(vecAA, vecBB);
        if(strCompare == ">"){// Елси первое число больше а оно отрицательное. Значит отнимаем числа
            // и полученный результат оставляем отрицательным.
            operations.minus(vecAA, vecBB, vecResult);
            refreshFlags(false, false, false, false, true);
        }
        else if(strCompare == "<"){// Елси первое число меньше а оно отрицательное. Значит отнимаем числа
            // наоборот и полученный результат оставляем положительным.
            operations.minus(vecBB, vecAA, vecResult);
            refreshFlags(true, true, false, false, true);
        }
        else if(strCompare == "=="){// Если числа противоположны (-9 + 9) равно ноль
            vecResult.clear();
            vecResult.push_back(0);
            refreshFlags(true, true, false, false, true);
        }
    }
    else if((boolComaVecA || boolComaVecB) && strPositiveNegativeVecA.isEmpty()){
        // Если запятые есть и vecA положительное
        QString strCompareComma = operations.compareVectorsWithComma(vecAA, vecBB, boolComaVecA, boolComaVecB);
        if(strCompareComma == ">" || strCompareComma == "=="){
            operations.plusWithComma(vecAA, vecBB, vecResult);
            bool boolComa = operations.findComma(vecResult) != vecResult.size(); // узнаем есть ли запятая
            refreshFlags(true, true, boolComa, false, true);
        }
        else{// Число А меньше числа B, и в конечном итоге нужно получить положительное число.
            operations.plusWithComma(vecAA, vecBB, vecResult);
            bool boolComa = operations.findComma(vecResult) != vecResult.size(); // узнаем есть ли запятая
            refreshFlags(true, true, boolComa, false, true);

        }
    }
    else if((boolComaVecA || boolComaVecB) && strPositiveNegativeVecA == "-"){
        // Если заяпятые есть и первое число с минусом а операция плюс.
        QString strCompareComma = operations.compareVectorsWithComma(vecAA, vecBB, boolComaVecA, boolComaVecB);
        if(strCompareComma == ">"){// Елси первое число больше а оно отрицательное. Значит отнимаем числа
            // и полученный результат оставляем отрицательным.
            operations.minusWithComma(vecAA, vecBB, vecResult);
            bool boolComa = operations.findComma(vecResult) != vecResult.size(); // узнаем есть ли запятая
            refreshFlags(false, false, boolComa, false, true);
        }
        else if(strCompareComma == "<"){// Елси первое число меньше а оно отрицательное. Значит отнимаем числа
            // наоборот и полученный результат оставляем положительным.
            operations.minusWithComma(vecBB, vecAA, vecResult);
            bool boolComa = operations.findComma(vecResult) != vecResult.size(); // узнаем есть ли запятая
            refreshFlags(true, true, boolComa, false, true);
        }
        else if(strCompareComma == "=="){// Если числа противоположны (-9.4 + 9.4) равно ноль
            vecResult.clear();
            vecResult.push_back(0);
            refreshFlags(true, true, false, false, true);
        }
    }

    operations.clearZero(vecResult); // удаляется перед результатным числом ноль, если он есть.
    showResult(vecResult);
}

void MainWindow::operationMinus(QVector <int> &vecAA, QVector <int> &vecBB)
{
    QVector <int> vecResult;

    if(!boolComaVecA && !boolComaVecB && strPositiveNegativeVecA.isEmpty()){
        // Если запятых нет и vecA положительное
        QString strCompare = operations.compareVectors(vecAA, vecBB);
        if(strCompare == ">" || strCompare == "=="){
            operations.minus(vecAA, vecBB, vecResult);
            refreshFlags(true, true, false, false, true);
        }
        else{// Число А меньше числа B, и в конечном итоге нужно получить отрицательное число.
            operations.minus(vecBB, vecAA, vecResult);
            refreshFlags(false, false, false, false, true);
        }
    }
    else if(!boolComaVecA && !boolComaVecB && strPositiveNegativeVecA == "-"){
        // Если заяпятых нет и первое число с минусом и операция минус. Значит прибавляем числа
        // и полученный результат оставляем отрицательным.
        operations.plus(vecAA, vecBB, vecResult);
        refreshFlags(false, false, false, false, true);
    }
    else if((boolComaVecA || boolComaVecB) && strPositiveNegativeVecA.isEmpty()){
        // Если запятые есть и vecA положительное
        QString strCompareComma = operations.compareVectorsWithComma(vecAA, vecBB, boolComaVecA, boolComaVecB);
        if(strCompareComma == ">" || strCompareComma == "=="){
            operations.minusWithComma(vecAA, vecBB, vecResult);
            bool boolComa = operations.findComma(vecResult) != vecResult.size(); // узнаем есть ли запятая
            refreshFlags(true, true, boolComa, false, true);
        }
        else{// Число А меньше числа B, и в конечном итоге нужно получить отрицательное число.
            operations.minusWithComma(vecBB, vecAA, vecResult);
            bool boolComa = operations.findComma(vecResult) != vecResult.size(); // узнаем есть ли запятая
            refreshFlags(false, false, boolComa, false, true);

        }
    }
    else if((boolComaVecA || boolComaVecB) && strPositiveNegativeVecA == "-"){
        // Если заяпятые есть и первое число с минусом и операция минус. Значит прибавляем числа
        // и полученный результат оставляем отрицательным.
        operations.plusWithComma(vecAA, vecBB, vecResult);
        bool boolComa = operations.findComma(vecResult) != vecResult.size(); // узнаем есть ли запятая
        refreshFlags(false, false, boolComa, false, true);
    }

    operations.clearZero(vecResult); // удаляется перед результатным числом ноль, если он есть.
    showResult(vecResult);
}


void MainWindow::operationMultiply(QVector <int> &vecAA, QVector <int> &vecBB)
{
    QVector <int> vecResult = {0};

    if(!boolComaVecA && !boolComaVecB){
        // Если запятых нет и vecA положительное или отрицательное. Сравнивать числа не нужно. (6*5 = 5*6)
        operations.multiply(vecAA, vecBB, vecResult);
        if(strPositiveNegativeVecA.isEmpty()){
            refreshFlags(true, true, false, false, true);// Обозначаем результат как положительный
        }
        else{
            refreshFlags(false, false, false, false, true);// Обозначаем результат как отрицательный
        }
    }
    else if(boolComaVecA || boolComaVecB){
        // Если запятые есть и vecA положительное или отрицательное
        operations.multiplyWithComma(vecAA, vecBB, vecResult);
        bool boolComa = operations.findComma(vecResult) != vecResult.size(); // узнаем есть ли запятая
        if(strPositiveNegativeVecA.isEmpty()){
            refreshFlags(true, true, boolComa, false, true);// Обозначаем результат как положительный
        }
        else{
            refreshFlags(false, false, boolComa, false, true);// Обозначаем результат как отрицательный
        }
    }

    operations.clearZero(vecResult); // удаляется перед результатным числом ноль, если он есть.
    showResult(vecResult);
}

void MainWindow::operationDivide(QVector <int> &vecAA, QVector <int> &vecBB)
{
    // vecAA - делимое  // vecBB - делитель
    QVector <int> vecResult;

    if(!boolComaVecA && !boolComaVecB){
        // Если запятых нет и vecA положительное или отрицательное. Сравнивать числа не нужно.
        operations.divide(vecAA, vecBB, vecResult);
        bool boolComa = operations.findComma(vecResult) != vecResult.size(); // узнаем есть ли запятая
        if(strPositiveNegativeVecA.isEmpty()){
            refreshFlags(true, true, boolComa, false, true);// Обозначаем результат как положительный
        }
        else{
            refreshFlags(false, false, boolComa, false, true);// Обозначаем результат как отрицательный
        }
    }
    else if(boolComaVecA || boolComaVecB){
        // Если запятые есть и vecA положительное или отрицательное
        operations.divideWithComma(vecAA, vecBB, vecResult);
        bool boolComa = operations.findComma(vecResult) != vecResult.size(); // узнаем есть ли запятая
        if(strPositiveNegativeVecA.isEmpty()){
            refreshFlags(true, true, boolComa, false, true);// Обозначаем результат как положительный
        }
        else{
            refreshFlags(false, false, boolComa, false, true);// Обозначаем результат как отрицательный
        }
    }

    showResult(vecResult);
}


void MainWindow::operationElevate(QVector<int> &vecAA, QVector<int> &vecBB)
{
    QVector <int> vecResult = {1};

    if(!boolComaVecA && !boolComaVecB && strPositiveNegativeVecA.isEmpty()){
        // Если запятых нет и vecA положительное
        operations.elevate(vecAA, vecBB, vecResult);
        if(vecB.isEmpty() || vecA.isEmpty() || boolClose){// Выходим если нажата кнопка стерень, удалить
            return;
        }
    }
    else{
        refreshFlags(true, true, false, false, true, false, true, true, false);
        ui->textEditMain->clear();
        ui->textEditMain->setText("Cори, но пока возводить можно положительные числа и без точки запятой."
                                  " Жмите кнопку стереть и посчитайте что-нибудь другое :)");
//        ui->textEditMain->selectAll();
        return;
    }

    showResult(vecResult);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    boolClose = true;
    emit signalClose();
    QWidget::closeEvent(event);
}
