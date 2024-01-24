#include "stdafx.h"
#include "AES.h"


AES::AES()
{
    m_ctxen = EVP_CIPHER_CTX_new();
    m_ctxde = EVP_CIPHER_CTX_new();
}

AES::~AES()
{
    EVP_CIPHER_CTX_free(m_ctxen);
    EVP_CIPHER_CTX_free(m_ctxde);
}

bool AES::SetParam(const char *mode, uint32_t bits, const uint8_t *key, uint32_t keylen, const uint8_t *iv, uint32_t ivlen)
{
    if (!mode || !IsValidMode(mode)) return false;
    m_mode = mode;

    if (!IsValidBits(bits)) return false;
    m_bits = bits;

    if (!key) return false;

    auto len = bits / 8;
    if (keylen < len) return false;

    m_key.resize(keylen);
    memcpy(&m_key[0], key, keylen);

    if (iv) {
        if (ivlen < 16) return false;

        m_iv.resize(ivlen);
        memcpy(&m_iv[0], iv, ivlen);
    }

    SetCipher();

    return true;
}

bool AES::IsValidMode(const char *mode)
{
    const char *validModes[] = { "ecb", "cbc", "cfb", "ofb", "ctr", "ccm", "gcm" };

    return std::find_if(std::begin(validModes), std::end(validModes),
        [&](const char *p) { return strcmp(mode, p) == 0; }) != std::end(validModes);
}

bool AES::IsValidBits(uint32_t bits)
{
    uint32_t validBits[] = { 128, 192, 256 };

    return std::find(std::begin(validBits), std::end(validBits), bits) != std::end(validBits);
}

void AES::SetCipher()
{
    switch (m_bits) {

    case 128:
        if (m_mode == "ecb") m_cipher = EVP_aes_128_ecb();
        else if (m_mode == "cbc") m_cipher = EVP_aes_128_cbc();
        else if (m_mode == "cfb") m_cipher = EVP_aes_128_cfb();
        else if (m_mode == "ofb") m_cipher = EVP_aes_128_ofb();
        else if (m_mode == "ctr") m_cipher = EVP_aes_128_ctr();
        else if (m_mode == "ccm") m_cipher = EVP_aes_128_ccm();
        else if (m_mode == "gcm") m_cipher = EVP_aes_128_gcm();
        break;

    case 192:
        if (m_mode == "ecb") m_cipher = EVP_aes_192_ecb();
        else if (m_mode == "cbc") m_cipher = EVP_aes_192_cbc();
        else if (m_mode == "cfb") m_cipher = EVP_aes_192_cfb();
        else if (m_mode == "ofb") m_cipher = EVP_aes_192_ofb();
        else if (m_mode == "ctr") m_cipher = EVP_aes_192_ctr();
        else if (m_mode == "ccm") m_cipher = EVP_aes_192_ccm();
        else if (m_mode == "gcm") m_cipher = EVP_aes_192_gcm();
        break;

    case 256:
        if (m_mode == "ecb") m_cipher = EVP_aes_256_ecb();
        else if (m_mode == "cbc") m_cipher = EVP_aes_256_cbc();
        else if (m_mode == "cfb") m_cipher = EVP_aes_256_cfb();
        else if (m_mode == "ofb") m_cipher = EVP_aes_256_ofb();
        else if (m_mode == "ctr") m_cipher = EVP_aes_256_ctr();
        else if (m_mode == "ccm") m_cipher = EVP_aes_256_ccm();
        else if (m_mode == "gcm") m_cipher = EVP_aes_256_gcm();
        break;

    default:
        break;
    }
}

int AES::Encrypt(const uint8_t *ptext, uint32_t plen, uint8_t *ctext)
{
    auto rc = EVP_EncryptInit_ex(m_ctxen, m_cipher, nullptr,
        m_key.empty() ? nullptr : &m_key[0], m_iv.empty() ? nullptr : &m_iv[0]);
    if (rc != 1) return -1;

    int clen = 0;
    int out = 0;

    rc = EVP_EncryptUpdate(m_ctxen, ctext, &out, ptext, plen);
    if (rc != 1) return -2;
    clen += out;

    rc = EVP_EncryptFinal_ex(m_ctxen, ctext + out, &out);
    if (rc != 1) return -3;
    clen += out;

    return clen;
}

int AES::Decrypt(const uint8_t *ctext, uint32_t clen, uint8_t *ptext)
{
    auto rc = EVP_DecryptInit_ex(m_ctxde, m_cipher, nullptr,
        m_key.empty() ? nullptr : &m_key[0], m_iv.empty() ? nullptr : &m_iv[0]);
    if (rc != 1) return -1;

    int plen = 0;
    int out = 0;

    rc = EVP_DecryptUpdate(m_ctxde, ptext, &out, ctext, clen);
    if (rc != 1) return -2;
    plen += out;

    rc = EVP_DecryptFinal_ex(m_ctxde, ptext + out, &out);
    if (rc != 1) return -3;
    plen += out;

    return plen;
}
