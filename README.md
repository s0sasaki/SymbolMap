
# SymbolMap

SymbolMap scans symbols, sections, and segments in an ELF file and lists them with its process memory map.

See hello.c and its result at hello.symbolmap_result.txt for example.


# Usage

Run an ELF file and execute symbolmap like this:

./symbolmap [ELFFILE] [PID]


# References

 - 坂井 弘亮 "リンカ・ローダ実践開発テクニック"
 - Linux Programmer's Manual (5) ELF
 - Linux Programmer's Manual (5) PROC
 - https://github.com/cbbrowne/pmap


