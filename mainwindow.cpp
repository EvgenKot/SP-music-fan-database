#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include <vector>
#include <fstream>

#include <nlohmann/json.hpp>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "process.h"

List<Author> AuthorList;
Element<Author> *at;
Author currentAuthor;
int AuthorId;
std::string AuthorName;
std::vector<int> AuthorListIdSong;


List<Disk> DiskList;
Element<Disk> *dt;
Disk currentDisk;
int DiskId;
std::string DiskName;
std::vector<int> DiskListIdSong;

List<Song> SongList;
Element<Song> *st;
Song currentSong;
int SongId;
std::string SongName;
std::vector<int> ListIdAuthor;
std::vector<int> ListIdDisk;

QString fileNameInput;
QString fileNameOutput;
QString fileNameDefaultOutput;

bool AuthorEdited = false;
bool DiskEdited = false;
bool SongEdited = false;

void MainWindow::refresh()
{
    ui->listWidgetAuthorGoTo->clear();
    ui->comboBoxSongAddAuthor->clear();
    ui->comboBoxDisplaySearchByAuthor->clear();

    ui->listWidgetDiskGoTo->clear();
    ui->comboBoxSongAddDisk->clear();

    ui->comboBoxDisplaySearchBySong->clear();
    ui->listWidgetSongGoTo->clear();

    at = AuthorList.GetFirst();
    while (at)
    {
        QString QAuthorName = QString::fromUtf8((at->data.GetName()).data(), (at->data.GetName()).size());
        ui->listWidgetAuthorGoTo->addItem(QAuthorName);
        ui->comboBoxSongAddAuthor->addItem(QAuthorName);
        ui->comboBoxDisplaySearchByAuthor->addItem(QAuthorName);
        at = at->next;
    }

    dt = DiskList.GetFirst();
    while (dt)
    {
        QString QDiskName = QString::fromUtf8((dt->data.GetName()).data(), (dt->data.GetName()).size());
        ui->listWidgetDiskGoTo->addItem(QDiskName);
        ui->comboBoxSongAddDisk->addItem(QDiskName);
        dt = dt->next;
    }

    st = SongList.GetFirst();
    while (st)
    {
        QString QSongName = QString::fromUtf8((st->data.GetName()).data(), (st->data.GetName()).size());
        ui->listWidgetSongGoTo->addItem(QSongName);
        ui->comboBoxDisplaySearchBySong->addItem(QSongName);
        st = st->next;
    }
}

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
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Open", "Do you really want to open new file? Unsaved data will be lost.", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        fileNameInput = "";
        fileNameInput = QFileDialog::getOpenFileName(this, tr("Open base"), "/home", tr("Image Files (*.json)"));
        if (fileNameInput != "")
        {
            qDebug() << "Opening" << fileNameInput << "...";
            ui->statusBar->showMessage("Opening \"" + fileNameInput + "\"...");

            nlohmann::json file_json = jsonFromFile(fileNameInput.toStdString());
            std::cout << file_json << std::endl;

            //Если список не пустой, чистим
            if (AuthorList.GetCount() != 0)
                AuthorList.Clear();
            if (DiskList.GetCount() != 0)
                DiskList.Clear();
            if (SongList.GetCount() != 0)
                SongList.Clear();

            std::cout << "Author reading..." << std::endl;
                for (nlohmann::json::iterator it1 = file_json.at("authors").begin(); it1 != file_json.at("authors").end(); ++it1)
                {
                    AuthorId = std::stoi(it1.key());
                    AuthorName = file_json.at("authors").at(it1.key())["name"].get<std::string>();
                    AuthorListIdSong = file_json.at("authors").at(it1.key())["songs"].get<std::vector<int>>();
                    currentAuthor.ChangeAuthor(AuthorId, AuthorName, AuthorListIdSong);
                    AuthorList.AddEnd(currentAuthor);
                }
                std::cout << "Author reading completed." << std::endl;

                std::cout << "Disk reading..." << std::endl;
                for (nlohmann::json::iterator it1 = file_json.at("disks").begin(); it1 != file_json.at("disks").end(); ++it1)
                {
                    DiskId = std::stoi(it1.key());
                    DiskName = file_json.at("disks").at(it1.key())["name"].get<std::string>();
                    DiskListIdSong = file_json.at("disks").at(it1.key())["songs"].get<std::vector<int>>();
                    currentDisk.ChangeDisk(DiskId, DiskName, DiskListIdSong);
                    DiskList.AddEnd(currentDisk);
                }
                std::cout << "Disk reading completed." << std::endl;

                std::cout << "Song reading..." << std::endl;
                for (nlohmann::json::iterator it1 = file_json.at("songs").begin(); it1 != file_json.at("songs").end(); ++it1)
                {
                    SongId = std::stoi(it1.key());
                    SongName = file_json.at("songs").at(it1.key())["name"].get<std::string>();
                    ListIdAuthor = file_json.at("songs").at(it1.key())["authors"].get<std::vector<int>>();
                    ListIdDisk = file_json.at("songs").at(it1.key())["disks"].get<std::vector<int>>();
                    currentSong.ChangeSong(SongId, SongName, ListIdAuthor, ListIdDisk);
                    SongList.AddEnd(currentSong);
                }
                std::cout << "Song reading completed." << std::endl;


            fileNameDefaultOutput = fileNameInput;
            qDebug() << "Opening completed";
            ui->statusBar->showMessage("Opening completed");
            MainWindow::refresh();
        }
        else
        {
            qDebug() << "Opening aborted.";
            ui->statusBar->showMessage("Opening aborted");
        }

    }
    else
    {
        qDebug() << "Opening aborted.";
        ui->statusBar->showMessage("Opening aborted");
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    fileNameOutput = "";

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Save as", "Do you really want to save it? If this file exists, it will be overwritten.", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        fileNameOutput = QFileDialog::getSaveFileName(this, tr("Save base as"), "/home", tr("Image Files (*.json)"));
        if (fileNameOutput != "")
        {
            ui->statusBar->showMessage("Saving as \"" + fileNameOutput + "\"...");
            qDebug() << "Saving as " << fileNameOutput;

            nlohmann::json output_file_json{};

            std::cout << "Author writing..." << std::endl;
            at = AuthorList.GetFirst();
            while (at)
            {
                output_file_json["authors"][std::to_string(at->data.GetId())]["name"] = at->data.GetName();
                output_file_json["authors"][std::to_string(at->data.GetId())]["songs"] = at->data.GetSongs();
                at = at->next;
            }
            std::cout << "Author writing completed." << std::endl;

            std::cout << "Disk writing..." << std::endl;
            dt = DiskList.GetFirst();
            while (dt)
            {
                output_file_json["disks"][std::to_string(dt->data.GetId())]["name"] = dt->data.GetName();
                output_file_json["disks"][std::to_string(dt->data.GetId())]["songs"] = dt->data.GetSongs();
                dt = dt->next;
            }
            std::cout << "Disk writing completed." << std::endl;

            std::cout << "Song writing..." << std::endl;
            st = SongList.GetFirst();
            while (st)
            {
                output_file_json["songs"][std::to_string(st->data.GetId())]["name"] = st->data.GetName();
                output_file_json["songs"][std::to_string(st->data.GetId())]["authors"] = st->data.GetAuthors();
                output_file_json["songs"][std::to_string(st->data.GetId())]["disks"] = st->data.GetDisks();
                st = st->next;
            }
            std::cout << "Song writing completed." << std::endl;

            //Вывод в файл
            std::ofstream outputstream(fileNameOutput.toStdString());
            outputstream << output_file_json << std::endl;


            ui->statusBar->showMessage("Saved");
            qDebug() << "Saved";

            fileNameDefaultOutput = fileNameOutput;
        }
        else
        {
            qDebug() << "Saving aborted";
            ui->statusBar->showMessage("Saving aborted");
        }

    }
    else
    {
        qDebug() << "Saving aborted";
        ui->statusBar->showMessage("Saving aborted");
    }
}

void MainWindow::on_actionSave_triggered()
{
    if (fileNameDefaultOutput != "")
    {
        ui->statusBar->showMessage("Saving as \"" + fileNameDefaultOutput + "\"...");
        qDebug() << "Saving as " << fileNameDefaultOutput;

        nlohmann::json output_file_json{};

        std::cout << "Author writing..." << std::endl;
        at = AuthorList.GetFirst();
        while (at)
        {
            output_file_json["authors"][std::to_string(at->data.GetId())]["name"] = at->data.GetName();
            output_file_json["authors"][std::to_string(at->data.GetId())]["songs"] = at->data.GetSongs();
            at = at->next;
        }
        std::cout << "Author writing completed." << std::endl;

        std::cout << "Disk writing..." << std::endl;
        dt = DiskList.GetFirst();
        while (dt)
        {
            output_file_json["disks"][std::to_string(dt->data.GetId())]["name"] = dt->data.GetName();
            output_file_json["disks"][std::to_string(dt->data.GetId())]["songs"] = dt->data.GetSongs();
            dt = dt->next;
        }
        std::cout << "Disk writing completed." << std::endl;

        std::cout << "Song writing..." << std::endl;
        st = SongList.GetFirst();
        while (st)
        {
            output_file_json["songs"][std::to_string(st->data.GetId())]["name"] = st->data.GetName();
            output_file_json["songs"][std::to_string(st->data.GetId())]["authors"] = st->data.GetAuthors();
            output_file_json["songs"][std::to_string(st->data.GetId())]["disks"] = st->data.GetDisks();
            st = st->next;
        }
        std::cout << "Song writing completed." << std::endl;

        //Вывод в файл
        std::ofstream outputstream(fileNameDefaultOutput.toStdString());
        outputstream << output_file_json << std::endl;


        ui->statusBar->showMessage("Saved");
        qDebug() << "Saved";
    }
    else
    {
        on_actionSave_As_triggered();
    }

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

//Вкладка Авторы

void MainWindow::AuthorGoToEdit (int index)
{
    ui->listWidgetAuthorSongList->clear();

    at = AuthorList.Move(index);
    std::cout << "Author: " <<"Moving to "<< index << std::endl;
    ui->statusBar->showMessage("Author: Moving to " + QString::number(index));

    AuthorId = at->data.GetId();
    AuthorName = at->data.GetName();
    AuthorListIdSong = at->data.GetSongs();


    ui->lineEditAuthorId->setText(QString::number(AuthorId));
    ui->lineEditAuthorName->setText(QString::fromUtf8((AuthorName).data(), (AuthorName).size()));


    if (SongList.GetCount() !=0)
    {
        st = SongList.GetFirst();
        QString currentSongName;
        while (st)
        {
            //setHidden(true),
            currentSongName = QString::fromUtf8((st->data.GetName()).data(), (st->data.GetName()).size());
            QListWidgetItem* item = new QListWidgetItem(currentSongName);
            ui->listWidgetAuthorSongList->addItem(item);
            item->setHidden(true);
            for (int i = 0; i < AuthorListIdSong.size(); i++)
            {
                if (st->data.GetId() == AuthorListIdSong[i])
                {
                        item->setHidden(false);
                        break;
                }
            }
            st = st->next;
        }
    }
}

void MainWindow::on_listWidgetAuthorGoTo_doubleClicked(const QModelIndex &index) // Переход на позицию
{
    AuthorGoToEdit(index.row());
}

void MainWindow::on_pushButtonAuthorGoTo_clicked() // Кнопка перейти на
{
    if (ui->listWidgetAuthorGoTo->currentIndex().row() != -1)
        on_listWidgetAuthorGoTo_doubleClicked(ui->listWidgetAuthorGoTo->currentIndex());
}

void MainWindow::on_lineEditAuthorSearch_textChanged(const QString &arg1) // Быстрый поиск
{
    for(int i=0; i < ui->listWidgetAuthorGoTo->count(); i++)
    {
        QListWidgetItem* item = ui->listWidgetAuthorGoTo->item(i);
        if(not(item->text().contains(ui->lineEditAuthorSearch->text())))
            item->setHidden(true);
        else
            item->setHidden(false);
    }
}

void MainWindow::on_listWidgetAuthorSongList_doubleClicked(const QModelIndex &index) // Переход из внутреннего листа
{
    SongGoToEdit(index.row());
    ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(2));
}

void MainWindow::on_pushButtonAuthorEditSong_clicked() // Кнопка перехода из внутреннего списка
{
    if (ui->listWidgetAuthorSongList->currentIndex().row() != -1)
        SongGoToEdit(ui->listWidgetAuthorSongList->currentIndex().row());
}

//Вкладка Диски

void MainWindow::DiskGoToEdit(int index)
{
    ui->listWidgetDiskSongList->clear();

    dt = DiskList.Move(index);
    std::cout << "Disk: " << "Moving to " << index << std::endl;
    ui->statusBar->showMessage("Disk: Moving to " + QString::number(index));

    DiskId = dt->data.GetId();
    DiskName = dt->data.GetName();
    DiskListIdSong = dt->data.GetSongs();



    ui->lineEditDiskId->setText(QString::number(DiskId));
    ui->lineEditDiskName->setText(QString::fromUtf8((DiskName).data(), (DiskName).size()));
    //QString currentSongName;
    if (SongList.GetCount() !=0)
    {
        st = SongList.GetFirst();
        QString currentSongName;
        while (st)
        {
            //setHidden(true),
            currentSongName = QString::fromUtf8((st->data.GetName()).data(), (st->data.GetName()).size());
            QListWidgetItem* item = new QListWidgetItem(currentSongName);
            ui->listWidgetDiskSongList->addItem(item);
            item->setHidden(true);
            for (int i = 0; i < DiskListIdSong.size(); i++)
            {
                if (st->data.GetId() == DiskListIdSong[i])
                {
                        item->setHidden(false);
                        break;
                }
            }
            st = st->next;
        }
    }
}

void MainWindow::on_listWidgetDiskGoTo_doubleClicked(const QModelIndex &index) // Переход на позицию
{
    DiskGoToEdit(index.row());
}

void MainWindow::on_pushButtonDiskGoTo_clicked() // Кнопка перейти на
{
    if (ui->listWidgetDiskGoTo->currentIndex().row() != -1)
        DiskGoToEdit(ui->listWidgetDiskGoTo->currentIndex().row());
}

void MainWindow::on_lineEditDiskSearch_textChanged(const QString &arg1) // Быстрый поиск
{
    for(int i=0; i < ui->listWidgetDiskGoTo->count(); i++)
    {
        QListWidgetItem* item = ui->listWidgetDiskGoTo->item(i);
        if(not(item->text().contains(ui->lineEditDiskSearch->text())))
            item->setHidden(true);
        else
            item->setHidden(false);
    }
}

void MainWindow::on_listWidgetDiskSongList_doubleClicked(const QModelIndex &index) // Переход из внутреннего листа
{
    SongGoToEdit(index.row());
    ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(2));
}

void MainWindow::on_pushButtonDiskEditSong_clicked() // Кнопка перехода из внутреннего списка
{
    if (ui->listWidgetDiskSongList->currentIndex().row() != -1)
         SongGoToEdit(ui->listWidgetDiskSongList->currentIndex().row());
}


//Вкладка Песни
void MainWindow::SongGoToEdit(int index)
{
    ui->listWidgetSongAuthorList->clear();
    ui->listWidgetSongDiskList->clear();

    st = SongList.Move(index);
    std::cout << "Song: " << "Moving to " << index << std::endl;
    ui->statusBar->showMessage("Song: Moving to " + QString::number(index));

    SongId = st->data.GetId();
    SongName = st->data.GetName();
    ListIdAuthor = st->data.GetAuthors();
    ListIdDisk = st->data.GetDisks();


    ui->lineEditSongId->setText(QString::number(SongId));
    ui->lineEditSongName->setText(QString::fromUtf8((SongName).data(), (SongName).size()));

    QString currentAuthorName;
    if (AuthorList.GetCount() != 0)
    {
        at = AuthorList.GetFirst();
        //QString currentSongName;
        while (at)
        {
            //setHidden(true),
            currentAuthorName = QString::fromUtf8((at->data.GetName()).data(), (at->data.GetName()).size());
            QListWidgetItem* item = new QListWidgetItem(currentAuthorName);
            ui->listWidgetSongAuthorList->addItem(item);
            item->setHidden(true);
            for (int i = 0; i < ListIdAuthor.size(); i++)
            {
                if (at->data.GetId() == ListIdAuthor[i])
                {
                        item->setHidden(false);
                        break;
                }
            }
            at = at->next;
        }
    }

    QString currentDiskName;
    if (DiskList.GetCount() != 0)
    {
        dt = DiskList.GetFirst();
        //QString currentSongName;
        while (dt)
        {
            //setHidden(true),
            currentDiskName = QString::fromUtf8((dt->data.GetName()).data(), (dt->data.GetName()).size());
            QListWidgetItem* item = new QListWidgetItem(currentDiskName);
            ui->listWidgetSongDiskList->addItem(item);
            item->setHidden(true);
            for (int i = 0; i < ListIdDisk.size(); i++)
            {
                if (dt->data.GetId() == ListIdDisk[i])
                {
                        item->setHidden(false);
                        break;
                }
            }
            dt = dt->next;
        }
    }
}

void MainWindow::on_listWidgetSongGoTo_doubleClicked(const QModelIndex &index) // Переход на позицию
{
    SongGoToEdit(index.row());
}

void MainWindow::on_pushButtonSongGoTo_clicked() // Кнопка перейти на
{
    if (ui->listWidgetSongGoTo->currentIndex().row() != -1)
        SongGoToEdit(ui->listWidgetSongGoTo->currentIndex().row());
}

void MainWindow::on_lineEditSongSearch_textChanged(const QString &arg1) // Быстрый поиск
{
    for(int i=0; i < ui->listWidgetSongGoTo->count(); i++)
    {
        QListWidgetItem* item = ui->listWidgetSongGoTo->item(i);
        if(not(item->text().contains(ui->lineEditSongSearch->text())))
            item->setHidden(true);
        else
            item->setHidden(false);
    }
}

void MainWindow::on_listWidgetSongAuthorList_doubleClicked(const QModelIndex &index) // Переход из внутреннего списка авторов
{
    AuthorGoToEdit(index.row());
    ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(0));
}

void MainWindow::on_pushButtonSongEditAuthor_clicked() // Кнопка перехода из внутреннего списка авторов
{
    if (ui->listWidgetSongAuthorList->currentIndex().row() != -1)
        AuthorGoToEdit(ui->listWidgetSongAuthorList->currentIndex().row());
}

void MainWindow::on_listWidgetSongDiskList_doubleClicked(const QModelIndex &index) // Переход из внутреннего списка дисков
{
    DiskGoToEdit(index.row());
    ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(1));
}

void MainWindow::on_pushButtonSongEditDisk_clicked() // Кнопка перехода из внутреннего списка дисков
{
    if (ui->listWidgetSongDiskList->currentIndex().row() != -1)
        DiskGoToEdit(ui->listWidgetSongDiskList->currentIndex().row());
}


