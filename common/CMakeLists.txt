set(SOURCES
	${CMAKE_CURRENT_LIST_DIR}/HTTPServer.cpp
	${CMAKE_CURRENT_LIST_DIR}/HTTPServer.h
	${CMAKE_CURRENT_LIST_DIR}/N7Common.h
	${CMAKE_CURRENT_LIST_DIR}/Base64.h
	${CMAKE_CURRENT_LIST_DIR}/Base64.cpp
	${CMAKE_CURRENT_LIST_DIR}/Utility.h
	${CMAKE_CURRENT_LIST_DIR}/Utility.cpp
)

add_library(N7Common STATIC ${SOURCES})
target_link_libraries(N7Common MDK)

if (RS_64BIT EQUAL 1)
	target_compile_definitions(N7Common PRIVATE __64BIT__)
endif()
