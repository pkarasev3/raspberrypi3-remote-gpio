# Standard CMake header config.
cmake_minimum_required(VERSION 3.3)
set(CMAKE_CXX_STANDARD 14)

####################################################
#### Note: LEDServer should be compiled only on the raspberry-pi!
set(BUILDING_FOR_RASPBERRY_PI  FALSE)
if(EXISTS /usr/lib/arm-linux-gnueabihf AND EXISTS /home/pi)
    set( BUILDING_FOR_RASPBERRY_PI  TRUE )
    add_definitions(-DBUILDING_FOR_RASPI=1)
    message(STATUS  "looks like we are building for raspberry pi, standby ...")
endif()


####################################################3
set(TRG LEDServer)
add_executable(${TRG} ${TRG}.cpp)
target_link_libraries(${TRG} PRIVATE  ${Boost_LIBRARIES}       )
if(${BUILDING_FOR_RASPBERRY_PI})
    target_link_libraries(${TRG}  PRIVATE  wiringPi)
endif()

####################################################3
set (TRG LEDClient)
add_executable(${TRG} ${TRG}.cpp)
target_link_libraries(${TRG} PRIVATE ${Boost_LIBRARIES})

if ( MSVC )
    set_property( TARGET ${TRG}
        APPEND PROPERTY LINK_FLAGS_RELEASE "/DEBUG"
    )
endif()
