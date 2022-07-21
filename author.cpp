#include "author.h"

void Author::ChangeAuthor(int _AuthorId, std::string _AuthorName, std::vector<int> _ListIdSong)
{
    AuthorId = _AuthorId;
    AuthorName = _AuthorName;
    ListIdSong = _ListIdSong;
}

//Изменить Id автора
void Author::SetId(int _AuthorId)
{
    AuthorId = _AuthorId;
}

//Получить Id автора
int Author::GetId()
{
    return AuthorId;
}

//Изменить название группы
void Author::SetName(std::string _AuthorName)
{
    AuthorName = _AuthorName;
}

//Получить название группы
std::string Author::GetName()
{
    return AuthorName;
}

//Получить песни у Автора
std::vector<int> Author::GetSongs()
{
    return ListIdSong;
}

//Добавить песню автору
void Author::AddSong(int songid)
{
    for (int i = 0; i < ListIdSong.size(); i++)
        if (ListIdSong[i] == songid)
            return;
    ListIdSong.push_back(songid);
}

//Удалить песню у Автора
void Author::RemoveSong(int songid)
{
    for (int i = 0; i < ListIdSong.size(); i++)
        if (ListIdSong[i] == songid)
            ListIdSong.erase(ListIdSong.begin() + i);
}
