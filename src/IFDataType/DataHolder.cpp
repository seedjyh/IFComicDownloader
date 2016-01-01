//
//   File name      : DataHolder.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFDataType
//
//   Create datetime: 2012-06-23 13:58:57
//

// Tested or implemented header
#include "DataHolder.h"

// C system headers
#include <assert.h>
#include <memory.h>

// C++ system headers
// ...

// Headers from other projects
#include "IFMacros/BasicOperateMacro.h"

// Headers of current project
// ...

DataHolder::DataHolder()
:	buffer_size_(0),
	content_length_(0),
	content_(NULL){};

DataHolder::DataHolder(const std::string &kData)
:   buffer_size_(0),
    content_length_(0),
    content_(NULL){
    Append(kData.size(), kData.c_str());
}

DataHolder::DataHolder(int data_size, const char kData[])
:   buffer_size_(0),
    content_length_(0),
    content_(NULL){
    Append(data_size, kData);
}

DataHolder::~DataHolder()
{
	clear();
}

void DataHolder::clear()
{
	MY_DELETEARRAY(content_);
	content_length_ = 0;
	buffer_size_ = 0;
}

void DataHolder::Append(int data_size, const char kData[])
{
	if (content_length_ + data_size > buffer_size_)
	{
		int require_size = content_length_ + data_size;
		int target_size = 1;
		while (target_size < require_size)
		{
			target_size <<= 1;
		}

		char *new_content = new char[target_size];
		assert(new_content);

		memcpy(new_content, content_, content_length_);

		buffer_size_ = target_size;
		MY_DELETEARRAY(content_);
		content_ = new_content;
	}

	assert(content_length_ + data_size <= buffer_size_);
	memcpy(content_ + content_length_, kData, data_size);
	content_length_ += data_size;

	return;
}

void DataHolder::SetData(int start_index, int length, const char kData[])
{
	assert(start_index + length <= content_length_);
	memcpy(content_ + start_index, kData, length);

	return;
}

bool operator==(const DataHolder &kSelf, const DataHolder &kAnother)
{
    if (kSelf.size() != kAnother.size())
    {
        return false;
    }

    if (memcmp(kSelf.content(), kAnother.content(), kSelf.size()) != 0)
    {
        return false;
    }

    return true;
}

char GetOneByte(const DataHolder &kHolder, int index)
{
	assert(index < kHolder.size() );

	return kHolder.content()[index];
}

int  GetFourByte(const DataHolder &kHolder, int start_index)
{
	int result = 0;
	assert(start_index + 4 <= kHolder.size() );

	memcpy(&result, kHolder.content() + start_index, sizeof(int) );
	return result;
}

const char* GetString(const DataHolder &kHolder, int start_index)
{
	assert(start_index < kHolder.size() );

	return kHolder.content() + start_index;
}


void AppendOneByte(DataHolder &holder, char new_byte)
{
	char buffer[1] = {new_byte};
	holder.Append(1, buffer);

	return;
}

void AppendFourByte(DataHolder &holder, int new_int)
{
	char buffer[4] = {'\0'};
	memcpy(buffer, &new_int, 4);
	holder.Append(4, buffer);
	return;
}

void AppendString(DataHolder &holder, int length, const char kNewString[])
{
	holder.Append(length, kNewString);
	return;
}

void SetFourByte(DataHolder &holder, int start_index, int new_int)
{
	holder.SetData(start_index, sizeof(int), (char*)&new_int);
	return;
}
