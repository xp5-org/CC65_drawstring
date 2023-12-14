Using CC65 tgi_bar - i have created a demo to show how large scaled fonts can be drawn on the C64 screen.
`drawstring(characterarray, inputstring, startXpos, startYpos, scalefactor);`

# Functions:

`drawstring:`
        This function iterates over an input string, manipulating the starting X and Y positions, and subsequently draws characters across the screen. However, it's worth noting that it might scramble the screen if drawing near the screen's edges or bottom.

`drawchar:`
        Responsible for handling an 8x8 grid of data for a single character. Based on the value of the scalefactor, it either prints an 8x8 grid for scalefactor - 1 or, for scalefactor - 4, draws a larger 16x16 sized character on the screen. This is achieved using the tgi_bar function, which employs a rapid fill method utilizing a character block, known to be faster than setting pixels.

`findcharindex:`
        This function is tasked with converting the current character string slice and then returning the appropriate index position.




## where to get the font
i used this one as it looked nice 
- `https://github.com/dhepper/font8x8/blob/master/font8x8_basic.h`

The font array looks like this in the code
```
char alphabet[19][8] = {
{ 0x30, 0x78, 0xCC, 0xCC, 0xFC, 0xCC, 0xCC, 0x00}, // A
{ 0xFC, 0x66, 0x66, 0x7C, 0x66, 0x66, 0xFC, 0x00}, // B
{ 0x3C, 0x66, 0xC0, 0xC0, 0xC0, 0x66, 0x3C, 0x00}, // C
```

each row is 8 bits of information, and there are 8 rows. this gives us the 8x8 chararacter

I wrote a tool to horizontally transpose the bits of a hex 8x8 character font
<img width="542" alt="Screenshot 2023-12-13 at 8 28 18 PM" src="https://github.com/xp5-org/CC65_drawstring/assets/18539839/83676530-adee-4f10-927c-d914bbc02e0e">


An example for the letter B using [font_endian_conv.py ](https://github.com/xp5-org/CC65_drawstring/blob/main/font_endian_conv.py)
` python3 font_endian_conv.py infile.txt outfile.txt`

- cant recall if you need to add on curly braces or not but it does flip the bits correctly

<br>

### demo
a demo of using tgi_bar call to draw scaled fonts on the C64 screen 
![demo1](https://github.com/xp5-org/CC65_drawstring/assets/18539839/33a7db2d-2360-45c3-b2a0-95bc0e89d096)

