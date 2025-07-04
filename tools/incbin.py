#!/usr/bin/python3

import sys
import getopt
import os

autogenerated_warning = "/* autogenerated by incbin, do not modify manually */"

def file_name_transform(name, upper=False):
    name = os.path.basename(name)
    if upper:
        name = name.upper()
    name = name.replace(".", "_")
    return name

def build_source_file(files, header_file_name, source_file_name):
    source_file_lines = []

    source_file_lines.append(autogenerated_warning)
    source_file_lines.append(f"#include \"{header_file_name}\"")
    source_file_lines.append("")

    for file in files:
        filename = file_name_transform(file)
        contents = files[file]
        file_bytes = ",".join('0x{:02x}'.format(x) for x in bytes(contents, "utf8"))
        length = len(contents)
        source_file_lines.append(f"unsigned char {filename}[{length}] = ")
        source_file_lines.append("{")
        source_file_lines.append(file_bytes)
        source_file_lines.append("};")

    source_file = "\n".join(source_file_lines)

    return source_file

def build_header_file(files, header_file_name):
    header_file_lines = []

    transformed_name = file_name_transform(header_file_name, upper=True)
    header_file_lines.append(autogenerated_warning)
    header_file_lines.append(f"#ifndef _{transformed_name}_")
    header_file_lines.append(f"#define _{transformed_name}_")
    header_file_lines.append("")
    for file in files:
        filename = file_name_transform(file)
        contents = files[file]
        length = len(contents)
        header_file_lines.append(f"extern unsigned char {filename}[{length}];")
    # magic
    header_file_lines.append("")
    header_file_lines.append(f"#endif /* {transformed_name} */")

    header_file = "\n".join(header_file_lines)

    return header_file

def usage(code):
    print(f"usage: {sys.argv[0]} -o SOURCE_FILE -H HEADER_FILE file1,file2,file3")
    sys.exit(code)

def main():
    files = []
    output_file_name = ""
    output_header_file = False

    options = []

    try:
        options, files = getopt.getopt(sys.argv[1:], "o:H")
    except getopt.GetoptError as err:
        print(err)
        usage(1)

    for option, arg in options:
        if option == "-o":
            output_file_name = arg
        elif option == "-H":
            output_header_file = True
        else:
            print(f"Unknown option '{option}'")
            usage(1)

    if len(files) == 0 or len(output_file_name) == 0:
        usage(1)

    files_dict = {}
    for file in files:
        with open(file) as f:
            files_dict[file] = f.read()

    file_contents = "" 

    if output_header_file:
        file_contents = build_header_file(files_dict, output_file_name)
    else:
        header_filename = output_file_name[:-2] + '.h'
        file_contents = build_source_file(files_dict, header_filename, output_file_name)

    with open(output_file_name, "w") as f:
        f.write(file_contents)

if __name__ == '__main__':
    main()
