#include "PasswordUtils.h"
#include "cryptopp/sha.h"          // Crypto++ SHA-256
#include "cryptopp/hex.h"        // Crypto++ Hex编码
#include "cryptopp/osrng.h"        // Crypto++ 随机数生成器
#include "cryptopp/filters.h"      // Crypto++ 过滤器

using namespace CryptoPP;

//生成随机盐值
string PasswordUtils::generateSalt() {
    // 创建随机数生成器
    AutoSeededRandomPool rng;

    // 生成随机字节
    CryptoPP::byte salt[SALT_SIZE];
    rng.GenerateBlock(salt, SALT_SIZE);

    // 转换为十六进制字符串
    string saltHex;
    HexEncoder encoder(new StringSink(saltHex));
    encoder.Put(salt, SALT_SIZE);
    encoder.MessageEnd();

    return saltHex;
}

//计算哈希值
string PasswordUtils::hashPassword(const string& password, const string& salt) {
    // 将密码和盐值组合
    string combined = password + salt;

    // 使用SHA-256计算哈希值
    SHA256 hash;
    string digest;

    StringSource ss(combined, true,
        new HashFilter(hash,
            new HexEncoder(
                new StringSink(digest)
            )
        )
    );

    return digest;
}

//加密密码
string PasswordUtils::encryptPassword(const string& password) {
    // 生成随机盐值
    string salt = generateSalt();

    // 计算哈希值
    string hash = hashPassword(password, salt);

    // 返回 "salt:hash" 格式
    return salt + ":" + hash;
}

//验证密码
bool PasswordUtils::verifyPassword(const string& password, const string& encryptedPassword) {
    // 分割盐值和哈希值
    size_t colonPos = encryptedPassword.find(':');
    if (colonPos == string::npos) {
        // 格式错误
        return false;
    }

    string salt = encryptedPassword.substr(0, colonPos);
    string storedHash = encryptedPassword.substr(colonPos + 1);

    // 使用相同的盐值计算输入密码的哈希值
    string calculatedHash = hashPassword(password, salt);

    // 比较哈希值
    return calculatedHash == storedHash;
}