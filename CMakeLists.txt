cmake_minimum_required(VERSION 3.16)

project(Restaurant_Management_System VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# —————————————
# 1) Find Qt modules
# —————————————
# We need both Widgets and Charts
find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# —————————————
# 2) Gather your sources
# —————————————
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    table.cpp
    table.h

    product.cpp
    product.h

    restaurant.cpp
    restaurant.h

    productcatalog.cpp
    productcatalog.h

    tablespage.cpp
    tablespage.h
    tablespage.ui

    clickablelabel.cpp
    clickablelabel.h

    orderpage.cpp
    orderpage.h
    orderpage.ui

    checkoutpage.cpp
    checkoutpage.h
    checkoutpage.ui

    productspage.cpp
    productspage.h
    productspage.ui

    reportspage.cpp
    reportspage.h
    reportspage.ui

    resources.qrc
)

# —————————————————————————
# 3) Qt6 vs Qt5 executable
# —————————————————————————
if (QT_VERSION_MAJOR GREATER_EQUAL 6)
    qt_add_executable(Restaurant_Management_System
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if (ANDROID)
        add_library(Restaurant_Management_System SHARED ${PROJECT_SOURCES})
    else()
        add_executable(Restaurant_Management_System ${PROJECT_SOURCES}
            homepage.h homepage.cpp homepage.ui)
    endif()
endif()

# —————————————————————————————
# 4) Link against Qt Widgets + Charts
# —————————————————————————————
target_link_libraries(Restaurant_Management_System
    PRIVATE
        Qt6::Widgets
        Qt6::Charts
)

# —————————————————————————————
# 5) Bundle / install settings…
# —————————————————————————————
if (QT_VERSION VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION
        MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Restaurant_Management_System
    )
endif()

set_target_properties(Restaurant_Management_System PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION     ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING  ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Restaurant_Management_System
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Restaurant_Management_System)
endif()
