#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "SystemEndian.h"
#include "Platform.h"

BEGIN_NAMESPACE

class System
{
protected:
	SysEndian m_sysEndian;				// ����ϵͳ��С��
public:
	void checkEndian();		// ��Ȿ��ϵͳ�Ǵ�˻���С��
	bool isEndianDiffFromSys(SysEndian rhv);	// �����ϵͳ�Ĵ��С���Ƿ���ͬ
};

END_NAMESPACE

#endif