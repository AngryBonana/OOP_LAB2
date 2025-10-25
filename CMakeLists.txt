cmake_minimum_required(VERSION 3.10)

# Настройка проекта
project(lab_02 
    VERSION 1.0.0
    DESCRIPTION "Лабораторная работа 2: Класс Eleven"
    LANGUAGES CXX
)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройка директорий
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

# Добавление директории с заголовочными файлами
include_directories(${INCLUDE_DIR})

# Поиск исходных файлов библиотеки
file(GLOB_RECURSE LIBRARY_SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)

# Создание библиотеки
add_library(lab_02_lib ${LIBRARY_SOURCES})

# Создание исполняемого файла
add_executable(lab_02_exe main.cpp)

# Связывание библиотеки с исполняемым файлом
target_link_libraries(lab_02_exe PRIVATE lab_02_lib)

# Включение Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

FetchContent_MakeAvailable(googletest)

# Поиск тестовых файлов
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false ${TEST_DIR}/*.cpp)

# Создание исполняемого файла для тестов
add_executable(lab_02_tests ${TEST_SOURCES})

# Связывание тестов с библиотекой и gtest
target_link_libraries(lab_02_tests PRIVATE lab_02_lib GTest::gtest GTest::gtest_main)

# Добавление тестов в CTest
include(GoogleTest)
gtest_discover_tests(lab_02_tests)

# Настройка компилятора (опционально)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(lab_02_lib PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(lab_02_exe PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(lab_02_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()