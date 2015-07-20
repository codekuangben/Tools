#ifndef __LuaCFunction_H_
#define __LuaCFunction_H_

#include "GameEditor.h"
#include "lua.hpp"
#include "LuaCBase.h"
#include <vector>

BEGIN_NAMESPACE_GAMEEDITOR

class LuaCVM;

/**
 *@brief ��ʾһ�� Lua �еı����ȼ��� Lua Դ����� ltable.h
 */
class GAMEEDITOR_EXPORT LuaCFunction : public LuaCBase
{
protected:
	lua_State* L;

public:
	LuaCFunction(int reference, LuaCVM* interpreter);
	~LuaCFunction();

	std::vector<LuaCObject*> LuaCFunction::call(std::vector<LuaCObject*> args, std::vector<int> returnTypes);
	std::vector<LuaCObject*> Call(std::vector<LuaCObject*> args);
	std::vector<LuaCObject*> LuaCFunction::Call();
	std::vector<LuaCObject*> LuaCFunction::Call(double arg1);
	int LuaCFunction::BeginPCall();
	bool LuaCFunction::PCall(int oldTop, int args);
	std::vector<LuaCObject*> LuaCFunction::PopValues(int oldTop);
	void LuaCFunction::EndPCall(int oldTop);
	lua_State* LuaCFunction::GetLuaState();
	void LuaCFunction::push(lua_State* luaState);
	void LuaCFunction::push();
	std::string LuaCFunction::ToString();
	int LuaCFunction::GetReference();
};

END_NAMESPACE_GAMEEDITOR

#endif