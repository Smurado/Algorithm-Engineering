cmake_minimum_required(VERSION 3.26)
project(quantize LANGUAGES C)

set(QUANTIZE_SOURCES
        blur.h
        kmeans.h
        libimagequant.h
        mediancut.h
        mempool.h
        nearest.h
        pam.h
        blur.c
        kmeans.c
        libimagequant.c
        mediancut.c
        mempool.c
        nearest.c
        pam.c
)

add_library(quantize STATIC ${QUANTIZE_SOURCES})

target_link_directories(quantize PUBLIC ./)