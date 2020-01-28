ADD_CUSTOM_TARGET( examples )
INCLUDE_DIRECTORIES(include ${ROOT_INCLUDE_DIRS})

MACRO( ADD_PATHFINDER_EXAMPLE _name )
    ADD_EXECUTABLE( ${_name} ${ARGN} )
    TARGET_LINK_LIBRARIES( ${_name} ${PROJECT_NAME} ${ROOT_LIBS})
    INSTALL( TARGETS ${_name} DESTINATION bin )
ENDMACRO()

ADD_PATHFINDER_EXAMPLE( BasicHitExample BasicHitExample.cpp )
ADD_PATHFINDER_EXAMPLE( FinderParameterExample FinderParameterExample.cpp )
ADD_PATHFINDER_EXAMPLE( TrackGenerationExample TrackGenerationExample.cpp )
ADD_PATHFINDER_EXAMPLE( TrackFindingExample TrackFindingExample.cpp )
ADD_PATHFINDER_EXAMPLE( TestExample TestExample.cpp )


