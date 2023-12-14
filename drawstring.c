#include <stdio.h>
#include <conio.h>
#include <tgi.h>


// 8x8 char font https://github.com/dhepper/font8x8/blob/master/font8x8_basic.h
//horizontally transposed binary bits to work on 6502
char alphabet[19][8] = {
{ 0x30, 0x78, 0xCC, 0xCC, 0xFC, 0xCC, 0xCC, 0x00},
{ 0xFC, 0x66, 0x66, 0x7C, 0x66, 0x66, 0xFC, 0x00},
{ 0x3C, 0x66, 0xC0, 0xC0, 0xC0, 0x66, 0x3C, 0x00},
{ 0xF8, 0x6C, 0x66, 0x66, 0x66, 0x6C, 0xF8, 0x00},
{ 0xFE, 0x62, 0x68, 0x78, 0x68, 0x62, 0xFE, 0x00},
{ 0xFE, 0x62, 0x68, 0x78, 0x68, 0x60, 0xF0, 0x00},
{ 0x3C, 0x66, 0xC0, 0xC0, 0xCE, 0x66, 0x3E, 0x00},
{ 0xCC, 0xCC, 0xCC, 0xFC, 0xCC, 0xCC, 0xCC, 0x00},
{ 0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00},
{ 0x1E, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78, 0x00},
{ 0xE6, 0x66, 0x6C, 0x78, 0x6C, 0x66, 0xE6, 0x00},
{ 0xF0, 0x60, 0x60, 0x60, 0x62, 0x66, 0xFE, 0x00},
{ 0xC6, 0xEE, 0xFE, 0xFE, 0xD6, 0xC6, 0xC6, 0x00},
{ 0xC6, 0xE6, 0xF6, 0xDE, 0xCE, 0xC6, 0xC6, 0x00},
{ 0x38, 0x6C, 0xC6, 0xC6, 0xC6, 0x6C, 0x38, 0x00},
{ 0xFC, 0x66, 0x66, 0x7C, 0x60, 0x60, 0xF0, 0x00},
{ 0x78, 0xCC, 0xCC, 0xCC, 0xDC, 0x78, 0x1C, 0x00},
{ 0xFC, 0x66, 0x66, 0x7C, 0x6C, 0x66, 0xE6, 0x00},
};




int findcharindex(char character) {
    // only supports uppercase A-Z and digits 0-9
    if (character >= 'A' && character <= 'Z') {
        return character - 'A';
    } else if (character >= '0' && character <= '9') {
        return character - '0' + 26; // Numbers start position in array
    } else {
        return -1; // Not found in the array
    }
}

void drawchar(const unsigned char alphabet[][8], char character, unsigned char startX, unsigned char startY, unsigned char scalefactor) {
    int index = findcharindex(character);
    if (index != -1) { // draw the character at the specified index
        const unsigned char* nextchar = alphabet[index];
        int x, y;
        unsigned char scaledX, scaledY, scaledX2, scaledY2;

        static const unsigned char Palette[2] = { TGI_COLOR_WHITE, TGI_COLOR_BLACK };
        tgi_setpalette(Palette);

        for (y = 0; y < 8; y++) {   // iterate over 8 Y-axis pixels
            for (x = 0; x < 8; x++) { // for each Y column, 8 row pixels
                if ((*nextchar) & (1 << (7 - x))) {
                    scaledX = startX + (x * scalefactor);
                    scaledY = startY + (y * scalefactor); 
                    scaledX2 = scaledX + scalefactor - 1; // scale for X row
                    scaledY2 = scaledY + scalefactor - 1; // scale for Y row

                    // draw rectangle using tgi_bar
                    tgi_bar(scaledX, scaledY, scaledX2, scaledY2);
                }
            }
            nextchar++; // Move to the next row in the grid
        }
    } else {
        printf("character '%c' not found\n", character);
    }
}


void drawstring(const unsigned char alphabet[][8], const char* str, unsigned char startX, unsigned char startY, unsigned char scalefactor) {
    while (*str != '\0') {
        drawchar(alphabet, *str, startX, startY, scalefactor);
        startX += 8 * scalefactor; // each character takes 8 pixels width
        str++;
    }
}


void someDelay() {
    int delayCount = 30000; 
    while (delayCount > 0) {
        asm("nop");
        delayCount--;
    }
}


int main() {
    int i;
    int kbhit_check;
    const char* mystring = "ABCDEFGHIJKLMNOP"; 

    // Install TGI
    tgi_install(tgi_static_stddrv); 
    tgi_init(); // init tgi
    tgi_clear(); // Clear the screen

    // Check if tgi_init() failed
    if (tgi_geterror() != TGI_ERR_OK) {
        printf("Error initializing graphics.");
        return 1;
    }
  
    do {  // DEMO text wall
       for (i = 0; i < 180; i+=40){
   	drawstring(alphabet, mystring, 2, i, 2); // character array, string, startX, startY, scalefactor
   	drawstring(alphabet, mystring, 2, i+20, 1);
	}
    someDelay();
  	
	//DEMO large
    tgi_clear();
	drawstring(alphabet, "A", 2, 1, 14);
	drawstring(alphabet, "B", 120, 60, 14); 
    someDelay();
  
	//DEMO jumbo
  	tgi_clear();
  	drawstring(alphabet, "A", 50, 20, 24); 
    someDelay();
      
    //DEMO jumbo
  	tgi_clear();
  	drawstring(alphabet, "B", 50, 20, 24); 
    someDelay();
      
    //DEMO jumbo
  	tgi_clear();
  	drawstring(alphabet, "C", 50, 20, 24); 
    someDelay();
   	
    //reset
    tgi_clear();
      
    kbhit_check = kbhit(); 
    } while (!kbhit_check); // Wait for a key press before exiting

  
    tgi_done(); // Clean up TGI
    return 0;
}