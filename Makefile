GPP=g++
CXXFLAGS=-Wfatal-errors -Wall -std=c++11

all: scenes slideshow myscene

scenes: scene1 scene2 scene3 scene4 scene5

scene1: CXXFLAGS += -DMYSCENE -DSCENE1
scene2: CXXFLAGS += -DMYSCENE -DSCENE2
scene3: CXXFLAGS += -DMYSCENE -DSCENE3
scene4: CXXFLAGS += -DMYSCENE -DSCENE4
scene5: CXXFLAGS += -DMYSCENE -DSCENE5

myscene: main.cpp Scene.h MyScene.h
	$(GPP) $(CXXFLAGS) -o myscene main.cpp

scene1: main.cpp Scene.h Scene1.h 
	$(GPP) $(CXXFLAGS) -o scene1 main.cpp

scene2: main.cpp Scene.h Scene2.h 
	$(GPP) $(CXXFLAGS) -o scene2 main.cpp

scene3: main.cpp Scene.h Scene3.h 
	$(GPP) $(CXXFLAGS) -o scene3 main.cpp

scene4: main.cpp Scene.h Scene4.h 
	$(GPP) $(CXXFLAGS) -o scene4 main.cpp

scene5: main.cpp Scene.h Scene5.h 
	$(GPP) $(CXXFLAGS) -o scene5 main.cpp

slideshow: slideshow.cpp Scene.h MyScene.h Scene1.h Scene2.h Scene3.h Scene4.h Scene5.h
	$(GPP) $(CXXFLAGS) -o slideshow slideshow.cpp

.PHONY: clean

clean:
	@rm -rf *.o a.out scene1 scene2 scene3 scene4 scene5 slideshow myscene 2>/dev/null

