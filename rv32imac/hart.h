#ifndef HART_H
#define HART_H

#include <stdint.h>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include "types.h"
#include "rv32imac.h"
#include "memory.h"

using namespace riscv;

class hart
{
public:
	hart(memory& memory);
	err_t start(uint64_t entryPoint);
	err_t stop();
	err_t pause();
	err_t resume();
	err_t step();

private:
	void loop();
	err_t executeInstr();

	memory& iMemory;
	rv32imac iCpu;
	uint64_t iCounter{ 0 };
	std::thread iThread;
	std::mutex iHartMutex;
	std::mutex iPauseMutex;
	std::mutex iResumeMutex;
	std::condition_variable iPauseCV;
	std::condition_variable iResumeCV;
	bool iWorking{ false };
	bool iRunning{ false };
	bool iPausing{ false };
	bool iResuming{ false };
	err_t iThreadErr{ err_t::ok };
};

#endif	// HART_H