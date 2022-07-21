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


#endif // AUTHOR
