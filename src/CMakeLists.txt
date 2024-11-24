set(target ${MP2_LIBRARY})

file(GLOB hdrs "*.h*" "${MP2_INCLUDE}/*.h*")
file(GLOB srcs "*.cpp")

add_library(${target} STATIC "tbitfield.cpp" "tset.cpp")
# target_link_libraries(${target} ${LIBRARY_DEPS})
