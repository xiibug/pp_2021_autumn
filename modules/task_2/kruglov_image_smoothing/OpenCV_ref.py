# -*- coding: utf-8 -*-
"""
Created on Wed Nov 17 15:29:31 2021

@author: Kruglov, Aleksei
"""

import cv2 as cv

def JpgToTxt(number) :
    path = "dataset/"
    filename = str(number) +"input.jpg"
    path = path + filename
    img = cv.imread(path, cv.IMREAD_GRAYSCALE)
    sigma = 1.5
    imgBlur = cv.GaussianBlur(img, (3, 3), sigma)
    s = "dataset/" + str(number) +"output_opencv.jpg"
    cv.imwrite(s, imgBlur)

for i in range(1, 5) :
    JpgToTxt(i)

