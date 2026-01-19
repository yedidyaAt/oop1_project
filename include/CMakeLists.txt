#target_include_directories (${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
#file (GLOB MY_HEADER_FILES CONFIGURE_DEPENDS LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.h)
#target_sources (${CMAKE_PROJECT_NAME} PRIVATE ${MY_HEADER_FILES})

# מוצא את כל קבצי ה-Header בתיקייה זו ובתתי התיקיות
file(GLOB_RECURSE MY_HEADER_FILES CONFIGURE_DEPENDS "*.h")

# מוסיף אותם לרשימת הקבצים של הפרויקט (בשביל ה-IDE)
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MY_HEADER_FILES})

# מגדיר את נתיבי החיפוש (Include Directories)
# כדי שהקוד שלך ימצא את הקבצים בתוך התיקיות החדשות
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Board
    ${CMAKE_CURRENT_SOURCE_DIR}/Controllers
    ${CMAKE_CURRENT_SOURCE_DIR}/GameObjects
    ${CMAKE_CURRENT_SOURCE_DIR}/UI
    ${CMAKE_CURRENT_SOURCE_DIR}/Utilities
)
