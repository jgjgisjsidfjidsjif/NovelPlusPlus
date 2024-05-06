#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
//#include "storyContent.h" //This is where all of the scene methods are stored
#include <iostream>
#include <string>


using namespace std;

//This defines the resolution of this application.
const int ScreenWidth = 640;
const int ScreenLength = 480;
const int ScreenBpp = 32;


SDL_Surface* title = NULL;
SDL_Surface* lineOne = NULL;
SDL_Surface* lineTwo = NULL;
SDL_Surface* lineThree = NULL;
SDL_Surface* lineFour = NULL;

SDL_Surface* screen = NULL;
SDL_Surface* background_1 = NULL;
SDL_Surface* background_2 = NULL;
SDL_Surface* dialogue = NULL;

//Event structure that will be used
SDL_Event event;

//The font that will be used
TTF_Font *titleConf = NULL;
TTF_Font *subtextConf = NULL;

//This function loads an unoptimized image and turns it into an optimized image
SDL_Surface *LoadOptimizedImages(string filename){
	
	//Temporary storage for the unoptamized image
	SDL_Surface* UnoptimizedImage = NULL;
	
	//Optimized image from the temporarily stored image
	SDL_Surface* OptimizedImage = NULL;
	
	//Load the image
	UnoptimizedImage = IMG_Load(filename.c_str());
	
	if (UnoptimizedImage != NULL){
		
		//Create the optimized image
		OptimizedImage = SDL_DisplayFormat(UnoptimizedImage);
		
		//Delete the unneeded original unoptimized image from memory
		SDL_FreeSurface(UnoptimizedImage);
		
		//If the image was optimized just fine
		if (OptimizedImage != NULL){
            //Map the color key
            int colorkey = SDL_MapRGB( OptimizedImage->format, 0, 0xFF, 0xFF );
			
            //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
            SDL_SetColorKey( OptimizedImage, SDL_SRCCOLORKEY, colorkey );
		}
		
		
	}	
	
	
	//Return the optimized image
	return OptimizedImage;
}

//This function applies and blits a texture.
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination){
	//Make a temporary rectange to hold the offsets
	SDL_Rect offset;
	//Give le offsets to rectange
	offset.x = x;
	offset.y = y;
	
	//Blit the surface
	SDL_BlitSurface (source, NULL, destination, &offset );
	
	
}

//This function starts up SDL functions, if anything unusual is detected, it will return false
bool startSDL(){
	
	//Start SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1 ){
		return false;
	}
	
	//Set up the screen
	screen = SDL_SetVideoMode( ScreenWidth, ScreenLength, ScreenBpp, SDL_SWSURFACE);
	
	//If errors are found during setting up the screen
	if (screen == NULL ){
		return false;
	}
	
	if (TTF_Init () == -1){
		
		return false;
	}
	
	SDL_WM_SetCaption ("Hello World", NULL);
	
	return true;
	
	
	
}

void updateTitle (char* text, bool updateScreen, int R, int G, int B){ //Update the title. The bool allows one to update the screen and/or text color if desired.
	SDL_Color textColor = {R,G,B};
		    SDL_Rect clearRect;
    clearRect.x = 230;
    clearRect.y = 308;
    clearRect.w = 404; 
    clearRect.h = 30; 

	SDL_FillRect(screen, &clearRect, SDL_MapRGB(screen->format, 128, 128, 128)); // Fill with grey, adjust as needed

	title = TTF_RenderText_Solid (titleConf, text, textColor);
	apply_surface (230,308, title, screen);
	if (updateScreen == true){
		SDL_Flip (screen);
	}
	SDL_FreeSurface(title);
	title = NULL;
	
}

void updateL1 (char* text, bool updateScreen, int R, int G, int B){ //Update Line one of the subtext. The bool allows one to update the screen and/or change the text colour if desired.
	SDL_Color textColor = {R,G,B};
	    SDL_Rect clearRect;
    clearRect.x = 20;
    clearRect.y = 355;
    clearRect.w = 614; 
    clearRect.h = 28; 

	SDL_FillRect(screen, &clearRect, SDL_MapRGB(screen->format, 192, 192, 192)); // Fill with grey, adjust as needed
	lineOne = TTF_RenderText_Solid (subtextConf, text, textColor);
	apply_surface (20,350, lineOne, screen);
	if (updateScreen == true){
		SDL_Flip (screen);
	}
	SDL_FreeSurface(lineOne);
	lineOne = NULL;
}


void updateL2 (char* text, bool updateScreen, int R, int G, int B){ //Update Line two of the subtext. The bool allows one to update the screen and/or change the text colour if desired.
	SDL_Color textColor = {R,G,B};
	    // Clear the area occupied by the previous text
    SDL_Rect clearRect;
    clearRect.x = 20;
    clearRect.y = 375;
    clearRect.w = 614; 
    clearRect.h = 28; 

	SDL_FillRect(screen, &clearRect, SDL_MapRGB(screen->format, 192, 192, 192)); // Fill with grey, adjust as needed
	lineTwo = TTF_RenderText_Solid (subtextConf, text, textColor);
	apply_surface (20,375, lineTwo, screen);
	if (updateScreen == true){
		SDL_Flip (screen);
	}
	SDL_FreeSurface(lineTwo);
	lineTwo = NULL;
}

void updateL3 (char* text, bool updateScreen, int R, int G, int B){ //Update Line three of the subtext. The bool allows one to update the screen and/or change the text colour if desired.
	SDL_Color textColor = {R,G,B};
	
    // Clear the area occupied by the previous text
    SDL_Rect clearRect;
    clearRect.x = 20;
    clearRect.y = 400;
    clearRect.w = 614; 
    clearRect.h = 28; 

	SDL_FillRect(screen, &clearRect, SDL_MapRGB(screen->format, 192, 192, 192)); // Fill with grey, adjust as needed
	lineThree = TTF_RenderText_Solid (subtextConf, text, textColor);
	apply_surface (20,400, lineThree, screen);
	if (updateScreen == true){
		SDL_Flip (screen);
	}
	SDL_FreeSurface(lineThree);
	lineThree = NULL;
}

void updateL4 (char* text, bool updateScreen, int R, int G, int B){ //Update Line four of the subtext. The bool allows one to update the screen and/or change the text colour if desired.
	SDL_Color textColor = {R,G,B};
	    // Clear the area occupied by the previous text
    SDL_Rect clearRect;
    clearRect.x = 20;
    clearRect.y = 425;
    clearRect.w = 614; 
    clearRect.h = 28; 

	SDL_FillRect(screen, &clearRect, SDL_MapRGB(screen->format, 192, 192, 192)); // Fill with grey, adjust as needed


	lineFour = TTF_RenderText_Solid (subtextConf, text, textColor);
	apply_surface (20,425, lineFour, screen);
	if (updateScreen == true){
		SDL_Flip (screen);
	}
	SDL_FreeSurface(lineFour);
	lineFour = NULL;
}

void updateBackground (int background, int dialogueBox, bool updateScreen){ //Clears and updates the background and Dialogue box.
	SDL_Rect clearRect;
	clearRect.x = 0;
	clearRect.y = 0;
    clearRect.w = 0; 
    clearRect.h = 0; 
	SDL_FillRect(screen, &clearRect, SDL_MapRGB(screen->format, 0, 0, 0)); // Fill with grey, adjust as needed
	switch (background){
	case 0:
			apply_surface (0,0, background_1, screen);
	break;
		case 1:
			apply_surface (0,0, background_2, screen);
	break;
	}
	switch (dialogueBox){
	case 0:
			apply_surface (0,0, dialogue, screen);
	break;
	}
		if (updateScreen == true){
		SDL_Flip (screen);
	}

}

void initDialogue(){
	int chosenOption = MessageBox(NULL, "Do you want to load a save file? Press Yes to load a file, otherwise press no to create a new save file.", "Save File Detected", MB_ICONQUESTION | MB_YESNO);
	
	switch (chosenOption){
	case IDYES:
		MessageBox(NULL, "Save Loading is a WIP. This Message is here for debugging purposes", "Save File Detected", MB_ICONHAND | MB_OK);
		break;
	case IDNO:
		MessageBox(NULL, "Save Loading is a WIP. This Message is here for debugging purposes", "Save File Detected", MB_ICONHAND | MB_OK);
		break;
	}
}