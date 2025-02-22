#include <QApplication>
#include <QFontDatabase>
#include "ui/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    app.setApplicationName("Stealer Builder");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("RedTeam Tools");
    
    // Load embedded fonts from resources
    QStringList fontPaths = {
        ":/fonts/fonts/LiberationSans-Regular.ttf",
        ":/fonts/fonts/LiberationSans-Bold.ttf",
        ":/fonts/fonts/LiberationMono-Regular.ttf"
    };
    
    for (const QString& fontPath : fontPaths) {
        QFontDatabase::addApplicationFont(fontPath);
    }
    
    MainWindow window;
    window.show();
    
    return app.exec();
}



// Commit 26 - 2024-03-25



// Commit 79 - 2024-09-30

// Commit 92 - 2024-11-05

// Commit 97 - 2024-11-20


// Commit 103 - 2024-12-06




// Commit 131 - 2025-02-22
