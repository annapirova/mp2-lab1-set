set(target ${MP2_TESTS})

file(GLOB hdrs "*.h")
file(GLOB srcs "test_main.cpp test_tbitfield.cpp test_tset.cpp")

#add_executable(${target} ${srcs} ${hdrs})

add_executable (${target} "test_main.cpp" "test_tbitfield.cpp" "test_tset.cpp")
target_link_libraries(${target} gtest ${MP2_LIBRARY})
 