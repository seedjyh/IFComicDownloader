//
//   File name      : JavascriptTool.cpp
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-01-01 17:25:50
//

// Tested or implemented header
#include "JavascriptTool.h"

// C system headers
// ...

// C++ system headers
#include <sstream>

// Headers from other projects
// ...

// Headers of current project
// ...

std::string JavascriptTool::Eval(const std::string &kSrc)
{
    std::string confused_data;
    std::string confuse_base;
    std::string dictionary;
    ParseConfusionFunction(kSrc, confused_data, confuse_base, dictionary);
    return Deconfuse(confused_data, confuse_base, dictionary);
}

static std::string JumpAndGet(const char *kSrc, const char *kJumpedText, int jump_count, const char *kEndText, int &ret_read_count)
{
    std::string result;
    const char *kHead = kSrc;
    while (jump_count--)
    {
        kHead = strstr(kSrc, kJumpedText);
        if (NULL == kHead)
        {
            throw 1; // unknown format
        }
    }
    kHead += strlen(kJumpedText);
    const char *kTail = strstr(kHead, kEndText);
    if (NULL == kTail)
    {
        throw 1; // format error
    }
    ret_read_count = kTail + strlen(kEndText) - kSrc;
    return std::string(kHead, kTail - kHead);
}

void JavascriptTool::ParseConfusionFunction(const std::string &kSrc, std::string &ret_confused_data, std::string &ret_confuse_base, std::string &ret_dictionary)
{
    int read_total_count = 0;
    int read_count = 0;

    ret_confused_data = JumpAndGet(kSrc.c_str() + read_total_count, "}(\'", 1, "\',", read_count);
    read_total_count += read_count;

    ret_confuse_base = JumpAndGet(kSrc.c_str() + read_total_count, "", 0, ",", read_count);
    read_total_count += read_count;

    ret_dictionary = JumpAndGet(kSrc.c_str() + read_total_count, ",\'", 1, "\'", read_count);
    read_total_count += read_count;

    return;
}

std::string JavascriptTool::Deconfuse(const std::string &kConfusedData, const std::string &kConfuseBase, const std::string &kDictionaryText)
{
    std::stringstream result;

    DictionaryMap dictionary = ParseDictionary(kDictionaryText);
    std::string now_key;
    bool in_escape_character_mode = false;
    for (std::string::const_iterator ite = kConfusedData.begin(); ite != kConfusedData.end(); ++ite)
    {
        if (isalnum(*ite))
        {
            now_key += *ite;
        }
        else
        {
            if (now_key.size() > 0)
            {
                std::string value = dictionary[TransferBase(now_key, kConfuseBase)];
                if (value.empty())
                {
                    value = now_key;
                }
                result << value;
                now_key.clear();
            }

            // escape part
            if (in_escape_character_mode)
            {
                switch (*ite)
                {
                case '\\':
                case '\'':
                case '\"':
                    result << *ite;
                    break;
                case 'n':
                    result << '\n';
                    break;
                case 't':
                    result << '\t';
                    break;
                default:
                    throw 1;
                }
                in_escape_character_mode = false;
            }
            else
            {
                if ('\\' == *ite)
                {
                    in_escape_character_mode = true;
                }
                else
                {
                    result << *ite;
                }
            }
        }
    }
    if (now_key.size() > 0)
    {
        std::string value = dictionary[TransferBase(now_key, kConfuseBase)];
        if (value.empty())
        {
            value = now_key;
        }
        result << value;
    }

    return result.str();
}

DictionaryMap JavascriptTool::ParseDictionary(const std::string &kDictionaryText)
{
    DictionaryMap result;
    std::string value;
    for (std::string::const_iterator ite = kDictionaryText.begin(); ite != kDictionaryText.end(); ++ite)
    {
        if ('|' == *ite)
        {
            result[result.size()] = value;
            value.clear();
        }
        else
        {
            value += *ite;
        }
    }
    if (value.size() > 0)
    {
        result[result.size()] = value;
        value.clear();
    }
    return result;
}

int JavascriptTool::TransferBase(const std::string &kSrc, const std::string &kBase)
{
    static const std::string kBaseArray("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    static int c2i[256] = { '\0' };
    static bool first_call = true;
    if (first_call)
    {
        first_call = false;
        for (int i = 0; i < kBaseArray.size(); i++)
        {
            c2i[kBaseArray[i]] = i;
        }
    }

    int result = 0;
    int base = atoi(kBase.c_str());
    for (std::string::const_iterator ite = kSrc.begin(); ite != kSrc.end(); ++ite)
    {
        result *= base;
        result += c2i[*ite];
    }
    return result;
}
