#!/usr/bin/env python3

import argparse
import os, glob

# command-line args
parser = argparse.ArgumentParser(description='Change your file\'s encoding')

## infile code language
parser.add_argument('-lang', '--code-lang', metavar='CODE_LANG',
                    default='c/cpp', type=str,
                    help='input file code language')

## infile encoding
parser.add_argument('-i', '--infile-encoding', metavar='INFILE_ENCODING',
                    default='utf-8', type=str,
                    help='input file encoding')

## outfile encoding
parser.add_argument('-o', '--outfile-encoding', metavar='OUTFILE_ENCODING',
                    default='gb2312', type=str,
                    help='output file encoding')

## append encoding after filename?
# parser.add_argument('-a', '--append-encoding',
#                     help='append encoding to new files\' names')

## change line endings
parser.add_argument('-no-crlf', '--dont-convert-lf-to-crlf', action='store_true',
                    help='''with this flag on, the program will NOT
                    change unix line endings to win ones''')

## recursive
# parser.add_argument('-r', '--recursive')

args = vars(parser.parse_args())
# print(args)



# get filename list

## get name template
filename_regex_template = os.curdir
filename_regex = []
if args['code_lang'] == 'c/cpp':
    filename_regex.append(os.path.join(filename_regex_template, '*.c*'))
    filename_regex.append(os.path.join(filename_regex_template, '*.h*'))
# print(filename_regex)


## scan disk and get list
filenames = []
for each in filename_regex:
    filenames.extend(glob.glob(each))
# print(filenames)

## set dest directory
outdir = 'out_{}'.format(args['outfile_encoding'])
if outdir not in os.listdir():
    return_value = os.system('mkdir {}'.format(outdir))
else:
    print('Directory {} already exists!'.format(outdir))
    overwrite = input('Overwrite files? [y/n] ')
    while overwrite not in 'ynYN':
        overwrite = input('Choose again! [y/n] ')
    if overwrite in 'nN\n':
        print('Exiting! No changes are made!')
        exit(0)
    else:
        print('Overwrite!')

outdir = os.path.join(os.curdir, outdir)
# print(outdir)


# change encoding
for filename in filenames:

    with open(filename, 'rt', encoding=args['infile_encoding']) as f:

        file_content = f.read()

        # create new file
        new_name, extension = os.path.splitext(os.path.basename(filename))
        new_name = '{original}_{encoding}{extension}'.format(
                original=new_name,
                encoding=args['outfile_encoding'],
                extension=extension
        )
        new_name = os.path.join(outdir, new_name)
        # print(new_name)

        if os.system('touch {}'.format(new_name)) > 0:
            print('Failed when creating {}!'.format(new_name))
            continue

        # write to new file
        with open(new_name, 'wb') as n:

            # change line endings
            if not args['dont_convert_lf_to_crlf']:
                file_content = file_content.replace('\n', '\r\n')

            if  n.write(file_content.encode(args['outfile_encoding'])) > 0:
                # prompt user on success
                print('Successfully created file {}!'.format(new_name))
            else:
                print('Failed when writing {}!'.format(new_name))
