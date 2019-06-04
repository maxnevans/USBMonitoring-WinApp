#pragma once
#include <string>
class Exception
{
public:
	Exception(std::wstring message);
	virtual const wchar_t* what() const noexcept;

private:
	std::wstring message;
};

