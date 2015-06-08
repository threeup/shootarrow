#ifdef __unix__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif
#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#endif
#include <stdio.h>
#include <string>
#include <cmath>
#include "main.h"
#include "Core.h"
#include "cleanup.h"
#include "LTexture.h"
#include "GLUtils.h"
#include "../lib/GLFramework/ESUtil.h"

#include <GLES2/gl2.h>
#include <EGL/egl.h>
Core* gCore = NULL;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

typedef struct
{
	GLuint programObject;

} UserData;

bool InitGL(ESContext *esContext)
{
	UserData *userData = (UserData*)esContext->userData;
	GLbyte vShaderStr[] =
		"attribute vec4 vPosition;    \n"
		"void main()                  \n"
		"{                            \n"
		"   gl_Position = vPosition;  \n"
		"}                            \n";

	GLbyte fShaderStr[] =
		"precision mediump float;\n"\
		"void main()                                  \n"
		"{                                            \n"
		"  gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );\n"
		"}                                            \n";

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint programObject;
	GLint linked;

	// Load the vertex/fragment shaders
	vertexShader = GLUtils::LoadShader(GL_VERTEX_SHADER, (char*)vShaderStr);
	fragmentShader = GLUtils::LoadShader(GL_FRAGMENT_SHADER, (char*)fShaderStr);


	// Create the program object
	programObject = glCreateProgram();

	if (programObject == 0)
		return 0;

	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);

	// Bind vPosition to attribute 0   
	glBindAttribLocation(programObject, 0, "vPosition");

	// Link the program
	glLinkProgram(programObject);

	// Check the link status
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		GLint infoLen = 0;

		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = new char[infoLen];

			glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
			printf("Error linking program:\n%s\n", infoLog);

			free(infoLog);
		}

		glDeleteProgram(programObject);
		return FALSE;
	}

	// Store the program object
	userData->programObject = programObject;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	return TRUE;
}


///
// Draw a triangle using the shader pair created in Init()
//

int tick = 0;

GLfloat* MakeTriangle(int a, int b, int c)
{
	
	float angleA = (float)a * 3.1415f / 180.f;
	float angleB = (float)b * 3.1415f / 180.f;
	float angleC = (float)c * 3.1415f / 180.f;

	float factor = 0.5f;
	GLfloat* vVertices = new GLfloat[9];
	
	vVertices[0] = factor*cos(angleA);
	vVertices[1] = factor*sin(angleA);
	vVertices[3] = factor*cos(angleB);
	vVertices[4] = factor*sin(angleB);
	vVertices[6] = factor*cos(angleC);
	vVertices[7] = factor*sin(angleC);
	vVertices[2] = vVertices[5] = vVertices[8] = 0.f;
	return vVertices;
}

void Draw(ESContext *esContext)
{
	UserData *userData = (UserData *)esContext->userData;
	tick++;
	GLfloat* vVertices = MakeTriangle(90 + tick, 210 + tick, 330 + tick);
	

	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// Set the viewport
	glViewport(0, 0, esContext->width, esContext->height);


	// Use the program object
	glUseProgram(userData->programObject);

	// Load the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

#ifdef _WIN32 
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
#endif
	delete[] vVertices;
}

bool initSDL()
{
	//Initialization flag
	bool success = true;
	
	success = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) >= 0;
	if (!success) { printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError()); }

	success = SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") == SDL_TRUE;
	if (!success) { printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError()); }

	//Check for joysticks
	if (SDL_NumJoysticks() < 1)
	{
		printf("Warning: No joysticks connected!\n");
	}
	else
	{
		//Load joystick
		gCore->gGameController = SDL_JoystickOpen(0);
		success = gCore->gGameController != NULL;
		if (!success) { printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError()); }
	}

	bool sdlWindow = false;

	if (sdlWindow)
	{
		//Create window
		gCore->gWindow = SDL_CreateWindow("Shoot Arrow X", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		success = gCore->gWindow != NULL;
		if (!success) { printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError()); }

		gCore->gRenderer = SDL_CreateRenderer(gCore->gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		success = gCore->gRenderer != NULL;
		if (!success) { printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError()); }

		//Initialize renderer color
		SDL_SetRenderDrawColor(gCore->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;

		success = (IMG_Init(imgFlags) & imgFlags) > 0;
		if (!success) { printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError()); }
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	return success;
}

void close()
{
	gCore->ClearData();

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Update(ESContext *esContext, float deltaTime)
{
	bool quit = false;
	gCore->CoreLoopTick(quit);

}

int main(int argc, char* args[])
{
	bool success = true;
	ESContext esContext;
	UserData  userData;
	ESUtil* esUtil = new ESUtil();

	gCore = Core::GetInstance();

	if (success)
	{
		esUtil->InitContext(&esContext);
		esContext.userData = &userData;

		esUtil->CreateMainWindow(&esContext, "Hello Triangle", 320, 240, ES_WINDOW_RGB);

		success = InitGL(&esContext);
	}
	if (!success)
	{
		printf("Failed to initialize!\n");
	}
	
	if (success)
	{
		//success = initSDL();
	}
	if (!success)
	{
		printf("Failed to initialize!\n");
	}
	if (success)
	{
		//success = loadMedia();
		gCore->CoreStart();
	}
	if (!success)
	{
		printf("Failed to load media!\n");
	}
	
	//Main loop flag
	bool quit = false;

	//Event handler
	//SDL_Event e;

	printf("start\n");
	//While application is running
	

	esUtil->RegisterDrawFunc(&esContext, Draw);
	esUtil->RegisterUpdateFunc(&esContext, Update);
	esUtil->MainLoop(&esContext);
	

	printf("quit\n");

	//Free resources and close SDL
	close();

	return 0;
}
