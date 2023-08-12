# CMakeList.txt : CMake project for Image Steganography, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#add_library(stb_image SHARED "ext/stb/stb_image.h")
#set_target_properties(stb_image PROPERTIES LINKER_LANGUAGE C)
#target_compile_definitions(stb_image PRIVATE STB_IMAGE_IMPLEMENTATION)

#add_library(stb_image_write SHARED "ext/stb/stb_image_write.h")
#set_target_properties(stb_image_write PROPERTIES LINKER_LANGUAGE C)
#target_compile_definitions(stb_image_write PRIVATE STB_IMAGE_WRITE_IMPLEMENTATION)

project ("Image Steganography")

# set(IMGSteganography "Image Steganography")

# Add source to this project's executable.
add_executable (IMGSteganography "src/main.h" "src/main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET IMGSteganography PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
