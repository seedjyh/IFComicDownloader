//
//   File name      : DataHolder.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFDataType
//
//   Create datetime: 2012-06-23 13:55:34
//

#ifndef _IFDATATYPE_SRC_DATAHOLDER_H_
#define _IFDATATYPE_SRC_DATAHOLDER_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
#include <string>
#include <boost/shared_ptr.hpp>

// Headers from other projects
// ...

// Headers of current project
// ...

class DataHolder
{
	char *content_;
	int content_length_;
	int buffer_size_;
public:
	DataHolder();
    explicit DataHolder(const std::string &kData);
    DataHolder(int data_size, const char kData[]);
	~DataHolder();

	void clear();

	int size() const {return content_length_;}

	const char* content() const {return content_;}

	void Append(int data_size, const char kData[]);

	int empty() const {return (0 == content_length_);}

	void SetData(int start_index, int length, const char kData[]);

    friend bool operator==(const DataHolder &kSelf, const DataHolder &kAnother);
protected:
private:
};

char GetOneByte(const DataHolder &kHolder, int index);
int  GetFourByte(const DataHolder &kHolder, int start_index);
const char* GetString(const DataHolder &kHolder, int start_index);

void AppendOneByte(DataHolder &holder, char new_byte);
void AppendFourByte(DataHolder &holder, int new_int);
void AppendString(DataHolder &holder, int length, const char kNewString[]);

void SetFourByte(DataHolder &holder, int start_index, int new_int);

typedef boost::shared_ptr<DataHolder> DATAHOLDER_PTR;

#endif
