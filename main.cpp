#include "mainwindow.h"
#include <QApplication>

// Можно доделать голосовой коментарий вводимых цифр. Это вроде не так сложно (цифр 10).
// доделать корень квадратный
// Можно доделать чтобы вставлять примеры в ui->textEditMain



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

