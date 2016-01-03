//
//   File name      : CFunctionForLuaLib.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2012-04-25 15:48:16
//

// Tested or implemented header
#include "CFunctionForLuaLib.h"

// C system headers
// ...

// C++ system headers
#include <iostream>

// Headers from other projects
#include "IFOperator/Base64.h"
#include "IFOperator/CodeTransformer.h"
#include "IFCurlAdaptor/UrlDownloader.h"
#include "IFMacros/SleepMacro.h"
#include "IFDataType/IFException.h"
#include "IFOperator/JavascriptTool.h"

// Headers of current project
#include "UrlDownloaderFactoryWithCache.h"
#include "CacheManager.h"
#include "ProgramArguments.h"

int CFunctionForLuaLib::Base64Decode(lua_State *state)
{
    int ret_code = false;
    std::string cipher_text("");
    std::string plain_text("");
    const char *kCipherText = lua_tostring(state, -1);
    if (NULL == kCipherText)
    {
        lua_pushnil(state);
        lua_pushstring(state, "Parameter error.");
        return 2;
    }

    cipher_text.assign(kCipherText);

    ret_code = Base64::Decode(cipher_text, plain_text);
    if (!ret_code)
    {
        lua_pushnil(state);
        lua_pushstring(state, "C/C++ function Base64::Decode returns false.");
        return 2;
    }

    lua_pushstring(state, plain_text.c_str() );
    return 1;
}


int CFunctionForLuaLib::TransUtf8ToAnsi(lua_State *state)
{
    int ret_code = false;
    std::string cipher_text("");
    std::string plain_text("");
    const char *kCipherText = lua_tostring(state, -1);
    if (NULL == kCipherText)
    {
        lua_pushnil(state);
        lua_pushstring(state, "Parameter error.");
        return 2;
    }

    cipher_text.assign(kCipherText);

    ret_code = CodeTransformer::TransUtf8ToAnsi(cipher_text, plain_text);
    if (!ret_code)
    {
        lua_pushnil(state);
        lua_pushstring(state, "C/C++ function CodeTransformer::TransUtf8ToAnsi returns false.");
        return 2;
    }

    lua_pushstring(state, plain_text.c_str() );
    return 1;
}


int CFunctionForLuaLib::TransBigEndianUnicodeToAnsi(lua_State *state)
{
    int ret_code = false;

    std::string plain_text("");
    int cipher_text_length  = static_cast<int>(lua_tonumber(state, -2) );
    const char *kCipherText = lua_tostring(state, -1);
    if (NULL == kCipherText)
    {
        lua_pushnil(state);
        lua_pushstring(state, "Parameter error.");
        return 2;
    }

    ret_code = CodeTransformer::TransBigEndianUnicodeToAnsi(cipher_text_length, kCipherText, plain_text);
    if (!ret_code)
    {
        lua_pushnil(state);
        lua_pushstring(state, "C/C++ function CodeTransformer::TransBigEndianUnicodeToAnsi returns false.");
        return 2;
    }

    lua_pushstring(state, plain_text.c_str() );
    return 1;
}

int CFunctionForLuaLib::TransCode(lua_State *state)
{
	int ret_code = false;
	std::string cipher_text("");
	int cipher_code_page = 0;
	int plain_code_page = 0;
	std::string plain_text("");

	const char *kCipherText = lua_tostring(state, -3);
	if (NULL == kCipherText)
	{
		lua_pushnil(state);
		lua_pushstring(state, "Parameter error.");
		return 2;
	}
	cipher_text.assign(kCipherText);

	cipher_code_page = static_cast<int>(lua_tonumber(state, -2) );
	plain_code_page  = static_cast<int>(lua_tonumber(state, -1) );

	ret_code = CodeTransformer::TransCode(cipher_text, cipher_code_page, plain_code_page, plain_text);
	if (!ret_code)
	{
		lua_pushnil(state);
		lua_pushstring(state, "C/C++ function CodeTransformer::TransCode returns false.");
		return 2;
	}

	lua_pushstring(state, plain_text.c_str() );
	return 1;
}

int CFunctionForLuaLib::DownloadURL(lua_State *state)
{
	int ret_code = NULL;
	std::string url("");
	std::string referer_url("");
    std::string cookie("");
	std::string pagestr("");

	const char *kURL = lua_tostring(state, 1);
	const char *kRefererURL = lua_tostring(state, 2);
    const char *kCookie = lua_tostring(state, 3);
	url.assign(kURL);
	referer_url.assign(kRefererURL);
	if (kCookie != NULL)
	{
		cookie.assign(kCookie);
	}

    try
    {
        static UrlDownloaderFactoryWithCache downloader_factory(ProgramArguments::Instance().curl_dll_path(), CacheManager::Instance());
        URLDOWNLOADER_PTR downloader = downloader_factory.Create();
        DATAHOLDER_PTR page_data = downloader->Download(url, referer_url, cookie);
        pagestr.assign(page_data->content(), page_data->size());
    }
    catch (IFException &e)
    {
        lua_pushnil(state);
        lua_pushstring(state, e.message().c_str());
        return 2;
    }

	lua_pushstring(state, pagestr.c_str() );
	return 1;
}

int CFunctionForLuaLib::WriteLog(lua_State *state)
{
	const char *kContent = lua_tostring(state, -1);
	if (NULL == kContent)
	{
		lua_pushnil(state);
		lua_pushstring(state, "No content to write.");
		return 2;
	}

	puts(kContent);
	lua_pushnumber(state, strlen(kContent) );
	return 1;
}

int CFunctionForLuaLib::FormatUrltoUtf8(lua_State *state)
{
	std::string result;
	const char *kURL = lua_tostring(state, -1);
	if (NULL == kURL)
	{
		lua_pushnil(state);
		lua_pushstring(state, "Request a string parameter.");
		return 2;
	}

	if (!CodeTransformer::FormatUrltoUtf8(std::string(kURL), result) )
	{
		lua_pushnil(state);
		lua_pushstring(state, "Tranforming failed.");
		return 2;
	}

	lua_pushstring(state, result.c_str() );

	return 1;
}

int CFunctionForLuaLib::SleepMilliSecond(lua_State *state)
{
    std::string result;
    int sleep_millisecond_count = static_cast<int>(lua_tonumber(state, -1) );
    if (sleep_millisecond_count < 0)
    {
        lua_pushnil(state);
        lua_pushstring(state, "Request a number parameter no less than zero.");
        return 2;
    }

    SLEEP_MS(sleep_millisecond_count);

    return 0;
}

int CFunctionForLuaLib::JavascriptEval(lua_State *state)
{
    const char *script = lua_tostring(state, -1);
    if (NULL == script)
    {
        lua_pushnil(state);
        lua_pushstring(state, "Request a string parameter.");
        return 2;
    }

    std::string eval_result;
    try
    {
        eval_result = JavascriptTool::Eval(std::string(script));
    }
    catch (IFException &e)
    {
        lua_pushnil(state);
        lua_pushstring(state, (std::string("eval failed because: ") + e.message()).c_str());
        return 2;
    }

    lua_pushstring(state, eval_result.c_str());
    return 1;
}

int CFunctionForLuaLib::Print(lua_State *state)
{
    const char *text = lua_tostring(state, -1);
    if (NULL == text)
    {
        lua_pushnil(state);
        lua_pushstring(state, "Request a string parameter.");
        return 2;
    }

    std::cout << text << std::endl;
    return 0;
}
