一、cmake部分指令

1、project
profect(projectname [cxx] [x] [java])
执行工程支持的语言

隐式定义了两个变量
-<projectname>_BINARY_DIR            编译过程中二进制文件路径
-<projectname>_SOURCE_DIR           源文件路径

2、message
message([send_err | status | fatal_error] "message")
打印信息

status           打印前缀为--d的信息
send_error    产生错误 生成过程被跳过
fatal_error    立即终止所有的cmake过程

3、set
set(var [value] [cache type docstring [force]])
定义变量

设置库和执行文件的输出路径 覆盖add_subdirectory中的输出路径
set(executable_output_path ${project_binary_dir}/bin)   设置执行文件输出路径为 编译路径下bin文件夹中
set(library_output_path ${project_binary_dir}/lib)           设置库文件的输出路径


4、add_executable
add_executable(exe ${src_list})
定义可执行文件 包含源文件列表

5、add_subdirectory
add_subdirectory(source_dir [binary_dir] [exclude_from_all])
向当前工程添加存放源文件的目录 可以置顶中间二进制和目标二进制存放的位置
如果不指定编译输出路径 则在build下创建路径名的文件夹编译

subdirs(dir) 添加多个子目录，目前不推荐使用

6、add_library
add_library(libname [SHARED|STATIC|MOUDLE][EXCLUDE_FROM_ALL] source1 source2...)
SHARED 动态库
STATIC 静态库
MOUDLE 在使用dyld的系统有效 否则是动态库
EXCLUDE_FROM_ALL 不会被默认构建 除非有其他组件依赖或者手动构建

7、set_target_properities
set_target_properities(target1 target2 ...PROPERITIES prop1 value1 prop2 value2 ...)
设置输出的名称 设置动态库的版本和API版本

8、get_target_property
get_target_property(VAR target property)


二、基本语法规则
1、使用${}的方式取变量中的值 ，IF语句中可以直接用变量名 
2、指令参数之间用 “ ”或者“;”隔开
3、指令大小写都可以 参数和变量区分大小写
4、源文件名字难处理的可以set设置变量 源文件名称用“”括起来
5、可以使用make clean清理makefile的中间文件 cmake的中间文件要用rm -rf清理
6、project_source_dir指代工程路径 project_binary_dir指代编译路径

三、安装
将生成的可执行文件放到想放到的位置
1、makefile：
DESTDIR=
PREFIX=
install:
	mkdir -p $(DESTDIR)/$(PREFIX)/usr/bin
	install -m 755 hello $(DESTDIR)/$(PREFIX)/usr/bin
然后通过 make install安装

2、cmake
install(TARGETS targets ...
	[[ARCHIVE|LIBRARY|RUNTIME]\
	[DESTINATION<dir>]
	[PERMISSIONS permissions ...]
	[CONFIGURATION [Debug|Release|...]
	[COMPONENT <component>]
	[OPTIONAL]
	][...])
TARGETS 后面是生成的可执行文件或者库文件
	ARCHIVE：静态库
	LIBRARY：动态库
	RUNTIME：可执行目标二进制
	DESTINATION：定义安装路径 /为绝对路径(cmake_install_prefix无效) 否则为相对路径
eg：    
INSTALL(TARGETS myrun mylib mystaticlib
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION libstatic)

