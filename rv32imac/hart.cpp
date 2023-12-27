#include "hart.h"

hart::hart(uint8_t* memory)
{
	iCpu.pMemory = memory;
}

void hart::start(uint64_t entryPoint)
{
	iCpu.pc = entryPoint;
	iRunning.store(true);
	iThread = std::thread([this]() { this->loop(); });
}

err_t hart::stop()
{
	iRunning.store(false);
	iThread.join();
	return iThreadErr;
}

void hart::loop()
{
	uint64_t counter = 0;
	while (iRunning.load()) {
		const uint32_t mcode = *((uint32_t*)&iCpu.pMemory[iCpu.pc]);
		const err_t err = iCpu.execute(mcode);
		counter++;
		if (err != err_t::ok) {
			iRunning.store(false);
			iThreadErr = err_t::error;
			fprintf(stderr, "ERROR at pc = %lu, counter = %lu\n", iCpu.pc, counter);
		}
	}
}