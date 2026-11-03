#ifndef LIBRARYDATA_H
#define LIBRARYDATA_H

#include <QString>
#include <vector>

using namespace std;

struct User
{
    QString username;
    QString password;
    bool isLibrarian;
};

struct Book
{
    QString title;
    QString author;
    QString isbn;
    QString category;
    QString borrowedBy;
    int year;
    bool isReferenceOnly;
    bool isBorrowed;
};

extern vector<User> users;
extern vector<Book> books;

void loadSampleData();

#endif