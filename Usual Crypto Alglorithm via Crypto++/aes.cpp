#ifndef _CRYPTO_UTIL_H_
#define _CRYPTO_UTIL_H_
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string>
using namespace std;
#include <cryptopp/aes.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/default.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>
using namespace CryptoPP;

enum AESKeyLength
{
	AES_KEY_LENGTH_16=16,AES_KEY_LENGTH_24=24,AES_KEY_LENGTH_32=32
};

class CCryptoUtil
{
public:
	static int encrypt4aes(const string &inData,const string &strKey,string &outData,string &errMsg)
	{
		outData = "";
		errMsg = "";
		if (inData.empty() || strKey.empty())	//判断待加密的字符串或者秘钥是否空
		{
			errMsg = "indata or key is empty!!!";
			return -1;
		}
		unsigned int iKeyLen = strKey.length();
		//判断秘钥的长度是否符合要求
		if (iKeyLen!=AES_KEY_LENGTH_16 &&iKeyLen!=AES_KEY_LENGTH_24 &&iKeyLen!=AES_KEY_LENGTH_32)
		{
			errMsg = "aes key invalid!!!";
			return -2;
		}
		byte iv[AES::BLOCKSIZE];
		int iResult = 0;
		try
		{
			CBC_Mode<AES>::Encryption e;	//CBC模式加密
			e.SetKeyWithIV((byte*) strKey.c_str(),iKeyLen,iv);
			//加密函数，outDATA是加密的结果
			StringSource ss(inData,true,new StreamTransformationFilter(e,new StringSink(outData)));
		}catch(const CryptoPP::Exception& e)
		{	
			errMsg = "Encryptor throw exception!!!";
			iResult = -3;
		}
		return iResult;
	}

	static int decrypt4aes(const string &inData,const string &strKey,string &outData,string &errMsg)
	{
		outData = "";
		errMsg = "";
		if (inData.empty() || strKey.empty())	//判断待加密的字符串或者秘钥是否空
		{
			errMsg = "indata or key is empty!!!";
			return -1;
		}
		unsigned int iKeyLen = strKey.length();
		//判断秘钥的长度是否符合要求
		if (iKeyLen!=AES_KEY_LENGTH_16 &&iKeyLen!=AES_KEY_LENGTH_24 &&iKeyLen!=AES_KEY_LENGTH_32)
		{
			errMsg = "aes key invalid!!!";
			return -2;
		}
		byte iv[AES::BLOCKSIZE];
		int iResult = 0;
		try
		{
			CBC_Mode<AES>::Decryption d;	
			d.SetKeyWithIV((byte*) strKey.c_str(),iKeyLen,iv);	//CBC模式解密
			//解密函数，outDATA是解密的结果
			StringSource ss(inData,true,new StreamTransformationFilter(d,new StringSink(outData)));
		}catch(const CryptoPP::Exception& e)
		{	
			errMsg = "Encryptor throw exception!!!";
			iResult = -3;
		}
		return iResult;
	}
};

int main(int argc , char **argv)
{
	string strCipher;	//待加密的字符串
	string strKey;		//同来加密的密钥
	cout << "Please enter a string"<<endl;	
	cin >> strCipher;
	cout << "Please enter a key,you just can write 16,24 or 32 words as a key"<<endl;
	cin >> strKey;


	string strResult;
	string strErrMsg;
	int iResult = CCryptoUtil::encrypt4aes(strCipher,strKey,strResult,strErrMsg);
	if(iResult)
	{
		cout<<"CCryptoUtil::encrypt4ase failed,errMsg:"<<strErrMsg;
		return -1;
	}
	
	string strPlainText;
	iResult = CCryptoUtil::decrypt4aes(strResult,strKey,strPlainText,strErrMsg);	
	if(iResult)
	{
		cout<<"CCryptoUtil::decrypt4ase failed,errMsg:"<<strErrMsg;
		return -2;
	}
	cout << "PlainText:"<<strPlainText << endl;
}
#endif //_CRYPTO_UTIL_H_
