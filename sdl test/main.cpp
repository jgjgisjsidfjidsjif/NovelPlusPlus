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
	SDL_FreeSurface(background_2);
	SDL_FreeSurface(inputChar);
	SDL_FreeSurface(twoOptionBox);
		SDL_FreeSurface(inputBox);
				SDL_FreeSurface(SecurityInputBox);
				SDL_FreeSurface(dialogue);
	SDL_FreeSurface(background_1);
	TTF_CloseFont(titleConf);
	TTF_CloseFont(subtextConf);
	TTF_Quit();
	SDL_Quit();
}

int main( int argc, char* argv[] ){ //This is where all of the code runs.
	

	
	
	if (startSDL() == false){ //If the SDL dlls and other various libraries can't be found, this will close the app and notify the user.
		MessageBox(NULL, "SDL 1.2 and its associated libraries cannot be initialized. Novel++ Cannnot start further.",
			"Critical Error 1!", MB_ICONHAND | MB_OK);
		return 1;
	}
	
	
	load_files();
	
	
	if (load_files() == false){ //If assets cannot be found, this will close the app and notify the user. This does get set when running the app from the debugger, however.
		MessageBox(NULL, "Asset files cannot be found. Check if your installation is not corrupted. Novel++ Cannnot start further. Make sure you also do not run Novel++ using the Visual C++ 6 debugger, this seems to crash novel++.",
			"Critical Error 2!", MB_ICONHAND | MB_OK);
		return 2;
	}
	
	//These set the default, beginning background.
	apply_surface (0,0, inputBox, screen);
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
		
		if (page == 4 && usernameSelected == true){
			page = page + 1;
			sortPage(page);
		}
		
		if (unlockedPasscode == true){
			page = 7;
			sortPage(page);	
		}

		if (SDL_PollEvent(&event)){ //Using events seems to fix the bug of skipping pages, because it seemingly checks if a key is pressed once.
			
			if (event.type == SDL_KEYDOWN){ //This forces SDL to register key down presses only, since without it, one key press would flip two pages.
				switch (event.key.keysym.sym){
				case SDLK_PAGEDOWN:
				case SDLK_LEFT:
					if (page - 1 == 6 && unlockedPasscode == true){
					page = page - 2;
					}
					else{
					page = page - 1;
					}
					 
					sortPage(page);
					break;
				case SDLK_PAGEUP: 
				case SDLK_RIGHT:
					if (page + 1 == 6 && unlockedPasscode == true){
					page = page + 2;
					}
					else{
					page = page + 1;
					}
					
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
				
				if(page == 4){ //To prevent anything strange from happening in the first place, the keyboard is only activated at page 4.
					if (characterLocation == 0){ // This if statement is to fix a bug where any previous text entered disappears from the user.
						apply_surface (0,0, inputBox, screen);
						SDL_Flip (screen);
					}
					
					switch (event.key.keysym.sym){ //This looks painful, but there is no other way that I can implement keyboard text input in a short time period.
					case SDLK_a:				   //Basically, this is just under 30ish cases worth of keys, assigned to imput text.
						keyboardTextInput("A");
						break;
					case SDLK_b:
						keyboardTextInput("B");
						break;
					case SDLK_c:
						keyboardTextInput("C");
						break;
					case SDLK_d:
						keyboardTextInput("D");
						break;
					case SDLK_e:
						keyboardTextInput("E");
						break;
					case SDLK_f:
						keyboardTextInput("F");
						break;
					case SDLK_g:
						keyboardTextInput("G");
						break;
					case SDLK_h:
						keyboardTextInput("H");
						break;
					case SDLK_i:
						keyboardTextInput("I");
						break;
					case SDLK_j:
						keyboardTextInput("J");
						break;
					case SDLK_k:
						keyboardTextInput("K");
						break;
					case SDLK_l:
						keyboardTextInput("L");
						break;
					case SDLK_m:
						keyboardTextInput("M");
						break;
					case SDLK_n:
						keyboardTextInput("N");
						break;
					case SDLK_o:
						keyboardTextInput("O");
						break;
					case SDLK_p:
						keyboardTextInput("P");
						break;
					case SDLK_q:
						keyboardTextInput("Q");
						break;
					case SDLK_r:
						keyboardTextInput("R");
						break;
					case SDLK_s:
						keyboardTextInput("S");
						break;
					case SDLK_t:
						keyboardTextInput("T");
						break;
					case SDLK_u:
						keyboardTextInput("U");
						break;
					case SDLK_v:
						keyboardTextInput("V");
						break;
					case SDLK_w:
						keyboardTextInput("W");
						break;
					case SDLK_x:
						keyboardTextInput("X");
						break;
					case SDLK_y:
						keyboardTextInput("Y");
						break;
					case SDLK_z:
						keyboardTextInput("Z");
						break;
					case SDLK_RETURN: //When the user presses enter, it will call the selectUsername() function.
						selectUsername();
						break;
					case SDLK_BACKSPACE: //When the user presses backspace, the entered data will be deleted, and the screen refreshes to clear any residual text.
						characterBuffer[7] = " "," "," "," "," "," "," "," ";
						characterLocation = 0;
						apply_surface (0,0, inputBox, screen);
						SDL_Flip (screen);
						break;
					}
				}
				
				if (page == 6){
					if (characterLocation == 0){ // This if statement is to fix a bug where any previous text entered disappears from the user.
						apply_surface (0,0, inputBox, screen);
						SDL_Flip (screen);
					}
					switch (event.key.keysym.sym){ //This looks painful, but there is no other way that I can implement keyboard text input in a short time period.
					case SDLK_1:				   //There is only 11 things needed, since only numbers are used.
						keyboardNumberInput(1);
						break;
					case SDLK_2:
						keyboardNumberInput(2);
						break;
					case SDLK_3:
						keyboardNumberInput(3);
						break;
					case SDLK_4:
						keyboardNumberInput(4);
						break;
					case SDLK_5:
						keyboardNumberInput(5);
						break;
					case SDLK_6:
						keyboardNumberInput(6);
						break;
					case SDLK_7:
						keyboardNumberInput(7);
						break;
					case SDLK_8:
						keyboardNumberInput(8);
						break;
					case SDLK_9:
						keyboardNumberInput(9);
						break;
					case SDLK_0:
						keyboardNumberInput(0);
						break;

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
		}
	}
	exit(); //Activate Exit Functions.
	return 0;
	
}
