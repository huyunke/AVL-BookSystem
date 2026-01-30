cmake_minimum_required(VERSION 3.14)
add_compile_definitions(_WIN32_WINNT=0x0A00)
project(AVL_BookSystem)

set(CMAKE_CXX_STANDARD 20)

# 修复 MinGW 汇编器不支持 gdwarf-5 的问题
if(MINGW)
    string(REPLACE "-g" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    string(REPLACE "-g" "" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g0")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g0")
endif()

# 添加 SQLite3 库
add_library(sqlite3 STATIC utils/sqlite3.c)
target_include_directories(sqlite3 PUBLIC utils)

add_executable(AVL_BookSystem
        entity/Book.cpp
        entity/Book.h
        entity/User.cpp
        entity/User.h
        database/DatabaseOperator.cpp
        database/DatabaseOperator.h
        database/dao/BookDAO.cpp
        database/dao/BookDAO.h
        database/dao/UserDAO.cpp
        database/dao/UserDAO.h
        entity/BookCopy.cpp
        entity/BookCopy.h
        database/dao/BookCopyDAO.cpp
        database/dao/BookCopyDAO.h
        utils/PasswordUtils.cpp
        utils/PasswordUtils.h
        database/dao/RecordDAO.cpp
        database/dao/RecordDAO.h
        entity/Record.cpp
        entity/Record.h
        utils/TxtToDatabaseWriter.cpp
        utils/TxtToDatabaseWriter.h
        database/DatabaseInitializer.cpp
        database/DatabaseInitializer.h
        service/borrowService.cpp
        service/borrowService.h
        service/InventoryService.cpp
        service/InventoryService.h
        service/UserService.cpp
        service/UserService.h
        service/SearchService.cpp
        service/SearchService.h
)

# 添加测试程序
add_executable(test_database_init
        database/DatabaseOperator.cpp
        database/DatabaseOperator.h
        database/DatabaseInitializer.cpp
        database/DatabaseInitializer.h
        database/dao/BookDAO.cpp
        database/dao/BookDAO.h
        database/dao/UserDAO.cpp
        database/dao/UserDAO.h
        database/dao/BookCopyDAO.cpp
        database/dao/BookCopyDAO.h
        database/dao/RecordDAO.cpp
        database/dao/RecordDAO.h
        entity/Book.cpp
        entity/Book.h
        entity/BookCopy.cpp
        entity/BookCopy.h
        entity/User.cpp
        entity/User.h
        entity/Record.cpp
        entity/Record.h
        utils/PasswordUtils.cpp
        utils/PasswordUtils.h
)

# 链接SQLite3库和BCrypt库到主程序
target_link_libraries(AVL_BookSystem PRIVATE sqlite3 bcrypt)

# 添加HTTP服务器程序
add_executable(server_main server_main.cpp
        database/DatabaseOperator.cpp
        database/DatabaseOperator.h
        database/DatabaseInitializer.cpp
        database/DatabaseInitializer.h
        database/dao/UserDAO.cpp
        database/dao/UserDAO.h
        service/UserService.cpp
        service/UserService.h
        controller/AuthController.cpp
        controller/AuthController.h
        controller/Router.cpp
        controller/Router.h
        entity/User.cpp
        entity/User.h
        utils/PasswordUtils.cpp
        utils/PasswordUtils.h
)

# 链接SQLite3库和系统库到服务器程序
target_link_libraries(server_main PRIVATE sqlite3 ws2_32 bcrypt)

# 链接SQLite3库和BCrypt库到测试程序
target_link_libraries(test_database_init PRIVATE sqlite3 bcrypt)