#pragma once

#include <openssl/evp.h>
#include <string>
#include <vector>

class AES
{
public:
    AES();
    ~AES();

    bool SetParam(const char *mode, uint32_t bits, const uint8_t *key, uint32_t keylen, const uint8_t *iv, uint32_t ivlen);

    int Encrypt(const uint8_t *ptext, uint32_t plen, uint8_t *ctext);
    int Decrypt(const uint8_t *ctext, uint32_t clen, uint8_t *ptext);

private:
    bool IsValidMode(const char *mode);
    bool IsValidBits(uint32_t bits);
    void SetCipher();

private:
    std::string             m_mode;
    uint32_t                m_bits;
    std::vector<uint8_t>    m_key;
    std::vector<uint8_t>    m_iv;
    const EVP_CIPHER       *m_cipher = nullptr;

    EVP_CIPHER_CTX         *m_ctxen = nullptr;
    EVP_CIPHER_CTX         *m_ctxde = nullptr;
};
