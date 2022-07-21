#ifndef DISK_H
#define DISK_H

#include <iostream>
#include <string>
#include <vector>

class Disk
{
private:
    int DiskId;                  // Id диска
    std::string DiskName;        //Название диска
    std::vector<int> ListIdSong; //Список песен

public:
    Disk()
    {
        DiskId = 0;
        DiskName = "";
        ListIdSong = {};
    }

    void ChangeDisk(int _DiskId, std::string _DiskName, std::vector<int> _ListIdSong);

    void SetId(int _DiskId); //Изменить Id диска
    int GetId();             //Получить Id диска

    void SetName(std::string _DiskName); //Изменить название диска
    std::string GetName();               //Получить название диска

    void Show();                 //Показать список песен диска
    void AddSong(int songid);    //Добавить песню диску
    void RemoveSong(int songid); //Удалить песню у диска
    std::vector<int> GetSongs(); //Получить песни у диска
};


#endif // DISK_H
