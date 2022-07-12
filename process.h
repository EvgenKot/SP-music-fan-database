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

class Process
{
public:
    static std::string SearchName(List<Song> SongList, int SongId);
    static std::string SearchName(List<Author> AuthorList, int AuthorId);
    static std::string SearchName(List<Disk> DiskList, int DiskId);

    static Element<Author> *SearchElemetById(List<Author> AuthorList, int AuthorId);
    static Element<Disk> *SearchElemetById(List<Disk> DiskList, int DiskId);
    static Element<Song> *SearchElemetById(List<Song> SongList, int SongId);

    static void deleteLinks(Element<Author> *at, List<Song> &SongList);
    static void deleteLinks(Element<Disk> *dt, List<Song> &SongList);
    static void deleteLinks(Element<Song> *st, List<Author> &AuthorList, List<Disk> &DiskList);

    static nlohmann::ordered_json jsonFromFile(std::string FileNameInput);

    static void readAuthors(nlohmann::ordered_json file_json, List<Author> &AuthorList);
    static void readDisks(nlohmann::ordered_json file_json, List<Disk> &DiskList);
    static void readSongs(nlohmann::ordered_json file_json, List<Song> &SongList);

    static void writeAuthors(nlohmann::ordered_json &output_file_json, List<Author> &AuthorList);
    static void writeDisks(nlohmann::ordered_json &output_file_json, List<Disk> &DiskList);
    static void writeSongs(nlohmann::ordered_json &output_file_json, List<Song> &SongList);

    static void jsonToFile(nlohmann::ordered_json output_file_json, std::string Output);

    static void updateLinksSongAuthors(Element<Song> *est, std::vector<int> ListIdAuthor, std::vector<int> ListIdAuthorOld, List<Author> &AuthorList);
    static void updateLinksSongDisks(Element<Song> *est, std::vector<int> ListIdDisk, std::vector<int> ListIdDiscOld, List<Disk> &DiskList);
};



#endif // PROCESS_H
