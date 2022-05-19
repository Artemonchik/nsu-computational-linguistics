cmake_minimum_required(VERSION 3.21)
project(task1)
set(CMAKE_CXX_STANDARD 17)
include(FetchContent)
FetchContent_Declare(
        pugixml
        GIT_REPOSITORY https://github.com/zeux/pugixml
)
FetchContent_MakeAvailable(pugixml)

FetchContent_Declare(
        termcolor
        GIT_REPOSITORY https://github.com/ikalnytskyi/termcolor
)
FetchContent_MakeAvailable(termcolor)

target_include_directories(pugixml INTERFACE
        $<BUILD_INTERFACE:${pugixml_SOURCE_DIR}/src>)


add_executable(task1 main.cpp src/dict/OpenCorpaDict.cpp include/dict/OpenCorpaDict.h src/dict/WordForm.cpp include/dict/WordForm.h src/dict/Lemma.cpp include/dict/Lemma.h src/text-parser/TextAnalyzer.cpp include/text-parser/TextAnalyzer.h src/text-parser/Converter.cpp include/text-parser/Converter.hpp src/Matchers.cpp include/Matchers.hpp include/Models.hpp src/Models.cpp include/types.hpp)
target_include_directories(termcolor INTERFACE
        $<BUILD_INTERFACE:${termcolor_SOURCE_DIR}/include>)

target_link_libraries(task1 pugixml termcolor)