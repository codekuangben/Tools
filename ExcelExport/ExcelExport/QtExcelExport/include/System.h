#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "SystemEndian.h"
#include "Platform.h"

BEGIN_NAMESPACE

class System
{
protected:
	SysEndian m_sysEndian;				// 决定系统大小端
public:
	void checkEndian();		// 检测本地系统是大端还是小端
	bool isEndianDiffFromSys(SysEndian rhv);	// 检测与系统的大端小端是否相同
};

END_NAMESPACE

#endif