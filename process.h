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

std::string SearchSongName(List<Song> SongList, int SongId)
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

std::string SearchAuthorName(List<Author> AuthorList, int AuthorId)
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

std::string SearchDiskName(List<Disk> DiskList, int DiskId)
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


nlohmann::json jsonFromFile(std::string FileNameInput)
{

}

void toFile(std::string FileNameOutput,List<Author> AuthorList, List<Disk> DiskList, List<Song> SongList)
{
    nlohmann::json output_file_json{};
    
    std::cout << "Author writing..." << std::endl;
    Element<Author> *at = AuthorList.GetFirst();
    while (at)
    {
        output_file_json["authors"][std::to_string(at->data.GetId())]["name"] = at->data.GetName();
        output_file_json["authors"][std::to_string(at->data.GetId())]["songs"] = at->data.GetSongs();
        at = at->next;
    }
    std::cout << "Author writing completed." << std::endl;

    std::cout << "Disk writing..." << std::endl;
    Element<Disk> *dt = DiskList.GetFirst();
    while (dt)
    {
        output_file_json["disks"][std::to_string(dt->data.GetId())]["name"] = dt->data.GetName();
        output_file_json["disks"][std::to_string(dt->data.GetId())]["songs"] = dt->data.GetSongs();
        dt = dt->next;
    }
    std::cout << "Disk writing completed." << std::endl;

    std::cout << "Song writing..." << std::endl;
    Element<Song> *st = SongList.GetFirst();
    while (st)
    {
        output_file_json["songs"][std::to_string(st->data.GetId())]["name"] = st->data.GetName();
        output_file_json["songs"][std::to_string(st->data.GetId())]["authors"] = st->data.GetAuthors();
        output_file_json["songs"][std::to_string(st->data.GetId())]["disks"] = st->data.GetDisks();
        st = st->next;
    }
    std::cout << "Song writing completed." << std::endl;

    //Вывод в файл
    std::ofstream outputstream(FileNameOutput);    
    outputstream << output_file_json << std::endl;
}

#endif // PROCESS_H
