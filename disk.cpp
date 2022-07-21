#include "disk.h"


void Disk::ChangeDisk(int _DiskId, std::string _DiskName, std::vector<int> _ListIdSong)
{
    DiskId = _DiskId;
    DiskName = _DiskName;
    ListIdSong = _ListIdSong;
}

//Изменить Id диска
void Disk::SetId(int _DiskId)
{
    DiskId = _DiskId;
}

//Получить Id диска
int Disk::GetId()
{
    return DiskId;
}

//Изменить название диска
void Disk::SetName(std::string _DiskName)
{
    DiskName = _DiskName;
}

//Получить название диска
std::string Disk::GetName()
{
    return DiskName;
}

//Получить песни у диска
std::vector<int> Disk::GetSongs()
{
    return ListIdSong;
}

//Добавить песню диску
void Disk::AddSong(int songid)
{
    for (int i = 0; i < ListIdSong.size(); i++)
        if (ListIdSong[i] == songid)
            return;
    ListIdSong.push_back(songid);
}

//Удалить песню у диска
void Disk::RemoveSong(int songid)
{
    for (int i = 0; i < ListIdSong.size(); i++)
        if (ListIdSong[i] == songid)
            ListIdSong.erase(ListIdSong.begin() + i);
}
