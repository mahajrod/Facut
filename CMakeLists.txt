cmake_minimum_required(VERSION 3.5)
project(FaCut)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    header/filter_by_mean_quality.h
    header/filter_by_mean_quality_options.h
    header/kseq.h
    header/split_fastq.h
    header/split_fastq_options.h
    header/stat.h
    header/subsample_fastq.h
    header/subsample_fastq_options.h
    header/trim_and_filter_by_mean_quality.h
    header/trim_and_filter_by_mean_quality_options.h
    src/filter_by_mean_quality.c
    src/split_fastq.c
    src/stat.c
    src/subsample_fastq.c
    src/trim_and_filter_by_mean_quality.c)

add_executable(FaCut ${SOURCE_FILES})