
#include "map_parser.h"

namespace MapParser{

std::vector<Mapinfo> readMapinfo(const std::string mapsfilename){
    std::ifstream ifsmaps(mapsfilename);
    std::string buf;
    Mapinfo mapinfo;
    std::vector<Mapinfo> mapinfo_vec;
    while(getline(ifsmaps, buf)){
        std::memset(&mapinfo, 0, sizeof(Mapinfo));
        sscanf(buf.c_str(), "%lx-%lx %4s %lx %5s %ld %s", 
            &mapinfo.begin, &mapinfo.end, mapinfo.perm, &mapinfo.offset, 
            mapinfo.dev, &mapinfo.inode, mapinfo.mapname);
        mapinfo_vec.emplace_back(mapinfo);
    }
    ifsmaps.close();
    return mapinfo_vec;
}

}

