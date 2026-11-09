add_executable(Editor src/main.cpp)
target_link_libraries(Editor PRIVATE NautilusEngine)
add_dependencies(Editor GameCode)

add_custom_command(TARGET Editor POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_if_different
$<TARGET_RUNTIME_DLLS:Editor> $<TARGET_FILE_DIR:Editor>
COMMAND_EXPAND_LISTS)