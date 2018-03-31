
#include "elf_parser.h"

ElfParser::ElfParser(std::string elffilename): elffilename(elffilename){}

Elf_Ehdr ElfParser::readElfHeader(){
    Elf_Ehdr elf_header;
    std::ifstream ifs(elffilename);
    ifs.read(reinterpret_cast<char *>(&elf_header), sizeof(Elf_Ehdr));
    assert(IS_ELF(elf_header) && "This is not ELF file.");
    assert(elf_header.e_ident[EI_CLASS] == ELF_CLASS && "Unknown class.");
    assert(elf_header.e_ident[EI_DATA]  == ELF_DATA  && "Unknown class.");
    ifs.close();
    return elf_header;
}

std::vector<Elf_Phdr> ElfParser::readProgramHeaders(){
    Elf_Ehdr elf_header;
    Elf_Phdr program_header;
    std::vector<Elf_Phdr> program_header_vec;
    std::ifstream ifs(elffilename);
    elf_header = readElfHeader();
    for(int i=0; i<elf_header.e_phnum; i++){
        ifs.seekg(elf_header.e_phoff + elf_header.e_phentsize * i, std::ios_base::beg);
        ifs.read(reinterpret_cast<char *>(&program_header), sizeof(Elf_Phdr));
        program_header_vec.emplace_back(program_header);
    }
    ifs.close();
    return program_header_vec;
}

std::vector<Elf_Shdr> ElfParser::readSectionHeaders(){
    Elf_Ehdr elf_header;
    Elf_Shdr section_header;
    std::vector<Elf_Shdr> section_header_vec;
    std::ifstream ifs(elffilename);
    elf_header = readElfHeader();
    for(int i=0; i<elf_header.e_shnum; i++){
        ifs.seekg(elf_header.e_shoff + elf_header.e_shentsize * i, std::ios_base::beg);
        ifs.read(reinterpret_cast<char *>(&section_header), sizeof(Elf_Shdr));
        section_header_vec.emplace_back(section_header);
    }
    ifs.close();
    return section_header_vec;
}

Elf_Shdr ElfParser::readSectionShstrtab(){
    Elf_Ehdr elf_header;
    Elf_Shdr section_shstrtab;
    std::ifstream ifs(elffilename);
    elf_header = readElfHeader();
    
    ifs.seekg(elf_header.e_shoff + elf_header.e_shentsize * elf_header.e_shstrndx, std::ios_base::beg);
    ifs.read(reinterpret_cast<char *>(&section_shstrtab), sizeof(Elf_Shdr));
    ifs.close();
    return section_shstrtab;
}

Elf_Shdr ElfParser::readSectionSymtab(){
    Elf_Ehdr elf_header;
    Elf_Shdr section_symtab;
    std::vector<Elf_Shdr> section_header_vec;
    std::ifstream ifs(elffilename);
    elf_header = readElfHeader();
    section_header_vec = readSectionHeaders();
    for(auto i: section_header_vec){
        if(i.sh_type != SHT_SYMTAB) 
            continue;
        section_symtab = i;
    }
    ifs.close();
    return section_symtab;
}

std::string ElfParser::readSectionname(const Elf_Shdr &section_header){
    std::string sectionname;
    Elf_Shdr section_shstrtab;
    std::ifstream ifs(elffilename);
    section_shstrtab = readSectionShstrtab();
    ifs.seekg(section_shstrtab.sh_offset + section_header.sh_name, std::ios_base::beg);
    getline(ifs, sectionname, '\0');
    ifs.close();
    return sectionname;
}

Elf_Shdr ElfParser::readASectionHeader(std::string target_sectionname){
    Elf_Shdr section_header;
    std::vector<Elf_Shdr> section_header_vec;
    section_header_vec = readSectionHeaders();
    for(auto i: section_header_vec){
        std::string sectionname;
        sectionname = readSectionname(i);
        if(sectionname == target_sectionname)
            section_header = i;
    }
    return section_header;
}

std::vector<Elf_Sym> ElfParser::readSymbols(){
    Elf_Shdr section_symtab;
    Elf_Sym  symbol;
    std::vector<Elf_Sym>  symbol_vec;
    std::ifstream ifs(elffilename);
    section_symtab = readSectionSymtab();
    for(int i=0; i<section_symtab.sh_size/section_symtab.sh_entsize; i++){
        ifs.seekg(section_symtab.sh_offset + section_symtab.sh_entsize * i, std::ios_base::beg);
        ifs.read(reinterpret_cast<char *>(&symbol), sizeof(Elf_Sym));
        symbol_vec.emplace_back(symbol);
    }
    ifs.close();
    return symbol_vec;
}

std::string ElfParser::readSymbolname(const Elf_Sym &symbol){
    std::string symbolname;
    Elf_Shdr section_strtab;
    std::ifstream ifs(elffilename);
    section_strtab = readASectionHeader(".strtab");
    if(!symbol.st_name)
        return "";
    ifs.seekg(section_strtab.sh_offset + symbol.st_name, std::ios_base::beg);
    getline(ifs, symbolname, '\0');
    ifs.close();
    return symbolname;
}


