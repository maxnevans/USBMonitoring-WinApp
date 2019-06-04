#include "Exception.h"

Exception::Exception(std::wstring message)
{
	this->message = message;
}

const wchar_t* Exception::what() const noexcept
{
	return this->message.c_str();
}
