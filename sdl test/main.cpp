#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "novel++.h" //This is where all of the magic happens
#include "storyContent.h" //This is where all of the scene methods are stored
#include <iostream>
#include <string>
#include "Windows.h"

using namespace std;

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

int main( int argc, char* argv[] ){ //This is where all of the code runs.
	
	//These variables are set to default values, so nothing funky can be done.
	bool quit = false;
	int page = 1;
	
	if (startSDL() == false){ //If the SDL dlls and other various libraries can't be found, this will close the app and notify the user.
		MessageBox(NULL, "SDL 1.2 and its associated libraries cannot be initialized. Novel++ Cannnot start further.", "Critical Error 1!", MB_ICONHAND | MB_OK);
		return 1;
	}
	
	
	load_files();
	
	
	if (load_files() == false){ //If assets cannot be found, this will close the app and notify the user. This does get set when running the app from the debugger, however.
				MessageBox(NULL, "Asset files cannot be found. Check if your installation is not corrupted. Novel++ Cannnot start further. Make sure you also do not run Novel++ using the Visual C++ 6 debugger, this seems to crash novel++.", "Critical Error 2!", MB_ICONHAND | MB_OK);
		return 2;
	}

	//These set the default, beginning background.
	apply_surface (0,0, background_1, screen);
	apply_surface (0,0, dialogue, screen);
	updateL1("Start by using Page Up", false, 0,0,0);
	updateTitle("Novel++ Demo App", false, 0,0,0);	
	updateL2("Click F1 to activate help dialogue", false, 60,255,120);	


				
				
	//If SDL can't update the screen, notify the user and close the application to prevent further issues.
	if ( SDL_Flip (screen) == -1 ){
				MessageBox(NULL, "Your screen cannot be initialized. Check your Graphics drivers for issues. Novel++ Cannnot start further.", "Critical Error 3!", MB_ICONHAND | MB_OK);
		return 3;
	}


	
	
	//Main Loop when everything has loaded
	while(quit == false){
		
		if (SDL_PollEvent(&event)){ //Using events seems to fix the bug of skipping pages, because it seemingly checks if a key is pressed once.

			if (event.type == SDL_KEYDOWN){ //This forces SDL to register key down presses only, since without it, one key press would flip two pages.
			switch (event.key.keysym.sym){
			case SDLK_PAGEDOWN: 
				page = page - 1; 
				sortPage(page);

				break;
			case SDLK_PAGEUP:
				page = page + 1;
				sortPage(page);
				break;
			
			case SDLK_LSHIFT: // This is for option 1
				if(page == 3){
				selectedOption = 1;
				page = page + 1;
				sortPage(page);

				}
				
				break;
			
			case SDLK_RSHIFT: // This is for option 2
				if(page == 3){
				selectedOption = 2;
				page = page + 1;
				sortPage(page);
				}
				
				break;
			}

		}
		}
		if (event.type == SDL_QUIT){ //When the user X's out of the app, close the application normally.
			quit = true;
		}
		
		Uint8 *keystates = SDL_GetKeyState(NULL); //Keystates shine when you want the user to hold something down. I've also used keystates with the help thing, since its not used often
		
		if (keystates[SDLK_F1]){
		helpDialogue();
		}


		if (keystates[SDLK_ESCAPE]){
			quit = true;
		}
		
		
	}
				
	exit(); //Activate Exit Functions.
				
	return 0;
}