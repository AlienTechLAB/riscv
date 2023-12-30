#include "hart.h"

hart::hart(uint8_t* memory)
{
	iCpu.pMemory = memory;
}

err_t hart::start(uint64_t entryPoint)
{
	std::lock_guard<std::mutex> hartLock(iHartMutex);
	if (!iWorking) {
		iCpu.pc = entryPoint;
		iWorking = true;
		iRunning = true;
		iCounter = 0;
		iThreadErr = err_t::ok;
		if (iThread.joinable())
			iThread.join();
		iThread = std::thread([this]() { this->loop(); });
		return err_t::ok;
	}
	return err_t::error;
}

err_t hart::pause()
{
	std::lock_guard<std::mutex> hartLock(iHartMutex);
	if (iWorking && iRunning) {
		std::unique_lock<std::mutex> pauseLock(iPauseMutex);
		iRunning = false;
		iPauseCV.wait(pauseLock, [this] { return iPausing; });
		iPausing = false;
		return err_t::ok;
	}
	return err_t::error;
}

err_t hart::resume()
{
	std::lock_guard<std::mutex> hartLock(iHartMutex);
	if (iWorking && !iRunning) {
		iPauseMutex.lock();
		iRunning = true;
		iPauseCV.notify_one();
		std::unique_lock<std::mutex> resumeLock(iResumeMutex);
		iPauseMutex.unlock();
		iResumeCV.wait(resumeLock, [this] { return iResuming; });
		iResuming = false;
		return err_t::ok;
	}
	return err_t::error;
}

err_t hart::stop()
{
	std::lock_guard<std::mutex> hartLock(iHartMutex);
	if (iWorking){
		if (iRunning) {
			iWorking = false;
			iThread.join();
			return err_t::ok;
		} else {
			iWorking = false;
			iPauseMutex.lock();
			iRunning = true;
			iPauseCV.notify_one();
			std::unique_lock<std::mutex> resumeLock(iResumeMutex);
			iPauseMutex.unlock();
			iResumeCV.wait(resumeLock, [this] { return iResuming; });
			iResuming = false;
			iThread.join();
			return err_t::ok;
		}
	}
	return err_t::error;
}

err_t hart::step()
{
	std::lock_guard<std::mutex> hartLock(iHartMutex);
	if (iWorking && !iRunning && iThreadErr == err_t::ok) {
		iThreadErr = executeInstr();
		return iThreadErr == err_t::ok ? err_t::ok : err_t::error;
	}
	return err_t::error;
}

void hart::loop()
{
	while (iWorking) {
		if (iRunning) {
			if (iThreadErr == err_t::ok)
				executeInstr();
			else {
				if (iHartMutex.try_lock()) {
					iWorking = false;
					iRunning = false;
					iHartMutex.unlock();
					return;
				}
			}
		} else {
			std::unique_lock<std::mutex> pauseLock(iPauseMutex);
			iPausing = true;
			iPauseCV.notify_one();
			iPauseCV.wait(pauseLock, [this] { return iRunning; });
			iResumeMutex.lock();
			iResuming = true;
			iResumeCV.notify_one();
			iResumeMutex.unlock();
		}
	}
}

err_t hart::executeInstr()
{
	const uint32_t mcode = *((uint32_t*)&iCpu.pMemory[iCpu.pc]);
	const err_t cpuErr = iCpu.execute(mcode);
	iCounter++;
	return cpuErr;
}