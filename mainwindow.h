#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "about.h"
#include "report.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAbout_triggered();

    void on_pushButtonDisplaySearchByAuthor_clicked();

    void on_pushButtonDisplaySearchBySong_clicked();

    void on_actionOpen_File_triggered();

    void on_actionSave_As_triggered();

    void on_actionExit_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    About *about;
    Report *report;
};

#endif // MAINWINDOW_H
