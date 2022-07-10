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

void Disk::ChangeDisk(int _DiskId, std::string _DiskName, std::vector<int> _ListIdSong)
{
    DiskId = _DiskId;
    DiskName = _DiskName;
    ListIdSong = _ListIdSong;
}

void Disk::SetId(int _DiskId)
{
    DiskId = _DiskId;
}
int Disk::GetId()
{
    return DiskId;
}

void Disk::SetName(std::string _DiskName)
{
    DiskName = _DiskName;
}
std::string Disk::GetName()
{
    return DiskName;
}

std::vector<int> Disk::GetSongs()
{
    return ListIdSong;
}

void Disk::AddSong(int songid)
{
    for (int i = 0; i < ListIdSong.size(); i++)
        if (ListIdSong[i] == songid)
            return;
    ListIdSong.push_back(songid);
}

void Disk::RemoveSong(int songid)
{
    for (int i = 0; i < ListIdSong.size(); i++)
        if (ListIdSong[i] == songid)
            ListIdSong.erase(ListIdSong.begin() + i);
}

#endif // DISK_H
