File=main.cpp
SRC=./src/*.cpp glad.c
OBJ=./obj
APP=./bin/a.out
LIB=-lfreetype
HEAD=  -I ./include/ \
	   -I ./include/shader/ \
	   -I ./include/texture/ \
	   -I ./include/resource_manager/ \
	   -I ./include/sprite_render/\
	   -I ./include/stb_image/\
	   -I ./include/test/\
	   -I ./include/gameObj/\
	   -I ./include/particleGenerator/\
	   -I ./include/PostProcess/\
	   -I ./include/powerUp/\
	   -I ./include/irrKlang-1.5.0/include/\
	   -I ./include/TexRender/
$(APP):
	g++ $(File) $(SRC) $(HEAD) $(LIB)  -lglfw3 -lGL -lGLU  -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl -lXinerama -lXcursor -lGLEW -lSOIL   -o $@
	@echo "$(File) make successful"
clean:
	@rm $(APP)     
run:
	@$(APP)
buildAndRun:
	@if [ -e $(APP) ]; then \
		echo "file exit";\
		make clean; \
		make $(APP); \
		make run ;\
	else\
		echo "file not exit";\
		make $(APP); \
		make run ;\
	fi ; \
