
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <elf.h>

#include "elf_helper.h"
#include "elf_parser.h"
#include "map_parser.h"

void symbolmap(std::string mapsfilename, std::string elffilename){
    std::string mapname_short;
    Elf_Ehdr elf_header;
    ElfParser elf(elffilename);
    Elf_Shdr section_strtab;
    std::vector<MapParser::Mapinfo> mapinfo_vec;
    std::vector<Elf_Phdr> program_header_vec;
    std::vector<Elf_Shdr> section_header_vec;
    std::vector<Elf_Sym>  symbol_vec;
    mapinfo_vec = MapParser::readMapinfo(mapsfilename);
    elf_header = elf.readElfHeader();
    program_header_vec = elf.readProgramHeaders();
    section_header_vec = elf.readSectionHeaders();
    section_strtab = elf.readASectionHeader(".strtab");
    symbol_vec = elf.readSymbols();
    std::cout << 
"                        Memory Maps                             |     Segment     |           Section           |           Symbol          \n" 
"----------------------------------------------------------------|-----------------|-----------------------------|---------------------------\n" 
"       Address       Perm   Size             PathName           | FileSize   Type | FileSize     SectionName    | FileSize     SymbolName   \n" 
"-------------------- ---- ------- ------------------------------|--------- -------|--------- -------------------|--------- -----------------\n";
    for(int i=0; i<mapinfo_vec.size(); i++){
        mapname_short = static_cast<std::string>(mapinfo_vec[i].mapname);
        if (mapname_short.size() > 30)
            mapname_short = mapname_short.substr(0, 7) + "..." +mapname_short.substr(mapname_short.size()-20);
        std::cout << std::setw(20) << std::right << mapinfo_vec[i].begin;
        std::cout << std::setw(5)  << std::right << mapinfo_vec[i].perm;
        std::cout << std::setw(8)  << std::right << mapinfo_vec[i].end - mapinfo_vec[i].begin;
        std::cout << " ";
        std::cout << std::setw(30) << std::left  << mapname_short;
        std::cout << "----------------------------------------------------------------------------" << std::endl;
        for(int j=0; j<program_header_vec.size(); j++){
            if(ElfHelper::segmentType(program_header_vec[j]) != "    LOAD" &&
               ElfHelper::segmentType(program_header_vec[j]) != " DYNAMIC" &&
               ElfHelper::segmentType(program_header_vec[j]) != "  INTERP" &&
               ElfHelper::segmentType(program_header_vec[j]) != "    PHDR" )
                continue;
            if(i==0 && program_header_vec[j].p_offset < mapinfo_vec[1].offset  ||
               i==1 && mapinfo_vec[1].offset <= program_header_vec[j].p_offset && program_header_vec[j].p_offset < mapinfo_vec[2].offset ||
               i==2 && mapinfo_vec[2].offset <= program_header_vec[j].p_offset) {
                std::cout << std::setw(20) << " ";
                std::cout << std::setw(5)  << std::right << mapinfo_vec[i].perm;
                std::cout << std::setw(39) << " " << "|";
                std::cout << std::setw(9) << std::right << program_header_vec[j].p_memsz;
                std::cout << ElfHelper::segmentType(program_header_vec[j]);
                std::cout << "----------------------------------------------------------" << std::endl;
            }
            for(int k=0; k<section_header_vec.size(); k++){
                if(section_header_vec[k].sh_addr == 0)
                    continue;
                if(i==0 && section_header_vec[k].sh_offset < mapinfo_vec[1].offset  
                        && program_header_vec[j].p_offset <= section_header_vec[k].sh_offset 
                        && section_header_vec[k].sh_offset < program_header_vec[j+1].p_offset  ||
                   i==1 && mapinfo_vec[1].offset          <= section_header_vec[k].sh_offset 
                        && section_header_vec[k].sh_offset < mapinfo_vec[2].offset 
                        && program_header_vec[j].p_offset <= section_header_vec[k].sh_offset 
                        && section_header_vec[k].sh_offset < program_header_vec[j+1].p_offset  ||
                   i==1 && mapinfo_vec[1].offset          <= section_header_vec[k].sh_offset 
                        && section_header_vec[k].sh_offset < mapinfo_vec[2].offset 
                        && ElfHelper::segmentType(program_header_vec[j]) == " DYNAMIC"       
                        && program_header_vec[j].p_offset <= section_header_vec[k].sh_offset   ||
                   i==2 && mapinfo_vec[2].offset          <= section_header_vec[k].sh_offset 
                        && program_header_vec[j].p_offset <= section_header_vec[k].sh_offset
                        && ElfHelper::segmentType(program_header_vec[j+1]) == " DYNAMIC" ){
                    std::cout << std::setw(20) << " ";
                    std::cout << std::setw(5)  << std::right << mapinfo_vec[i].perm;
                    std::cout << std::setw(39) << " " << "|";
                    std::cout << std::setw(17) << " " << "|";
                    std::cout << std::setw(9) << std::right << section_header_vec[k].sh_size;
                    std::cout << std::setw(20)  << std::right << elf.readSectionname(section_header_vec[k]);
                    std::cout << "----------------------------" << std::endl;
                    for(auto m: symbol_vec){
                        if(m.st_shndx != k)
                            continue;
                        if(elf.readSymbolname(m) == "")
                            continue;
                        std::cout << std::setw(20) << " ";
                        std::cout << std::setw(5)  << std::right << mapinfo_vec[i].perm;
                        std::cout << std::setw(39) << " " << "|";
                        std::cout << std::setw(17) << " " << "|";
                        std::cout << std::setw(29) << " " << "|";
                        std::cout << std::setw(9)  << std::right << m.st_size;
                        std::cout << " ";
                        std::string symbolname_short = elf.readSymbolname(m);
                        if(symbolname_short.size() > 17) 
                            symbolname_short = symbolname_short.substr(0, 17);
                        std::cout << std::left << symbolname_short << std::endl;
                    }
                }
            }
        }
    }
    return;
}

int main(int argc, char **argv){
    std::string pid;
    std::string mapsfilename;
    std::string elffilename;

    if(argc < 3){
        std::cerr << "usage: " << argv[0] << " ELFFILENAME PID"<< std::endl;
        exit(1);
    }
    elffilename = static_cast<std::string>(argv[1]);
    pid = static_cast<std::string>(argv[2]);
    mapsfilename = "/proc/" + pid + "/maps";

    symbolmap(mapsfilename, elffilename);

    return 0;
}
