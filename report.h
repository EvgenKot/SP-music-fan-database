#ifndef REPORT_H
#define REPORT_H

#include <QDialog>

namespace Ui {
class Report;
}

class Report : public QDialog
{
    Q_OBJECT

public:
    explicit Report(QWidget *parent = 0);
    ~Report();

private:
    Ui::Report *ui;

public slots:
    void slotDisplaySearchSetHeader(QString item);
    void slotDisplaySearchAddToList(QString item);
};

#endif // REPORT_H
