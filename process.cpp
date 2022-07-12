#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "process.h"


// Возвращает имя песни по id
std::string Process::SearchName(List<Song> SongList, int SongId)
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
// Возвращает имя Автора по id
std::string Process::SearchName(List<Author> AuthorList, int AuthorId)
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
// Возвращает имя Диска по id
std::string Process::SearchName(List<Disk> DiskList, int DiskId)
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


// Поиск элемента по id среди авторов
Element<Author> *Process::SearchElemetById(List<Author> AuthorList, int AuthorId)
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
// Поиск элемента по id среди дисков
Element<Disk> *Process::SearchElemetById(List<Disk> DiskList, int DiskId)
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
// Поиск элемента по id среди песен
Element<Song> *Process::SearchElemetById(List<Song> SongList, int SongId)
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
void Process::deleteLinks(Element<Author> *at, List<Song> &SongList)
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
void Process::deleteLinks(Element<Disk> *dt, List<Song> &SongList)
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
void Process::deleteLinks(Element<Song> *st, List<Author> &AuthorList, List<Disk> &DiskList)
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
// Открытие файла запись в json
nlohmann::ordered_json Process::jsonFromFile(std::string FileNameInput)
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
void Process::readAuthors(nlohmann::ordered_json file_json, List<Author> &AuthorList)
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
void Process::readDisks(nlohmann::ordered_json file_json, List<Disk> &DiskList)
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
void Process::readSongs(nlohmann::ordered_json file_json, List<Song> &SongList)
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

// Запись в json авторов
void Process::writeAuthors(nlohmann::ordered_json &output_file_json, List<Author> &AuthorList)
{
    Element<Author> *at = AuthorList.GetFirst();
    while (at)
    {
        output_file_json["authors"][std::to_string(at->data.GetId())]["name"] = at->data.GetName();
        output_file_json["authors"][std::to_string(at->data.GetId())]["songs"] = at->data.GetSongs();
        at = at->next;
    }
}
// Запись в json дисков
void Process::writeDisks(nlohmann::ordered_json &output_file_json, List<Disk> &DiskList)
{
    Element<Disk> *dt = DiskList.GetFirst();
    while (dt)
    {
        output_file_json["disks"][std::to_string(dt->data.GetId())]["name"] = dt->data.GetName();
        output_file_json["disks"][std::to_string(dt->data.GetId())]["songs"] = dt->data.GetSongs();
        dt = dt->next;
    }
}
// Запись в json песен
void Process::writeSongs(nlohmann::ordered_json &output_file_json, List<Song> &SongList)
{
    Element<Song> *st = SongList.GetFirst();
    while (st)
    {
        output_file_json["songs"][std::to_string(st->data.GetId())]["name"] = st->data.GetName();
        output_file_json["songs"][std::to_string(st->data.GetId())]["authors"] = st->data.GetAuthors();
        output_file_json["songs"][std::to_string(st->data.GetId())]["disks"] = st->data.GetDisks();
        st = st->next;
    }
}
// Запись в файл из json
void Process::jsonToFile(nlohmann::ordered_json output_file_json, std::string Output)
{
    std::ofstream outputstream(Output);
    outputstream << output_file_json << std::endl;

}

// Обновление связей Авторов
void Process::updateLinksSongAuthors(Element<Song> *est, std::vector<int> ListIdAuthor, std::vector<int> ListIdAuthorOld, List<Author> &AuthorList)
{
    Element<Author> *at;
    bool flag;

    for (int i = 0; i < ListIdAuthorOld.size(); i++)
    {
        flag = false;
        for (int j = 0; j < ListIdAuthor.size(); j++)
        {
            if (ListIdAuthorOld[i] == ListIdAuthor[j])
            {
                flag = true;
                break;
            }
        }
        if (not flag) // Delete links
        {
            at = AuthorList.GetFirst();
            while (at)
            {
                if (at->data.GetId() == ListIdAuthorOld[i])
                {
                    at->data.RemoveSong(est->data.GetId());
                    break;
                }

                at = at->next;
            }
            std::cout << ListIdAuthorOld[i] << " Deleteng Author link" << std::endl;
        }
    }
    for (int i = 0; i < ListIdAuthor.size(); i++)
    {
        flag = false;
        for (int j = 0; j < ListIdAuthorOld.size(); j++)
        {
            if (ListIdAuthor[i] == ListIdAuthorOld[j])
            {
                flag = true;
                break;
            }
        }
        if (not flag) // Add links
        {
            at = AuthorList.GetFirst();
            while (at)
            {
                if (at->data.GetId() == ListIdAuthor[i])
                {
                    at->data.AddSong(est->data.GetId());
                    break;
                }
                at = at->next;
            }
            std::cout << ListIdAuthor[i] << " Add Author link" << std::endl; // Del
        }
    }
}

// Обновление связей Дисков
void Process::updateLinksSongDisks(Element<Song> *est, std::vector<int> ListIdDisk, std::vector<int> ListIdDiscOld, List<Disk> &DiskList)
{
    bool flag;
    Element<Disk> *dt;


    for (int i = 0; i < ListIdDiscOld.size(); i++)
    {
        flag = false;
        for (int j = 0; j < ListIdDisk.size(); j++)
        {
            if (ListIdDiscOld[i] == ListIdDisk[j])
            {
                flag = true;
                break;
            }
        }
        if (not flag) // Delete links
        {
            dt = DiskList.GetFirst();
            while (dt)
            {
                if (dt->data.GetId() == ListIdDiscOld[i])
                {
                    dt->data.RemoveSong(est->data.GetId());
                    break;
                }

                dt = dt->next;
            }
            std::cout << ListIdDiscOld[i] << " Deleteng Disk link" << std::endl;
        }
    }

    for (int i = 0; i < ListIdDisk.size(); i++)
    {
        flag = false;
        for (int j = 0; j < ListIdDiscOld.size(); j++)
        {
            if (ListIdDisk[i] == ListIdDiscOld[j])
            {
                flag = true;
                break;
            }
        }
        if (not flag) // Add links
        {
            dt = DiskList.GetFirst();
            while (dt)
            {
                if (dt->data.GetId() == ListIdDisk[i])
                {
                    dt->data.AddSong(est->data.GetId());
                    break;
                }
                dt = dt->next;
            }
            std::cout << ListIdDisk[i] << " Add Disk link" << std::endl; // Del
        }
    }
}
