#include <stdio.h>
#include <conio.h>
#include <tgi.h>

# define font1_width = 4;
# define font2_width = 7;

extern void cycle_counter(void);

const unsigned short alphabet[40][4] = {
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
    {0b1111, 0b0100, 0b0010, 0b1111}, // Z
    {0b0110, 0b1010, 0b1010, 0b1100}, // 0
    {0b0010, 0b0110, 0b0010, 0b0010}, // 1
    {0b0110, 0b0010, 0b0100, 0b0110}, // 2
    {0b0110, 0b0011, 0b0001, 0b0110}, // 3
    {0b0101, 0b0111, 0b0001, 0b0001}, // 4
    {0b0110, 0b0100, 0b0010, 0b0110}, // 5
    {0b0100, 0b0110, 0b0101, 0b0011}, // 6
    {0b0111, 0b0101, 0b0001, 0b0001}, // 7
    {0b0111, 0b0101, 0b0111, 0b0111}, // 8
    {0b0110, 0b0101, 0b0011, 0b0001}, // 9
    {0b0000, 0b0000, 0b0100, 0b1000}, // , comma
    {0b0000, 0b0000, 0b0110, 0b0110}, // . decimal
    {0b0001, 0b0010, 0b0100, 0b1000}, // /forwardslash
      {0b0001, 0b0010, 0b0100, 0b1000}, // /forwardslash
};


const unsigned short cryllic7x7[33][7] = {
{0b0000000,0b0011000,0b0100100,0b0100100,0b0111100,0b0100100,0b0000000}, // А
{0b0000000,0b0111100,0b0100000,0b0111000,0b0100100,0b0111000,0b0000000}, // Б
{0b0000000,0b0111000,0b0100100,0b0111000,0b0100100,0b0111000,0b0000000}, // В
{0b0000000,0b0111100,0b0100000,0b0100000,0b0100000,0b0100000,0b0000000}, // Г
{0b0000000,0b0001100,0b0010100,0b0010100,0b0111110,0b0100010,0b0000000}, // Д
{0b0000000,0b0111100,0b0100000,0b0111000,0b0100000,0b0111100,0b0000000}, // Е
{0b0000000,0b0101010,0b0101010,0b0011100,0b0101010,0b0101010,0b0000000}, // Ж
{0b0000000,0b0011000,0b0000100,0b0011000,0b0000100,0b0011000,0b0000000}, // З
{0b0000000,0b0100010,0b0100110,0b0101010,0b0110010,0b0100010,0b0000000}, // И
{0b0010100,0b0001000,0b0100010,0b0100110,0b0101010,0b0110010,0b0000000}, // Й
{0b0000000,0b0100100,0b0101000,0b0110000,0b0101000,0b0100100,0b0000000}, // К
{0b0000000,0b0001100,0b0010100,0b0010100,0b0010100,0b0100100,0b0000000}, // Л
{0b0000000,0b0100010,0b0110110,0b0101010,0b0100010,0b0100010,0b0000000}, // М
{0b0000000,0b0100100,0b0100100,0b0111100,0b0100100,0b0100100,0b0000000}, // Н
{0b0000000,0b0011000,0b0100100,0b0100100,0b0100100,0b0011000,0b0000000}, // О
{0b0000000,0b0111100,0b0100100,0b0100100,0b0100100,0b0100100,0b0000000}, // П
{0b0000000,0b0111000,0b0100100,0b0100100,0b0111000,0b0100000,0b0000000}, // Р
{0b0000000,0b0011100,0b0100000,0b0100000,0b0100000,0b0011100,0b0000000}, // С
{0b0000000,0b0111110,0b0001000,0b0001000,0b0001000,0b0001000,0b0000000}, // Т
{0b0000000,0b0100100,0b0100100,0b0011100,0b0000100,0b0111000,0b0000000}, // У
{0b0000000,0b0011100,0b0101010,0b0101010,0b0011100,0b0001000,0b0000000}, // Ф
{0b0000000,0b0100010,0b0010100,0b0001000,0b0010100,0b0100010,0b0000000}, // Х
{0b0000000,0b0100100,0b0100100,0b0100100,0b0100100,0b0111110,0b0000010}, // Ц
{0b0000000,0b0100100,0b0100100,0b0011100,0b0000100,0b0000100,0b0000000}, // Ч
{0b0000000,0b0101010,0b0101010,0b0101010,0b0101010,0b0111110,0b0000000}, // Ш
{0b0000000,0b0101010,0b0101010,0b0101010,0b0101010,0b0111111,0b0000001}, // Щ
{0b0000000,0b0110000,0b0010000,0b0011100,0b0010010,0b0011100,0b0000000}, // Ъ
{0b0000000,0b1000010,0b1000010,0b1110010,0b1001010,0b1110010,0b0000000}, // Ы
{0b0000000,0b0100000,0b0100000,0b0111000,0b0100100,0b0111000,0b0000000}, // Ь
{0b0000000,0b0111000,0b0000100,0b0011100,0b0000100,0b0111000,0b0000000}, // Э
{0b0000000,0b1001100,0b1010010,0b1110010,0b1010010,0b1001100,0b0000000}, // Ю
{0b0000000,0b0011100,0b0100100,0b0011100,0b0100100,0b0100100,0b0000000}, // Я
{0b0010100,0b0111100,0b0100000,0b0111000,0b0100000,0b0111100,0b0000000} // Ё
};




int findcharindex(char character) {
    // only supports uppercase A-Z, digits 0-9, comma, period, and forward slash
    if (character >= 'A' && character <= 'Z') {
        return character - 'A';
    } else if (character >= '0' && character <= '9') {
        return character - '0' + 26;
    } else if (character == ',') {
        return 36; // Index for comma
    } else if (character == '.') {
        return 37; // Index for period
    } else if (character == '/') {
        return 38; // Index for forward slash
    } else {
        return -1; // Not found in the array
    }
}


void drawchar(char fontnumber, char character, unsigned int startX, unsigned char startY) {
    int font1width = 4;
    int font2width = 7;
    int fontwidth;
    int index;

    if (fontnumber == 1) {
        fontwidth = font1width;
        index = findcharindex(character);
        if (index != -1) {
            const unsigned short* nextchar = alphabet[index];
            int x, y;
            unsigned int scaledX, scaledY;

           // static const unsigned char Palette[3] = { TGI_COLOR_WHITE, TGI_COLOR_BLACK };
          //can set character color here 

            for (y = 0; y < fontwidth; y++) {   // iterate over Y-axis pixels (rows)
                for (x = 0; x < fontwidth; x++) { // for each X column, font_width pixels
                    if ((*nextchar) & (1 << (fontwidth - 1 - x))) {
                        scaledX = startX + x;
                        scaledY = startY + y;

                        // draw pixel using tgi_setpixel
                        tgi_setpixel(scaledX, scaledY);
                    }
                }
                nextchar++; // Move to the next row in the grid
            }
        } else {
            printf("character '%c' not found\n", character);
        }
    } else if (fontnumber == 2) {
        fontwidth = font2width;
        index = findcharindex(character);
        if (index != -1) {
            const unsigned short* nextchar = cryllic7x7[index];
            int x, y;
            unsigned int scaledX, scaledY;

          //  static const unsigned char Palette[3] = { TGI_COLOR_WHITE, TGI_COLOR_BLACK };

            for (y = 0; y < font2width; y++) {   // iterate over Y-axis pixels (rows)
                for (x = 0; x < font2width; x++) { // for each X column, font2_width pixels
                    if ((*nextchar) & (1 << (font2width - 1 - x))) {
                        scaledX = startX + x;
                        scaledY = startY + y;

                        // draw pixel using tgi_setpixel
                        tgi_setpixel(scaledX, scaledY);
                    }
                }
                nextchar++; // Move to the next row in the grid
            }
        } else {
            printf("character '%c' not found\n", character);
        }
    } else {
        printf("Invalid font number\n");
        return;
    }
}






void drawstring(char fontnumber,
                const char* str, 
                unsigned int startX, 
                unsigned char startY) {
    while (*str != '\0') {
         if (fontnumber == 1) {
        drawchar(1, *str, startX, startY);
        startX += 5; // font1 4x4 needs 5 pixels for each char
         }
         if (fontnumber == 2) {
        drawchar(2, *str, startX, startY);
      	startX += 6; // font2 7x7 needs 7 pixels for each char
         }
        str++;
    }
}


void drawWrappedString(char fontnumber,
                       const char* text, 
                       unsigned char maxLineLength, 
                       unsigned char startX, 
                       unsigned char startY) {
  
    int fontwidth, fontheight;    
    const char* currentWord = text;
    unsigned int currentLength = 0;
    char currentWordCopy[20]; // max word size , TODO: things break if its too small
    unsigned int currentLineStartX = startX;

    while (*text != '\0') {
               if (fontnumber == 1) {
                 fontwidth = 5;
                 fontheight = 5;
               }
                     if (fontnumber == 2) {
                       fontwidth = 7;
                     }
        if (*text == ' ') { //if the current char is a space we jump 6 pixels on Y axis
            currentWordCopy[currentLength] = '\0'; // Null-terminate the string
            if (currentLineStartX + (currentLength * fontwidth) > startX + maxLineLength * fontwidth ) {
                // If adding the current word would exceed maxLineLength, start a new line
                startY += 7 ; //advance y axis if current char is ' ' space
                currentLineStartX = startX;
            }
            drawstring(fontnumber, currentWordCopy, currentLineStartX, startY);
            currentLineStartX += currentLength * fontwidth + 3; // affects X axis character spacing
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
        if (currentLineStartX + (currentLength * 7 ) > startX + maxLineLength * 7) {
           //  If adding the last word would exceed maxLineLength, start a new line
            startY += 7;
            currentLineStartX = startX;
        }
        drawstring(fontnumber, currentWordCopy, currentLineStartX, startY);
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
    int i, linespacing;
    int kbhit_check;
   const char* myLongString1 = "NOW IS A TIME FOR ALL GOOD MEN TO COME TO THE AID OF THEIR COUNTRY. IN THIS MOMENT, WHERE THE FUTURE UNFOLDS BEFORE US, EACH INDIVIDUAL HOLDS THE POWER TO SHAPE THE DESTINY OF OUR NATION. LET US RISE TO THE CHALLENGES THAT CONFRONT US, UNITED IN OUR DIVERSITY, STRIVING FOR A COMMON PURPOSE. NOW IS NOT THE MOMENT FOR APATHY, BUT FOR ACTIVE ENGAGEMENT IN BUILDING A SOCIETY ROOTED IN JUSTICE, EQUALITY, AND FREEDOM. TOGETHER, WE CAN OVERCOME ADVERSITY, FOSTER UNITY, AND SECURE A BETTER TOMORROW. NOW, MORE THAN EVER, IS THE TIME FOR ALL GOOD MEN AND WOMEN TO STAND TOGETHER, EMBRACING THE RESPONSIBILITY THAT HISTORY BESTOWS UPON US, FOR IN OUR COLLECTIVE ACTIONS LIES THE STRENGTH OF OUR NATION";
 const char* myLongString2 = "WITH GREAT POWER COMES GREAT RESPONSIBILITY. THIS ADMONITION, ATTRIBUTED TO VARIOUS FIGURES THROUGH HISTORY, ENCOURAGES INDIVIDUALS TO RECOGNIZE THE IMPACT OF THEIR ACTIONS AND TO USE THEIR INFLUENCE WISELY. IT REMINDS US THAT POSSESSING ABILITIES, BE THEY INTELLECTUAL, SOCIAL, OR OTHERWISE, BRINGS A DUTY TO CONTRIBUTE TO THE GREATER GOOD OF SOCIETY. IN THE FACE OF OPPORTUNITY, LET US STRIVE TO UPLIFT AND EMPOWER THOSE AROUND US, FOSTERING A COMMUNITY BUILT ON MUTUAL RESPECT AND KINDNESS.";
  const char* myLongString3 = "BE THE CHANGE YOU WISH TO SEE IN THE WORLD. THIS INSPIRING UTTERANCE, OFTEN ATTRIBUTED TO MAHATMA GANDHI, ENCOURAGES INDIVIDUALS TO TAKE INITIATIVE IN CREATING POSITIVE TRANSFORMATIONS. IT CALLS FOR SELF-AWARENESS, PROMPTING US TO REFLECT ON OUR VALUES AND ASPIRATIONS";
  const char* mystring1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,./"; 
  const char* mystring2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123";
    // Install TGI
    tgi_install(tgi_static_stddrv); 
    tgi_init(); // init tgi
    tgi_clear(); // Clear the screen

    // Check if tgi_init() failed
    if (tgi_geterror() != TGI_ERR_OK) {
        printf("Error initializing graphics.");
        return 1;
    }
  

drawWrappedString(1, myLongString1, 63, 2, 1); // character array, string, maxLineLength, startX, startY, scalefactor
drawWrappedString(1, myLongString2, 32, 2, 84); // character array, string, maxLineLength, startX, startY, scalefactor
drawWrappedString(2, myLongString3, 22, 178, 84); // character array, string, maxLineLength, startX, startY, scalefactor


  
  
  
  
  
  
  
  
 someDelay();
 someDelay();
   someDelay();
 someDelay();
   someDelay();
 someDelay();
  tgi_clear();
    do {  // DEMO text wall
       for (i = 0; i < 180; i+=15){
         linespacing = 18;
         drawstring(1, mystring1, 2, i); // character array, string, startX, startY
          drawstring(2, mystring2, 2, i + 5); // character array, string, startX, startY
          
        }
    someDelay();
          

           
    //reset
    tgi_clear();
      
    kbhit_check = kbhit(); 
    } while (!kbhit_check); // Wait for a key press before exiting

  
    tgi_done(); // Clean up TGI
    return 0;
}