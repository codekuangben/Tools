#include "ArchiveParam.h"
#include <string.h>

BEGIN_NAMESPACE_FILEARCHIVETOOL

ArchiveParam::ArchiveParam()
{
	m_pArchiveDir = new char[MAX_PATH];
	m_pArchiveFilePath = new char[MAX_PATH];

	setArchiveFilePath("E:\\aaa.abc");
}

ArchiveParam::~ArchiveParam()
{
	delete m_pArchiveDir;
	delete m_pArchiveFilePath;
}

void ArchiveParam::setArchiveDir(const char* pPath)
{
	memset(m_pArchiveDir, 0, MAX_PATH);
	strcpy(m_pArchiveDir, pPath);
}

void ArchiveParam::setArchiveFilePath(const char* pPath)
{
	memset(m_pArchiveFilePath, 0, MAX_PATH);
	strcpy(m_pArchiveFilePath, pPath);
}

const char* ArchiveParam::getArchiveDir()
{
	return m_pArchiveDir;
}

const char* ArchiveParam::getArchiveFilePath()
{
	return m_pArchiveFilePath;
}

END_NAMESPACE_FILEARCHIVETOOL