# -*- coding: utf-8 -*-
"""
Created on Mon Nov 15 20:21:01 2021

@author: Kruglov, Aleksei
"""

import cv2 as cv
import numpy as np

def TxtToJpg(number) :
    path = "dataset/"
    filename = str(number) + "arr_output.txt"
    path = path + filename
    out = np.loadtxt(path, dtype=np.uint8)
    s = "dataset/" + str(number) +"output.jpg"
    cv.imwrite(s, out)


for i in range(1, 5) :
    TxtToJpg(i)