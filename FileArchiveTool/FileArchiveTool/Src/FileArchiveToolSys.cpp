#include "FileArchiveToolSys.h"
#include "Config.h"
#include "ArchiveData.h"
#include "CharsetConv.h"
#include "Util.h"
#include "TaskQueue.h"
#include "LogSys.h"
#include "ThreadPool.h"
#include "PakState.h"
#include "ManiFestData.h"
#include "PtrDefine.h"

#include <Thread>

BEGIN_NAMESPACE_FILEARCHIVETOOL

template <> FileArchiveToolSys* Singleton<FileArchiveToolSys>::m_sSingleton = 0;

FileArchiveToolSys::FileArchiveToolSys()
{
	m_pConfig = new Config;
	m_pArchiveData = new ArchiveData;
	m_pCharsetConv = new CharsetConv;
	m_pUtil = new Util;
	m_pTaskQueue = new TaskQueue;
	m_pLogSys = new LogSys;
	m_pThreadPool = new ThreadPool(std::thread::hardware_concurrency()/* * 2*/);		// 几个 CPU 就几个线程，如果乘以 2 机器太卡了
	m_pPakState = new PakState;
	m_pManiFestData = new ManiFestData;
}

FileArchiveToolSys::~FileArchiveToolSys()
{
	SAFE_DELETE(m_pConfig);
	SAFE_DELETE(m_pArchiveData);
	SAFE_DELETE(m_pCharsetConv);
	SAFE_DELETE(m_pUtil);
	SAFE_DELETE(m_pTaskQueue);
	SAFE_DELETE(m_pLogSys);
	SAFE_DELETE(m_pThreadPool);
	SAFE_DELETE(m_pPakState);
	SAFE_DELETE(m_pManiFestData);
}

Config* FileArchiveToolSys::getConfigPtr()
{
	return m_pConfig;
}

ArchiveData* FileArchiveToolSys::getArchiveDataPtr()
{
	return m_pArchiveData;
}

CharsetConv* FileArchiveToolSys::getCharsetConvPtr()
{
	return m_pCharsetConv;
}

Util* FileArchiveToolSys::getUtilPtr()
{
	return m_pUtil;
}

TaskQueue* FileArchiveToolSys::getTaskQueuePtr()
{
	return m_pTaskQueue;
}

LogSys* FileArchiveToolSys::getLogSysPtr()
{
	return m_pLogSys;
}

//ArchiveParam* FileArchiveToolSys::getArchiveParamPtr()
//{
//	return m_pArchiveParam;
//}
//
//UnArchiveParam* FileArchiveToolSys::getUnArchiveParamPtr()
//{
//	return m_pUnArchiveParam;
//}

ThreadPool* FileArchiveToolSys::getThreadPoolPtr()
{
	return m_pThreadPool;
}

PakState* FileArchiveToolSys::getPakStatePtr()
{
	return m_pPakState;
}

ManiFestData* FileArchiveToolSys::getManiFestDataPtr()
{
	return m_pManiFestData;
}

void FileArchiveToolSys::onTick()
{
	m_pTaskQueue->onTick();
	m_pLogSys->onTick();
}

void FileArchiveToolSys::init()
{
	m_pThreadPool->instanceThread();
	m_pConfig->loadConfig();
}

void FileArchiveToolSys::destroy()
{
	// 彻底释放自己
	SAFE_DELETE(FileArchiveToolSys::getSingletonPtr());
}

END_NAMESPACE_FILEARCHIVETOOL