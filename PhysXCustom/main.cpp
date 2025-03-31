#include <GL/freeglut.h>
#include <time.h>
#include <thread>

#include "StopWatch.h"
#include "Game.h"
#include "InputHandler.h"

Game* game;

void cleanup() {
	delete game;
	game = nullptr;
	exit(0);
}

int main(int argc, char** argv) {
	//GLUT init
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	game = new Game("myGame", 960, 720);
	InputHandler::setup(960, 720, 960, 720);

	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutKeyboardFunc(InputHandler::onKeyDown); //GLUT will call onKeyDown whenever user presses a keyboard button
	glutKeyboardUpFunc(InputHandler::onKeyUp);
	glutMouseFunc(InputHandler::mouseEvent); //same as above but for mouse
	glutMotionFunc(InputHandler::motionMouseEvent);
	glutCloseFunc(cleanup);
	srand(time(0)); //seeding random with time, such that each game is different (unless you can play 2 games at the same exact time)

	//Game init
	//FPS limit to avoid having the cpu be in 100% utilization
	const float FPS_Limit = 60;
	const float maxFrameTime = 1000.0f / FPS_Limit; //in ms
	StopWatch timer;

	float deltaTime = maxFrameTime; //in ms

	//main loop
	while (game->isRunning()) {
		timer.start();

		game->Update(deltaTime);
		game->Render();

		deltaTime = timer.stop();

		//if game was processed quicker than 60fps, let the cpu idle until it hits the maxFrameTime(60 fps)
		if (maxFrameTime > deltaTime) {
			std::this_thread::sleep_for(std::chrono::microseconds(int(maxFrameTime - deltaTime) * 1000));
			deltaTime += maxFrameTime - deltaTime;
		}

		glutMainLoopEvent(); //if glut doesnt receive events, the window freezes, calling this prevents this
	}

	return 0;
}