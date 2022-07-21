#include "report.h"
#include "ui_report.h"

Report::Report(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Report)
{
    ui->setupUi(this);
}

Report::~Report()
{
    delete ui;
}

void Report::slotDisplaySearchSetHeader(QString item)
{
    ui->labelReportHeader->setText(item);
}

void Report::slotDisplaySearchAddToList(QString item)
{
    ui->listWidgetReport->addItem(item);
}
