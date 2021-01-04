add_library(glad SHARED
    include/glad/glad.h
    glad.c)
target_include_directories(glad PUBLIC include/)
