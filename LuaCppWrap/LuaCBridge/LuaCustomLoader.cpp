#include "LuaCustomLoader.h"
#include <string>
#include <string.h>
#include <stdio.h>
#include "luaconf.h"

void loaderror(lua_State *L, const char *filename)
{
	luaL_error(L, "error loading module " LUA_QS " from file " LUA_QS ":\n\t%s",
		lua_tostring(L, 1), filename, lua_tostring(L, -1));
}

int lua_file_from_manual_func(lua_State *L)
{
	const char *filename = nullptr;
	const char *name = luaL_checkstring(L, 1);
	//filename = findfile(L, name, "path");
	if (filename == NULL) return 1;  /* library not found in this path */
	//if (manul_load_file && manul_load_file(L, filename) != 0)
	//	loaderror(L, filename);
	return 1;  /* library loaded successfully */
}

void InitManualFunction(lua_State *L)
{
	int type = 0;
	lua_getglobal(L, "package");
	type = lua_type(L, -1);
	//lua_getfield(L, -1, "loaders");	//lua5.1 package.loaders
	lua_getfield(L, -1, "searchers");	//lua5.3 package.searchers
	type = lua_type(L, -1);
	lua_pushnumber(L, 2);
	lua_gettable(L, -2);			//package.loader[2]
	lua_pushnumber(L, 2);			//先把索引压栈，用来设置C函数到这个索引位置
	lua_pushcfunction(L, MyLoader);	//压入自己的C函数
	lua_settable(L, -4);	//替换旧函数
	lua_pop(L, 3);			//清理堆栈
}

std::string g_searchsRootPath = "D:/file/opensource/unity-game-git/unitygame/Tools/LuaCppWrap/LuaScript";

int MyLoader(lua_State* pState)
{
	int top = 0;
	int type = 0;

	//const char *name = luaL_checkstring(pState, 1);
	std::string module = lua_tostring(pState, 1);
	module += ".lua";
	module = g_searchsRootPath + "/" + module;

	const char* fullPath = module.c_str();
	FILE* hFile = nullptr;
	hFile = fopen(fullPath, "r");
	fseek(hFile, 0, SEEK_END);
	int size = ftell(hFile);
	fseek(hFile, 0, SEEK_SET);

	if (size > 0)
	{
		char* buffer = new char[size];
		memset(buffer, 0, size);
		fread(buffer, size, 1, hFile);
		top = lua_gettop(pState);
		int status = luaL_loadbuffer(pState, (const char*)buffer, size, fullPath);
		//int status = luaL_dostring(pState, buffer);
		if (status == LUA_OK)	// 这个地方必须加载成功,否则 if (lua_isfunction(L, -2)) loadlib.c 将返回 false ,结果就导致不能正确执行
		{
			//lua_pushcfunction(pState, loadLua);
			//top = lua_gettop(pState);
			//type = lua_type(pState, -1);
			//lua_pushstring(pState, fullPath);
			//top = lua_gettop(pState);
		}
		//return checkload(pState, (luaL_loadfile(pState, fullPath) == LUA_OK), fullPath);
		return 2;
	}
	else
	{
		std::string err = "\n\tError - MyLoader could not find ";
		err += module;
		err += ".";
		lua_pushstring(pState, err.c_str());
	}

	return 1;
}

int loadLua(lua_State *L)
{
	// 此处的n是C++向栈中压入的参数个数，如果和压入栈个数不一致，可能导致栈失衡
	return 0;
}

void AddLoader(lua_State *L)
{
	int type = 0;
	lua_getglobal(L, "package");	// push "package"
	type = lua_type(L, -1);
	// lua_getfield(L, -1, "loaders");					// lua5.1 push "package.loaders"
	//lua_getfield(L, lua_upvalueindex(1), "searchers");					// lua5.3 push "package.searchers"
	lua_getfield(L, -1, "searchers");					// lua5.3 push "package.searchers"
	type = lua_type(L, -1);
	lua_remove(L, -2);								// remove "package"
	// Count the number of entries in package.loaders.
	// Table is now at index -2, since 'nil' is right on top of it.
	// lua_next pushes a key and a value onto the stack.
	int numLoaders = 0;
	lua_pushnil(L);
	while (lua_next(L, -2) != 0)
	{
		lua_pop(L, 1);
		numLoaders++;
	}

	lua_pushinteger(L, numLoaders + 1);
	lua_pushcfunction(L, MyLoader);
	lua_rawset(L, -3);
	// Table is still on the stack.  Get rid of it now.
	lua_pop(L, 1);
}

void dotAddLoader(lua_State *L)
{
	// Insert our loader FIRST
	lua_pushcfunction(L, dotLoadLua);
	int loaderFunc = lua_gettop(L);

	// lua_getfield(L, LUA_GLOBALSINDEX, "package");	// lua5.1
	lua_getglobal(L, "package");	// lua5.3 push "package" 
	lua_getfield(L, -1, "searchers");
	int loaderTable = lua_gettop(L);

	// Shift table elements right
	//for (int e = luaL_getn(L, loaderTable) + 1; e > 1; e--)		// lua5.1
	//for (int e = lua_objlen(L, loaderTable) + 1; e > 1; e--)		// lua5.3
	for (int e = (int)lua_rawlen(L, loaderTable) + 1; e > 1; e--)		// lua5.3
	{
		lua_rawgeti(L, loaderTable, e - 1);
		lua_rawseti(L, loaderTable, e);
	}
	lua_pushvalue(L, loaderFunc);
	lua_rawseti(L, loaderTable, 1);
	lua_settop(L, 0);
}

// http://blog.chinaunix.net/uid-552961-id-2736410.html
// ll_require会将这个loader的返回值符给package.loaded[modelname],如果loader不返回值同时 package.loaded[modelname]不存在时, ll_require就会把package.loaded[modelname]设为true。最后ll_reuqire把package.loaded [modelname]返回给调用者。
// 失败加载返回 0，成功返回 1
int dotLoadLua(lua_State *L)
{
	// Get script to load
	std::string fileName = lua_tostring(L, 1);
	fileName += ".lua";
	fileName = g_searchsRootPath + "/" + fileName;

	const char* fullPath = fileName.c_str();
	FILE* hFile = nullptr;
	hFile = fopen(fullPath, "r");

	lua_pushcfunction(L, traceback);	// 如果 luaL_loadbuffer 错误,继续调用 traceback
	int oldTop = lua_gettop(L);

	if (hFile == nullptr) 
	{
		lua_pop(L, 1);
		return 0;
	}

	fseek(hFile, 0, SEEK_END);
	int size = ftell(hFile);		// 这个地方是 31 ,明明是 29
	fseek(hFile, 0, SEEK_SET);
	if (size > 0)
	{
		char* buffer = new char[size];
		memset(buffer, 0, size);
		fread(buffer, size, 1, hFile);

		//fseek(hFile, 0, SEEK_SET);
		//std::string getStr = "";
		//char c;
		//int size_2 = 0;
		//while (!feof(hFile))
		//{
		//	c = fgetc(hFile);
		//	getStr += c;
		//	++size_2;
		//}

		for (int idx = size - 1; idx >= 0; --idx)
		{
			if (buffer[idx] == 0 || buffer[idx] == -1)	// 将最后的 0 或者 -1 减掉, luaL_loadbuffer 长度必须和字符数量相等,并且不能有 0 或者 -1, -1 在 fgetc 读取文件的时候,最后竟然将结束符 -1 也读取出来了,然后 feof 才为 true,奇怪
			{
				--size;
			}
			else
			{
				break;
			}
		}

		fclose(hFile);
		//char* buffer = "function add(a, b)\r\n\t \
					   			return 10\r\n \
											end";
		//char* buffer1 = "function add()\n\treturn 10\nend";
		//int size1 = strlen(buffer1);

		//int idx = 0;
		//for (idx = 0; idx < size1; ++idx)
		//{
		//	if (buffer[idx] != buffer1[idx])
		//	{
		//		break;
		//	}
		//}

		// 不知道为什么,从文件读取进来的字符内容 "function add()\n\treturn 10\nend" ,但是文件检查大小竟然是 31,明明是 29,最后多了两个  "\0\0" ,只要把 size 改成 29 就可以正确执行了

		if (luaL_loadbuffer(L, buffer, size, fileName.c_str()) != LUA_OK)
		{
			lua_pop(L, 1);
		}

		//delete buffer;
	}

	//int top = lua_gettop(L);
	//int type = lua_type(L, -1);		// LUA_TFUNCTION
	return 1;
}

int traceback(lua_State *L)
{
	// debug.traceback ([thread,] [message])
	lua_getglobal(L, "debug");
	lua_getfield(L, -1, "traceback");
	lua_pushvalue(L, 1);
	lua_pushnumber(L, 2);
	lua_call(L, 2, 1);

	char* error;
	if (lua_type(L, -1) == LUA_TSTRING)
	{
		error = (char*)lua_tostring(L, -1);
	}
	return 1;
}