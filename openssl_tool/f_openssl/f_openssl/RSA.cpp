#include "stdafx.h"
#include "RSA.h"
SELF_RSA::SELF_RSA()
{
#ifdef KEY_FILE
    Init();
#endif
}

SELF_RSA::~SELF_RSA()
{
#ifdef KEY_FILE
    BIO_free(m_pubio);
    BIO_free(m_priio);
    RSA_free(m_pubRsa);
    RSA_free(m_priRsa);
#endif
}

void SELF_RSA::Init()
{
    RSA* rsa = RSA_generate_key(2048, RSA_F4, NULL, NULL);
    BIO* bp = BIO_new(BIO_s_file());
    BIO_write_filename(bp, (void*)"publicEx.pem");
    PEM_write_bio_RSAPublicKey(bp, rsa);
    BIO_free_all(bp);

    bp = BIO_new(BIO_s_file());
    BIO_write_filename(bp, (void*)"privateEx.pem");
    PEM_write_bio_RSAPrivateKey(bp, rsa, NULL, NULL, 0, NULL, NULL);
    CRYPTO_cleanup_all_ex_data();
    BIO_free_all(bp);
    RSA_free(rsa);

    m_pubio = BIO_new_file("publicEx.pem", "rb");
    m_priio = BIO_new_file("privateEx.pem", "rb");

    m_pubRsa = PEM_read_bio_RSAPublicKey(m_pubio, NULL, NULL, NULL);
    if (rsa == nullptr) {
        LOG_ERROR("PEM_read_bio_RSAPublicKey failed!");
        return;
    }

    m_priRsa = PEM_read_bio_RSAPrivateKey(m_priio, NULL, NULL, NULL);
    if (rsa == nullptr) {
        LOG_ERROR("PEM_read_bio_RSAPrivateKey failed!");
        return;
    }
}

// 加密 并非签名
void SELF_RSA::SignByPrivateRsa(RSA* priRsa, const std::string& data, std::vector<char>& encrypt_data)
{
    int size = RSA_size(priRsa);
    size = size - RSA_PKCS1_PADDING_SIZE;// block_size 最大 如果加密的长度超出 需要循环分段加密 根据秘钥长度定 2048 即256字节 也就是245字节
    encrypt_data.resize(size);

    int ret = RSA_private_encrypt(data.size(), (unsigned char*)data.c_str(),
        (unsigned char*)encrypt_data.data(), priRsa, RSA_PKCS1_PADDING);
    if (ret < 0) {
        ERR_print_errors_fp(stderr);//错误输出
    }
}

void SELF_RSA::VerifySignByPublicRsa(RSA* pubRsa, const char* encrypt_data, std::string& outData)
{
    int size = RSA_size(pubRsa);
    std::vector<char>data;
    data.resize(size);

    int ret = RSA_public_decrypt(256, (unsigned char*)encrypt_data,
        (unsigned char*)data.data(), pubRsa, RSA_PKCS1_PADDING); // 如果加密数据超出 秘钥字节长度 256字节 即需要循环解密 
    
    outData = data.data();
}

void SELF_RSA::Base64Encode(const unsigned char* buffer, size_t len, char** base64Text)
{
    BIO* bio, * b64;
    BUF_MEM* bufferPtr;
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, buffer, len);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_CLOSE);

    *base64Text = (char*)calloc((*bufferPtr).length + 1, 1);
    (*base64Text)[(*bufferPtr).length] = '\0';
    if (!(*base64Text))
        LOG_ERROR("calloc base64Text failed!");
    memcpy_s(*base64Text, (*bufferPtr).length + 1, (*bufferPtr).data, (*bufferPtr).length);
    BIO_free_all(bio);
}

void SELF_RSA::Base64Decode(const char* b64message, unsigned char** buffer, size_t *len)
{
    BIO* bio, * b64;
    int decodeLen = CalcDecodeLength(b64message);

    *buffer = (unsigned char*)malloc(decodeLen + 1);
    (*buffer)[decodeLen] = '\0';

    bio = BIO_new_mem_buf(b64message, -1);
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);

    *len = BIO_read(bio, *buffer, strlen(b64message));
    BIO_free_all(bio);
}

size_t SELF_RSA::CalcDecodeLength(const char* b64input)
{
    size_t len = strlen(b64input), padding = 0;

    while (1) {
        if (b64input[len] == '\r' || b64input[len] == '\n' || b64input[len] == '\0') 
            len--;
        else
            break;
    }
    
    if ((char)b64input[len] == '=' && (char)b64input[len - 1] == '=')
        padding = 2;
    else if ((char)b64input[len] == '=')
        padding = 1;

    return (len * 3) / 4 - padding;
}

void SELF_RSA::Sha256(const std::string& data, std::string& encodedata)
{
    unsigned char msg[1000] = { 0 };
    SHA256((unsigned char*)data.c_str(), data.size(), msg);

    char* base64;
    size_t len;
    Base64Encode(msg, strlen((char*)msg), &base64);
    encodedata = (char*)msg;

}

void SELF_RSA::SignByPrivateRsa(const std::string& data, char** base64Text)
{
    std::vector<char> encrypt_data;
    SignByPrivateRsa(m_priRsa, data, encrypt_data);
    Base64Encode((unsigned char*)encrypt_data.data(), strlen(encrypt_data.data()), base64Text);
}

void SELF_RSA::VerifySignByPublicRsa(const char* b64message, std::string& outData)
{
    char* signMessage;
    size_t len;
    Base64Decode(b64message, (unsigned char**)&signMessage, &len);
    VerifySignByPublicRsa(m_pubRsa, signMessage, outData);
}

void SELF_RSA::PrivateKeySignAndBase64Encode(const std::string& priKey, const std::string& data, char** base64Text)
{
    BIO* in = BIO_new_mem_buf((void*)priKey.c_str(), -1);

    RSA* priRsa = PEM_read_bio_RSAPrivateKey(in, NULL, NULL, NULL);
    if (priRsa == nullptr) {
        LOG_ERROR("PEM_read_bio_RSAPrivateKey failed!");
        return;
    }
    std::vector<char> encrypt_data;
    SELF_RSA::SignByPrivateRsa(priRsa, data, encrypt_data);
    SELF_RSA::Base64Encode((unsigned char*)encrypt_data.data(), strlen(encrypt_data.data()), base64Text);
}

void SELF_RSA::PublicKeyVerifyAndBase64Decode(const std::string& pubKey, const std::string& b64message, std::string& outData)
{
    BIO* out = BIO_new_mem_buf((void*)pubKey.c_str(), -1);

    RSA* pubRsa = PEM_read_bio_RSAPublicKey(out, NULL, NULL, NULL);
    if (pubRsa == nullptr) {
        LOG_ERROR("PEM_read_bio_RSAPublicKey failed!");
        return;
    }
    char* signMessage;
    size_t len;
    Base64Decode(b64message.c_str(), (unsigned char**)&signMessage, &len);
    VerifySignByPublicRsa(pubRsa, signMessage, outData);
}

// 签名
void SELF_RSA::Marshal(const char* privateKey, const char* data, char* out)
{
    BIO* bio = BIO_new_mem_buf((void*)privateKey, -1);

    RSA* priRsa = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL);
    if (priRsa == nullptr) {
        LOG_ERROR("PEM_read_bio_RSAPublicKey failed!");
        return;
    }

    EVP_PKEY* pkey = EVP_PKEY_new();
    EVP_PKEY_set1_RSA(pkey, priRsa);
    RSA_free(priRsa);
    auto ctx = EVP_PKEY_CTX_new(pkey, NULL);

    // 签名
    auto mctx = EVP_MD_CTX_new();
    EVP_SignInit(mctx, EVP_sha256());

    unsigned int in_size = strlen(data);
    EVP_SignUpdate(mctx, data, in_size);

    EVP_SignFinal(mctx, (unsigned char*)out, &in_size, pkey);


    EVP_MD_CTX_free(mctx);
    EVP_PKEY_free(pkey);
}

void SELF_RSA::Unmarshal(const char* publicKey, const char* data, char* out)
{
    BIO* bio = BIO_new_mem_buf((void*)publicKey, -1);

    RSA* pubRsa = PEM_read_bio_RSAPublicKey(bio, NULL, NULL, NULL);
    if (pubRsa == nullptr) {
        LOG_ERROR("PEM_read_bio_RSAPublicKey failed!");
        return;
    }

    EVP_PKEY* pkey = EVP_PKEY_new();
    EVP_PKEY_set1_RSA(pkey, pubRsa);
    RSA_free(pubRsa);
    auto ctx = EVP_PKEY_CTX_new(pkey, NULL);

    // 签名
    auto mctx = EVP_MD_CTX_new();
    EVP_VerifyInit(mctx, EVP_sha256());

    unsigned int in_size = strlen(data);
    EVP_VerifyUpdate(mctx, data, in_size);

    EVP_VerifyFinal(mctx, (unsigned char*)out, in_size, pkey);

    EVP_MD_CTX_free(mctx);
    EVP_PKEY_free(pkey);
}