#include "GL_FunctionLoader.h"

#include "src/system/logging/Logger.h"
#include "src/system/render/openGL/GL_Include.h"

//**********Vertex arrays**************************
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
//*************************************************

//**********Buffers********************************
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBUFFERDATAPROC glBufferData;
//*************************************************

//**********Shaders********************************
PFNGLCREATESHADERPROC glCreateShader;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
//*************************************************

//**********Shaders Program************************
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLDETACHSHADERPROC glDetachShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLVALIDATEPROGRAMPROC glValidateProgram;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLUNIFORM1FPROC glUniform1f;
PFNGLUNIFORM2FPROC glUniform2f;
PFNGLUNIFORM3FPROC glUniform3f;
PFNGLUNIFORM4FPROC glUniform4f;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
//*************************************************

void* getGLFunctionPointer(const char* name) {
	void* p = (void*)wglGetProcAddress(name);
	if (p == 0 || (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) || (p == (void*)-1)) {
		Loggers::GL->error("Failed to load function %s.", name);
	}

	return p;
}

void loadAllGLFunctions() {
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)getGLFunctionPointer("glGenVertexArrays");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)getGLFunctionPointer("glBindVertexArray");
	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)getGLFunctionPointer("glDeleteVertexArrays");

	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)getGLFunctionPointer("glEnableVertexAttribArray");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)getGLFunctionPointer("glDisableVertexAttribArray");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)getGLFunctionPointer("glVertexAttribPointer");

	glGenBuffers = (PFNGLGENBUFFERSPROC)getGLFunctionPointer("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)getGLFunctionPointer("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)getGLFunctionPointer("glBufferData");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)getGLFunctionPointer("glDeleteBuffers");

	glCreateShader = (PFNGLCREATESHADERPROC)getGLFunctionPointer("glCreateShader");
	glDeleteShader = (PFNGLDELETESHADERPROC)getGLFunctionPointer("glDeleteShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)getGLFunctionPointer("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)getGLFunctionPointer("glCompileShader");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)getGLFunctionPointer("glGetShaderiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)getGLFunctionPointer("glGetShaderInfoLog");

	glCreateProgram = (PFNGLCREATEPROGRAMPROC)getGLFunctionPointer("glCreateProgram");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)getGLFunctionPointer("glDeleteProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC)getGLFunctionPointer("glAttachShader");
	glDetachShader = (PFNGLDETACHSHADERPROC)getGLFunctionPointer("glDetachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)getGLFunctionPointer("glLinkProgram");
	glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)getGLFunctionPointer("glValidateProgram");
	glUseProgram = (PFNGLUSEPROGRAMPROC)getGLFunctionPointer("glUseProgram");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)getGLFunctionPointer("glGetProgramiv");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)getGLFunctionPointer("glGetProgramInfoLog");

	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)getGLFunctionPointer("glBindAttribLocation");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)getGLFunctionPointer("glGetUniformLocation");
	glUniform1f = (PFNGLUNIFORM1FPROC)getGLFunctionPointer("glUniform1f");
	glUniform2f = (PFNGLUNIFORM2FPROC)getGLFunctionPointer("glUniform2f");
	glUniform3f = (PFNGLUNIFORM3FPROC)getGLFunctionPointer("glUniform3f");
	glUniform4f = (PFNGLUNIFORM4FPROC)getGLFunctionPointer("glUniform4f");
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)getGLFunctionPointer("glUniformMatrix4fv");
}