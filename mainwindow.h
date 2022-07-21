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
    void refresh(); // Обновление виджетов со cвязями

    void refreshAuthor(); // Обновление окна изменения автора

    void refreshDisk(); // Обновление окна изменения диска

    void refreshSong(); // Обновление окна изменения песни

    void AuthorOnEdit(bool option); // Блокирует все поля, кроме изменяемых у Автора

    void AuthorEditActivated(bool option); // Открывает поля для изменения

    void DiskOnEdit(bool option); // Блокирует все поля, кроме изменяемых у Диска

    void DiskEditActivated(bool option); // Открывает поля для изменения

    void SongOnEdit(bool option); // Блокирует все поля, кроме изменяемых у песни

    void SongEditActivated(bool option); // Открывает поля для изменения

    void on_actionAbout_triggered(); // Вызов справки

    void on_pushButtonDisplaySearchByAuthor_clicked(); // Поиск песен заданного автора

    void on_pushButtonDisplaySearchBySong_clicked(); // Поиск дисков, где встречается заданная песня

    void on_actionOpen_File_triggered(); // Открытие файла

    void saving(const QString fileNameOutput); // Сохранение

    void on_actionSave_As_triggered(); // Сохранить в произвольное место

    void on_actionExit_triggered(); // Выход

    void on_actionSave_triggered(); // Сохранить в исходный файл

    void AuthorGoToEdit (int index); // Переход к изменению автора

    void on_listWidgetAuthorGoTo_doubleClicked(const QModelIndex &index); // Переход на позицию по двойному щелчку

    void DiskGoToEdit (int index); // Переход к изменению автора

    void on_listWidgetDiskGoTo_doubleClicked(const QModelIndex &index); // Переход на позицию по двойному щелчку

    void SongGoToEdit (int index); // Переход к изменению автора

    void on_listWidgetSongGoTo_doubleClicked(const QModelIndex &index); // Переход на позицию по двойному щелчку

    void on_pushButtonAuthorGoTo_clicked(); // Кнопка перейти на

    void on_pushButtonDiskGoTo_clicked(); // Кнопка перейти на

    void on_pushButtonSongGoTo_clicked(); // Кнопка перейти на

    void on_lineEditAuthorSearch_textChanged(const QString &arg1); // Быстрый поиск

    void on_lineEditDiskSearch_textChanged(const QString &arg1); // Быстрый поиск

    void on_lineEditSongSearch_textChanged(const QString &arg1); // Быстрый поиск

    void on_listWidgetAuthorSongList_doubleClicked(const QModelIndex &index); // Переход из внутреннего листа

    void on_pushButtonAuthorEditSong_clicked(); // Кнопка перехода из внутреннего списка

    void on_listWidgetDiskSongList_doubleClicked(const QModelIndex &index); // Переход из внутреннего листа

    void on_pushButtonDiskEditSong_clicked(); // Кнопка перехода из внутреннего списка

    void on_listWidgetSongAuthorList_doubleClicked(const QModelIndex &index); // Переход из внутреннего списка авторов

    void on_pushButtonSongEditAuthor_clicked(); // Кнопка перехода из внутреннего списка авторов

    void on_listWidgetSongDiskList_doubleClicked(const QModelIndex &index); // Переход из внутреннего списка дисков

    void on_pushButtonSongEditDisk_clicked(); // Кнопка перехода из внутреннего списка дисков

    void on_lineEditAuthorName_textChanged(const QString &arg1); // Переключение в режим изменения, если изменилось название

    void on_pushButtonAuthorSave_clicked(); // Сохранение изменений

    void on_pushButtonAuthorDiscard_clicked(); // Отмена изменений

    void on_pushButtonAuthorNew_clicked(); // Создание нового автора

    void on_lineEditDiskName_textChanged(const QString &arg1); // Переключение в режим изменения, если изменилось название

    void on_pushButtonDiskSave_clicked(); // Сохранение изменений

    void on_pushButtonDiskDiscard_clicked(); // Отмена изменений

    void on_pushButtonDiskNew_clicked(); // Создание нового диска

    void on_pushButtonAuthorDelete_clicked(); // Удаление текущего автора

    void on_pushButtonDiskDelete_clicked(); // Удаление текущего диска

    void on_lineEditSongName_textChanged(const QString &arg1); // Переключение в режим изменения, если изменилось название

    void on_pushButtonSongSave_clicked(); // Сохранение изменений

    void on_pushButtonSongDiscard_clicked(); // Отмена изменений

    void on_pushButtonSongNew_clicked(); // Создание новой песни

    void on_pushButtonSongDelete_clicked(); // Удаление текущей песни

    void on_pushButtonSongAddAuthor_clicked(); // Добавление связи Автор-Песня

    void on_pushButtonSongAddDisk_clicked(); // Добавление связи Диск-Песня

    void on_pushButtonSongDeleteAuthor_clicked(); // Удаление связи Автор-Песня

    void on_pushButtonSongDeleteDisk_clicked(); // Удаление связи Диск-Песня

    void on_actionNew_File_triggered(); // Создание нового проекта

private:
    Ui::MainWindow *ui;
    About *about;
    Report *report;

signals:
    void signalDisplaySearchSetHeader(QString item);
    void signalDisplaySearchAddToList(QString item);

};

#endif // MAINWINDOW_H
