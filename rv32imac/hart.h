#ifndef HART_H
#define HART_H

#include <stdint.h>
#include <thread>
#include <atomic>
#include <mutex>
#include "types.h"
#include "rv32imac.h"

using namespace riscv;

class hart
{
public:
	hart(uint8_t* memory);
	void start(uint64_t entryPoint);
	err_t stop();

private:
	void loop();

	std::thread iThread;
	std::atomic<bool> iRunning{ true };
	std::mutex iMutex;
	bool iStarted{ false };
	rv32imac iCpu;
	err_t iThreadErr{ err_t::ok };
};

#endif	// HART_H