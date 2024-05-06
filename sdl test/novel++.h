#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
//#include "storyContent.h" //This is where all of the scene methods are stored. Including storyContent.h seems to introduce some errors to compilation.
#include <iostream>
#include <string>
#include "Windows.h"

using namespace std;

//This defines the resolution of this application.
const int ScreenWidth = 640;
const int ScreenLength = 480;
const int ScreenBpp = 32;
int selectedOption = 0;
int page = 0;

char* characterBuffer[7] = {" "," "," "," "," "," "," ",}; //This is for the character buffer for inputting text and other stuff. The Max character limit will be 8 characters.
int passcode = 0;
int failureThreshold = 0;
bool unlockedPasscode = false;
int characterLocation = 0; //This is used to determine where a typed character should be placed inside the characterBuffer array.
bool usernameSelected = false; //This bool determines if the user has selected their username; 

SDL_Surface* title = NULL;
SDL_Surface* lineOne = NULL;
SDL_Surface* lineTwo = NULL;
SDL_Surface* lineThree = NULL;
SDL_Surface* lineFour = NULL;
SDL_Surface* inputChar = NULL;
SDL_Surface* optionLines = NULL;

SDL_Surface* screen = NULL;
SDL_Surface* background_1 = NULL;
SDL_Surface* background_2 = NULL;
SDL_Surface* twoOptionBox = NULL;
SDL_Surface* inputBox = NULL;
SDL_Surface* SecurityInputBox = NULL;
SDL_Surface* dialogue = NULL;

//the quit boolean is set to default values, so nothing funky can be done.
bool quit = false;

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

// This function loads files. If the files are missing, it will quit the application.
bool load_files(){
	
	//Load the assets.
	background_1 = LoadOptimizedImages("images/pizza_bg.bmp");
	background_2 = LoadOptimizedImages("images/starz_bg.bmp");
	twoOptionBox = LoadOptimizedImages("images/twooption_fg.bmp");
	inputBox = LoadOptimizedImages("images/input_fg.bmp");
	SecurityInputBox = LoadOptimizedImages("images/securityinput_fg.bmp");
	
	dialogue = LoadOptimizedImages("images/dialogue_fg.bmp");
	
	//This loads the text files.
	titleConf = TTF_OpenFont("fonts/oswald.ttf", 24); // TTF_OpenFont("fontfile.ttf", fontSize);
	subtextConf = TTF_OpenFont("fonts/oswald.ttf", 19); // TTF_OpenFont("fontfile.ttf", fontSize);
	
	//If Novel++ can't find any one of these files, this function will fail, and Novel will close
	if(background_1 == NULL){
		return false;
	}
	if(background_2 == NULL){
		return false;
	}
	
	if(twoOptionBox == NULL){
		return false;
	}
	
	if(inputBox == NULL){
		return false;
	}
	
	if(SecurityInputBox == NULL){
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
	
	//If errors are found during setting up the text library...
	if (TTF_Init () == -1){
		
		return false;
	}
	
	SDL_WM_SetCaption ("Novel++ App", NULL);
	
	
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
	lineTwo = TTF_RenderText_Solid (subtextConf, text, textColor); //Set the text
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

void helpDialogue(){ //When called, this function should activate the help dialogue.
	MessageBox(NULL, "Keybinds: F1 to activate Help Dialogue, Page Up to flip forward a page, Page Down to flip back a page. Escape to exit the application. Left and Right shift keys activate left and right dialogue options respectively, and backspace deletes any text input, while enter enters your text input.",
	"Help Dialogue", MB_ICONQUESTION | MB_OK);
}

void two_options(char* dialogue_1, char* dialogue_2, bool updateScreen, int R, int G, int B){ //When called, this should set two options.
	selectedOption = 5;
	SDL_Color textColor = {R,G,B};
	apply_surface (0,0, twoOptionBox, screen);
	optionLines = TTF_RenderText_Solid (subtextConf, dialogue_1, textColor);
	apply_surface (70,110, optionLines, screen);
	SDL_FreeSurface(optionLines);
	optionLines = TTF_RenderText_Solid (subtextConf, dialogue_2, textColor);
	apply_surface (330,110, optionLines, screen);
	if (updateScreen == true){
		SDL_Flip (screen);
	}
	SDL_FreeSurface(optionLines);
	
}

void keyboardTextInput(char* key){ //This function allows the use to take keyboard input and place it inside of CharacterBuffer, an 8 character long array for Player names and other stuff.
	SDL_Color textColor = {0,255,0};
	inputChar = TTF_RenderText_Solid (subtextConf, key, textColor);
	characterBuffer[characterLocation] = key;
				if (page == 4){
					if (characterLocation <=7){
						switch (characterLocation){	//This switch where in the screen does the characters get placed in.
						case 0:
							apply_surface (110,165, inputChar, screen);
							break;
						case 1:
							apply_surface (120,165, inputChar, screen);
							break;
						case 2:
							apply_surface (130,165, inputChar, screen);
							break;
						case 3:
							apply_surface (140,165, inputChar, screen);
							break;
						case 4:
							apply_surface (150,165, inputChar, screen);
							break;
						case 5:
							apply_surface (160,165, inputChar, screen);
							break;
						case 6:
							apply_surface (170,165, inputChar, screen);
							break;
						case 7:
							apply_surface (180,165, inputChar, screen);
							break;
							
						}
						
						SDL_Flip (screen);
						SDL_FreeSurface(inputChar);
						characterLocation = characterLocation + 1;
					}
					else{
						MessageBox(NULL, "You have inputted too many characters. Maximum characters allowed is 8 characters.",
							"Error!", MB_ICONHAND | MB_OK);
						characterBuffer[7] = " "," "," "," "," "," "," "," ";
						characterLocation = 0;
						
					}
				}
				
}

void keyboardNumberInput(int key){ //This piece of code is actually neat. When activated, it uses the characterlocation variable to place the number in the correct place.
	switch (characterLocation){ //This switch determines the place of the number. If its the 1st number, say 2, the variable is 2000. If its the 2nd number, the variable is 2000+200, = 2200, repeat ad nauseaum.
	case 0:
		passcode = key * 1000;
		characterLocation = characterLocation + 1;
		break;
	case 1:
		passcode = passcode + key * 100;
		characterLocation = characterLocation + 1;
		break;
	case 2:
		passcode = passcode + key * 10;
		characterLocation = characterLocation + 1;
		break;
	case 3:
		passcode = passcode + key;
		characterLocation = characterLocation + 1;
		break;
		
	}
	if (characterLocation == 4){
		
		if (passcode >=1914 && passcode <=1918){ //This checks if the number is between 1914 and 1918
			unlockedPasscode = true;
			MessageBox(NULL, "Unlocked.",
				"Success!", MB_ICONQUESTION| MB_OK);
		}
		else{ //If that isn't the case, failure threshold will increase by 1. If you fail too much, the app will quit.
			
			MessageBox(NULL, "Wrong code. Try again.",
				"Error!", MB_ICONHAND | MB_OK);
			passcode = 0;
			characterLocation = 0;
			failureThreshold = failureThreshold + 1;
			if (failureThreshold >=3){
				MessageBox(NULL, "You have tripped the security systems. Your story ends here.",
					"You Failed!", MB_ICONHAND | MB_OK);
				quit = true;
				
			}
			
		}
	}
	
	
	
}


void selectUsername(){//This function asks the User about the user if they want to set their username, and sets it if desired.
    string message = "This will be your username: ";
    for (int i = 0; i < 7; ++i) { //This loop will go to the characterBuffer and turn it into a string that can be placed in a dialogue box.
        if (characterBuffer[i] != NULL) { 
            message += characterBuffer[i];
        }
    }
    message += ". Do you want to confirm your choice? This will lock you out of the previous pages.";
	
    int chosenOption = MessageBox(NULL, message.c_str(), "Confirm your choices.", MB_ICONQUESTION | MB_YESNO);
	
    switch (chosenOption){
    case IDYES:
		usernameSelected = true;
		characterLocation = 0;
		characterBuffer[7] = " "," "," "," "," "," "," ";
        break;
    case IDNO:
        break;
    }
}


