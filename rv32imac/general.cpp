#include <cstring>
#include <sys/stat.h>
#include <stdio.h>
#include <elf.h>
#include <cassert>
#include "general.h"

err_t getFileSize(const char* filename, int64_t& fileSize)
{
	if (filename == nullptr)
		return err_t::error;
	struct stat stats;
	if (stat(filename, &stats) != 0)
		return err_t::error;
	if (!S_ISREG(stats.st_mode))
		return err_t::error;
	fileSize = static_cast<int64_t>(stats.st_size);
	return err_t::ok;
}

err_t loadFile(const char* filename, uint8_t* buffer, uint64_t offset, int64_t size)
{
	if (filename == nullptr || buffer == nullptr)
		return err_t::error;
	int64_t fileSize = 0;
	if (getFileSize(filename, fileSize) == err_t::error)
		return err_t::error;
	if (size == -1)
		size = fileSize;
	if ((offset >= fileSize) || (size > fileSize - offset))
		return err_t::error;
	FILE* file = fopen(filename, "rb");
	if (file == nullptr)
		return err_t::error;
	if (fseek(file, offset, SEEK_SET) != 0) {
		fclose(file);
		return err_t::error;
	}
	if (fread(buffer, 1, size, file) != size) {
		fclose(file);
		return err_t::error;
	}
	if (fclose(file))
		return err_t::error;
	return err_t::ok;
}

err_t saveFile(const char* filename, uint8_t* buffer, uint64_t size)
{
	if (filename == nullptr || buffer == nullptr)
		return err_t::error;
	FILE* file = fopen(filename, "wb");
	if (file == nullptr)
		return err_t::error;
	if (fwrite(buffer, 1, size, file) != size) {
		fclose(file);
		return err_t::error;
	}
	if (fflush(file) != 0)
		return err_t::error;
	if (fclose(file))
		return err_t::error;
	return err_t::ok;
}

// Simple ELF loader. TODO
err_t loadElf(const char* filename, uint8_t* memory, uint64_t& startAddr)
{
	int64_t fileSize = 0;
	if (getFileSize(filename, fileSize) == err_t::error)
		return err_t::error;
	uint8_t* buffer = new uint8_t[fileSize];
	if (buffer == nullptr)
		return err_t::error;
	if (::loadFile(filename, buffer, 0, fileSize) == err_t::error) {
		delete[] buffer;
		buffer = nullptr;
	}
	const Elf64_Ehdr& header = *reinterpret_cast<Elf64_Ehdr*>(buffer);
	for (uint16_t i = 0; i < header.e_phnum; i++) {
		const Elf64_Phdr& phdr = *reinterpret_cast<const Elf64_Phdr*>(buffer + (header.e_ehsize + i * header.e_phentsize));
		if (phdr.p_type == PT_LOAD) {
			uint8_t* src = buffer + phdr.p_offset;
			uint8_t* dst = memory + phdr.p_paddr;
			memcpy(dst, src, phdr.p_filesz);
		}
	}
	startAddr = header.e_entry;
	return err_t::ok;
}