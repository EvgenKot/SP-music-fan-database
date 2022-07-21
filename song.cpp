#include "song.h"

// Установить все поля песни
void Song::ChangeSong(int _SongId, std::string _SongName, std::vector<int> _ListIdAuthor, std::vector<int> _ListIdDisk)
{
    SongId = _SongId;
    SongName = _SongName;
    ListIdAuthor = _ListIdAuthor;
    ListIdDisk = _ListIdDisk;
}
// Изменить Id песни
void Song::SetId(int _SongId)
{
    SongId = _SongId;
}
// Получить Id песни
int Song::GetId()
{
    return SongId;
}
// Изменить название песни
void Song::SetName(std::string _SongName)
{
    SongName = _SongName;
}
// Получить название песни
std::string Song::GetName()
{
    return SongName;
}

// Добавить автора песни
void Song::AddAuthor(int authorid)
{
    for (int i = 0; i < ListIdAuthor.size(); i++)
        if (ListIdAuthor[i] == authorid)
            return;
    ListIdAuthor.push_back(authorid);
}
// Удалить автора песни
void Song::RemoveAuthor(int authorid)
{
    for (int i = 0; i < ListIdAuthor.size(); i++)
        if (ListIdAuthor[i] == authorid)
            ListIdAuthor.erase(ListIdAuthor.begin() + i);
}
// Получить авторов песни
std::vector<int> Song::GetAuthors()
{
    return ListIdAuthor;
}

// Добавить диск песне
void Song::AddDisk(int diskid)
{
    for (int i = 0; i < ListIdDisk.size(); i++)
        if (ListIdDisk[i] == diskid)
            return;
    ListIdDisk.push_back(diskid);
}
// Удалить диск песни
void Song::RemoveDisk(int diskid)
{
    for (int i = 0; i < ListIdDisk.size(); i++)
        if (ListIdDisk[i] == diskid)
            ListIdDisk.erase(ListIdDisk.begin() + i);
}
// Получить диски песни
std::vector<int> Song::GetDisks()
{
    return ListIdDisk;
}

void Song::SetAuthors(std::vector<int> _ListIdAuthor)
{
    ListIdAuthor = _ListIdAuthor;
}

void Song::SetDisks(std::vector<int> _ListIdDisk)
{
    ListIdDisk = _ListIdDisk;
}
