#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    about = new About(this);
    about->show();
}

void MainWindow::on_pushButtonDisplaySearchByAuthor_clicked()
{
    report = new Report(this);
    report->show();
}

void MainWindow::on_pushButtonDisplaySearchBySong_clicked()
{
    report = new Report(this);
    report->show();
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString fileNameInput;
    fileNameInput = QFileDialog::getOpenFileName();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Open", "Do you really want to open this file? Unsaved data will be lost.", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        qDebug() << "Opening" << fileNameInput << "...";
        ui->statusBar->showMessage("Opening \"" + fileNameInput + "\"...");

        //------------------------------------------------

        qDebug() << "Opening completed.";
        ui->statusBar->showMessage("Opening completed");
    }
    else
    {
        qDebug() << "Opening aborted.";
        ui->statusBar->showMessage("Opening aborted");
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileNameOutput;
    fileNameOutput = QFileDialog::getOpenFileName();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Save as", "Do you really want to save it? If this file exists, it will be overwritten.", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        ui->statusBar->showMessage("Saving as \"" + fileNameOutput + "\"...");
        qDebug() << "Saving as " << fileNameOutput;

        //----------------------------------------------

        ui->statusBar->showMessage("Saved");
        qDebug() << "Saved";
    }
    else
    {
        qDebug() << "Saving aborted";
        ui->statusBar->showMessage("Saving aborted");
    }
}

void MainWindow::on_actionSave_triggered()
{
    qDebug() << "Saving not ready";
}

void MainWindow::on_actionExit_triggered()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Do you really want to Quit? Unsaved data will be lost.", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        ui->statusBar->showMessage("Quit");
        qDebug() << "Quit";
        QApplication::quit();
    }
    else
    {
        qDebug() << "Quit aborted";
        ui->statusBar->showMessage("Quit aborted");
    }
}
