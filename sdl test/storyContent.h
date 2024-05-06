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
		updateScene("Page 0.",
			"As I walked out out in the streets of Laredo",
			"As I walked out out in the street of Laredo one day",
			"As I walked out, I saw a lone cowboy wrapped all in white linen", 
			"Wrapped in white linen, as cold as the clay", 1);
	break;
	case 1:
		updateScene("Page 1.",
			"As I walked out out in the streets of Laredo",
			"As I walked out out in the street of Laredo one day",

			"As I walked out, I saw a lone cowboy wrapped all in white linen", 
			"Wrapped in white linen, as cold as the clay", 1);
	break;
		case 2:
			selectedOption = 8; //This is to force the shift keys to be only used for selecting options.
		updateScene("Page 2.",
			"As I walked out out in the streets of Laredo",
			"As I walked out out in the street of Laredo one day",
			"As I walked out, I saw a lone cowboy wrapped all in white linen", 
			"Wrapped in white linen, as cold as the clay", 1);
	break;
		case 3:
			
			updateScene("Page 3.",
			"As I walked out out in the streets of Laredo",
			"As I walked out out in the street of Laredo one day",
			"As I walked out, I saw a lone cowboy wrapped all in white linen",
			"Wrapped in white linen, as cold as the clay", 0);
			two_options("Honk", "Bonk", true, 60,255,120);
			
	break;
			case 4:

				if(selectedOption == 5 || selectedOption == 8 ){
				page = 3;
				sortPage(page);
				}
				switch (selectedOption){{
				case 1:
					updateScene("Page 4.",
					"You selected Option 1",
					"As I walked out out in the street of Laredo one day",
					"As I walked out, I saw a lone cowboy wrapped all in white linen",
					"Wrapped in white linen, as cold as the clay", 0);
					break;
				}
				

				case 2:{
			updateScene("Page 4.",
			"You selected Option 2",
			"As I walked out out in the street of Laredo one day",
			"As I walked out, I saw a lone cowboy wrapped all in white linen",
			"Wrapped in white linen, as cold as the clay", 0);
			break;
				}
			}
	break;
	}
}

