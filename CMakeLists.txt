cmake_minimum_required(VERSION 3.13)
project(netsim)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wno-unused-variable -Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)#TODO ten nie daje warningów o nieużywanych zmiennych
#add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)

include_directories(
        include
)

set(SOURCE_FILES
        src/factory.cpp  
        src/helpers.cpp  
        src/nodes.cpp  
        src/package.cpp
        src/reports.cpp  
        src/simulation.cpp  
        src/storage_types.cpp  
        src/types.cpp
        )

add_executable(netsim ${SOURCE_FILES} main.cpp)


# == Unit testing using Google Testing Framework ==

# Ustaw zmienną `SOURCES_FILES_TESTS`, która będzie przechowywać ścieżki do
# plików źródłowych z testami jednostkowymi.
set(SOURCES_FILES_TESTS
        test/test_package.cpp
        test/test_storage_types.cpp
        )

# Dodaj konfigurację typu `Test`.
add_executable(my_project_test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)

# Dodaj katalogi z plikami nagłówkowymi wyłącznie do konkretnej konfiguracji (tu: `Test`).
target_include_directories(my_project_test PUBLIC
        googletest-release-1.11.0/googlemock/include
        googletest-release-1.11.0/googletest/include
        mocks
        )

# Dodaj podkatalog `googletest-master`.
add_subdirectory(googletest-release-1.11.0)

# Podlinkuj bibliotekę o identyfikatorze `gmock` (w pliku CMake) wyłącznie do konkretnej
# konfiguracji (tu: `Test`).
target_link_libraries(my_project_test gmock)