
#include "elf_utility.h"

class ElfParser {
public:
    std::string elffilename;
    ElfParser(std::string elffilename);
    Elf_Ehdr readElfHeader();
    std::vector<Elf_Phdr> readProgramHeaders();
    std::vector<Elf_Shdr> readSectionHeaders();
    Elf_Shdr readSectionShstrtab();
    Elf_Shdr readSectionSymtab();
    std::string readSectionname(const Elf_Shdr &section_header);
    Elf_Shdr readASectionHeader(std::string target_sectionname);
    std::vector<Elf_Sym> readSymbols();
    std::string readSymbolname(const Elf_Sym &symbol);
};

