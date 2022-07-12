#include "disk.h"


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
