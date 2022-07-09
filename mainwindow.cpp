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
Element<Author> *at;  // Элемент для вывода всех значений
Element<Author> *eat; // Изменямый в данный момент элемент
Author currentAuthor;
int AuthorId;
std::string AuthorName;
std::vector<int> AuthorListIdSong;

List<Disk> DiskList;
Element<Disk> *dt;  // Элемент для вывода всех значений
Element<Disk> *edt; // Изменямый в данный момент элемент
Disk currentDisk;
int DiskId;
std::string DiskName;
std::vector<int> DiskListIdSong;

List<Song> SongList;
Element<Song> *st;  // Элемент для вывода всех значений
Element<Song> *est; // Изменямый в данный момент элемент
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
bool DataChanged = false;

bool OnLoad = false;

void MainWindow::refresh() // Обновление виджетов со вязями
{
    OnLoad = true;
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
    OnLoad = false;
}

void MainWindow::refreshAuthor() // Обновление окна изменения автора
{
    OnLoad = true;
    ui->lineEditAuthorId->clear();
    ui->lineEditAuthorName->clear();
    ui->listWidgetAuthorSongList->clear();
    OnLoad = false;
}

void MainWindow::refreshDisk() // Обновление окна изменения диска
{
    OnLoad = true;
    ui->lineEditDiskId->clear();
    ui->lineEditDiskName->clear();
    ui->listWidgetDiskSongList->clear();
    OnLoad = false;
}

void MainWindow::refreshSong() // Обновление окна изменения песни
{
    OnLoad = true;
    ui->lineEditSongId->clear();
    ui->lineEditSongName->clear();
    ui->listWidgetSongAuthorList->clear();
    ui->listWidgetSongDiskList->clear();
    OnLoad = false;
}

void MainWindow::AuthorOnEdit(bool option) // Блокирует все поля, кроме изменяемых у Автора
{
    AuthorEdited = option;
    ui->tabDisk->setEnabled(not option);
    ui->tabSong->setEnabled(not option);
    ui->tabDisplay->setEnabled(not option);
    ui->lineEditAuthorSearch->setEnabled(not option);
    ui->listWidgetAuthorGoTo->setEnabled(not option);
    ui->pushButtonAuthorSave->setEnabled(option);
    ui->listWidgetAuthorSongList->setEnabled(false);
    ui->pushButtonAuthorDelete->setEnabled(false);
    ui->pushButtonAuthorDiscard->setEnabled(option);
    ui->pushButtonAuthorEditSong->setEnabled(false);
    ui->pushButtonAuthorGoTo->setEnabled(not option);
    ui->pushButtonAuthorNew->setEnabled(not option);
    if (not option)
        ui->lineEditAuthorName->setEnabled(option);
}

void MainWindow::AuthorEditActivated(bool option) // Открывает поля для изменения
{
    ui->lineEditAuthorName->setEnabled(option);
    ui->listWidgetAuthorSongList->setEnabled(option);
    ui->pushButtonAuthorDelete->setEnabled(option);
    ui->pushButtonAuthorEditSong->setEnabled(option);
}

void MainWindow::DiskOnEdit(bool option) // Блокирует все поля, кроме изменяемых у Диска
{
    DiskEdited = option;
    ui->tabAuthor->setEnabled(not option);
    ui->tabSong->setEnabled(not option);
    ui->tabDisplay->setEnabled(not option);
    ui->lineEditDiskSearch->setEnabled(not option);
    ui->listWidgetDiskGoTo->setEnabled(not option);
    ui->pushButtonDiskSave->setEnabled(option);
    ui->listWidgetDiskSongList->setEnabled(false);
    ui->pushButtonDiskDelete->setEnabled(false);
    ui->pushButtonDiskDiscard->setEnabled(option);
    ui->pushButtonDiskEditSong->setEnabled(false);
    ui->pushButtonDiskGoTo->setEnabled(not option);
    ui->pushButtonDiskNew->setEnabled(not option);
    if (not option)
        ui->lineEditDiskName->setEnabled(option);
}

void MainWindow::DiskEditActivated(bool option) // Открывает поля для изменения
{
    ui->lineEditDiskName->setEnabled(option);
    ui->listWidgetDiskSongList->setEnabled(option);
    ui->pushButtonDiskDelete->setEnabled(option);
    ui->pushButtonDiskEditSong->setEnabled(option);
}

void MainWindow::SongOnEdit(bool option) // Блокирует все поля, кроме изменяемых у песни
{
    SongEdited = option;
    ui->tabAuthor->setEnabled(not option);
    ui->tabDisk->setEnabled(not option);
    ui->tabDisplay->setEnabled(not option);

    ui->lineEditSongSearch->setEnabled(not option);
    ui->listWidgetSongGoTo->setEnabled(not option);
    ui->pushButtonSongSave->setEnabled(option);
    ui->listWidgetSongAuthorList->setEnabled(true);

    ui->pushButtonSongDelete->setEnabled(false);
    ui->pushButtonSongDiscard->setEnabled(option);

    ui->pushButtonSongEditAuthor->setEnabled(false);
    ui->pushButtonSongEditDisk->setEnabled(false);

    ui->pushButtonSongGoTo->setEnabled(not option);
    ui->pushButtonSongNew->setEnabled(not option);

    if (not option)
    {
        ui->lineEditSongName->setEnabled(option);
        ui->comboBoxSongAddAuthor->setEnabled(option);
        ui->pushButtonSongAddAuthor->setEnabled(option);
        ui->listWidgetSongAuthorList->setEnabled(option);
        ui->pushButtonSongDeleteAuthor->setEnabled(option);
        ui->pushButtonSongAddDisk->setEnabled(option);
        ui->comboBoxSongAddDisk->setEnabled(option);
        ui->listWidgetSongDiskList->setEnabled(option);
        ui->pushButtonSongDeleteDisk->setEnabled(option);
    }
}

void MainWindow::SongEditActivated(bool option) // Открывает поля для изменения
{
    ui->lineEditSongName->setEnabled(option);
    ui->comboBoxSongAddAuthor->setEnabled(option);
    ui->pushButtonSongAddAuthor->setEnabled(option);
    ui->listWidgetSongAuthorList->setEnabled(option);
    ui->pushButtonSongDeleteAuthor->setEnabled(option);
    ui->pushButtonSongEditAuthor->setEnabled(option);
    ui->listWidgetSongAuthorList->setEnabled(option);
    ui->pushButtonSongAddDisk->setEnabled(option);
    ui->comboBoxSongAddDisk->setEnabled(option);
    ui->pushButtonSongDeleteDisk->setEnabled(option);
    ui->pushButtonSongEditDisk->setEnabled(option);
    ui->listWidgetSongDiskList->setEnabled(option);
    ui->pushButtonSongDelete->setEnabled(option);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() // Деструктор
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered() // Вызов справки
{
    about = new About(this);
    about->show();
}

void MainWindow::on_pushButtonDisplaySearchByAuthor_clicked() // Поиск песен заданного автора
{
    if (ui->comboBoxDisplaySearchByAuthor->currentIndex() != -1)
    {
        report = new Report(this);
        report->setModal(true);
        report->show();

        at = AuthorList.Move(ui->comboBoxDisplaySearchByAuthor->currentIndex());
        AuthorId = at->data.GetId();
        AuthorName = at->data.GetName();
        AuthorListIdSong = at->data.GetSongs();
        // Устанавливаем заголовок
        QString Header = QString::fromUtf8(AuthorName.data(), AuthorName.size()) + " songs:";
        connect(this, &MainWindow::signalDisplaySearchSetHeader, report, &Report::slotDisplaySearchSetHeader);
        emit signalDisplaySearchSetHeader(Header);
        // Добавляем песни
        QString item;
        connect(this, &MainWindow::signalDisplaySearchAddToList, report, &Report::slotDisplaySearchAddToList);
        for (int i = 0; i < AuthorListIdSong.size(); i++)
        {
            st = SearchElemetById(SongList, AuthorListIdSong[i]);
            SongName = " - " + st->data.GetName();
            ListIdAuthor = st->data.GetAuthors();
            std::string itemAuhors = SearchElemetById(AuthorList, ListIdAuthor[0])->data.GetName();
            at = SearchElemetById(AuthorList, ListIdAuthor[i]);
            for (int j = 1; j < ListIdAuthor.size(); j++)
            {
                itemAuhors = itemAuhors + ", " + SearchElemetById(AuthorList, ListIdAuthor[j])->data.GetName();
            }
            itemAuhors = itemAuhors + SongName;
            item = QString::fromUtf8(itemAuhors.data(), itemAuhors.size());
            emit signalDisplaySearchAddToList(item);
        }
        qDebug() << "Display: author songs report created";
        ui->statusBar->showMessage("Display: author songs report created");
    }
}

void MainWindow::on_pushButtonDisplaySearchBySong_clicked() // Поиск дисков, где встречается заданная песня
{   
    if (ui->comboBoxDisplaySearchBySong->currentIndex() != -1)
    {
        report = new Report(this);
        report->setModal(true);
        report->show();

        st = SongList.Move(ui->comboBoxDisplaySearchBySong->currentIndex());
        SongId = st->data.GetId();
        SongName = st->data.GetName();
        ListIdDisk = st->data.GetDisks();
        // Устанавливаем заголовок
        QString Header = QString::fromUtf8(SongName.data(), SongName.size()) + " disks:";
        connect(this, &MainWindow::signalDisplaySearchSetHeader, report, &Report::slotDisplaySearchSetHeader);
        emit signalDisplaySearchSetHeader(Header);
        // Добавляем диски
        QString item;
        connect(this, &MainWindow::signalDisplaySearchAddToList, report, &Report::slotDisplaySearchAddToList);
        for (int i = 0; i < ListIdDisk.size(); i++)
        {
            dt = SearchElemetById(DiskList, ListIdDisk[i]);
            DiskName = dt->data.GetName();
            item = QString::fromUtf8(DiskName.data(), DiskName.size());
            emit signalDisplaySearchAddToList(item);
        }
        qDebug() << "Display: song disks report created";
        ui->statusBar->showMessage("Display: song disks report created");
    }

}

void MainWindow::on_actionOpen_File_triggered() // Открытие файла
{
    if (DataChanged)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Open", "Do you really want to open new file? Unsaved data will be lost.", QMessageBox::Yes | QMessageBox::No);
        if (reply != QMessageBox::Yes)
        {
            qDebug() << "Opening aborted.";
            ui->statusBar->showMessage("Opening aborted");
            return;
        }
    }

    fileNameInput = "";
    fileNameInput = QFileDialog::getOpenFileName(this, tr("Open base"), "/home", tr("Image Files (*.json)"));
    if (fileNameInput != "")
    {
        nlohmann::json file_json;
        try
        {
            qDebug() << "Opening" << fileNameInput << "...";
            ui->statusBar->showMessage("Opening \"" + fileNameInput + "\"...");

            std::string FileNameInput = fileNameInput.toStdString();
            std::ifstream ifs{FileNameInput}; //Открытие файла
            if (!ifs.is_open())
            {
                std::cerr << "Unable to open file\n";
                throw 1;
            }
            file_json = nlohmann::json::parse(ifs); //Перевод в Json

            ifs.close(); //Закрытие файла
        }
        catch (const nlohmann::detail::parse_error &e)
        {
            qDebug() << e.what();
            ui->statusBar->showMessage(e.what());
            QMessageBox::warning(this, "Warning", "Error while parsing json");
            return;
        }
        catch (...)
        {
            qDebug() << "Error while opening";
            ui->statusBar->showMessage("Cant open file");
            QMessageBox::warning(this, "Warning", "Cant open file");
            return;
        }

        try
        {
            std::cout << file_json << std::endl;

            //Если список не пустой, чистим
            if (AuthorList.GetCount() != 0)
                AuthorList.Clear();
            if (DiskList.GetCount() != 0)
                DiskList.Clear();
            if (SongList.GetCount() != 0)
                SongList.Clear();

            //Обновление полей
            refresh();
            refreshAuthor();
            refreshDisk();
            refreshSong();
            AuthorEditActivated(false);
            DiskEditActivated(false);
            SongEditActivated(false);

            try // Чтение Авторов
            {
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
            }
            catch (...)
            {
                qDebug() << "Cant read Authors";
                ui->statusBar->showMessage("Cant read Authors");
                QMessageBox::warning(this, "Warning", "Cant read Authors");
            }
            try // Чтение Дисков
            {
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
            }
            catch (...)
            {
                qDebug() << "Cant read Disks";
                ui->statusBar->showMessage("Cant read Disks");
                QMessageBox::warning(this, "Warning", "Cant read Disks");
            }
            try // Чтение Песен
            {
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
            }
            catch (...)
            {
                qDebug() << "Cant read Songs";
                ui->statusBar->showMessage("Cant read Songs");
                QMessageBox::warning(this, "Warning", "Cant read Songs");
            }

            qDebug() << "Opening completed";
            ui->statusBar->showMessage("Opening completed");
            DataChanged = false;
            MainWindow::refresh();
        }
        catch (const nlohmann::detail::type_error &e)
        {
            qDebug() << e.what();
            ui->statusBar->showMessage(e.what());
            QMessageBox::warning(this, "Warning", "Error while converting from json");
            return;
        }
        catch (...)
        {
            qDebug() << "The file is damaged";
            ui->statusBar->showMessage("The file is damaged");
            QMessageBox::warning(this, "Warning", "The file is damaged");
            return;
        }
        fileNameDefaultOutput = fileNameInput;
    }
    else
    {
        qDebug() << "Opening aborted.";
        ui->statusBar->showMessage("Opening aborted");
    }
}

void MainWindow::saving(const QString fileNameOutput) // Сохранение
{

    if (fileNameOutput != "")
    {
        try
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

            DataChanged = false;
            ui->statusBar->showMessage("Saved");
            qDebug() << "Saved";
            fileNameDefaultOutput = fileNameOutput;
        }

        catch (...)
        {
            qDebug() << "Error while saving";
            ui->statusBar->showMessage("Error while saving");
            QMessageBox::warning(this, "Warning", "Error while saving");
            return;
        }
    }
    else
    {
        qDebug() << "Saving aborted";
        ui->statusBar->showMessage("Saving aborted");
    }
}

void MainWindow::on_actionSave_As_triggered() // Сохранить в произвольное место
{
    fileNameOutput = "";
    fileNameOutput = QFileDialog::getSaveFileName(this, tr("Save base as"), "/home", tr("Image Files (*.json)"));
    saving(fileNameOutput);
}

void MainWindow::on_actionSave_triggered() // Сохранить в исходный файл
{
    if (fileNameDefaultOutput != "")
    {
        saving(fileNameDefaultOutput);
    }
    else
    {
        on_actionSave_As_triggered();
    }
}

void MainWindow::on_actionExit_triggered() // Выход
{
    QMessageBox::StandardButton reply;
    if (DataChanged)
    {
        reply = QMessageBox::question(this, "Exit", "Do you really want to Quit? Unsaved data will be lost.", QMessageBox::Yes | QMessageBox::No);
        if (reply != QMessageBox::Yes)
        {
            qDebug() << "Quit aborted";
            ui->statusBar->showMessage("Quit aborted");
            return;
        }
    }
    ui->statusBar->showMessage("Quit");
    qDebug() << "Quit";
    QApplication::quit();
}

//Вкладка Авторы

void MainWindow::AuthorGoToEdit(int index)
{
    OnLoad = true;
    ui->listWidgetAuthorSongList->clear();

    at = AuthorList.Move(index);
    eat = at;
    std::cout << "Author: "
              << "Moving to " << index << std::endl;
    ui->statusBar->showMessage("Author: Moving to " + QString::number(index));

    AuthorId = at->data.GetId();
    AuthorName = at->data.GetName();
    AuthorListIdSong = at->data.GetSongs();

    ui->lineEditAuthorId->setText(QString::number(AuthorId));
    ui->lineEditAuthorName->setText(QString::fromUtf8((AuthorName).data(), (AuthorName).size()));

    if (SongList.GetCount() != 0)
    {
        st = SongList.GetFirst();
        QString currentSongName;
        while (st)
        {
            // setHidden(true),
            currentSongName = QString::fromUtf8((st->data.GetName()).data(), (st->data.GetName()).size());
            QListWidgetItem *item = new QListWidgetItem(currentSongName);
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
    OnLoad = false;
    AuthorEditActivated(true);
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
    for (int i = 0; i < ui->listWidgetAuthorGoTo->count(); i++)
    {
        QListWidgetItem *item = ui->listWidgetAuthorGoTo->item(i);
        if (not(item->text().contains(ui->lineEditAuthorSearch->text())))
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
    {
        SongGoToEdit(ui->listWidgetAuthorSongList->currentIndex().row());
        ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(2));
    }
}

//Вкладка Диски

void MainWindow::DiskGoToEdit(int index)
{
    OnLoad = true;
    ui->listWidgetDiskSongList->clear();

    dt = DiskList.Move(index);
    edt = dt;
    std::cout << "Disk: "
              << "Moving to " << index << std::endl;
    ui->statusBar->showMessage("Disk: Moving to " + QString::number(index));

    DiskId = dt->data.GetId();
    DiskName = dt->data.GetName();
    DiskListIdSong = dt->data.GetSongs();

    ui->lineEditDiskId->setText(QString::number(DiskId));
    ui->lineEditDiskName->setText(QString::fromUtf8((DiskName).data(), (DiskName).size()));
    // QString currentSongName;
    if (SongList.GetCount() != 0)
    {
        st = SongList.GetFirst();
        QString currentSongName;
        while (st)
        {
            // setHidden(true),
            currentSongName = QString::fromUtf8((st->data.GetName()).data(), (st->data.GetName()).size());
            QListWidgetItem *item = new QListWidgetItem(currentSongName);
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
    OnLoad = false;
    DiskEditActivated(true);
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
    for (int i = 0; i < ui->listWidgetDiskGoTo->count(); i++)
    {
        QListWidgetItem *item = ui->listWidgetDiskGoTo->item(i);
        if (not(item->text().contains(ui->lineEditDiskSearch->text())))
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
    {
        SongGoToEdit(ui->listWidgetDiskSongList->currentIndex().row());
        ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(2));
    }
}

//Вкладка Песни
void MainWindow::SongGoToEdit(int index) // Перейти на песню для изменения
{
    OnLoad = true;
    ui->listWidgetSongAuthorList->clear();
    ui->listWidgetSongDiskList->clear();

    st = SongList.Move(index);
    est = st;
    std::cout << "Song: "
              << "Moving to " << index << std::endl;
    ui->statusBar->showMessage("Song: Moving to " + QString::number(index));

    SongId = st->data.GetId();
    SongName = st->data.GetName();
    ListIdAuthor = st->data.GetAuthors();
    ListIdDisk = st->data.GetDisks();

    currentSong.ChangeSong(SongId, SongName, ListIdAuthor, ListIdDisk);

    ui->lineEditSongId->setText(QString::number(SongId));
    ui->lineEditSongName->setText(QString::fromUtf8((SongName).data(), (SongName).size()));

    QString currentAuthorName;
    if (AuthorList.GetCount() != 0)
    {
        at = AuthorList.GetFirst();
        // QString currentSongName;
        while (at)
        {
            // setHidden(true),
            currentAuthorName = QString::fromUtf8((at->data.GetName()).data(), (at->data.GetName()).size());
            QListWidgetItem *item = new QListWidgetItem(currentAuthorName);
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
        // QString currentSongName;
        while (dt)
        {
            // setHidden(true),
            currentDiskName = QString::fromUtf8((dt->data.GetName()).data(), (dt->data.GetName()).size());
            QListWidgetItem *item = new QListWidgetItem(currentDiskName);
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
    OnLoad = false;
    SongEditActivated(true);
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
    for (int i = 0; i < ui->listWidgetSongGoTo->count(); i++)
    {
        QListWidgetItem *item = ui->listWidgetSongGoTo->item(i);
        if (not(item->text().contains(ui->lineEditSongSearch->text())))
            item->setHidden(true);
        else
            item->setHidden(false);
    }
}

void MainWindow::on_listWidgetSongAuthorList_doubleClicked(const QModelIndex &index) // Переход из внутреннего списка авторов
{
    if (not SongEdited)
    {
        AuthorGoToEdit(index.row());
        ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(0));
    }
}

void MainWindow::on_pushButtonSongEditAuthor_clicked() // Кнопка перехода из внутреннего списка авторов
{
    if (ui->listWidgetSongAuthorList->currentIndex().row() != -1)
    {
        AuthorGoToEdit(ui->listWidgetSongAuthorList->currentIndex().row());
        ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(0));
    }
}

void MainWindow::on_listWidgetSongDiskList_doubleClicked(const QModelIndex &index) // Переход из внутреннего списка дисков
{
    if (not SongEdited)
    {
        DiskGoToEdit(index.row());
        ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(1));
    }
}

void MainWindow::on_pushButtonSongEditDisk_clicked() // Кнопка перехода из внутреннего списка дисков
{
    if (ui->listWidgetSongDiskList->currentIndex().row() != -1)
    {
        DiskGoToEdit(ui->listWidgetSongDiskList->currentIndex().row());
        ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(1));
    }
}

// Изменение данных автора

void MainWindow::on_lineEditAuthorName_textChanged(const QString &arg1) // Переключение в режим изменения, если изменилось название
{
    if (not OnLoad)
        AuthorOnEdit(true);
}

void MainWindow::on_pushButtonAuthorSave_clicked() // Сохранение изменений
{
    if (AuthorEdited = true)
    {
        std::string newAuthorName = ui->lineEditAuthorName->text().toStdString();
        if (newAuthorName == "")
            QMessageBox::warning(this, "Warning", "Fill the field Author Name");
        else
        {
            eat->data.SetName(newAuthorName);
            OnLoad = true;
            refreshDisk();
            refreshSong();
            refresh();
            AuthorOnEdit(false);
            AuthorEditActivated(true);
            OnLoad = false;
            DataChanged = true;
            qDebug() << "Author: saved";
            ui->statusBar->showMessage("Author: saved");
        }
    }
}

void MainWindow::on_pushButtonAuthorDiscard_clicked() // Отмена изменений
{
    refreshAuthor();
    AuthorOnEdit(false);
    qDebug() << "Author: edit discarded";
    ui->statusBar->showMessage("Author: edit discarded");
}

void MainWindow::on_pushButtonAuthorNew_clicked() // Создание нового автора
{
    if (AuthorList.GetCount() == 0)
        AuthorId = 1;
    else
        AuthorId = AuthorList.GetLast()->data.GetId() + 1;
    AuthorName = "Author" + std::to_string(AuthorId);
    AuthorListIdSong = {};
    currentAuthor.ChangeAuthor(AuthorId, AuthorName, AuthorListIdSong);
    AuthorList.AddEnd(currentAuthor);
    refresh(); // Обновление полей
    refreshAuthor();
    refreshDisk();
    refreshSong();
    //
    DiskEditActivated(false);
    SongEditActivated(false);
    DataChanged = true;

    AuthorGoToEdit(AuthorList.GetCount() - 1);
    qDebug() << "Author: Author" << AuthorId << " added";
    ui->statusBar->showMessage("Author: Author" + QString::number(AuthorId) + " added");
}

void MainWindow::on_pushButtonAuthorDelete_clicked() // Удаление текущего автора
{
    AuthorId = eat->data.GetId();
    AuthorListIdSong = eat->data.GetSongs();

    for (int i = 0; i < AuthorListIdSong.size(); i++)
    {
        st = SongList.GetFirst();
        while (st)
        {
            if (st->data.GetId() == AuthorListIdSong[i])
            {
                st->data.RemoveAuthor(AuthorId);
                break;
            }

            st = st->next;
        }
    }

    AuthorList.Delete(eat);

    refresh();
    refreshAuthor();
    refreshDisk();
    refreshSong();
    AuthorOnEdit(false);
    DiskOnEdit(false);
    SongOnEdit(false);
    DataChanged = true;
}

// Изменение данных диска

void MainWindow::on_lineEditDiskName_textChanged(const QString &arg1) // Переключение в режим изменения, если изменилось название
{
    if (not OnLoad)
        DiskOnEdit(true);
}

void MainWindow::on_pushButtonDiskSave_clicked() // Сохранение изменений
{
    if (DiskEdited = true)
    {
        std::string newDiskName = ui->lineEditDiskName->text().toStdString();
        if (newDiskName == "")
            QMessageBox::warning(this, "Warning", "Fill the field Disk Name");
        else
        {
            edt->data.SetName(newDiskName);
            OnLoad = true;
            refreshAuthor();
            refreshSong();
            refresh();
            DiskOnEdit(false);
            DiskEditActivated(true);
            OnLoad = false;
            DataChanged = true;
            qDebug() << "Disk: saved";
            ui->statusBar->showMessage("Disk: saved");
        }
    }
}

void MainWindow::on_pushButtonDiskDiscard_clicked() // Отмена изменений
{
    refreshDisk();
    DiskOnEdit(false);
    qDebug() << "Disk: edit discarded";
    ui->statusBar->showMessage("Disk: edit discarded");
}

void MainWindow::on_pushButtonDiskNew_clicked() // Создание нового диска
{
    if (DiskList.GetCount() == 0)
        DiskId = 1;
    else
        DiskId = DiskList.GetLast()->data.GetId() + 1;
    DiskName = "Disk" + std::to_string(DiskId);
    DiskListIdSong = {};
    currentDisk.ChangeDisk(DiskId, DiskName, DiskListIdSong);
    DiskList.AddEnd(currentDisk);
    refresh(); // Обновление полей
    refreshAuthor();
    refreshDisk();
    refreshSong();
    AuthorEditActivated(false);

    SongEditActivated(false);
    DataChanged = true;
    DiskGoToEdit(DiskList.GetCount() - 1);
    qDebug() << "Disk: Disk" << DiskId << " added";
    ui->statusBar->showMessage("Disk: Disk" + QString::number(DiskId) + " added");
}

void MainWindow::on_pushButtonDiskDelete_clicked() // Удаление текущего диска
{
    DiskId = edt->data.GetId();
    DiskName = edt->data.GetName();
    DiskListIdSong = edt->data.GetSongs();

    for (int i = 0; i < DiskListIdSong.size(); i++)
    {
        st = SongList.GetFirst();
        while (st)
        {
            if (st->data.GetId() == DiskListIdSong[i])
            {
                st->data.RemoveDisk(AuthorId);
                break;
            }

            st = st->next;
        }
    }

    DiskList.Delete(edt);

    refresh(); // Обновление полей.
    refreshAuthor();
    refreshDisk();
    refreshSong();
    AuthorOnEdit(false);
    DiskOnEdit(false);
    SongOnEdit(false);
    DataChanged = true;
    qDebug() << "Disk: " << QString::fromUtf8(DiskName.data(), DiskName.size()) << " deleted";
    ui->statusBar->showMessage("Disk: " + QString::fromUtf8(DiskName.data(), DiskName.size()) + " deleted");
}

// Изменение данных песни

void MainWindow::on_lineEditSongName_textChanged(const QString &arg1) // Переключение в режим изменения, если изменилось название
{
    if (not OnLoad)
        SongOnEdit(true);
}

void MainWindow::on_pushButtonSongSave_clicked() // Сохранение изменений
{
    if (SongEdited = true)
    {
        std::string newSongName = ui->lineEditSongName->text().toStdString();
        if (newSongName == "")
            QMessageBox::warning(this, "Warning", "Fill the field Song Name");
        else
        {
            bool flag;
            ListIdAuthor = currentSong.GetAuthors();

            // Обновление связей Авторов
            std::vector<int> ListIdAuthorOld = est->data.GetAuthors();

            for (int i = 0; i < ListIdAuthorOld.size(); i++)
            {
                flag = false;
                for (int j = 0; j < ListIdAuthor.size(); j++)
                {
                    if (ListIdAuthorOld[i] == ListIdAuthor[j])
                    {
                        flag = true;
                        break;
                    }
                }
                if (not flag) // Delete links
                {
                    at = AuthorList.GetFirst();
                    while (at)
                    {
                        if (at->data.GetId() == ListIdAuthorOld[i])
                        {
                            at->data.RemoveSong(est->data.GetId());
                            break;
                        }

                        at = at->next;
                    }
                    std::cout << ListIdAuthorOld[i] << " Deleteng Author" << std::endl;
                }
            }

            for (int i = 0; i < ListIdAuthor.size(); i++)
            {
                flag = false;
                for (int j = 0; j < ListIdAuthorOld.size(); j++)
                {
                    if (ListIdAuthor[i] == ListIdAuthorOld[j])
                    {
                        flag = true;
                        break;
                    }
                }
                if (not flag) // Add links
                {
                    at = AuthorList.GetFirst();
                    while (at)
                    {
                        if (at->data.GetId() == ListIdAuthor[i])
                        {
                            at->data.AddSong(est->data.GetId());
                            break;
                        }
                        at = at->next;
                    }
                    std::cout << ListIdAuthor[i] << " Add Author" << std::endl; // Del
                }
            }

            ListIdDisk = currentSong.GetDisks();

            // Обновление связей Дисков
            std::vector<int> ListIdDiscOld = est->data.GetDisks();

            for (int i = 0; i < ListIdDiscOld.size(); i++)
            {
                flag = false;
                for (int j = 0; j < ListIdDisk.size(); j++)
                {
                    if (ListIdDiscOld[i] == ListIdDisk[j])
                    {
                        flag = true;
                        break;
                    }
                }
                if (not flag) // Delete links
                {
                    dt = DiskList.GetFirst();
                    while (dt)
                    {
                        if (dt->data.GetId() == ListIdDiscOld[i])
                        {
                            dt->data.RemoveSong(est->data.GetId());
                            break;
                        }

                        dt = dt->next;
                    }
                    std::cout << ListIdDiscOld[i] << " Deleteng Disk" << std::endl;
                }
            }

            for (int i = 0; i < ListIdDisk.size(); i++)
            {
                flag = false;
                for (int j = 0; j < ListIdDiscOld.size(); j++)
                {
                    if (ListIdDisk[i] == ListIdDiscOld[j])
                    {
                        flag = true;
                        break;
                    }
                }
                if (not flag) // Add links
                {
                    dt = DiskList.GetFirst();
                    while (dt)
                    {
                        if (dt->data.GetId() == ListIdDisk[i])
                        {
                            dt->data.AddSong(est->data.GetId());
                            break;
                        }
                        dt = dt->next;
                    }
                    std::cout << ListIdDisk[i] << " Add Disk" << std::endl; // Del
                }
            }

            est->data.SetName(newSongName);
            est->data.SetAuthors(ListIdAuthor);
            est->data.SetDisks(ListIdDisk);
            refreshAuthor();
            refreshDisk();
            refresh();
            SongOnEdit(false);
            SongEditActivated(true);
            DataChanged = true;
            qDebug() << "Song: saved";
            ui->statusBar->showMessage("Song: saved");
        }
    }
}

void MainWindow::on_pushButtonSongDiscard_clicked() // Отмена изменений
{
    refreshSong();
    SongOnEdit(false);
    qDebug() << "Song: edit discarded";
    ui->statusBar->showMessage("Song: edit discarded");
}

void MainWindow::on_pushButtonSongNew_clicked() // Создание новой песни
{
    if (SongList.GetCount() == 0)
        SongId = 1;
    else
        SongId = SongList.GetLast()->data.GetId() + 1;
    SongName = "Song" + std::to_string(SongId);
    ListIdAuthor = {};
    ListIdDisk = {};
    currentSong.ChangeSong(SongId, SongName, ListIdAuthor, ListIdDisk);
    SongList.AddEnd(currentSong);
    refresh(); // Обновление полей
    refreshAuthor();
    refreshDisk();
    refreshSong();
    AuthorOnEdit(false);
    DiskOnEdit(false);

    DataChanged = true;
    SongGoToEdit(SongList.GetCount()-1);
    qDebug() << "Song: Song" << SongId << " added";
    ui->statusBar->showMessage("Song: Song" + QString::number(SongId) + " added");
}

void MainWindow::on_pushButtonSongDelete_clicked() // Удаление текущей песни
{

    SongId = est->data.GetId();
    SongName = est->data.GetName();
    ListIdAuthor = est->data.GetAuthors();
    ListIdDisk = est->data.GetDisks();

    // Удаление связей с авторами
    for (int i = 0; i < ListIdAuthor.size(); i++)
    {
        at = AuthorList.GetFirst();
        while (at)
        {
            if (at->data.GetId() == ListIdAuthor[i])
            {
                at->data.RemoveSong(SongId);
                break;
            }
            at = at->next;
        }
    }
    // Удаление связей с дисками
    for (int i = 0; i < ListIdDisk.size(); i++)
    {
        dt = DiskList.GetFirst();
        while (dt)
        {
            if (dt->data.GetId() == ListIdDisk[i])
            {
                dt->data.RemoveSong(SongId);
                break;
            }
            dt = dt->next;
        }
    }

    SongList.Delete(est);

    refresh();
    refreshAuthor();
    refreshDisk();
    refreshSong();
    AuthorOnEdit(false);
    DiskOnEdit(false);
    SongOnEdit(false);
    DataChanged = true;
    qDebug() << "Song: " << QString::fromUtf8(SongName.data(), SongName.size()) << " deleted";
    ui->statusBar->showMessage("Song: " + QString::fromUtf8(SongName.data(), SongName.size()) + " deleted");
}

void MainWindow::on_pushButtonSongAddAuthor_clicked() // Добавление связи Автор-Песня
{
    if (ui->comboBoxSongAddAuthor->currentIndex() != -1)
    {
        SongOnEdit(true);
        currentSong.AddAuthor(AuthorList.Move(ui->comboBoxSongAddAuthor->currentIndex())->data.GetId());
        ui->listWidgetSongAuthorList->item(ui->comboBoxSongAddAuthor->currentIndex())->setHidden(false);
    }
}

void MainWindow::on_pushButtonSongAddDisk_clicked() // Добавление связи Диск-Песня
{
    if (ui->comboBoxSongAddDisk->currentIndex() != -1)
    {
        SongOnEdit(true);
        currentSong.AddDisk(DiskList.Move(ui->comboBoxSongAddDisk->currentIndex())->data.GetId());
        ui->listWidgetSongDiskList->item(ui->comboBoxSongAddDisk->currentIndex())->setHidden(false);
    }
}

void MainWindow::on_pushButtonSongDeleteAuthor_clicked() // Удаление связи Автор-Песня
{
    if (ui->listWidgetSongAuthorList->currentIndex().row() != -1)
    {
        SongOnEdit(true);
        currentSong.RemoveAuthor(AuthorList.Move(ui->listWidgetSongAuthorList->currentIndex().row())->data.GetId());
        ui->listWidgetSongAuthorList->item(ui->listWidgetSongAuthorList->currentIndex().row())->setHidden(true);
    }
}

void MainWindow::on_pushButtonSongDeleteDisk_clicked() // Удаление связи Диск-Песня
{
    if (ui->listWidgetSongDiskList->currentIndex().row() != -1)
    {
        SongOnEdit(true);
        currentSong.RemoveDisk(DiskList.Move(ui->listWidgetSongDiskList->currentIndex().row())->data.GetId());
        ui->listWidgetSongDiskList->item(ui->listWidgetSongDiskList->currentIndex().row())->setHidden(true);
    }
}

void MainWindow::on_actionNew_File_triggered() // Создание нового проекта
{
    qDebug() << "Creating new base..";
    ui->statusBar->showMessage("Creating new base...");

    if (DataChanged)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Open", "Do you really want create new file? Unsaved data will be lost.", QMessageBox::Yes | QMessageBox::No);
        if (reply != QMessageBox::Yes)
        {
            qDebug() << "Creating aborted.";
            ui->statusBar->showMessage("Creating aborted");
            return;
        }
    }

    //Если список не пустой, чистим
    if (AuthorList.GetCount() != 0)
        AuthorList.Clear();
    if (DiskList.GetCount() != 0)
        DiskList.Clear();
    if (SongList.GetCount() != 0)
        SongList.Clear();

    //Обновление полей
    refresh();
    refreshAuthor();
    refreshDisk();
    refreshSong();
    AuthorEditActivated(false);
    DiskEditActivated(false);
    SongEditActivated(false);
    qDebug() << "New base created";
    ui->statusBar->showMessage("New base created");
}
