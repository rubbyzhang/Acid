set(OPENAL_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Libraries/openal/Include" PARENT_SCOPE)

if(UNIX AND APPLE)
	find_path(OPENAL_INCLUDE_DIR al.h)
	find_library(OPENAL_LIBRARY NAMES OpenAL)
else()
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		find_library(OPENAL_LIBRARY NAMES openal OpenAL32 OpenAL PATHS "${PROJECT_SOURCE_DIR}/Libraries/openal/Lib/" PARENT_SCOPE)
	elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
		find_library(OPENAL_LIBRARY NAMES openal OpenAL32 OpenAL PATHS "${PROJECT_SOURCE_DIR}/Libraries/openal/Lib32/" PARENT_SCOPE)
	endif()
endif()

set(OPENAL_FOUND "NO")

if(OPENAL_LIBRARY AND OPENAL_INCLUDE_DIR)
	set(OPENAL_FOUND "YES")
endif()
