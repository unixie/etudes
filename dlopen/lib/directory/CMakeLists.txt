set(ME directory)

add_library(${ME} OBJECT)

# Since going into multiple independent targets
set_property(TARGET ${ME} PROPERTY POSITION_INDEPENDENT_CODE ON)

target_compile_definitions(${ME}
    PRIVATE
    __LIB_DEVELOPMENT__

)

target_sources(${ME}
PRIVATE
    directory.cpp
)

target_include_directories(${ME}
PRIVATE
    ${PROJECT_SOURCE_DIR}/lib/include
)
