cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_STANDARD_DEFAULT 99)
set(CMAKE_C_STANDARD_REQUIRED 99)

project(SmartFileOrganizer)

find_package(SndFile)
find_package(LibArchive REQUIRED)

add_executable(sfo src/main.c src/file_type_detection/file_type_detector.c src/file_type_detection/sound_files/get_sound_file_info.c
                   src/organize.c src/file_type_detection/archive_files/get_archive_file_info.c)

target_link_libraries(sfo PRIVATE SndFile::sndfile LibArchive::LibArchive magic)