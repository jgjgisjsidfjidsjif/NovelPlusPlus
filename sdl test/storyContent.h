#include <iostream>
#include <string>


using namespace std;




void updateScene(char* title, char* L1, char* L2, char * L3, char* L4, int bg){ //This big function updates the screen's text. First 5 parameters are for title, l1,l2,l3, and l4 respectively. BG allows the user to select the background, and option allows the user to set dialogue boxes.
	char* screenText[5] = {title, L1, L2, L3, L4};
				updateBackground (bg, 0, false);
				updateTitle(screenText[0], false, 60,0,120);
				updateL1(screenText[1], false, 60,0,120);
				updateL2(screenText[2], false, 60,0,120);
				updateL3(screenText[3], false, 60,0,120);
				updateL4(screenText[4], true, 60,0,120);
				
}



void sortPage (int page){// Yes its gonna be one big switch array.
	switch (page){
	case 0:
		page = 1;
		break;
	case 1:
		updateScene("Page 1.",
			"For millenia, war never changes",
			"From the first rocks millions of eons ago thrown by the first humans",
			"To the great war that laid down troughs and troughs of men", 
			"War never changes", 1);
		break;
	case 2:
		selectedOption = 8; //This is to force the shift keys to be only used for selecting options.
		updateScene("Page 2.",
			"This way of life was inevitable",
			"Until the invention of the Garden of Eden",
			"This invention, while gave peace to mankind", 
			"gave trouble to other civilizations living out there.", 1);
		break;
	case 3:
		
		updateScene("Page 3.",
			"Today, the Eden defence force is bolstering numbers",
			"Which gives me a great source of income, and adventure",
			"Something of which couldn't be found in the VR pods of Eden.",
			"Oh right, how do I open the bunkers?", 0);
		two_options("Open the door", "Check the Terminal", true, 60,255,120);
		
		break;
	case 4:
		
		if(selectedOption == 5 || selectedOption == 8 ){
			page = 3;
			sortPage(page);
		}
		
		if(usernameSelected == true ){
			page = 5;
			sortPage(page);
		}
		
		switch (selectedOption){
		case 1:
			
			updateScene("Page 4.",
				"You selected Option 1",
				"As I saw the handle of the door, I gave it a tug.",
				"...",
				"I think the Terminal is the only way to open that thing.", 0);
			break;
			
			
			
		case 2:
			
			updateScene("Page 4.",
				"You selected Option 2",
				"The terminal lights up with a slight hum",
				"Perfect!",
				"Time to start my newfangled job!", 0);
			break;
		}
		
		break;
		case 5:
			updateScene("Page 5.",
				"Welcome to N.O.V.E.L",
				".",
				"..", 
				"A security question pops up, I better answer it before anything happens to me.", 1);
			break;
		case 6:
			updateScene("Page 6.",
				".",
				"..",
				"...", 
				"Type in a year where the great war was occuring? Drats! I think it was around Nineteen... ", 1);
			break;
		case 7:
			if (unlockedPasscode == false){
				page = 6;
				sortPage(page);	
			}
			else {
				updateScene("Page 7.",
					"Finally, i'm in.",
					"It's time to start my work",
					"", 
					"... To be continued...", 1);
				
			}
			break;
		case 8:
		MessageBox(NULL, "This demo was produced with the Novel++ Engine. Download and edit it to create your own Visual Novel",
			"Thanks for trying us out!.", MB_ICONQUESTION | MB_OK);
		quit = true;
			break;
	}
	
}