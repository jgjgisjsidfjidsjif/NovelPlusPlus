#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "novel++.h" //This is where all of the magic happens
#include "storyContent.h" //This is where all of the scene methods are stored
#include <iostream>
#include <string>
#include "Windows.h"


using namespace std;
	const char* muchoTexto[] = {"Anon Y Mous.","Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incidid","As I walked out out in the streets of Laredo","As I walked out out in the street of Laredo one day","As I walked out, I saw a lone cowboy"};

// This function loads files. If the files are missing, it will quit the application.
bool load_files(){
	
	background_1 = LoadOptimizedImages("images/pizza_bg.bmp");
	background_2 = LoadOptimizedImages("images/starz_bg.bmp");
	
	dialogue = LoadOptimizedImages("images/dialogue_fg.bmp");
	
	titleConf = TTF_OpenFont("fonts/oswald.ttf", 24); // TTF_OpenFont("fontfile.ttf", fontSize);
	
	subtextConf = TTF_OpenFont("fonts/oswald.ttf", 19); // TTF_OpenFont("fontfile.ttf", fontSize);
	
	if(background_1 == NULL){
		return false;
	}
	if(background_2 == NULL){
		return false;
	}
	
	if(dialogue == NULL){
		return false;
	}
	
	if(titleConf == NULL){
		return false;
	}
	
	return true;
}

void exit(){ //This function frees everything and closes the app.
	SDL_FreeSurface(title);
	SDL_FreeSurface(lineOne);
	SDL_FreeSurface(lineTwo);
	SDL_FreeSurface(lineThree);
	SDL_FreeSurface(lineFour);
	
	SDL_FreeSurface(background_1);
	TTF_CloseFont(titleConf);
	TTF_CloseFont(subtextConf);
	TTF_Quit();
	SDL_Quit();
}

int main( int argc, char* argv[] ){
	
	bool quit = false;
	int page = 1;
	
	if (startSDL() == false){
		MessageBox(NULL, "SDL 1.2 and its associated libraries cannot be initialized. Novel++ Cannnot start further.", "Critical Error 1!", MB_ICONHAND | MB_OK);
		return 1;
	}
	
	
	load_files();
	
	
	if (load_files() == false){
				MessageBox(NULL, "Asset files cannot be found. Check if your installation is not corrupted. Novel++ Cannnot start further. Make sure you also do not run Novel++ using the Visual C++ 6 debugger, this seems to crash novel++.", "Critical Error 2!", MB_ICONHAND | MB_OK);
		return 2;
	}
	
	apply_surface (0,0, background_1, screen);
	apply_surface (0,0, dialogue, screen);
	
	
	updateL1("test", false, 0,0,0);
	updateTitle("Tutor.Ial", false, 0,0,0);	
	updateL2("Testing 12345678901234567890", false, 60,255,120);	
	updateL3("Testing 12345678901234567890", false, 60,255,120);	
	updateL4("Testing 12345678901234567890", false, 60,255,120);	
				
				
				
	if ( SDL_Flip (screen) == -1 ){
				MessageBox(NULL, "Your screen cannot be initialized. Check your Graphics drivers for issues. Novel++ Cannnot start further.", "Critical Error 3!", MB_ICONHAND | MB_OK);
		return 3;
	}


	
	
	//Main Loop when everything has loaded
	while(quit == false){
		
		if (SDL_PollEvent(&event)){
		}
		
		if (event.type == SDL_QUIT){
			quit = true;
		}
		
		Uint8 *keystates = SDL_GetKeyState(NULL);

		if (keystates[SDLK_PAGEDOWN]){
						sortPage(page - 1);
				page = page - 1; 
				MessageBox(NULL, "You went back a page.", "Page", MB_ICONQUESTION | MB_OK);
		}

		if (keystates[SDLK_PAGEUP]){
						sortPage(page + 1);
				page = page + 1;
				MessageBox(NULL, "You went forward a page.", "Page", MB_ICONQUESTION | MB_OK);
		}
		
		if (keystates[SDLK_F1]){
		helpDialogue();
		}


		if (keystates[SDLK_ESCAPE]){
			quit = true;
		}
		
		
	}
				
	exit();
				
	return 0;
}