//
//   File name      : PathHandler.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFOperator
//
//   Create datetime: 2012-04-04 21:44:4
//

// Tested or implemented header
#include "PathHandler.h"

// C system headers
#include <tchar.h>
#include <shlwapi.h>

// C++ system headers
// ...

// Headers from other projects
#include "IFMacros/BasicProcessMacro.h"
#include "CodeTransformer.h"
#include "IFMacros/BasicOperateMacro.h"
#include "IFDataType/Tstring.h"

// Headers of current project
// ...

int PathHandler::Remove(const TCHAR kPath[])
{
    int nResult  = false;
    int nRetCode = false;

    PathList file_list;
    PathList directory_list;

	if (!PathFileExists(kPath) )
	{
		MY_PROCESS_SUCCESS(true);
	}

    nRetCode = List(kPath, file_list, directory_list);
    MY_PROCESS_ERROR(nRetCode);

    for (int i = 0; i < static_cast<int>(file_list.size()); i++)
    {
        nRetCode = DeleteFile(file_list[i].c_str() );
        MY_PROCESS_ERROR(nRetCode);
    }

    for (int i = 0; i < static_cast<int>(directory_list.size()); i++)
    {
        nRetCode = Remove(directory_list[i].c_str() );
        MY_PROCESS_ERROR(nRetCode);
    }

    nRetCode = RemoveDirectory(kPath);
    MY_PROCESS_ERROR(nRetCode);

Exit1:
    nResult = true;
Exit0:
    return nResult;
}

int PathHandler::List(const Tstring &kRootPath, PathList &ret_file_list, PathList &ret_directory_list)
{
    int nResult  = false;
    int nRetCode = false;

    TCHAR search_modal[MAX_PATH] = {TCHAR('\0')};

    GetSearchModal(kRootPath.c_str(), search_modal);

    WIN32_FIND_DATA wfd;
    HANDLE hIterator = FindFirstFile(search_modal, &wfd);
	if (INVALID_HANDLE_VALUE == hIterator)
	{
		throw std::string("Cannot find first file");
	}

    ret_file_list.clear();
    ret_directory_list.clear();
    while (1)
    {
        if (_tcscmp(wfd.cFileName, TEXT(".") ) && _tcscmp(wfd.cFileName, TEXT("..") ) )
        {
            TCHAR t_file_name[MAX_PATH];

            _tcscpy(t_file_name, kRootPath.c_str() );
            _tcscat(t_file_name, TEXT("\\") );
            _tcscat(t_file_name, wfd.cFileName);

            if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                ret_directory_list.push_back(Tstring(t_file_name) );
            }
            else
            {
                ret_file_list.push_back(Tstring(t_file_name) );
            }
        }

        int ret_code = FindNextFile(hIterator, &wfd);
        if (!ret_code)
        {
            if (ERROR_NO_MORE_FILES == GetLastError() )
            {
                break;
            }
            MY_PROCESS_ERROR(false);
        }
    }

// Exit1:
    nResult = true;
Exit0:
    MY_FINDCLOSE(hIterator);
    return nResult;
}


int PathHandler::CreatePathRecursive(const Tstring &kPath)
{
    int nResult  = false;
    int nRetCode = false;

    Tstring now_path;

    int path_len = kPath.length();

    MY_PROCESS_ERROR(TCHAR('\\') == kPath[path_len - 1]);

    for (int i = 0; i < path_len; i++)
    {
        if (TCHAR('\\') == kPath[i])
        {
            now_path = Tstring(kPath);

            if (i + 1 < now_path.size())
            {
                now_path.resize(i + 1);
            }

            nRetCode = CreatePath(now_path.c_str() );
            MY_PROCESS_ERROR(nRetCode);
        }
    }

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}

void PathHandler::Validate(string &path)
{
    for (size_t i = 0; i < path.size(); i++)
    {
        switch (path[i])
        {
        case '/':
        case '*':
        case '?':
        case '\"':
        case '>':
        case '<':
        case '|':
		case '\r':
        case '\n':
		case '\t':
		case ' ':
            path[i] = '_';
            break;
        case ':':
            if (i != 1)
            {
                path[i] = '_';
            }
            
            break;
        default:;
        }
    }

	while (path.size() > 0  && ' ' == path[0])
	{
		path.erase(path.begin() );
	}

    return;
}

int PathHandler::IsValidate(const Tstring &kPath)
{
    for (int i = 0; i < kPath.size(); i++)
    {
        switch (kPath[i])
        {
        case TCHAR('/'):
        case TCHAR('*'):
        case TCHAR('?'):
        case TCHAR('\"'):
        case TCHAR('>'):
        case TCHAR('<'):
		case TCHAR('|'):
		case TCHAR('\r'):
		case TCHAR('\n'):
		case TCHAR('\t'):
		case TCHAR(' '):
            return false;
        case TCHAR(':'):
            if (i != 1)
            {
                return false;
            }

            break;
        default:;
        }
    }

    return true;
}

void PathHandler::Validate(Tstring &path)
{
    for (int i = 0; i < path.size(); i++)
	{
		switch (path[i])
		{
		case TCHAR('?'):
			path[i] = TEXT('£¿');
			break;
		case TCHAR('/'):
		case TCHAR('*'):
		case TCHAR('\"'):
		case TCHAR('>'):
		case TCHAR('<'):
		case TCHAR('|'):
		case TCHAR('\r'):
		case TCHAR('\n'):
		case TCHAR('\t'):
		case TCHAR(' '):
			path[i] = TEXT('_');
			break;
		case TCHAR(':'):
			if (i != 1)
			{
				path[i] = TEXT('£º');
			}

			break;
		default:;
		}
	}
	return;
}

int PathHandler::CreatePath(const Tstring &kPath)
{
    int nResult  = false;
    int nRetCode = false;

    size_t char_len = 0;

    MY_PROCESS_ERROR(kPath.length() > 0);
    MY_PROCESS_ERROR(TCHAR('\\') == kPath[kPath.length() - 1]);

    char_len = kPath.length();
#if defined WIN32
    if (
        (char_len >= 3) &&
        (TCHAR(':') == kPath[char_len - 2]) &&
        (TCHAR('\\') == kPath[char_len - 1])
    )
    {
        MY_PROCESS_SUCCESS(true);
    }

    nRetCode = CreateDirectory(kPath.c_str(), NULL);
    if (!nRetCode)
    {
        nRetCode = GetLastError();
		MY_PROCESS_ERROR(nRetCode == ERROR_ALREADY_EXISTS);
    }
#elif defined linux
    nRetCode = mkdir(kPath.c_str(), 0777);
    if (nRetCode)
    {
        assert(17 == errno);
    }
#endif

Exit1:
    nResult = true;
Exit0:
    return nResult;
}


void PathHandler::GetSearchModal(const TCHAR kRootPath[], TCHAR ret_search_modal[])
{
    _tcscpy(ret_search_modal, kRootPath);

    if (ret_search_modal[_tcslen(ret_search_modal) - 1] != TCHAR('\\') )
    {
        _tcscat(ret_search_modal, TEXT("\\") );
    }
    _tcscat(ret_search_modal, TEXT("*") );

    return;
}

void PathHandler::TransSlashToBackslash(Tstring &kPath)
{
    for (int i = 0; i < kPath.size(); i++)
    {
        if (TCHAR('/') == kPath[i])
        {
            kPath[i] = TCHAR('\\');
        }
    }
    return;
}

bool PathHandler::CheckFileExistance(const Tstring &kFilePath)
{
    return (0 == _taccess(kFilePath.c_str(), 0));
}
