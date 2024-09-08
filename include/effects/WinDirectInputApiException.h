#pragma once
#include <exception>
#include <string>
#include "Windows.h" //DWORD
#include "winbase.h"
namespace RS21::direct_input {

class WinDirectInputApiException : public std::exception
{
public:
    WinDirectInputApiException(HRESULT newHResult, std::string additionalString);
    WinDirectInputApiException(HRESULT newHResult, const char* additionalString);

    long hResult() const throw()
    {
        return m_hResult;
    }
    virtual const char* what() const throw() override
    {
        return m_errorString.c_str();
    }
private:
    HRESULT m_hResult;
    std::string m_errorString;
    std::string ConvertWStringToString(wchar_t* wstr);
};
}//rs21::direct_input

