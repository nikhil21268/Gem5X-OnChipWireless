def extract_and_save_lines_with_total(input_file_path, output_file_path):
    # This function reads a file and writes lines containing the word "total" to another file
    with open(input_file_path, 'r') as file, open(output_file_path, 'w') as outfile:
        for line in file:
            if 'total' in line:
                outfile.write(line)

# Specify the path to your stats.txt file
input_file_path = 'stats.txt'
# Specify the path for the output file
output_file_path = 'output_file_with_total_lines.txt'

# Call the function
extract_and_save_lines_with_total(input_file_path, output_file_path)
