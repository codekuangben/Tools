#include "LuaCFunction.h"
#include "LuaCVM.h"
#include "LuaCScriptMgr.h"
#include "LuaCObjectTranslator.h"
#include "LuaCommon.h"

LuaCFunction::LuaCFunction(int reference, LuaCVM* interpreter)
{
	m_ref = reference;
	m_luavm = interpreter;
}

LuaCFunction::~LuaCFunction()
{

}

/*
* Calls the function casting return values to the types
* in returnTypes
*/
std::vector<LuaCObject*> LuaCFunction::call(std::vector<LuaCObject*> args, std::vector<int> returnTypes)
{
	int nArgs = 0;
	m_luavm->PushTraceBack();
	int oldTop = lua_gettop(L);

	if (!lua_checkstack(L, (int)args.size() + 6))
	{
		lua_pop(L, 1);
		//throw new LuaException("Lua stack overflow");
	}

	push(L);

	if (args.size() > 0)
	{
		nArgs = (int)args.size();

		for (int i = 0; i < args.size(); i++)
		{
			PushArgs(args[i]);
		}
	}

	int error = lua_pcall(L, nArgs, -1, -nArgs - 2);

	if (error != 0)
	{
		std::string err = lua_tostring(L, -1);
		lua_settop(L, oldTop - 1);
		if (err == "") err = "Unknown Lua Error";
		//throw new LuaScriptException(err, "");
	}

	std::vector<LuaCObject*> ret = returnTypes.size() > 0 ? m_luavm->m_translator->popValues(oldTop, returnTypes) : m_luavm->m_translator->popValues(oldTop);
	lua_settop(L, oldTop - 1);
	return ret;
}

/*
* Calls the function and returns its return values inside
* an array
*/
std::vector<LuaCObject*> LuaCFunction::Call(std::vector<LuaCObject*> args)
{
	std::vector<int> returnTypes;
	//return call(args, null);
	return call(args, returnTypes);
}

std::vector<LuaCObject*> LuaCFunction::Call()
{
	std::vector<LuaCObject*> objs;
	int oldTop = BeginPCall();

	if (PCall(oldTop, 0))
	{
		objs = PopValues(oldTop);
		EndPCall(oldTop);
		return objs;
	}

	lua_settop(L, oldTop - 1);
	return objs;
}

std::vector<LuaCObject*> LuaCFunction::Call(double arg1)
{
	std::vector<LuaCObject*> objs;
	int oldTop = BeginPCall();
	//LuaCScriptMgr.Push(L, arg1);

	if (PCall(oldTop, 1))
	{
		//std::vector<LuaCObject*> objs = PopValues(oldTop);
		objs = PopValues(oldTop);
		EndPCall(oldTop);
		return objs;
	}

	lua_settop(L, oldTop - 1);
	//return null;
	return objs;
}

int beginPos = -1;

int LuaCFunction::BeginPCall()
{
	m_luavm->PushTraceBack();
	beginPos = lua_gettop(L);
	push(L);
	return beginPos;
}

bool LuaCFunction::PCall(int oldTop, int args)
{
	if (lua_pcall(L, args, -1, -args - 2) != 0)
	{
		std::string err = lua_tostring(L, -1);
		lua_settop(L, oldTop - 1);
		if (err == "") err = "Unknown Lua Error";
		//throw new LuaScriptException(err, "");
	}

	return true;
}

std::vector<LuaCObject*> LuaCFunction::PopValues(int oldTop)
{
	std::vector<LuaCObject*> ret = m_luavm->m_translator->popValues(oldTop);
	return ret;
}

void LuaCFunction::EndPCall(int oldTop)
{
	lua_settop(L, oldTop - 1);
}

lua_State* LuaCFunction::GetLuaState()
{
	return L;
}

/*
* Pushes the function into the Lua stack
*/
void LuaCFunction::push(lua_State* luaState)
{
	if (m_ref != 0)
	{
		lua_getref(luaState, m_ref);
	}
	else
	{
		//m_luavm.pushCSFunction(function);
	}
}

void LuaCFunction::push()
{
	if (m_ref != 0)
	{
		lua_getref(L, m_ref);
	}
	else
	{
		//m_luavm.pushCSFunction(function);
	}
}

std::string LuaCFunction::ToString()
{
	return "function";
}

int LuaCFunction::GetReference()
{
	return m_ref;
}