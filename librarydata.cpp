#include "librarydata.h"

vector<User> users;
vector<Book> books;

void loadSampleData()
{
    users.push_back({"admin", "1234", true});

    users.push_back({"jana", "1111", false});
    users.push_back({"sara", "2222", false});

    books.push_back({"Harry Potter and the Philosopher's Stone", "J.K. Rowling", "1001", "Fiction", "", 1997, false, false});

    books.push_back({"The Hunger Games", "Suzanne Collins", "1002", "Fiction", "", 2008, false, false});

    books.push_back({"The Silent Patient", "Alex Michaelides", "1003", "Fiction", "", 2019, false, false});

    books.push_back({"Verity", "Colleen Hoover", "1004", "Fiction", "", 2018, false, false});

    books.push_back({"The Cruel Prince", "Holly Black", "1005", "Fiction", "", 2018, true, false});
}
