#define _CRYTO_UTIL_H_
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <iostream>
#include <string>
using namespace std;
#include <cryptopp/md5.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/default.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>
using namespace CryptoPP;

int main()
{
	std::string digest,inData;
	std::cin >> inData;
	Weak1::MD5 md5;		//创建md5对象
	StringSource(inData,true,new HashFilter(md5,new HexEncoder(new StringSink(digest))));			//转换的关键
	std::cout << digest;
}
//_CRYPTO_UTIL_H_
