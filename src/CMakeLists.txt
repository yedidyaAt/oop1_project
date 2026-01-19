#file (GLOB_RECURSE MY_SOURCE_FILES CONFIGURE_DEPENDS LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.cpp)
#target_sources (${CMAKE_PROJECT_NAME} PRIVATE ${MY_SOURCE_FILES})

# מוצא את כל קבצי ה-CPP בתיקייה זו ובתתי התיקיות
file(GLOB_RECURSE MY_SOURCE_FILES CONFIGURE_DEPENDS "*.cpp")

# מוסיף אותם ל-Executable שהוגדר בקובץ הראשי
# ${CMAKE_PROJECT_NAME} הוא "oop1_ex04" לפי הקובץ שלך
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MY_SOURCE_FILES})