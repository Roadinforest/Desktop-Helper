#include "myspline.h"
#include "ui_myspline.h"
#include "tallybook.h"
#include <Qtime>

MySpline::MySpline(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MySpline)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:white");

    connect(ui->QuitSpline,SIGNAL(clicked(bool)),this,SLOT(close()));

    QDateTime Today =QDateTime::currentDateTime();
    QDateTime Yesterday= Today.addDays(-1);
    QString today =Today.toString("yyyy/MM/dd");
    QString today_year =Today.toString("yyyy");
    QString today_month =Today.toString("M");
    QString today_day =Today.toString("d");
    QString yesterday_year =Yesterday.toString("yyyy");
    QString yesterday_month =Yesterday.toString("M");
    QString yesterday_day =Yesterday.toString("d");
    qDebug()<<"today is: "<<today;

    QFile file(Filename1);
    file.open(QIODevice::ReadOnly);
    QDataStream fout(&file);
    if (!fout.atEnd())
    {
        qDebug() << "fout open error!!!" << Qt::endl;
    }

    Node1* pHead = NULL;
    //准备读取数据文件中的头结点
    Node1* Each = new Node1;
    //先在这里声明一个结点

    int i = 0;
    int  lastseven[7]{0};

    int deal;
    Node1* pointer=NULL;
    while (!fout.atEnd())
    {
        fout>>Each;
        if(QString::number(Each->value.GetYear())==today_year
            &&QString::number(Each->value.GetMonth())==today_month
            &&(Each->value.GetDate())==today_day.toInt()
            ){
            if(Each->value.GetCase()==Income){
                deal=Each->value.GetValue();
            }
            else if(Each->value.GetCase()==Outlay){
                deal=-Each->value.GetValue();
            }
            lastseven[6]+=deal;
        }
        else if(QString::number(Each->value.GetYear())==today_year
                 &&QString::number(Each->value.GetMonth())==today_month
                   &&(Each->value.GetDate())==today_day.toInt()-1
                 ){
            if(Each->value.GetCase()==Income){
                deal=Each->value.GetValue();
            }
            else if(Each->value.GetCase()==Outlay){
                deal=-Each->value.GetValue();
            }
            lastseven[5]+=deal;
        }
        else if(QString::number(Each->value.GetYear())==today_year
                 &&QString::number(Each->value.GetMonth())==today_month
                 &&(Each->value.GetDate())==today_day.toInt()-2
                 ){
            if(Each->value.GetCase()==Income){
                deal=Each->value.GetValue();
            }
            else if(Each->value.GetCase()==Outlay){
                deal=-Each->value.GetValue();
            }
            lastseven[4]+=deal;
        }
        else if(QString::number(Each->value.GetYear())==today_year
                 &&QString::number(Each->value.GetMonth())==today_month
                 &&(Each->value.GetDate())==today_day.toInt()-3
                 ){
            if(Each->value.GetCase()==Income){
                deal=Each->value.GetValue();
            }
            else if(Each->value.GetCase()==Outlay){
                deal=-Each->value.GetValue();
            }
            lastseven[3]+=deal;
        }
        else if(QString::number(Each->value.GetYear())==today_year
                 &&QString::number(Each->value.GetMonth())==today_month
                 &&(Each->value.GetDate())==today_day.toInt()-4
                 ){
            if(Each->value.GetCase()==Income){
                deal=Each->value.GetValue();
            }
            else if(Each->value.GetCase()==Outlay){
                deal=-Each->value.GetValue();
            }
            lastseven[2]+=deal;
        }
        else if(QString::number(Each->value.GetYear())==today_year
                 &&QString::number(Each->value.GetMonth())==today_month
                 &&(Each->value.GetDate())==today_day.toInt()-5
                 ){
            if(Each->value.GetCase()==Income){
                deal=Each->value.GetValue();
            }
            else if(Each->value.GetCase()==Outlay){
                deal=-Each->value.GetValue();
            }
            lastseven[1]+=deal;
        }
        else if(QString::number(Each->value.GetYear())==today_year
                 &&QString::number(Each->value.GetMonth())==today_month
                 &&(Each->value.GetDate())==today_day.toInt()-6
                 ){
            if(Each->value.GetCase()==Income){
                deal=Each->value.GetValue();
            }
            else if(Each->value.GetCase()==Outlay){
                deal=-Each->value.GetValue();
            }
            lastseven[0]+=deal;
        }

        Each = new Node1;
        //千万千万注意只可以在结尾处给Each分配动态内存，因为我们的改变操作是在while中进行的
        //若是将上面语句放在第一行（也就是将创建放在读取之前），会将所有数据变成默认值
    }
    for(int i=0;i<7;i++){
        qDebug()<<lastseven[i]<<Qt::endl;
    }

    QLineSeries *lineSeries = new QLineSeries();
        //创建折线系列
        for(int i=0; i<7; i++)

        {

            lineSeries->append(i,lastseven[i]);

        }
        //创建坐标
        QValueAxis *axisX = new QValueAxis;//X轴
        axisX->setRange(0, 10);//设置坐标轴范围
        axisX->setTitleText("日期");//标题
        axisX->setLabelFormat("%.1f"); //标签格式：每个单位保留几位小数
        axisX->setTickCount(1); //主分隔个数：0到10分成20个单位
        axisX->setMinorTickCount(2); //每个单位之间绘制了多少虚网线
        //    axisX->setGridLineVisible(false);

        QValueAxis *axisY = new QValueAxis; //Y 轴
        axisY->setRange(-10000, 10000);
        axisY->setTitleText("value");
        axisY->setLabelFormat("%.2f"); //标签格式
        axisY->setTickCount(1);
        axisY->setMinorTickCount(2);
        //    axisX->setGridLineVisible(false);

    QChartView *chartView = new QChartView(this);
    lineSeries->setName("近一周的账单变化折线图");                  //设置系列名称

    mChart = new QChart();                          //创建图标对象

    mChart->addSeries(lineSeries);                  //向图表中添加系列

    mChart->createDefaultAxes();                       //创建默认的坐标，必须在addSeries之后调用

    mChart->setTheme(QChart::ChartThemeDark);           //设置图标主题

    mChart->setTitle("一周账单");                       //设置图标名称

    mChart->legend()->hide();                          //隐藏图例，也就是不显示系列名称了

    chartView->setChart(mChart);                    //向chartView中添加图标

    chartView->resize(QSize(500,300));              //重新设置chartView的大小

    chartView->setRenderHints(QPainter::Antialiasing);//消除边缘，看起来平滑一些

    ui->horizontalLayout->addWidget(chartView);     //把chartView放到水平布局中（在ui中拖一个水平布局）


}

MySpline::~MySpline()
{
    delete ui;
}
