#pragma once
#include <openssl\rsa.h>
#include <openssl\evp.h>
#include <openssl\pem.h>
#include <openssl\err.h>

#include <string>
#include <vector>

#define DY_PUBLIC_KEY "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4AmWbebQkjxBJO6W/72X\
pPGazDltoDPXlXNkvaF79djof28KVrwSyOwV/GpjB8nQajCzKHLGCwf1Pf6WAWu0\
ehtxw0PxXSEq/SbH2oDqBGvq4LNi48C0SPKEIgPRos0G8r5R78+DHC8ZzrB7NOmH\
iCHavL+CPG0krBRsdqxF7X41bD7ug6x1Z01c+FxpiUVi1P6GBaakqU1B7IALxMNu\
iXABNReGhJpVtlBjaCQ4mH9Ews/WUbWxVwqPIDqUlGUN2B/PGQJ2fN+uXClIOZG3\
p4rSPyLqlycUuOveyQjyfwh7JXvtW5up9t2oX6qZRNJAdB4fPj1MreVSV318fCnz\
eQIDAQAB"

#define KEY_FILE
class SELF_RSA {
public:
	SELF_RSA();
	~SELF_RSA();
	RSA* getpu() { return m_pubRsa; }
	RSA* getpr() { return m_priRsa; }

public:
	void Init();
	static void SignByPrivateRsa(RSA* priRsa,const std::string& data, std::vector<char>& encrypt_data);
	static void VerifySignByPublicRsa(RSA* pubRsa,const char* encrypt_data, std::string& outData);
	static void Base64Encode(const unsigned char* buffer, size_t len, char** base64Text);
	static void Base64Decode(const char* b64message, unsigned char** buffer, size_t* len);
	static size_t CalcDecodeLength(const char* b64input);

	static void Sha256(const std::string& data, std::string& encodedata);

public:

#ifdef KEY_FILE
	void SignByPrivateRsa(const std::string& data, char** base64Text);
	void VerifySignByPublicRsa(const char* b64message, std::string& outData);
#endif

	static void PrivateKeySignAndBase64Encode(const std::string& priKey, const std::string& data, char** base64Text);
	static void PublicKeyVerifyAndBase64Decode(const std::string& pubKey, const std::string& b64message, std::string& outData);

	static void Marshal(const char* privateKey, const char* data, char* out);
	static void Unmarshal(const char* publicKey, const char* data, char* out);

private:


	//EVP_PKEY    * m_pkey = nullptr;
	//EVP_PKEY_CTX* m_enctx = nullptr;
	//EVP_PKEY_CTX* m_dectx = nullptr;

#ifndef KEY_FILE
	std::string m_pubKey;
	std::string m_priKey;
#endif // !KEY_FILE

	BIO* m_pubio = nullptr;
	BIO* m_priio = nullptr;

	RSA* m_pubRsa = nullptr;
	RSA* m_priRsa = nullptr;



};
