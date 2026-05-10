cmake_minimum_required(VERSION 3.20)

project(COMP4300)

set(CMAKE_CXX_STANDARD 17)


set(SRC_FILES
    "src/Config/ConfigManager.cpp"
    "src/Actors/ShapeActor.cpp"
    "src/Actors/Circle.cpp"
    "src/Actors/Rectangle.cpp"
)


add_executable(${PROJECT_NAME} main.cpp ${SRC_FILES})

target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/external/imgui/imgui.cpp
    ${PROJECT_SOURCE_DIR}/external/imgui/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/external/imgui/imgui_tables.cpp
    ${PROJECT_SOURCE_DIR}/external/imgui/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/external/imgui/imgui_demo.cpp
    ${PROJECT_SOURCE_DIR}/external/imgui-sfml/imgui-SFML.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC 
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/external/include
    ${PROJECT_SOURCE_DIR}/external/include/imgui
    ${PROJECT_SOURCE_DIR}/external/include/imgui-sfml

)

target_link_directories(${PROJECT_NAME} PRIVATE
	${PROJECT_SOURCE_DIR}/external/lib
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/external/lib/sfml-graphics-d.lib
    ${PROJECT_SOURCE_DIR}/external/lib/sfml-window-d.lib
    ${PROJECT_SOURCE_DIR}/external/lib/sfml-system-d.lib
    opengl32
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/external/bin/
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/fonts
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/fonts
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${PROJECT_SOURCE_DIR}/config.txt
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/
)