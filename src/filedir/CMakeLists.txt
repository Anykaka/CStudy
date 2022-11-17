# 设置库名
SET(LIB filedir)
# 获取当前目录全部头文件GLOB_RECURSE
FILE (GLOB ALL_HEAD "*.hpp" "*.h")
# 获取当前目录全部源文件
FILE (GLOB ALL_SOURCE "*.cpp" "*.c")
# # 获取指定路径下全部文件
# AUX_SOURCE_DIRECTORY(. TCP_IP_LIST)
# # 获取当前目录及子目录全部头文件
# FILE (GLOB_RECURSE ALL_HEAD "*.hpp" "*.h")
# # 获取当前目录及子目录全部源文件
# FILE (GLOB_RECURSE ALL_SOURCE "*.cpp" "*.c")
# 构建库
ADD_LIBRARY(${LIB}
    ${ALL_HEAD}
    ${ALL_SOURCE}
)
# 安装库到安装路径
INSTALL (TARGETS ${LIB} DESTINATION lib)
# 安装全部头文件到安装路径
INSTALL (FILES 
    ${ALL_HEAD}
    DESTINATION include/${LIB}
)


