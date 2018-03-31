
#include "elf_utility.h"

namespace ElfHelper{

void printElfHeader(const Elf_Ehdr &elf_header);
void printProgramHeader(const Elf_Phdr &program_header);
void printSectionHeader(const Elf_Shdr &section_header);
void printSymbol(const Elf_Sym &symbol);
std::string segmentType(const Elf_Phdr &program_header);

}

