set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Укажите путь к компиляторам
set(CMAKE_C_COMPILER /usr/local/bin/x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER /usr/local/bin/x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER /usr/local/bin/x86_64-w64-mingw32-windres)

# Укажите путь к вашей установке Qt для Windows
set(CMAKE_PREFIX_PATH "/win")

# Укажите, что вы хотите искать библиотеки и заголовочные файлы в корневом пути
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
