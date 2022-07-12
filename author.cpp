#include "author.h"

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
