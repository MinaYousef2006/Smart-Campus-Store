#ifndef search_h
#define search_h
#include "Resource.h"
#include <vector>
class search {
private:
    vector<Resource*>items;
public:
    search(vector<Resource*>& inventory);
    void searchId(int id);
};
#endif