// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include <stdio.h>

/*
	GLFW

	GLFW是一个专门针对OpenGL的C语言库，它提供了一些渲染物体所需的最低限度的接口。
	它允许用户创建OpenGL上下文，定义窗口参数以及处理用户输入。
	--
	Wiki
	GLFW is a lightweight utility library for use with OpenGL. 
	GLFW stands for Graphics Library Framework. It provides programmers 
	with the ability to create and manage windows and OpenGL contexts, 
	as well as handle joystick, keyboard and mouse input.

	http://www.glfw.org/download.html
	(源代码编译库可以保证生成的库是兼容你的操作系统和CPU的，而预编译的二进制文件可能会出现兼容问题)
*/

/*
	GLEW (OpenGL Extension Wrangler Library)

	OpenGL只是一个标准/规范，具体的实现是由驱动开发商针对特定显卡实现的。由于OpenGL驱动版本众多，
	它大多数函数的位置都无法在编译时确定下来，需要在运行时查询。任务就落在了开发者身上，
	开发者需要在运行时获取函数地址并将其保存在一个函数指针中供以后使用。取得地址的方法因平台而异，
	在Windows上会是类似这样：

	// 定义函数原型
	typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
	// 找到正确的函数并赋值给函数指针
	GL_GENBUFFERS glGenBuffers  = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
	// 现在函数可以被正常调用了
	GLuint buffer;
	glGenBuffers(1, &buffer);

	GLEW 能解决上面那个繁琐的问题。
*/

int main()
{
	GLFWwindow* window;

	/* 初始化glfw库 */
	if (!glfwInit())
		return -1;

	/* 
		在初始化GLEW之前设置glewExperimental变量的值为GL_TRUE,
		这样做能让GLEW在管理OpenGL的函数指针时更多地使用现代化的技术，
		如果把它设置为GL_FALSE的话可能会在使用OpenGL的核心模式时出现一些问题
	*/
	glewExperimental = GL_TRUE;
	/* 初始化glew库 */
	if (!glewInit())
		return -1;

	/* 设置OpenGL模式 */
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* 设置版本号 等相关环境参数 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	/* 创建一个窗口和它的OpenGL上下文 */
	window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
	if (!window)
	{
		/* 没有创建会返回NULL */
		glfwTerminate();
		return -1;
	}

	/* 设置当前的窗口上下文 */
	glfwMakeContextCurrent(window);

	/* 查询版本相关信息 */
	/* glGetString 该函数需要在上下文初始化完成后才有效，否则返回NULL  */
	const char* version = (const char*)glGetString(GL_VERSION);
	printf("version = %s", version);

	/* 视口设置 */
	/*
		glViewport函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素），
		这里我们是直接从GLFW中获取的。我们从GLFW中获取视口的维度而不设置为800*600是为了让它在高DPI的屏幕上（比如说Apple的视网膜显示屏）也能正常工作。

		Important:
		OpenGL幕后使用glViewport中定义的位置和宽高进行2D坐标的转换，将OpenGL中的位置坐标转换为你的屏幕坐标。
		例如，OpenGL中的坐标(-0.5, 0.5)有可能（最终）被映射为屏幕中的坐标(200,450)。
		注意，处理过的OpenGL坐标范围只为-1到1，因此我们事实上将(-1到1)范围内的坐标映射到(0, 800)和(0, 600)。
	*/
	int iWidth, iHeight;
	glfwGetFramebufferSize(window, &iWidth, &iHeight);
	glViewport(0, 0, iWidth, iHeight);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	/* 循环，直到用户关闭窗口 */
	while (!glfwWindowShouldClose(window))
	{
		/* 在这里做渲染 */
		glClear(GL_COLOR_BUFFER_BIT);

		/* 交换缓冲区，即在window上更新内容 */
		glfwSwapBuffers(window);

		/* 轮询事件 */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
