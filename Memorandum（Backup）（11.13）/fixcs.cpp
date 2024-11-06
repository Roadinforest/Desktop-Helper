#include "fixcs.h"
#include "ui_fixcs.h"

fixcs::fixcs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fixcs)
{
    ui->setupUi(this);
}

fixcs::~fixcs()
{
    delete ui;
}
