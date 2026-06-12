#pragma once
#include "pch.h"
#include <windows.h>
#include <wincrypt.h>
#include <vector>

#pragma comment(lib, "advapi32.lib")

class HashHelper
{
public:
    static CString SHA256(const CString& input)
    {
        HCRYPTPROV hProv = 0;
        HCRYPTHASH hHash = 0;
        CString result;

        if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
            return result;

        if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash))
        {
            CryptReleaseContext(hProv, 0);
            return result;
        }

        int len = WideCharToMultiByte(CP_UTF8, 0, input, -1, NULL, 0, NULL, NULL);
        std::vector<char> buf(len);
        WideCharToMultiByte(CP_UTF8, 0, input, -1, buf.data(), len, NULL, NULL);

        if (!CryptHashData(hHash, (BYTE*)buf.data(), len - 1, 0))
        {
            CryptDestroyHash(hHash);
            CryptReleaseContext(hProv, 0);
            return result;
        }

        BYTE hash[32];
        DWORD hashLen = 32;
        if (CryptGetHashParam(hHash, HP_HASHVAL, hash, &hashLen, 0))
        {
            for (int i = 0; i < 32; i++)
            {
                CString hex;
                hex.Format(_T("%02x"), hash[i]);
                result += hex;
            }
        }

        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return result;
    }
};