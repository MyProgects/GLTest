// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include <stdio.h>

/*
	GLFW

	GLFW��һ��ר�����OpenGL��C���Կ⣬���ṩ��һЩ��Ⱦ�������������޶ȵĽӿڡ�
	�������û�����OpenGL�����ģ����崰�ڲ����Լ������û����롣
	--
	Wiki
	GLFW is a lightweight utility library for use with OpenGL. 
	GLFW stands for Graphics Library Framework. It provides programmers 
	with the ability to create and manage windows and OpenGL contexts, 
	as well as handle joystick, keyboard and mouse input.

	http://www.glfw.org/download.html
	(Դ����������Ա�֤���ɵĿ��Ǽ�����Ĳ���ϵͳ��CPU�ģ���Ԥ����Ķ������ļ����ܻ���ּ�������)
*/

/*
	GLEW (OpenGL Extension Wrangler Library)

	OpenGLֻ��һ����׼/�淶�������ʵ��������������������ض��Կ�ʵ�ֵġ�����OpenGL�����汾�ڶ࣬
	�������������λ�ö��޷��ڱ���ʱȷ����������Ҫ������ʱ��ѯ������������˿��������ϣ�
	��������Ҫ������ʱ��ȡ������ַ�����䱣����һ������ָ���й��Ժ�ʹ�á�ȡ�õ�ַ�ķ�����ƽ̨���죬
	��Windows�ϻ�������������

	// ���庯��ԭ��
	typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
	// �ҵ���ȷ�ĺ�������ֵ������ָ��
	GL_GENBUFFERS glGenBuffers  = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
	// ���ں������Ա�����������
	GLuint buffer;
	glGenBuffers(1, &buffer);

	GLEW �ܽ�������Ǹ����������⡣
*/

int main()
{
	GLFWwindow* window;

	/* ��ʼ��glfw�� */
	if (!glfwInit())
		return -1;

	/* 
		�ڳ�ʼ��GLEW֮ǰ����glewExperimental������ֵΪGL_TRUE,
		����������GLEW�ڹ���OpenGL�ĺ���ָ��ʱ�����ʹ���ִ����ļ�����
		�����������ΪGL_FALSE�Ļ����ܻ���ʹ��OpenGL�ĺ���ģʽʱ����һЩ����
	*/
	glewExperimental = GL_TRUE;
	/* ��ʼ��glew�� */
	if (!glewInit())
		return -1;

	/* ����OpenGLģʽ */
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* ���ð汾�� ����ػ������� */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	/* ����һ�����ں�����OpenGL������ */
	window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
	if (!window)
	{
		/* û�д����᷵��NULL */
		glfwTerminate();
		return -1;
	}

	/* ���õ�ǰ�Ĵ��������� */
	glfwMakeContextCurrent(window);

	/* ��ѯ�汾�����Ϣ */
	/* glGetString �ú�����Ҫ�������ĳ�ʼ����ɺ����Ч�����򷵻�NULL  */
	const char* version = (const char*)glGetString(GL_VERSION);
	printf("version = %s", version);

	/* �ӿ����� */
	/*
		glViewport����ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ���
		����������ֱ�Ӵ�GLFW�л�ȡ�ġ����Ǵ�GLFW�л�ȡ�ӿڵ�ά�ȶ�������Ϊ800*600��Ϊ�������ڸ�DPI����Ļ�ϣ�����˵Apple������Ĥ��ʾ����Ҳ������������

		Important:
		OpenGLĻ��ʹ��glViewport�ж����λ�úͿ�߽���2D�����ת������OpenGL�е�λ������ת��Ϊ�����Ļ���ꡣ
		���磬OpenGL�е�����(-0.5, 0.5)�п��ܣ����գ���ӳ��Ϊ��Ļ�е�����(200,450)��
		ע�⣬�������OpenGL���귶ΧֻΪ-1��1�����������ʵ�Ͻ�(-1��1)��Χ�ڵ�����ӳ�䵽(0, 800)��(0, 600)��
	*/
	int iWidth, iHeight;
	glfwGetFramebufferSize(window, &iWidth, &iHeight);
	glViewport(0, 0, iWidth, iHeight);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	/* ѭ����ֱ���û��رմ��� */
	while (!glfwWindowShouldClose(window))
	{
		/* ����������Ⱦ */
		glClear(GL_COLOR_BUFFER_BIT);

		/* ����������������window�ϸ������� */
		glfwSwapBuffers(window);

		/* ��ѯ�¼� */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
