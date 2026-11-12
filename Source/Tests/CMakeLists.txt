cmake_minimum_required(VERSION 3.15)
project(NautilusTests LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v3.7.1
	DOWNLOAD_EXTRACT_TIMESTAMP ON
)

FetchContent_MakeAvailable(Catch2)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS *.cpp)
add_executable(RunTests ${TEST_SOURCES})

target_compile_features(RunTests PRIVATE cxx_std_20)

target_link_libraries(RunTests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(RunTests PRIVATE NautilusCore)
target_link_libraries(RunTests PRIVATE NautilusEngine)

include(CTest)
include(Catch)
catch_discover_tests(RunTests DISCOVERY_MODE PRE_TEST)
