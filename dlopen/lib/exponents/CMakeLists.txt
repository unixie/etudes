set(ME exponents)

add_library(${ME} SHARED)

set_target_properties(${ME}
PROPERTIES
    C_VISIBILITY_PRESET hidden
    CXX_VISIBILITY_PRESET hidden
)

target_compile_definitions(${ME}
    PRIVATE
    __LIB_DEVELOPMENT__
)

target_sources(${ME}
PRIVATE
    exponents.cpp
    exponents2.cpp
)

target_include_directories(${ME}
PRIVATE
    ${PROJECT_SOURCE_DIR}/lib/include
)

target_link_libraries(${ME}
PRIVATE
    directory
)

install(TARGETS ${ME} DESTINATION bin)