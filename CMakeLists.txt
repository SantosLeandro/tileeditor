cmake_minimum_required(VERSION 3.10)
project(fltk_opengl_project)

# Find FLTK
find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIR})

# Find OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# Add nlohmann json (installed via dnf)
include_directories(/usr/include/nlohmann)

include_directories(/usr/include)

# Add all source files
set(SOURCES
    main.cpp
    editor.cpp
    editorUI.cpp
    gl_render.cpp
    level.cpp
    texture.cpp
    layer.cpp
    loader.cpp
    tilesetUI.cpp
    global.cpp
)

# Add executable
add_executable(editor ${SOURCES})

# Link libraries
target_link_libraries(editor ${FLTK_LIBRARIES} ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} GL GLU)
