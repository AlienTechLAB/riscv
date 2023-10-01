#include <cstring>
#include <sys/stat.h>
#include <stdio.h>
#include <elf.h>
#include "General.h"

res_t getFileSize(const char* filename, uint64_t& fileSize)
{
	if (filename == nullptr)
		return res_t::ERROR;
	struct stat stats;
	if (stat(filename, &stats) != 0)
		return res_t::ERROR;
	if (!S_ISREG(stats.st_mode))
		return res_t::ERROR;
	fileSize = static_cast<uint64_t>(stats.st_size);
	return res_t::OK;
}

res_t loadFile(const char* filename, uint8_t* buffer, uint64_t offset, uint64_t size)
{
	if (filename == nullptr || buffer == nullptr)
		return res_t::ERROR;
	uint64_t fileSize = 0;
	if (getFileSize(filename, fileSize) == res_t::ERROR)
		return res_t::ERROR;
	if ((offset >= fileSize) || (size > fileSize - offset))
		return res_t::ERROR;
	FILE* file = fopen(filename, "rb");
	if (file == nullptr)
		return res_t::ERROR;
	if (fseek(file, offset, SEEK_SET) != 0) {
		fclose(file);
		return res_t::ERROR;
	}
	if (fread(buffer, 1, size, file) != size) {
		fclose(file);
		return res_t::ERROR;
	}
	if (fclose(file))
		return res_t::ERROR;
	return res_t::OK;
}

res_t saveFile(const char* filename, uint8_t* buffer, uint64_t size)
{
	if (filename == nullptr || buffer == nullptr)
		return res_t::ERROR;
	FILE* file = fopen(filename, "wb");
	if (file == nullptr)
		return res_t::ERROR;
	if (fwrite(buffer, 1, size, file) != size) {
		fclose(file);
		return res_t::ERROR;
	}
	if (fflush(file) != 0)
		return res_t::ERROR;
	if (fclose(file))
		return res_t::ERROR;
	return res_t::OK;
}

// Simple ELF loader. TODO
res_t loadElf(const char* filename, uint8_t* memory, uint64_t& startAddr)
{
	uint64_t fileSize = 0;
	if (getFileSize(filename, fileSize) == res_t::ERROR)
		return res_t::ERROR;
	uint8_t* buffer = new uint8_t[fileSize];
	if (buffer == nullptr)
		return res_t::ERROR;
	if (::loadFile(filename, buffer, 0, fileSize) == res_t::ERROR) {
		delete[] buffer;
		buffer = nullptr;
	}
	const Elf64_Ehdr& header = *reinterpret_cast<Elf64_Ehdr*>(buffer);
	for (uint16_t i = 0; i < header.e_phnum; i++) {
		const Elf64_Phdr& phdr = *reinterpret_cast<const Elf64_Phdr*>(buffer + (header.e_phoff + i * header.e_phentsize));
		if (phdr.p_type == PT_LOAD) {
			uint8_t* src = buffer + phdr.p_offset;
			uint8_t* dst = memory + phdr.p_paddr;
			memcpy(dst, src, phdr.p_filesz);
		}
	}
	startAddr = header.e_entry;
	return res_t::OK;
}