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

