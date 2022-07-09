#ifndef SONG_H
#define SONG_H

#include <iostream>
#include <string>
#include <vector>

class Song
{
private:
    int SongId;                    // Id песни
    std::string SongName;          // Название песни
    std::vector<int> ListIdAuthor; // Список авторов песни
    std::vector<int> ListIdDisk;   // Список дисков песен

public:
    Song() // Конструктор
    {
        SongId = 0;
        SongName = "";
        ListIdAuthor = {};
        ListIdDisk = {};
    }
    // Установить все поля песни
    void ChangeSong(int _SongId, std::string _SongName, std::vector<int> _ListIdAuthor, std::vector<int> _ListIdDisk);

    void SetId(int _SongId); // Изменить Id песни
    int GetId();             // Получить Id песни

    void SetName(std::string _SongName); // Изменить название песни
    std::string GetName();               // Получить название песни

    void AddAuthor(int authorid);    // Добавить автора песни
    void RemoveAuthor(int authorid); // Удалить автора песни
    void SetAuthors(std::vector<int> _ListIdAuthor); //Установить авторов песни
    std::vector<int> GetAuthors();   // Получить авторов песни

    void AddDisk(int diskid);    // Добавить диск песне
    void RemoveDisk(int diskid); // Удалить диск песни
    void SetDisks(std::vector<int> _ListIdDisk); //Установить диски песни
    std::vector<int> GetDisks(); // Получить диски песни
};
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


#endif // SONG_H
