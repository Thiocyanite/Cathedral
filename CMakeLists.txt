cmake_minimum_required(VERSION 3.13)
project(OpenGlSetup)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/Modules/")
message(WARNING CMAKE_MODULE_PATH : ${PROJECT_SOURCE_DIR}/Modules/)

set(SOURCE_FILES Source/main.cpp
        Source/Audio/Audio.h Source/Audio/Audio.cpp
        Source/Object/Converter.h
        Source/Object/Object.h
        Source/Object/ObjectLoader.h
        Source/Object/ObjectMenager.h
        Source/Object/Mesh.h
        Source/Object/MeshLoader.h
        Source/Menager.h Source/Menager.cpp
        Source/Observer.h Source/Observer.cpp
        Source/Object/Converter.cpp
        Source/Utility.cpp
        Source/Object/ObjectLoader.cpp
        Source/Shader.cpp Source/Shader.h
        Source/Object/AnimatedObject.cpp Source/Object/AnimatedObject.h
        Source/Object/AnimatedObjectCreator.cpp Source/Object/AnimatedObjectCreator.h
        Source/Object/ObjectCreationTools.cpp Source/Object/ObjectCreationTools.h)

add_executable(OpenGlSetup ${SOURCE_FILES})

find_package(glfw3 REQUIRED)
IF (NOT glfw3_FOUND)
    message(WARNING glfw3-NOT-FOUND : ${glfw3_INCLUDE_DIR})
ENDIF()

find_package(ASSIMP REQUIRED)
IF(NOT ASSIMP_FOUND)
    message(WARNING ASSIMP-NOT-FOUND : ${ASSIMP_INCLUDE_DIRS})
ENDIF()

find_package(GLEW REQUIRED)
IF (NOT GLEW_FOUND)
    message(WARNING GLEW-NOT-FOUND : ${GLEW_INCLUDE_DIR})
ENDIF()

find_package(GLM REQUIRED)
IF (NOT GLM_FOUND)
    message(WARNING GLM-NOT-FOUND : ${GLM_INCLUDE_DIR})
ENDIF()

find_package(GLM REQUIRED)
IF (NOT GLM_FOUND)
    message(WARNING GLM-NOT-FOUND : ${GLM_INCLUDE_DIR})
ENDIF()

find_package(SDL2_mixer REQUIRED)
IF (NOT SDL2_MIXER_FOUND)
    message(WARNING SDL2_mixer-NOT-FOUND : ${SDL2_MIXER_INCLUDE_DIRS})
ENDIF()

find_package(OpenGL REQUIRED)
IF (NOT OPENGL_FOUND)
    message(WARNING OPENGL-NOT-FOUND: ${OPENGL_INCLUDE_DIR})
else()
    message(OPENGL-FOUND: ${OPENGL_INCLUDE_DIR})
    message(SDL2-FOUND: ${SDL2_INCLUDE_DIR})
    message(GLM-FOUND : ${GLM_INCLUDE_DIRS})
    message(glfw3-FOUND : ${glfw3})
    message(GLEW-FOUND : ${GLEW_INCLUDE_DIRS})
    message(ASSIMP-FOUND : ${ASSIMP_INCLUDE_DIRS})
    message(SDL2_mixer-FOUND : ${SDL2_MIXER_INCLUDE_DIRS})
ENDIF()

include_directories(${OPENGL_INCLUDE_DIR} ${GLM_INCLUDE_DIRS} )

target_link_libraries(OpenGlSetup ${OPENGL_LIBRARY} ${GLEW_LIBRARY} ${ASSIMP_LIBRARIES} ${SDL2_MIXER_LIBRARIES} glfw)
