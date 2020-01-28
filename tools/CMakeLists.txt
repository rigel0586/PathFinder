ADD_CUSTOM_TARGET( tools )
INCLUDE_DIRECTORIES(include ${ROOT_INCLUDE_DIRS})

MACRO( ADD_PATHFINDER_TOOLS _name )
    ADD_EXECUTABLE( ${_name} ${ARGN} )
    TARGET_LINK_LIBRARIES( ${_name} ${PROJECT_NAME} ${ROOT_LIBS})
    INSTALL( TARGETS ${_name} DESTINATION bin )
ENDMACRO()

ADD_PATHFINDER_TOOLS( EfficiencyTest EfficiencyTest.cpp )
ADD_PATHFINDER_TOOLS( HoughSpaceTest HoughSpaceTest.cpp )
ADD_PATHFINDER_TOOLS( HoughSpaceComputingTimeTest HoughSpaceComputingTimeTest.cpp )
