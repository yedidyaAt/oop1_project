# העתקת כל תיקיית התמונות
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images DESTINATION ${CMAKE_BINARY_DIR})

# העתקת כל תיקיית הסאונד
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sounds DESTINATION ${CMAKE_BINARY_DIR})

# העתקת הפונטים
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/fonts DESTINATION ${CMAKE_BINARY_DIR})

# העתקת קובץ הלוח (אם הוא לא בתיקייה)
configure_file("Board.txt" ${CMAKE_BINARY_DIR}/Board.txt COPYONLY)