#ifndef BOOK_STORE
#define BOOK_STORE

#include "Resource.h"
using namespace std;
class BookStore:public Resource{
    private:
        string author;
        int pages;

    public:
        BookStore(int id, string n, double p, int q, string a, int pa);
        void display() override;
        string GetCategory() override;
        string GetAuthor();
        int GetPages();
};

#endif