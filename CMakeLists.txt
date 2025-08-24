cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_STANDARD_DEFAULT 99)
set(CMAKE_C_STANDARD_REQUIRED 99)

project(SmartFileOrganizer)

find_package(SndFile)
find_package(LibArchive REQUIRED)

file(GLOB_RECURSE SOURCE_DIRS LIST_DIRECTORIES true "${CMAKE_SOURCE_DIR}/src/*")
file(GLOB_RECURSE INCLUDE_DIRS LIST_DIRECTORIES true "${CMAKE_SOURCE_DIR}/include/*")

set(INCLUDES "")
set(SOURCES "")

foreach(ITEM ${SOURCE_DIRS})
    if(NOT IS_DIRECTORY ${ITEM})
        list(APPEND SOURCES ${ITEM})
    endif()
endforeach()

foreach(ITEM ${INCLUDE_DIRS})
    if(IS_DIRECTORY ${ITEM})
        list(APPEND INCLUDES ${ITEM})
    endif()
endforeach()

list(APPEND INCLUDES "${CMAKE_SOURCE_DIR}/include/")

message(STATUS "Sources found: ${SOURCES}")
message(STATUS "Include directories found: ${INCLUDES}")

#Main target

add_executable(sfo ${SOURCES})
target_link_libraries(sfo PRIVATE SndFile::sndfile LibArchive::LibArchive magic)

#Test sounds target
#add_executable(test_sounds
#    tests/tests_get_sound_file_info.c
#    src/file_type_detection/sound_files/get_sound_file_info.c)
#target_link_libraries(test_sounds PRIVATE cunit SndFile::sndfile)

#Test images target
#add_executable(test_images
#    tests/tests_get_image_files.c
#    src/file_type_detection/file_type_detector.c
#    src/file_type_detection/sound_files/get_sound_file_info.c
#    src/file_type_detection/image_files/get_image_files.c)
#target_link_libraries(test_images PRIVATE cunit magic SndFile::sndfile)
