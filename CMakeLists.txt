project(GardenApp)
add_executable(GardenApp src/start.c src/sim.c src/app.c)
target_link_libraries(GardenApp SDL2)

