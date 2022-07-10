#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "list.h"
#include "author.h"
#include "song.h"
#include "disk.h"

std::string SearchName(List<Song> SongList, int SongId)
{
    Element<Song> *t = SongList.GetFirst();
    while (t)
    {
        if (SongId == t->data.GetId())
            return (t->data.GetName());
        t = t->next;
    }
    return "NOREF";
}

std::string SearchName(List<Author> AuthorList, int AuthorId)
{
    Element<Author> *t = AuthorList.GetFirst();
    while (t)
    {
        if (AuthorId == t->data.GetId())
            return (t->data.GetName());
        t = t->next;
    }
    return "NOREF";
}

std::string SearchName(List<Disk> DiskList, int DiskId)
{
    Element<Disk> *t = DiskList.GetFirst();
    while (t)
    {
        if (DiskId == t->data.GetId())
            return (t->data.GetName());
        t = t->next;
    }
    return "NOREF";
}


// Поиск элемента по id
Element<Author> *SearchElemetById(List<Author> AuthorList, int AuthorId)
{
    Element<Author> *t = AuthorList.GetFirst();
    while (t)
    {
        if (AuthorId == t->data.GetId())
            return t;
        t = t->next;
    }
    return NULL;
}

Element<Disk> *SearchElemetById(List<Disk> DiskList, int DiskId)
{
    Element<Disk> *t = DiskList.GetFirst();
    while (t)
    {
        if (DiskId == t->data.GetId())
            return t;
        t = t->next;
    }
    return NULL;
}

Element<Song> *SearchElemetById(List<Song> SongList, int SongId)
{
    Element<Song> *t = SongList.GetFirst();
    while (t)
    {
        if (SongId == t->data.GetId())
            return t;
        t = t->next;
    }
    return NULL;
}
// Удаление связей Автора
void deleteLinks(Element<Author> *at, List<Song> &SongList)
{
    int AuthorId = at->data.GetId();
    std::vector<int> AuthorListIdSong = at->data.GetSongs();
    for (int i = 0; i < AuthorListIdSong.size(); i++)
    {
        Element<Song> *st = SongList.GetFirst();
        while (st)
        {
            if (st->data.GetId() == AuthorListIdSong[i])
            {
                st->data.RemoveAuthor(AuthorId);
                break;
            }
            st = st->next;
        }
    }

}
// Удаление связей Диска
void deleteLinks(Element<Disk> *dt, List<Song> &SongList)
{
    int DiskId = dt->data.GetId();
    std::vector<int> DiskListIdSong = dt->data.GetSongs();

    for (int i = 0; i < DiskListIdSong.size(); i++)
    {
        Element<Song> *st = SongList.GetFirst();
        while (st)
        {
            if (st->data.GetId() == DiskListIdSong[i])
            {
                st->data.RemoveDisk(DiskId);
                break;
            }
            st = st->next;
        }
    }
}
// Удаление связей Песни
void deleteLinks(Element<Song> *st, List<Author> &AuthorList, List<Disk> &DiskList)
{
    int SongId = st->data.GetId();

    std::vector<int> ListIdAuthor = st->data.GetAuthors();
    std::vector<int> ListIdDisk = st->data.GetDisks();

    // Удаление связей с авторами
    for (int i = 0; i < ListIdAuthor.size(); i++)
    {
        Element<Author> *at = AuthorList.GetFirst();
        while (at)
        {
            if (at->data.GetId() == ListIdAuthor[i])
            {
                at->data.RemoveSong(SongId);
                break;
            }
            at = at->next;
        }
    }
    // Удаление связей с дисками
    for (int i = 0; i < ListIdDisk.size(); i++)
    {
        Element<Disk> *dt = DiskList.GetFirst();
        while (dt)
        {
            if (dt->data.GetId() == ListIdDisk[i])
            {
                dt->data.RemoveSong(SongId);
                break;
            }
            dt = dt->next;
        }
    }
}

nlohmann::ordered_json jsonFromFile(std::string FileNameInput)
{
    std::ifstream ifs{FileNameInput}; //Открытие файла
    if (!ifs.is_open())
    {
        std::cerr << "Unable to open file\n";
        throw 1;
    }
    nlohmann::ordered_json file_json = nlohmann::ordered_json::parse(ifs); //Перевод в Json
    ifs.close(); //Закрытие файла

    return file_json;
}

// Чтение Json в Лист
void readAuthors(nlohmann::ordered_json file_json, List<Author> &AuthorList)
{
    int AuthorId;
    std::string AuthorName;
    std::vector<int> AuthorListIdSong;
    Author currentAuthor;
    for (nlohmann::ordered_json::iterator it1 = file_json.at("authors").begin(); it1 != file_json.at("authors").end(); ++it1)
    {
        AuthorId = std::stoi(it1.key());
        AuthorName = file_json.at("authors").at(it1.key())["name"].get<std::string>();
        AuthorListIdSong = file_json.at("authors").at(it1.key())["songs"].get<std::vector<int>>();
        currentAuthor.ChangeAuthor(AuthorId, AuthorName, AuthorListIdSong);
        AuthorList.AddEnd(currentAuthor);
    }
}
// Чтение Json в Лист
void readDisks(nlohmann::ordered_json file_json, List<Disk> &DiskList)
{
    int DiskId;
    std::string DiskName;
    std::vector<int> DiskListIdSong;
    Disk currentDisk;
    for (nlohmann::ordered_json::iterator it1 = file_json.at("disks").begin(); it1 != file_json.at("disks").end(); ++it1)
    {
        DiskId = std::stoi(it1.key());
        DiskName = file_json.at("disks").at(it1.key())["name"].get<std::string>();
        DiskListIdSong = file_json.at("disks").at(it1.key())["songs"].get<std::vector<int>>();
        currentDisk.ChangeDisk(DiskId, DiskName, DiskListIdSong);
        DiskList.AddEnd(currentDisk);
    }
}
// Чтение Json в Лист
void readSongs(nlohmann::ordered_json file_json, List<Song> &SongList)
{
    int SongId;
    std::string SongName;
    std::vector<int> ListIdAuthor;
    std::vector<int> ListIdDisk;
    Song currentSong;
    for (nlohmann::ordered_json::iterator it1 = file_json.at("songs").begin(); it1 != file_json.at("songs").end(); ++it1)
    {
        SongId = std::stoi(it1.key());
        SongName = file_json.at("songs").at(it1.key())["name"].get<std::string>();
        ListIdAuthor = file_json.at("songs").at(it1.key())["authors"].get<std::vector<int>>();
        ListIdDisk = file_json.at("songs").at(it1.key())["disks"].get<std::vector<int>>();
        currentSong.ChangeSong(SongId, SongName, ListIdAuthor, ListIdDisk);
        SongList.AddEnd(currentSong);
    }
}

#endif // PROCESS_H
