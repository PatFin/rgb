add_executable(Cascade    cascade.cpp)
add_executable(Cycle      cycle.cpp)
add_executable(Raindrop   raindrop.cpp)
add_executable(Random     random.cpp)


target_link_libraries(Cascade PUBLIC rgb)
target_link_libraries(Cycle PUBLIC rgb)
target_link_libraries(Raindrop PUBLIC rgb)
target_link_libraries(Random PUBLIC rgb)
