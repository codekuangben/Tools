#include "AppFrame.h"
#include "MImport3dMax.h"
#include "ProgOptions.h"

AppFrame* g_pAppFrame;

AppFrame::AppFrame()
{
	m_ProgOptions = new ProgOptions;
	m_pMImport3dMax = new MImport3dMax;
}

AppFrame::~AppFrame()
{

}

void AppFrame::init(int argc, char *argv[])
{
	m_ProgOptions->parseParam(argc, argv);
}

void AppFrame::run()
{
	m_pMImport3dMax->import(m_ProgOptions->m_inFileFullPath);
}

void AppFrame::stop()
{

}