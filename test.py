#!/usr/bin/env python

import numpy as np
import PupilTrackerPythonWrapper as pt
import cv2

image = cv2.imread('Lenna.png')
#print(image)
print(pt.findPupil(image))
