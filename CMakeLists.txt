cmake_minimum_required(VERSION 3.16)
project(MyWebviewApp CXX)

# Require C++17 or later
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# 1. Fetch webview library
FetchContent_Declare(
    webview
    GIT_REPOSITORY https://github.com/webview/webview.git
    GIT_TAG master
)
FetchContent_MakeAvailable(webview)

# 2. Fetch sqlite_orm library (header-only)
FetchContent_Declare(
    sqlite_orm
    GIT_REPOSITORY https://github.com/fnc12/sqlite_orm.git
    GIT_TAG v1.9.1
)
FetchContent_MakeAvailable(sqlite_orm)

# 3. Locate system SQLite3 on macOS
find_package(SQLite3 REQUIRED)

# 4. Define your executable target
add_executable(MyWebviewApp main.cpp)

# 5. Link libraries and native macOS frameworks
target_link_libraries(MyWebviewApp PRIVATE
    webview::core
    sqlite_orm::sqlite_orm
    SQLite3::SQLite3
)

# macOS GUI apps require linking WebKit framework explicitly
if(APPLE)
    target_link_libraries(MyWebviewApp PRIVATE "-framework WebKit")
endif()