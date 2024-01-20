#include <stdio.h>
#include <conio.h>
#include <tgi.h>


const unsigned short alphabet[37][4] = {
    {0b1111, 0b1001, 0b1111, 0b1001}, // A
    {0b1000, 0b1110, 0b1010, 0b1110}, // B
    {0b1111, 0b1000, 0b1000, 0b1111}, // C
    {0b1110, 0b1001, 0b1001, 0b1110}, // D
    {0b1111, 0b1110, 0b1000, 0b1111}, // E
    {0b1111, 0b1110, 0b1000, 0b1000}, // F
    {0b1111, 0b1000, 0b1001, 0b1111}, // G
    {0b1000, 0b1000, 0b1111, 0b1001}, // H
    {0b0100, 0b0100, 0b0100, 0b0100}, // I
    {0b0100, 0b0100, 0b0100, 0b1100}, // J
    {0b1010, 0b1100, 0b1010, 0b1001}, // K
    {0b1000, 0b1000, 0b1000, 0b1111}, // L
    {0b1001, 0b1111, 0b1001, 0b1001}, // M
    {0b1001, 0b1101, 0b1011, 0b1001}, // N
    {0b1111, 0b1001, 0b1001, 0b1111}, // O
    {0b1111, 0b1001, 0b1110, 0b1000}, // P
    {0b1111, 0b1001, 0b1111, 0b0001}, // Q
    {0b1110, 0b1001, 0b1100, 0b1010}, // R
    {0b1111, 0b1000, 0b0001, 0b1111}, // S
    {0b1111, 0b0100, 0b0100, 0b0100}, // T
    {0b1001, 0b1001, 0b1001, 0b1111}, // U
    {0b1001, 0b0101, 0b0011, 0b0001}, // V
    {0b1001, 0b1001, 0b1001, 0b0110}, // W
    {0b0000, 0b1010, 0b0100, 0b1010}, // X
    {0b1001, 0b0110, 0b0010, 0b0010}, // Y
    {0b1111, 0b0100, 0b0010, 0b1111},  // Z
    {0b0110,0b1010,0b1010,0b1100}, //0
    {0b0010,0b0110,0b0010,0b0010}, //1
    {0b0110,0b0010,0b0100,0b0110}, //2
    {0b0110,0b0011,0b0001,0b0110}, //3
    {0b0101,0b0111,0b0001,0b0001}, //4
    {0b0110,0b0100,0b0010,0b0110}, //5
    {0b0100,0b0110,0b0101,0b0011}, //6
    {0b0111,0b0101,0b0001,0b0001}, //7
    {0b0111,0b0101,0b0111,0b0111}, //8
    {0b0110,0b0101,0b0011,0b0001}, //9
};




int findcharindex(char character) {
    // only supports uppercase A-Z and digits 0-9
    if (character >= 'A' && character <= 'Z') {
        return character - 'A';
    } else if (character >= '0' && character <= '9') {
        return character - '0' + 26;
    } else {
        return -1; // Not found in the array
    }
}


void drawchar( 
              char character, 
              unsigned int startX, 
              unsigned char startY ) {
  
    int index = findcharindex(character);
    if (index != -1) { // draw the character at the specified index
        const unsigned short* nextchar = alphabet[index];
        int x, y;
        unsigned int scaledX, scaledY; 
      //unsigned int scaledX2, scaledY2;

        static const unsigned char Palette[3] = { TGI_COLOR_WHITE, TGI_COLOR_BLACK };
        //tgi_setpalette(Palette);

        for (y = 0; y < 4; y++) {   // iterate over 4 Y-axis pixels (rows)
            for (x = 0; x < 4; x++) { // for each X column, 4 pixels
                if ((*nextchar) & (1 << (3 - x))) {
                    scaledX = startX + x;
                    scaledY = startY + y; 

                    // draw rectangle using tgi_bar
                    tgi_setpixel(scaledX, scaledY);
                }
            }
            nextchar++; // Move to the next row in the grid
        }
    } else {
        printf("character '%c' not found\n", character);
    }
}



void drawstring(const char* str, unsigned int startX, 
                unsigned char startY) {
    while (*str != '\0') {
        drawchar(*str, startX, startY);
        startX += 5; // each character takes 8 pixels width
        str++;
    }
}


void drawWrappedString(const char* text, 
                       unsigned char maxLineLength, 
                       unsigned char startX, 
                       unsigned char startY) {
  
    const char* currentWord = text;
    unsigned int currentLength = 0;
    char currentWordCopy[20]; // max word size , TODO: things break if its too small
    unsigned int currentLineStartX = startX;

    while (*text != '\0') {
        if (*text == ' ') { //if the current char is a space we jump 6 pixels on Y axis
            currentWordCopy[currentLength] = '\0'; // Null-terminate the string
            if (currentLineStartX + (currentLength * 5) > startX + maxLineLength * 5 ) {
                // if adding current word would exceed maxLineLength, start a new line
                startY += 6 ; //advance y axis if current char is ' ' space
                currentLineStartX = startX;
            }
            drawstring(currentWordCopy, currentLineStartX, startY);
            currentLineStartX += currentLength * 5 + 3; // move y for space 3*sf val
            currentLength = 0;
        } else {
            currentWordCopy[currentLength] = *text;
            currentLength++;
        }
      
        text+=1;
    }

    // Draw the last word if needed
    if (currentLength > 0) {
        currentWordCopy[currentLength] = '\0'; // Null-terminate the string
        if (currentLineStartX + (currentLength * 5 ) > startX + maxLineLength * 5) {
           //  if adding the last word would exceed maxLineLength, start a new line
            startY += 8;
            currentLineStartX = startX;
        }
        drawstring(currentWordCopy, currentLineStartX, startY);
      //TODO: need to decide what to do if the word length is longer than the max length
    }
}
//#link "counter.s"






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
 const char* myLongString1 = "NOW IS A TIME FOR ALL GOOD MEN TO COME TO THE AID OF THEIR COUNTRY. IN THIS MOMENT, WHERE THE FUTURE UNFOLDS BEFORE US, EACH INDIVIDUAL HOLDS THE POWER TO SHAPE THE DESTINY OF OUR NATION. LET US RISE TO THE CHALLENGES THAT CONFRONT US, UNITED IN OUR DIVERSITY, STRIVING FOR A COMMON PURPOSE. NOW IS NOT THE MOMENT FOR APATHY, BUT FOR ACTIVE ENGAGEMENT IN BUILDING A SOCIETY ROOTED IN JUSTICE, EQUALITY, AND FREEDOM. TOGETHER, WE CAN OVERCOME ADVERSITY, FOSTER UNITY, AND SECURE A BETTER TOMORROW. NOW, MORE THAN EVER, IS THE TIME FOR ALL GOOD MEN AND WOMEN TO STAND TOGETHER, EMBRACING THE RESPONSIBILITY THAT HISTORY BESTOWS UPON US, FOR IN OUR COLLECTIVE ACTIONS LIES THE STRENGTH OF OUR NATION";
 const char* myLongString2 = "WITH GREAT POWER COMES GREAT RESPONSIBILITY. THIS ADMONITION, ATTRIBUTED TO VARIOUS FIGURES THROUGH HISTORY, ENCOURAGES INDIVIDUALS TO RECOGNIZE THE IMPACT OF THEIR ACTIONS AND TO USE THEIR INFLUENCE WISELY. IT REMINDS US THAT POSSESSING ABILITIES, BE THEY INTELLECTUAL, SOCIAL, OR OTHERWISE, BRINGS A DUTY TO CONTRIBUTE TO THE GREATER GOOD OF SOCIETY. IN THE FACE OF OPPORTUNITY, LET US STRIVE TO UPLIFT AND EMPOWER THOSE AROUND US, FOSTERING A COMMUNITY BUILT ON MUTUAL RESPECT AND KINDNESS.";
  const char* myLongString3 = "BE THE CHANGE YOU WISH TO SEE IN THE WORLD. THIS INSPIRING UTTERANCE, OFTEN ATTRIBUTED TO MAHATMA GANDHI, ENCOURAGES INDIVIDUALS TO TAKE INITIATIVE IN CREATING POSITIVE TRANSFORMATIONS. IT CALLS FOR SELF-AWARENESS, PROMPTING US TO REFLECT ON OUR VALUES AND ASPIRATIONS";
  const char* mystring1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789012345678901234567890123456"; 
      // Install TGI
    tgi_install(tgi_static_stddrv); 
    tgi_init(); // init tgi
    tgi_clear(); // Clear the screen

    // Check if tgi_init() failed
    if (tgi_geterror() != TGI_ERR_OK) {
        printf("Error initializing graphics.");
        return 1;
    }
  

drawWrappedString(myLongString1, 63, 2, 1); // character array, string, maxLineLength, startX, startY, scalefactor
drawWrappedString(myLongString2, 32, 2, 80); // character array, string, maxLineLength, startX, startY, scalefactor
drawWrappedString(myLongString3, 22, 180, 80); // character array, string, maxLineLength, startX, startY, scalefactor


  
  
  
  
  
  
  
  
 someDelay();
 someDelay();
   someDelay();
 someDelay();
   someDelay();
 someDelay();
  tgi_clear();
    do {  // DEMO text wall
       for (i = 0; i < 260; i+=5){
          drawstring(mystring1, 2, i); // character array, string, startX, startY
          // drawstring(alphabet, mystring2, 2, i+linespacing); // character array, string, startX, startY, scalefactor
          
         // drawstring(alphabet, mystring, 2, i+7, 1);
        }
    someDelay();
          

           
    //reset
    tgi_clear();
      
    kbhit_check = kbhit(); 
    } while (!kbhit_check); // Wait for a key press before exiting

  
    tgi_done(); // Clean up TGI
    return 0;
}