import glob
import os
import shutil
HEADER = 'POKEMON_OPTIONS = [\n'
CONTENTS = '''\t{{
\t\t"label": "{name}",
\t\t"value": "{number}",
\t}},
'''
FOOTER = "];\n"

# For file.txt in this directory
# 1. open the file
# 2. open an output file
# 3. write HEADER to output
# 4. start number at 0
# 5. For each line in file.txt
# 6. Read the line into name
# 7. Replace vars in CONTENTS (name, number)
# 8. append CONTENTS to output
# 9. increment number
# 10. repeat
if __name__ == "__main__":
    if os.path.exists("Output"):
        shutil.rmtree("Output")
    os.makedirs("Output")

    for input_filename in glob.glob("*.txt"):
        output_filename = "Output\\" + input_filename.split('.')[0] + ".js"
        print(f"Writing from {input_filename} to {output_filename}")
        number = 0
        with open(input_filename, "r") as name_file:
            with open(output_filename, "w") as out_file:
                out_file.write(HEADER)
                name = name_file.readline().strip()
                while name:
                    out_file.write(CONTENTS.format(**locals()))
                    name = name_file.readline().strip()
                    number += 1
                out_file.write(FOOTER)

    