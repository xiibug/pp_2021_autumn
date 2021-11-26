# -*- coding: utf-8 -*-
"""
Created on Mon Nov 15 21:47:41 2021

@author: Kruglov, Aleksei
"""
import cv2 as cv
import numpy as np

def JpgToTxt(number) :
    path = "dataset/"
    filename = str(number) +"input.jpg"
    path = path + filename
    out = cv.imread(path, cv.IMREAD_GRAYSCALE)
    arr = np.copy(out)
    s = "dataset/" + str(number) +"arr_input.txt"
    np.savetxt(s, arr, fmt='%i')

for i in range(1, 5) :
    JpgToTxt(i)
