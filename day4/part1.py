#!/usr/bin/env python3

import argparse, os, sys
import hashlib

def load_data(input_filename:str):

    assert(os.path.isfile(input_filename))

    data = list()

    with open(input_filename, 'r') as ifile:
        for row in ifile.readlines():
            r = row.strip('\n')
            print(r)
            data.append(r)
    return data

def get_md5(msg:str):
    m = hashlib.md5()
    m.update(msg.encode('UTF-8'))
    return m.hexdigest()

def get_salted_hash(row: str):
    idx = 0
    salt_hash = row

    while (get_md5(salt_hash)[:5] != '00000'):
        idx += 1
        salt_hash = f"{row}{idx}"
    return salt_hash



def get_salted_hashes(data:list):

    salt_hashes = list()

    for row in data:
        salt_hashes.append(get_salted_hash(row))

    return salt_hashes


def main():
    
    parser = argparse.ArgumentParser(description="Using python because of hashlib")
    parser.add_argument('input_filename', type=str, help="list of inputs - file")
    args = parser.parse_args()

    data = load_data(args.input_filename)
    salt_hashes = get_salted_hashes(data)

    for s in salt_hashes:
        print(s)

if __name__ == '__main__':
    main()
