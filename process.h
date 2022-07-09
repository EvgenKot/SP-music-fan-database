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

#endif // PROCESS_H
