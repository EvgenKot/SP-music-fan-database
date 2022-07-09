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
    void refresh();

    void refreshAuthor();

    void refreshDisk();

    void refreshSong();

    void AuthorOnEdit(bool option);

    void AuthorEditActivated(bool option);

    void DiskOnEdit(bool option);

    void DiskEditActivated(bool option);

    void SongOnEdit(bool option);

    void SongEditActivated(bool option);

    void on_actionAbout_triggered();

    void on_pushButtonDisplaySearchByAuthor_clicked();

    void on_pushButtonDisplaySearchBySong_clicked();

    void on_actionOpen_File_triggered();

    void saving(const QString fileNameOutput);

    void on_actionSave_As_triggered();

    void on_actionExit_triggered();

    void on_actionSave_triggered();

    void AuthorGoToEdit (int index);

    void on_listWidgetAuthorGoTo_doubleClicked(const QModelIndex &index);

    void DiskGoToEdit (int index);

    void on_listWidgetDiskGoTo_doubleClicked(const QModelIndex &index);

    void SongGoToEdit (int index);

    void on_listWidgetSongGoTo_doubleClicked(const QModelIndex &index);

    void on_pushButtonAuthorGoTo_clicked();

    void on_pushButtonDiskGoTo_clicked();

    void on_pushButtonSongGoTo_clicked();

    void on_lineEditAuthorSearch_textChanged(const QString &arg1);

    void on_lineEditDiskSearch_textChanged(const QString &arg1);

    void on_lineEditSongSearch_textChanged(const QString &arg1);

    void on_listWidgetAuthorSongList_doubleClicked(const QModelIndex &index);

    void on_pushButtonAuthorEditSong_clicked();

    void on_listWidgetDiskSongList_doubleClicked(const QModelIndex &index);

    void on_pushButtonDiskEditSong_clicked();

    void on_listWidgetSongAuthorList_doubleClicked(const QModelIndex &index);

    void on_pushButtonSongEditAuthor_clicked();

    void on_listWidgetSongDiskList_doubleClicked(const QModelIndex &index);

    void on_pushButtonSongEditDisk_clicked();

    void on_lineEditAuthorName_textChanged(const QString &arg1);

    void on_pushButtonAuthorSave_clicked();

    void on_pushButtonAuthorDiscard_clicked();

    void on_pushButtonAuthorNew_clicked();

    void on_lineEditDiskName_textChanged(const QString &arg1);

    void on_pushButtonDiskSave_clicked();

    void on_pushButtonDiskDiscard_clicked();

    void on_pushButtonDiskNew_clicked();

    void on_pushButtonAuthorDelete_clicked();

    void on_pushButtonDiskDelete_clicked();

    void on_lineEditSongName_textChanged(const QString &arg1);

    void on_pushButtonSongSave_clicked();

    void on_pushButtonSongDiscard_clicked();

    void on_pushButtonSongNew_clicked();

    void on_pushButtonSongDelete_clicked();

    void on_pushButtonSongAddAuthor_clicked();

    void on_pushButtonSongAddDisk_clicked();

    void on_pushButtonSongDeleteAuthor_clicked();

    void on_pushButtonSongDeleteDisk_clicked();

    void on_actionNew_File_triggered();

private:
    Ui::MainWindow *ui;
    About *about;
    Report *report;

signals:
    void signalDisplaySearchSetHeader(QString item);
    void signalDisplaySearchAddToList(QString item);

};

#endif // MAINWINDOW_H
