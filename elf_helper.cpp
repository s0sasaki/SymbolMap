
#include "elf_helper.h"

namespace ElfHelper{

void printElfHeader(const Elf_Ehdr &elf_header){
    std::cout << "elf_header.e_type      " << elf_header.e_type      << std::endl;
    std::cout << "elf_header.e_machine   " << elf_header.e_machine   << std::endl;
    std::cout << "elf_header.e_version   " << elf_header.e_version   << std::endl;
    std::cout << "elf_header.e_entry     " << elf_header.e_entry     << std::endl;
    std::cout << "elf_header.e_phoff     " << elf_header.e_phoff     << std::endl;
    std::cout << "elf_header.e_shoff     " << elf_header.e_shoff     << std::endl;
    std::cout << "elf_header.e_flags     " << elf_header.e_flags     << std::endl;
    std::cout << "elf_header.e_ehsize    " << elf_header.e_ehsize    << std::endl;
    std::cout << "elf_header.e_phentsize " << elf_header.e_phentsize << std::endl;
    std::cout << "elf_header.e_phnum     " << elf_header.e_phnum     << std::endl;
    std::cout << "elf_header.e_shentsize " << elf_header.e_shentsize << std::endl;
    std::cout << "elf_header.e_shnum     " << elf_header.e_shnum     << std::endl;
    std::cout << "elf_header.e_shstrndx  " << elf_header.e_shstrndx  << std::endl;
}
void printProgramHeader(const Elf_Phdr &program_header){
    std::cout << "program_header.p_type   " << segmentType(program_header) << std::endl;
    std::cout << "program_header.p_flags  " << program_header.p_flags  << std::endl;
    std::cout << "program_header.p_offset " << program_header.p_offset << std::endl;
    std::cout << "program_header.p_vaddr  " << program_header.p_vaddr  << std::endl;
    std::cout << "program_header.p_paddr  " << program_header.p_paddr  << std::endl;
    std::cout << "program_header.p_filesz " << program_header.p_filesz << std::endl;
    std::cout << "program_header.p_memsz  " << program_header.p_memsz  << std::endl;
    std::cout << "program_header.p_align  " << program_header.p_align  << std::endl;
}
void printSectionHeader(const Elf_Shdr &section_header){
    std::cout << "section_header.sh_name     " << section_header.sh_name       << std::endl;
    std::cout << "section_header.sh_type     " << section_header.sh_type       << std::endl;
    std::cout << "section_header.sh_flags    " << section_header.sh_flags      << std::endl;
    std::cout << "section_header.sh_addr     " << section_header.sh_addr       << std::endl;
    std::cout << "section_header.sh_offset   " << section_header.sh_offset     << std::endl;
    std::cout << "section_header.sh_size     " << section_header.sh_size       << std::endl;
    std::cout << "section_header.sh_link     " << section_header.sh_link       << std::endl;
    std::cout << "section_header.sh_info     " << section_header.sh_info       << std::endl;
    std::cout << "section_header.sh_addralign" << section_header.sh_addralign  << std::endl;
    std::cout << "section_header.sh_entsize  " << section_header.sh_entsize    << std::endl;
}
void printSymbol(const Elf_Sym &symbol){
    std::cout << "symbol.st_name  " << symbol.st_name  << std::endl;
    std::cout << "symbol.st_info  " << static_cast<int>ELF_ST_TYPE(symbol.st_info)  << std::endl;
    std::cout << "symbol.st_other " << static_cast<int>(symbol.st_other) << std::endl;
    std::cout << "symbol.st_shndx " << symbol.st_shndx << std::endl;
    std::cout << "symbol.st_value " << symbol.st_value << std::endl;
    std::cout << "symbol.st_size  " << symbol.st_size  << std::endl;
}
std::string segmentType(const Elf_Phdr &program_header){
    switch(program_header.p_type){
        case PT_NULL:       return "    NULL";
        case PT_LOAD:       return "    LOAD"; 
        case PT_DYNAMIC:    return " DYNAMIC";
        case PT_INTERP:     return "  INTERP";
        case PT_NOTE:       return "    NOTE";
        case PT_SHLIB:      return "   SHLIB";
        case PT_PHDR:       return "    PHDR";
        case PT_LOPROC:     return "  LOPROC";
        case PT_HIPROC:     return "  HIPROC";
        case PT_GNU_STACK:  return "GNUSTACK";
        default:            return "    ****";
    }
}

}

