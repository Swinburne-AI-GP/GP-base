#include <random>
#include <iostream>
#include <fstream>
#include <chrono>
#include "sdl/SDL.h"

// RENDER - set to false to disable rendering
#define RENDER true

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

const int BOX_WIDTH = 50;
const int BOX_HEIGHT = 50;
const int BOX_SPEED = 10;

const int TEST_TIME = 10 * 1000; // 10 seconds

enum BoxState { CONTACT_NO, CONTACT_YES };

struct CrashBox {
	int x, y; // pos
	int dx, dy; // vel
	int w, h; // size
	BoxState state;
};

// Global variables.
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int BOX_COUNT;
CrashBox* boxes;

void (*crash_test_all_ptr)(); // function pointer!

//-----------------------------------------------------------------------------

void init_boxes() {
	// seed value - Set explicitly if you want repeatable results!!
	// srand((unsigned)time(0));
	srand(9999);
	// set each box to a random position, size, and velocity
	for (int i = 0; i < BOX_COUNT; i++) {
		// position
		boxes[i].x = rand() % SCREEN_WIDTH;
		boxes[i].y = rand() % SCREEN_HEIGHT;
		// size
		boxes[i].w = (rand() % BOX_WIDTH) + 1;
		boxes[i].h = (rand() % BOX_HEIGHT) + 1;
		// velocity (both positive and negative "delta" values)
		boxes[i].dx = (rand() % (BOX_SPEED * 2)) - (BOX_SPEED / 2);
		boxes[i].dy = (rand() % (BOX_SPEED * 2)) - (BOX_SPEED / 2);
	}
}

void render_box(CrashBox box, uint8_t r, uint8_t g, uint8_t b) { //TODO: try &box
	SDL_SetRenderDrawColor(renderer, r,g,b,255);
	SDL_Rect rect = { box.x, box.y, box.w, box.h}; //TODO: try cached rect's
	SDL_RenderFillRect(renderer, &rect);
}

void render_boxes() {
	for (int i = 0; i < BOX_COUNT; i++) {
		if (boxes[i].state == CONTACT_NO) {
			render_box(boxes[i], 000, 255, 000); // green
		}
		else {
			render_box(boxes[i], 255, 000, 000); // red
		}
	}
}

//-----------------------------------------------------------------------------

bool crash_test_A(int i, int j) { // via index
	//The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

	CrashBox A, B;
	A = boxes[i];
	B = boxes[j];

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if (bottomA <= topB) return false;
    if (topA >= bottomB) return false;
    if (rightA <= leftB) return false;
    if (leftA >= rightB) return false;

    //If none of the sides from A are outside B
    return true;
}

bool crash_test_B(CrashBox A, CrashBox B) { // struct (copy)
	//The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if (bottomA <= topB) return false;
    if (topA >= bottomB) return false;
    if (rightA <= leftB) return false;
    if (leftA >= rightB) return false;
    //If none of the sides from A are outside B
    return true;
}

bool crash_test_C(CrashBox &A, CrashBox &B) { // via struct (ref!)
	//The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if (bottomA <= topB) return false;
    if (topA >= bottomB) return false;
    if (rightA <= leftB) return false;
    if (leftA >= rightB) return false;

    //If none of the sides from A are outside B
    return true;
}

bool crash_test_D(CrashBox &A, CrashBox &B) {
    if ((A.y + A.h) <= B.y) return false;
    if (A.y >= (B.y + B.h)) return false;
	if ((A.x + A.w) <= B.x) return false;
	if (A.x >= (B.x + B.w)) return false;
    return true;
}

//-----------------------------------------------------------------------------

void crash_test_all_A1() {
	// check i against j
	for (int i = 0; i < BOX_COUNT; i++) {
		for (int j = 0; j < BOX_COUNT; j++) {
			if (crash_test_A(i,j)) {
				if (i != j) {
					boxes[i].state = CONTACT_YES;
					boxes[j].state = CONTACT_YES;
				}
			}
		}
	}
}

void crash_test_all_A2() {
	// check i against j
	for (int i = 0; i < BOX_COUNT; i++) {
		for (int j = i+1; j < BOX_COUNT; j++) {
			if (crash_test_A(i,j)) {
				boxes[i].state = CONTACT_YES;
				boxes[j].state = CONTACT_YES;
			}
		}
	}
}

void crash_test_all_B() {
	// check i against j
	for (int i = 0; i < BOX_COUNT; i++) {
		for (int j = i+1; j < BOX_COUNT; j++) {
			if (crash_test_B(boxes[i],boxes[j])) {
				boxes[i].state = CONTACT_YES;
				boxes[j].state = CONTACT_YES;
			}
		}
	}
}

void crash_test_all_C() {
	// check i against j
	for (int i = 0; i < BOX_COUNT; i++) {
		for (int j = i+1; j < BOX_COUNT; j++) {
			if (crash_test_C(boxes[i],boxes[j])) {
				boxes[i].state = CONTACT_YES;
				boxes[j].state = CONTACT_YES;
			}
		}
	}
}


void crash_test_all_D() {
	// check i against j
	for (int i = 0; i < BOX_COUNT; i++) {
		for (int j = i+1; j < BOX_COUNT; j++) {
			if (crash_test_D(boxes[i],boxes[j])) {
				boxes[i].state = CONTACT_YES;
				boxes[j].state = CONTACT_YES;
			}
		}
	}
}

//-----------------------------------------------------------------------------

void update_boxes() {
	// First move all boxes
	for (int i = 0; i < BOX_COUNT; i++) {
		// update position using current velocity
		boxes[i].x = boxes[i].x + boxes[i].dx;
		boxes[i].y = boxes[i].y + boxes[i].dy;
		// check for wrap-around condition
		if (boxes[i].x >= SCREEN_WIDTH) boxes[i].x -= SCREEN_WIDTH;
		if (boxes[i].x < 0) boxes[i].x += SCREEN_WIDTH;
		if (boxes[i].y >= SCREEN_HEIGHT) boxes[i].y -= SCREEN_HEIGHT;
		if (boxes[i].y < 0) boxes[i].y += SCREEN_HEIGHT;
		//TODO: try else if logic
	}

	// 1. mark all boxes as not collided //TODO: put this in the move loop?
	for (int i = 0; i < BOX_COUNT; i++)
		boxes[i].state = CONTACT_NO;
	// 2. call whatever function has been set to test all i against j boxes
	crash_test_all_ptr();
}

//-----------------------------------------------------------------------------

int run_test(const char* title, void (*function_ptr)()) {
	// SETUP

#if RENDER
	SDL_Event event;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL){
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}
	//Create vsynced renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL){
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return 1;
	}
#endif // RENDER

	// redirect console output to file
	std::ofstream outFile("results.txt", std::ios::app);
	std::ofstream errFile("results.txt", std::ios::app);

	if (outFile.is_open() && errFile.is_open()) {
		std::cout.rdbuf(outFile.rdbuf());
		std::cerr.rdbuf(errFile.rdbuf());
	}else {
		std::cerr << "Error opening results.txt for logging." << std::endl;
		return 1;
	}

	// some pretty test output to the console
	std::cout << "-- New Test: \t" <<  title;
	crash_test_all_ptr = function_ptr;
	// sanity check that the crash test function pointer has been set
	if (crash_test_all_ptr == NULL) {
		printf("EH? Set the crash_test_all_ptr first!\n");
		return 1;
	}

	// initialise each crashbox
	init_boxes();

	// initialise test count/time values
	Uint32 loop_count = 0;
	auto start = std::chrono::high_resolution_clock::now();
	auto target = std::chrono::milliseconds(TEST_TIME);

	// CLASSIC GAME LOOP
	bool running = true;
	while (running)	{
		// UPDATE
#if RENDER
		// 1. check for quit event
        while( SDL_PollEvent( &event ) ) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
        }
#endif

		// 2. count...
		loop_count++;
		// 3. check for test time finished
		// Note: the way chrono time points work, we subtract them to get a duration,
		// then see if the duration is greater than the target.
		if (std::chrono::high_resolution_clock::now() - start >= target) {
			running = false;
		}
		// 4. move all the crash boxes and check for collisions
		update_boxes();

		
#if RENDER
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		// 2. render all boxes
		render_boxes();
		// 3. fill the screen to show it
		SDL_RenderPresent(renderer);
		// SDL_Delay(50); // uncomment to see at slow speed.
#endif
	}
	// note the end time
	auto end = std::chrono::high_resolution_clock::now();

	// CLEAN UP TIME (and close the SDL window)
	SDL_Quit();

	// SHOW STATS
	std::cout << "Loops: \t" << loop_count << std::endl;
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "Time (ms): \t" << duration << std::endl;
	std::cout << "Loops/Second: \t" << (float(loop_count) / duration * 1000.0) << std::endl;
	std::cout << "Num boxes: \t" <<  BOX_COUNT << std::endl;

	return 0;
}

int main(int argc, char* args[]) {
	for (BOX_COUNT = 2; BOX_COUNT <= 50; ++BOX_COUNT) {
		boxes = new CrashBox[BOX_COUNT];
		for (int i = 0; i < 5; ++i) {
			run_test("Test A1", crash_test_all_A1); //TODO: not paying attention to return values. :(
			run_test("Test A2", crash_test_all_A2);
			run_test("Test B", crash_test_all_B);
			run_test("Test C", crash_test_all_C);
			run_test("Test D", crash_test_all_D);
		}
		delete[] boxes;
	}

	return 0;
}