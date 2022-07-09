#ifndef AUTHOR
#define AUTHOR

#include <iostream>
#include <string>
#include <vector>

class Author
{
private:
    int AuthorId;                // Id Автора
    std::string AuthorName;      //Название группы
    std::vector<int> ListIdSong; //Список песен

public:
    Author()
    {
        AuthorId = 0;
        AuthorName = "";
        ListIdSong = {};
    }

    void ChangeAuthor(int _AuthorId, std::string _AuthorName, std::vector<int> _ListIdSong);

    void SetId(int _AuthorId); //Изменить Id автора
    int GetId();               //Получить Id автора

    void SetName(std::string _AuthorName); //Изменить название группы
    std::string GetName();                 //Получить название группы

    void Show();                 //Показать список песен автора
    void AddSong(int songid);    //Добавить песню автору
    void RemoveSong(int songid); //Удалить песню у Автора
    std::vector<int> GetSongs(); //Получить песни у Автора
};

void Author::ChangeAuthor(int _AuthorId, std::string _AuthorName, std::vector<int> _ListIdSong)
    {
        AuthorId = _AuthorId;
        AuthorName = _AuthorName;
        ListIdSong = _ListIdSong;
    }

void Author::SetId(int _AuthorId)
{
    AuthorId = _AuthorId;
}

int Author::GetId()
{
    return AuthorId;
}

void Author::SetName(std::string _AuthorName)
{
    AuthorName = _AuthorName;
}

std::string Author::GetName()
{
    return AuthorName;
}

std::vector<int> Author::GetSongs()
{
    return ListIdSong;
}

void Author::AddSong(int songid)
{
    for (int i = 0; i < ListIdSong.size(); i++)
        if (ListIdSong[i] == songid)
            return;
    ListIdSong.push_back(songid);
}

void Author::RemoveSong(int songid)
{
    for (int i = 0; i < ListIdSong.size(); i++)
        if (ListIdSong[i] == songid)
            ListIdSong.erase(ListIdSong.begin() + i);
}


#endif // AUTHOR
