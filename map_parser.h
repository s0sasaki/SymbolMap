
#include <fstream>
#include <string>
#include <cstring>
#include <climits>
#include <vector>

namespace MapParser{

struct Mapinfo{
    unsigned long begin;
    unsigned long end;
    unsigned long inode;
    unsigned long offset;
    char perm[5];
    char dev[6];
    char mapname[PATH_MAX];
};

std::vector<Mapinfo> readMapinfo(const std::string mapsfilename);

}
