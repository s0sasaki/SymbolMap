
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <algorithm>
#include <cassert>

#include <elf.h>

#ifndef __FBSD_TO_LINUX__
#define __FBSD_TO_LINUX__

#define ELF_ST_TYPE(v) ELF64_ST_TYPE(v)
#define ELF_ST_BIND(v) ELF64_ST_BIND(v)
#define ELF_R_SYM(v)   ELF64_R_SYM(v)
#define ELF_R_TYPE(v)  ELF64_R_TYPE(v)

#define ELF_CLASS      ELFCLASS64 
#define ELF_DATA       ELFDATA2LSB
#define ELF_TARG_CLASS ELFCLASS64 
#define ELF_TARG_DATA  ELFDATA2LSB
#define ELF_TARG_MACH  EM_386     
#define ELF_TARG_VER   1          

using Elf_Ehdr = Elf64_Ehdr;
using Elf_Phdr = Elf64_Phdr;
using Elf_Shdr = Elf64_Shdr; 
using Elf_Sym  = Elf64_Sym ; 
using Elf_Rel  = Elf64_Rel ; 
using Elf_Rela = Elf64_Rela; 

using Elf_Size = Elf64_Word; 
using Elf_Addr = Elf64_Addr; 
using Elf_Note = Elf64_Nhdr; 

inline bool IS_ELF(Elf_Ehdr ehdr){
	return (ehdr).e_ident[EI_MAG0] == ELFMAG0 &&
	       (ehdr).e_ident[EI_MAG1] == ELFMAG1 && 
	       (ehdr).e_ident[EI_MAG2] == ELFMAG2 && 
	       (ehdr).e_ident[EI_MAG3] == ELFMAG3;
}

#endif


