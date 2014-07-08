#!/usr/bin/env python

import numpy as np
import PupilTrackerPythonWrapper as pt
import cv2

params = [3.0, 8.0, 1.0, 20.0, 40.0, 0.0, 30.0, 2.0, 95.0, -1.0]
image = cv2.imread('Lenna.png')

print("Test 1:")
(center_x, center_y, size_width, size_height, angle) = pt.findPupil(image)
print("Center_x: %f"%(center_x))
print("Center_y: %f"%(center_y))
print("Size_width: %f"%(size_width))
print("Size_height: %f"%(size_height))
print("Angle: %f"%(angle))
print("----------------")
print("Test 2:")
(center_x, center_y, size_width, size_height, angle) = pt.findPupil(image, 10, 20, 2, 30, 50, 3)
print("Center_x: %f"%(center_x))
print("Center_y: %f"%(center_y))
print("Size_width: %f"%(size_width))
print("Size_height: %f"%(size_height))
print("Angle: %f"%(angle))
