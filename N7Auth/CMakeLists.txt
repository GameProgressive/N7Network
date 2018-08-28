set(SOURCES
	${CMAKE_CURRENT_LIST_DIR}/N7Server.cpp
	${CMAKE_CURRENT_LIST_DIR}/N7Server.h
	${CMAKE_CURRENT_LIST_DIR}/ModuleMain.cpp
	${CMAKE_CURRENT_LIST_DIR}/GSClient.cpp
	${CMAKE_CURRENT_LIST_DIR}/GSClient.h
	${CMAKE_CURRENT_LIST_DIR}/GSContainer.cpp
	${CMAKE_CURRENT_LIST_DIR}/GSContainer.h
)

include_directories("${CMAKE_CURRENT_LIST_DIR}/../common")

add_library(N7Auth SHARED ${SOURCES})
target_link_libraries(N7Auth N7Common)
