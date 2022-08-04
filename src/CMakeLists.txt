cmake_minimum_required(VERSION 3.10.2)

project(wallhugger)

add_executable(${PROJECT_NAME}
	main.c
	player.c
	animation.c
	tiles.c
	entity.c
)

add_subdirectory(raylib)

target_include_directories(${PROJECT_NAME} PUBLIC raylib/include)
target_link_directories(${PROJECT_NAME} PRIVATE raylib/src)

target_link_libraries(${PROJECT_NAME} raylib)
