from PIL import Image
import sys

def process_font_rows(filename, threshold=0):
    # open the PNG file
    image = Image.open(filename)

    # get image dimensions
    image_width, image_height = image.size

    # print the opening brace
    print('{', end='')

    # iterate over all rows in the image
    for row_number in range(image_height):
        row_values = []
        # iterate over the pixels in the current row
        for x in range(image_width):
            # get pixel value from red channel
            pixel_value = image.getpixel((x, row_number))[0]

            # check if the pixel is below the threshold (consider it black)
            is_black = pixel_value < threshold
            binary_value = "1" if is_black else "0"
            row_values.append(binary_value)

        # calculate the summary for the current row
        summary = int("".join(row_values), 2)
        # format the summary based on the width of the image
        summary_format = f'0x{summary:0{image_width}b}'

        # print the summary for the current row, with comma if not the last row
        print(summary_format + (',' if row_number < image_height - 1 else ''), end='')

    # Print the closing brace
    print('}')

if __name__ == "__main__":
    # Check if the correct number of arguments is provided
    if len(sys.argv) != 2:
        print("Usage: python fontstuff.py input.png > output.txt")
        sys.exit(1)

    # get the input filename from command line arguments
    input_filename = sys.argv[1]

    # process the rows and print
    process_font_rows(input_filename, threshold=128) # color threshhold to set 1 or 0 reading
