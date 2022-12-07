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


def get_salted_hash(row: str, n=5):
    idx = 0
    salt_hash = row
    zero_check = ''.join('0' for _ in range(n))

    while (get_md5(salt_hash)[:n] != zero_check):
        idx += 1
        salt_hash = f"{row}{idx}"
    return salt_hash


def get_salted_hashes(data:list, n=5):

    salt_hashes = list()

    for row in data:
        salt_hashes.append(get_salted_hash(row, n))

    return salt_hashes


def main():
    
    parser = argparse.ArgumentParser(description="Using python because of hashlib")
    parser.add_argument('input_filename', type=str, help="list of inputs - file")
    parser.add_argument('-n', type=int, default=5)
    args = parser.parse_args()

    data = load_data(args.input_filename)
    salt_hashes = get_salted_hashes(data, args.n)

    for s in salt_hashes:
        print(s)

if __name__ == '__main__':
    main()
