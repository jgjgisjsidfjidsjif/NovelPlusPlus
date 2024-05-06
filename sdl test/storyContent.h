#include <iostream>
#include <string>


using namespace std;



void sceneOne(){
	char* muchoTexto[5] = {"Anon Y Mous.","As I walked out out in the streets of Laredo","As I walked out out in the street of Laredo one day","As I walked out, I saw a lone cowboy wrapped all in white linen", "Wrapped in white linen, as cold as the clay"};
				updateBackground (1, 0, false);
				updateTitle(muchoTexto[0], false, 60,0,120);
				updateL1(muchoTexto[1], false, 60,0,120);
				updateL2(muchoTexto[2], false, 60,0,120);
				updateL3(muchoTexto[3], false, 60,0,120);
				updateL4(muchoTexto[4], true, 60,0,120);
}
void updateScene(char* title, char* L1, char* L2, char * L3, char* L4, int bg){
	char* muchoTexto[5] = {title, L1, L2, L3, L4};
				updateBackground (bg, 0, false);
				updateTitle(muchoTexto[0], false, 60,0,120);
				updateL1(muchoTexto[1], false, 60,0,120);
				updateL2(muchoTexto[2], false, 60,0,120);
				updateL3(muchoTexto[3], false, 60,0,120);
				updateL4(muchoTexto[4], true, 60,0,120);
}



void sortPage (int page){// Yes its gonna be one big switch array.
	switch (page){
	case 0:
					updateScene("AAAAAAAAAAAAAAAAAAAAA.","As I walked out out in the streets of Laredo","As I walked out out in the street of Laredo one day","As I walked out, I saw a lone cowboy wrapped all in white linen", "Wrapped in white linen, as cold as the clay", 1);
	break;
	case 1:
		updateScene("Anon Y dsfsdasdasdasdasdsd.","As I walked out out in the streets of Laredo","As I walked out out in the street of Laredo one day","As I walked out, I saw a lone cowboy wrapped all in white linen", "Wrapped in white linen, as cold as the clay", 1);
	break;
		case 2:
		updateScene("Anon Y asdddddddddddddddddddddddddd.","As I walked out out in the streets of Laredo","As I walked out out in the street of Laredo one day","As I walked out, I saw a lone cowboy wrapped all in white linen", "Wrapped in white linen, as cold as the clay", 1);
	break;
		default:
		updateScene ("Test","Test","Test","Test","Test", 0);
	break;
	}
}

