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

    void AddAuthor(int authorid);                    // Добавить автора песни
    void RemoveAuthor(int authorid);                 // Удалить автора песни
    void SetAuthors(std::vector<int> _ListIdAuthor); //Установить авторов песни
    std::vector<int> GetAuthors();                   // Получить авторов песни

    void AddDisk(int diskid);                    // Добавить диск песне
    void RemoveDisk(int diskid);                 // Удалить диск песни
    void SetDisks(std::vector<int> _ListIdDisk); //Установить диски песни
    std::vector<int> GetDisks();                 // Получить диски песни
};


#endif // SONG_H
