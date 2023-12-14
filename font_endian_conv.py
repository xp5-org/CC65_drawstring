def horizontal_mirror(binary_str):
    return binary_str[::-1]  # reverse order of the string characters

with open('infile.txt', 'r') as file:
    lines = file.readlines()

output_values = []

for line in lines:
    if '{' in line and '}' in line:
        hex_entries = line[line.index('{') + 1:line.index('}')]  # get hex between curly braces
        hex_values = [x.strip() for x in hex_entries.split(',') if x.strip().startswith('0x')]

        hex_values_mirror = []
        for hex_val in hex_values:
            hex_val = hex_val.strip()[2:]  # Remove '0x' prefix
            binary_val = format(int(hex_val, 16), '08b')  # hex to binary 8bit
            mirrored_binary_val = horizontal_mirror(binary_val)
            mirrored_hex_val = format(int(mirrored_binary_val, 2), '02X')  # binary to hex
            hex_values_mirror.append('0x' + mirrored_hex_val)  # add 0x infront of hex value to format it
        output_values.append(', '.join(hex_values_mirror))

with open('outfile.txt', 'w') as outfile:
    for output_line in output_values:
        outfile.write(output_line)
        outfile.write('\n')