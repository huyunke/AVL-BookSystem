#include "PasswordUtils.h"
#include <sstream>
#include <iomanip>
#include <vector>

// 定义这个宏以避免 Windows API 的 byte 类型与 std::byte 冲突
#define byte win_byte_override
#include <windows.h>
#include <bcrypt.h>
#undef byte

// 辅助函数：将字节数组转换为十六进制字符串
static string bytesToHex(const unsigned char* data, size_t length) {
    stringstream ss;
    ss << hex << setfill('0');
    for (size_t i = 0; i < length; i++) {
        ss << setw(2) << static_cast<int>(data[i]);
    }
    return ss.str();
}

//生成随机盐值
string PasswordUtils::generateSalt() {
    unsigned char salt[SALT_SIZE];

    // 使用 BCryptGenRandom 生成随机字节
    NTSTATUS status = BCryptGenRandom(
        nullptr,                    // 使用默认算法提供程序
        salt,                       // 输出缓冲区
        SALT_SIZE,                  // 缓冲区大小
        BCRYPT_USE_SYSTEM_PREFERRED_RNG  // 使用系统首选RNG
    );

    if (!BCRYPT_SUCCESS(status)) {
        // 如果失败，返回空字符串或抛出异常
        return "";
    }

    // 转换为十六进制字符串
    return bytesToHex(salt, SALT_SIZE);
}

//计算哈希值
string PasswordUtils::hashPassword(const string& password, const string& salt) {
    // 将密码和盐值组合
    string combined = password + salt;

    BCRYPT_ALG_HANDLE hAlg = nullptr;
    BCRYPT_HASH_HANDLE hHash = nullptr;
    NTSTATUS status;
    DWORD hashLength = 0;
    DWORD resultLength = 0;

    // 打开SHA-256算法提供程序
    status = BCryptOpenAlgorithmProvider(
        &hAlg,
        BCRYPT_SHA256_ALGORITHM,
        nullptr,
        0
    );

    if (!BCRYPT_SUCCESS(status)) {
        return "";
    }

    // 获取哈希对象的长度
    status = BCryptGetProperty(
        hAlg,
        BCRYPT_HASH_LENGTH,
        reinterpret_cast<PUCHAR>(&hashLength),
        sizeof(DWORD),
        &resultLength,
        0
    );

    if (!BCRYPT_SUCCESS(status)) {
        BCryptCloseAlgorithmProvider(hAlg, 0);
        return "";
    }

    // 创建哈希对象
    status = BCryptCreateHash(
        hAlg,
        &hHash,
        nullptr,
        0,
        nullptr,
        0,
        0
    );

    if (!BCRYPT_SUCCESS(status)) {
        BCryptCloseAlgorithmProvider(hAlg, 0);
        return "";
    }

    // 哈希数据
    status = BCryptHashData(
        hHash,
        reinterpret_cast<PUCHAR>(const_cast<char*>(combined.c_str())),
        static_cast<ULONG>(combined.length()),
        0
    );

    if (!BCRYPT_SUCCESS(status)) {
        BCryptDestroyHash(hHash);
        BCryptCloseAlgorithmProvider(hAlg, 0);
        return "";
    }

    // 完成哈希并获取结果
    vector<unsigned char> hash(hashLength);
    status = BCryptFinishHash(
        hHash,
        hash.data(),
        hashLength,
        0
    );

    // 清理资源
    BCryptDestroyHash(hHash);
    BCryptCloseAlgorithmProvider(hAlg, 0);

    if (!BCRYPT_SUCCESS(status)) {
        return "";
    }

    // 转换为十六进制字符串
    return bytesToHex(hash.data(), hashLength);
}

//加密密码
string PasswordUtils::encryptPassword(const string& password) {
    // 生成随机盐值
    string salt = generateSalt();

    if (salt.empty()) {
        return "";
    }

    // 计算哈希值
    string hash = hashPassword(password, salt);

    if (hash.empty()) {
        return "";
    }

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