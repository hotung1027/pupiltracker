find_package (OpenCV REQUIRED)
find_package (Boost REQUIRED)
find_package (TBB REQUIRED)
find_package (Boost COMPONENTS python REQUIRED)
find_package (PythonLibs REQUIRED)
find_package (PythonInterp REQUIRED)



add_library (
    pupiltracker

    PupilTracker.cpp
    cvx.cpp
    utils.cpp
)

add_library (
    pupiltracker-pythonwrapper
    SHARED
    conversion.cpp
)

include_directories(
    SYSTEM
    ${Boost_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    ${TBB_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}    
)

target_link_libraries(pupiltracker-pythonwrapper ${PYTHON_LIBRARIES})

install(TARGETS pupiltracker
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(DIRECTORY pupiltracker
        DESTINATION include)
install(TARGETS pupiltracker-pythonwrapper
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
install(DIRECTORY pupiltracker-pythonwrapper
	DESTINATION include)
