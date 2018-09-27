set(SOURCES
	${CMAKE_CURRENT_LIST_DIR}/N7Server.cpp
	${CMAKE_CURRENT_LIST_DIR}/N7Server.h
)

include_directories("${CMAKE_CURRENT_LIST_DIR}/../common")

add_library(N7Auth SHARED ${SOURCES})
target_link_libraries(N7Auth N7Common)
