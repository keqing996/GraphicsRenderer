cmake_minimum_required(VERSION 3.26)

project(RenderEngine)
set(CMAKE_CXX_STANDARD 20)
set(TargetName RenderEngine)

# ====== Submodule ======
add_subdirectory(SubModule/PIIK)
add_subdirectory(SubModule/NativeWindow)

# ====== Source files ======
file (GLOB_RECURSE SRC_RES_FILES        Resource/*.rc)
file (GLOB_RECURSE SRC_CPP_FILES        Src/*.cpp)
file (GLOB_RECURSE SRC_MANIFEST_FILES   Manifest/*.manifest)

# ===== Executable ======
add_executable              (${TargetName} ${SRC_RES_FILES} ${SRC_CPP_FILES} ${SRC_MANIFEST_FILES})
set_target_properties       (${TargetName} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
set_target_properties       (${TargetName} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
target_include_directories  (${TargetName} PRIVATE Src/)
target_include_directories  (${TargetName} PRIVATE ThirdParty/)
target_link_libraries       (${TargetName} native_window)
target_link_libraries       (${TargetName} piik)
