find_package (OpenCV REQUIRED)
find_package (Boost REQUIRED)
find_package (TBB REQUIRED)
find_package (Boost COMPONENTS python REQUIRED)
find_package (PythonLibs REQUIRED)
find_package (PythonInterp REQUIRED)

add_library (
    pupiltracker
    SHARED
    PupilTracker.cpp
    cvx.cpp
    utils.cpp
)

add_library (
    PupilTrackerPythonWrapper
    SHARED
    PupilTrackerPythonWrapper.cpp
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

target_link_libraries(PupilTrackerPythonWrapper ${PYTHON_LIBRARIES} ${BOOST_LIBRARIES} boost_python boost_numpy pupiltracker opencv_imgproc tbb)

set_target_properties(PupilTrackerPythonWrapper PROPERTIES PREFIX "")

install(TARGETS pupiltracker
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(DIRECTORY pupiltracker
        DESTINATION include)
install(TARGETS PupilTrackerPythonWrapper
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
install(DIRECTORY PupilTrackerPythonWrapper
	DESTINATION include)
