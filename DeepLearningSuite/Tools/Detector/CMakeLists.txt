IF (DARKNET_ACTIVE)
    SET(EXTRA_LIBS ${EXTRA_LIBS} ${DARKNET_LIBRARIES} ${CUDA_LIBRARIES} -L/usr/local/cuda/lib64 cudart cublas curand)
    include_directories(${DARKNET_INCLUDE_DIR})
ENDIF()


include_directories(
        ${JdeRobot_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIR}
        ${CMAKE_CURRENT_LIST_DIR}
        ${DeepLearningSuite_INCLUDE_DIR}

)

add_executable (detector detector.cpp)

TARGET_LINK_LIBRARIES(detector
        DeepLearningSuite
        ${EXTRA_LIBS}
        ${JdeRobot_LIBRARIES}
        ${OpenCV_LIBRARIES}
        ${Boost_LIBRARIES}
        ${GLOG_LIBRARIES}
        ${Ice_LIBRARIES}
        ssl
        crypto
        )
