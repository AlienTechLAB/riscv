#include <sys/stat.h>
#include <stdio.h>
#include "general.h"

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