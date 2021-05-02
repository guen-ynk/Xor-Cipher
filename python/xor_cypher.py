"""
@author:       Guen Yanik
@Title:        XORCpyher
@License:      MIT
@Description:  encrypt/decrypt files using XOR in diffrent ways
"""
import os
import time

import numpy as np



# data stuffing
def equalize(p1, p2):
    d1 = open(p1, "rb").read()
    d2 = open(p2, "rb").read()
    l1 = len(d1)
    l2 = len(d2)
    if l1 > l2:
        d2 = d2 + os.urandom(l1 - l2)
    else:
        d1 = d1 + os.urandom(l2 - l1)
    with open(p1, "wb") as out:
        out.write(d1)
    with open(p2, "wb") as out:
        out.write(d2)


'''
    Running XOR on two files, saving the result in a 3rd file - USING NUMPY FOR FASTER COMPUTATION SPEED -- ALSO SEE C IMPLEMENATION
    
    Args:
        stuffing: SLOW enable bytestuffing ( encryption mode only ) for 2 files of diffrent length / FAST disable stuffing and use % for byte repitition 
        path_origin: Filename-path of file you want to encrypt / decrypt ( .pdf, .img, .zip etc. / .key )
        enc_path:   Filename-path of file you wish to use as key ( .pdf .img .zip .txt etc. )
        key_path:   Filename-path of the written file. Encryption: .key - Decryption: .ext ( the extention of original file )  
'''


def crypt(
        stuffing: bool, path_origin: str,
        enc_path: str, key_path: str
):
    start_time = time.time()

    # byte Stuffing option
    if stuffing:
        equalize(path_origin, enc_path)

    # get the files
    try:
        original = np.fromfile(path_origin, dtype='uint8')
        encrypted = np.fromfile(enc_path, dtype='uint8')
    except FileNotFoundError:
        print("invalid Filename")
        return

    if encrypted.size < original.size:
        times = np.ceil(original.size / encrypted.size)
        encrypted = np.tile(encrypted, int(times))
    if encrypted.size > original.size:
        encrypted = encrypted[:-(encrypted.size - original.size)]

    key = np.bitwise_xor(original, encrypted)

    tmp = time.time() - start_time
    print("\n" + 30 * "-" + "\nExecution time with Numpy" + "Stuffing - " + str(stuffing) + ": " + str(tmp))
    print(str((key.size / 1024) / 1024) + " MB Written" + "\n" + 30 * "-")

    # write .key
    with open(key_path, "wb") as out:
        out.write(key)

    return


'''
    Running XOR on two files, saving the result in a 3rd file -- SLOW /  NO NUMPY -- PYTHON ONLY

    Args:
        path_origin: Filename-path of file you want to encrypt / decrypt ( .pdf, .img, .zip etc. / .key )
        enc_path:   Filename-path of file you wish to use as key ( .pdf .img .zip .txt etc. )
        key_path:   Filename-path of the written file. Encryption: .key - Decryption: .ext ( the extention of original file )  
'''


def crypt_old(
        path_origin: str, enc_path:str, key_path: str
):
    equalize(path_origin, enc_path)

    start_timec = time.time()

    try:
        original = open(path_origin, "rb").read()
        encrypted = open(enc_path, "rb").read()
    except FileNotFoundError:
        print("invalid Filename")
        return

    key = bytes(a ^ b for (a, b) in zip(original, encrypted))

    tmp = time.time() - start_timec
    print("\n" + 30 * "-" + "\nExecution time without Numpy" + ": " + str(tmp))
    print(str((len(key) / 1024) / 1024) + " MB Written" + "\n" + 30 * "-")

    with open(key_path, "wb") as out:
        out.write(key)

    return


'''
    Something regarding the diffrence in computation speed:
    
    In: ~450 megabyte file
    Key: ~1 kilobyte file
    
    with numpy and no bytestuffing:     1.79   sec
    with numpy and bytestuffing:        11.08  sec 
    without numpy an with bytestuffing: 127.89 sec
'''