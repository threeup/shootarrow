#OBJS specifies which files to compile as part of the project
OBJS = code/main.cpp code/Actor.cpp code/Camera.cpp code/Core.cpp code/cleanup.cpp code/Director.cpp code/Entity.cpp code/LTexture.cpp code/Physics.cpp code/User.cpp code/GLUtils.cpp lib/GLFramework/ESShader.cpp lib/GLFramework/ESShapes.cpp lib/GLFramework/ESTransform.cpp lib/GLFramework/ESUtil.cpp lib/GLFramework/ESUtil_winrpi.cpp

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
CFLAGS = -std=gnu++0x
CFLAGS+=-DRPI_NO_X

LIB_DIRS = -L/opt/vc/lib
INCLUDE_DIRS = -I./lib/esUtil -I/opt/vc/include -I/opt/vc/include/interface/vcos/ -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux

#LIBS specifies the libraries we're linking against
LIBS = -lSDL2 -lSDL2_image -lGLESv2 -lEGL -lm -lbcm_host


#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = shootarrow

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS) $(LIB_DIRS) $(INCLUDE_DIRS) $(CFLAGS) $(LIBS) -o $(OBJ_NAME)
