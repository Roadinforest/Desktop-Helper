#include "mainwindow.h"
#include "tallybook.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

        MainWindow w;
        w.show();

//    Bill one(1,1,1,1,"NULL",1);
//    Bill two(2,3,5,2,"NULL",0);//value year month date note case
//    Node1 second{two,nullptr};
//    Node1 first{one,&second};
//    qDebug()<<"Start";
//    SaveList1(&first);
//    qDebug()<<"End";
//    ShowList1(BillFetch());
    //  ShowList1(BillFetch());

    return a.exec();
}
