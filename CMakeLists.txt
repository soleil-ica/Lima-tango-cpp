# --------------------------------------------------------------------------
# Dependencies
# --------------------------------------------------------------------------

find_package(yat4tango CONFIG REQUIRED)

# --------------------------------------------------------------------------
# Collect sources and includes
# --------------------------------------------------------------------------

file(GLOB_RECURSE sources
    src/*.cpp
    specifics/SimulatorCCD/*.cpp
    specifics/Layout/*.cpp
    specifics/Mask/*.cpp
    specifics/RoiCounters/*.cpp
)

set(includedirs
    src/
    specifics/SimulatorCCD/
    specifics/Layout/
    specifics/Mask/
    specifics/RoiCounters/
)

# --------------------------------------------------------------------------
# Mapping camera → folder + library
# --------------------------------------------------------------------------

set(CAMERA_INFO
    "andor:AndorCCD:limaandor"
    "basler:BaslerCCD:limabasler"
    "dhyana:Dhyana:limadhyana"
    "eiger:Eiger:limaeiger"
    "hamamatsu:Hamamatsu:limahamamatsu"
    "imxpad:ImXpad:limaimxpad"
    "lambda:Lambda:limalambda"
    "marccd:MarCCD:limamarccd"
    "merlin:Merlin:limamerlin"
    "pco:Pco:limapco"
    "perkinelmer:PerkinElmer:limaperkinelmer"
    "pilatus:PilatusPixelDetector:limapilatus"
    "roperscientific:PrincetonCCD:limaroperscientific"
    "slsjungfrau:SlsJungfrau:limaslsjungfrau"
    "slseiger:SlsEiger:limaslseiger"
    "spectralinstrument:SpectralInstrument:limaspectralinstrument"
    "spectrumone:SpectrumOneCCD:limaspectrumone"
    "ufxc:Ufxc:limaufxc"
    "uview:UviewCCD:limauview"
    "xpad:XpadPixelDetector:limaxpad"
)

set(EXTRA_CAMERA_SOURCES "")
set(EXTRA_CAMERA_INCLUDES "")
set(EXTRA_CAMERA_LIBS "")

string(ASCII 27 esc)
set(COL_GREEN "${esc}[32m")
set(COL_RED   "${esc}[31m")
set(COL_RESET "${esc}[0m")

message("Cameras enabled in ${EXECUTABLE_NAME}:")
foreach(entry ${CAMERA_INFO})
    string(REPLACE ":" ";" parts "${entry}")
    list(GET parts 0 cam)
    list(GET parts 1 subdir)
    list(GET parts 2 lib)

    string(TOUPPER ${cam} CAM_U)

    if(cam IN_LIST AVAILABLE_CAMERAS AND WITH_${CAM_U})
        message(STATUS "${COL_GREEN}✔${COL_RESET} Camera enabled: ${cam}  (subdir=${subdir}, lib=${lib})")
        file(GLOB_RECURSE camera_sources
            specifics/${subdir}/*.cpp
        )
        list(APPEND EXTRA_CAMERA_SOURCES ${camera_sources})
        list(APPEND EXTRA_CAMERA_INCLUDES specifics/${subdir})
        list(APPEND EXTRA_CAMERA_LIBS     ${lib})
    else()
        message(STATUS "${COL_RED}✘${COL_RESET} Camera skipped: ${cam}")
    endif()
endforeach()

set(EXTRA_SOURCES "")
set(EXTRA_INCLUDES "")
set(EXTRA_LIBS "")

if (WIN32 AND MSVC AND MSVC_VERSION LESS_EQUAL 1900)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        message(STATUS "Extra sources and includes for Windows 64 bits with Visual Studio 2015 or older (MSVC14)")
        file(GLOB_RECURSE plaform_sources
            specifics/Rixs/*.cpp
        )
        list(APPEND EXTRA_SOURCES ${plaform_sources})
        list(APPEND EXTRA_INCLUDES
            specifics/Rixs/
        )
        find_package(opencv_world)
        list(APPEND EXTRA_LIBS
            opencv_world::opencv_world
        )
    endif()
endif()

# --------------------------------------------------------------------------
# Target
# --------------------------------------------------------------------------

add_executable(${EXECUTABLE_NAME}
    ${sources}
    ${EXTRA_CAMERA_SOURCES}
    ${EXTRA_SOURCES}
)

target_include_directories(${EXECUTABLE_NAME}
    PRIVATE
        ${includedirs}
        ${EXTRA_CAMERA_INCLUDES}
        ${EXTRA_INCLUDES}
)

target_link_libraries(${EXECUTABLE_NAME} 
    PRIVATE 
        yat4tango::yat4tango
        nexuscpp::nexuscpp
        limasimulator
        ${EXTRA_CAMERA_LIBS}
        ${EXTRA_LIBS}
)

# --------------------------------------------------------------------------
# Compile definitions
# --------------------------------------------------------------------------

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" PROJECT_VERSION_RAW)
string(STRIP "${PROJECT_VERSION_RAW}" PROJECT_VERSION)

target_compile_definitions(${EXECUTABLE_NAME}
    PRIVATE
        PROJECT_NAME=${EXECUTABLE_NAME}
        PROJECT_VERSION=${PROJECT_VERSION}
)

# Enabling features
target_compile_definitions(${EXECUTABLE_NAME}
    PRIVATE
        SIMULATOR_ENABLED
        LAYOUT_ENABLED
        MASK_ENABLED
        ROICOUNTERS_ENABLED
)

target_compile_definitions(${EXECUTABLE_NAME}
    PRIVATE
        SOLEIL_YAT_STREAM
)

if (WIN32)
    if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
        message(STATUS "Compile definitions for Windows 32 bits")
        target_compile_definitions(${EXECUTABLE_NAME}
            PRIVATE
                _WIN32
        )
        # For uview camera
        # #import incompatibility with /MP option
        # With msvc 140 is not possible to disable multiprocessor compilation with /MP-
        if(MSVC)
            string(REGEX REPLACE "/MP[0-9]*" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
            message(STATUS "CMAKE_C_FLAGS=${CMAKE_C_FLAGS}")
            string(REGEX REPLACE "/MP[0-9]*" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
            message(STATUS "CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")
        endif()
    else()
        message(STATUS "Compile definitions for Windows 64 bits")
        target_compile_definitions(${EXECUTABLE_NAME}
            PRIVATE
                USE_NX_FINALIZER
                _WIN64
        )
        if (WIN32 AND MSVC AND MSVC_VERSION LESS_EQUAL 1900)
            # Windows 64 bits with Visual Studio 2015 or older (MSVC14)
            target_compile_definitions(${EXECUTABLE_NAME}
                PRIVATE
                    RIXS_ENABLED
            )
        endif()
    endif()
else()
    target_compile_definitions(${EXECUTABLE_NAME}
        PRIVATE
            __LINUX__
            linux
    )

    if(CMAKE_CXX_COMPILER_VERSION STREQUAL "4.4.7")
        # CentOS 6 default compiler
        if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
            message(STATUS "Compile definitions for CentOS 6 32 bits")
            target_compile_definitions(${EXECUTABLE_NAME}
                PRIVATE
                    UNIX_32_EL6
            )
        else()
            message(STATUS "Compile definitions for CentOS 6 64 bits")
           target_compile_definitions(${EXECUTABLE_NAME}
                PRIVATE
                    UNIX_64_EL6
            )
        endif()
    else()
        message(STATUS "Compile definitions for CentOS 7 64 bits")
        target_compile_definitions(${EXECUTABLE_NAME}
            PRIVATE
                LINUX64_NO_CRASH_REPORT
                UNIX_64_EL7
        )
    endif()
endif()

# --------------------------------------------------------------------------
# Install
# --------------------------------------------------------------------------

if(WIN32)
    # Add msvcp120.dll and msvcr120.dll to bin
    include(InstallRequiredSystemLibraries)
    install(
        TARGETS ${EXECUTABLE_NAME} 
        DESTINATION bin
    )
else()
    install(
        TARGETS ${EXECUTABLE_NAME} 
        LIBRARY DESTINATION lib
    )
endif()
