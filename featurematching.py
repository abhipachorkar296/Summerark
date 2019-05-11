import numpy as np
import cv2
from matplotlib import pyplot as plt

img1 = cv2.imread('helipadH2.jpg',1) # queryImage
img2 = cv2.imread('helipadH3.jpg',1) # trainImage
gray1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY);
gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY);
fast = cv2.FastFeatureDetector_create();
# find the keypoints and descriptors with FAST
kp1, des1 = fast.detectAndCompute(gray1,None)
print len(kp1)
kp2, des2 = fast.detectAndCompute(gray2,None)
# BFMatcher with default params
bf = cv2.BFMatcher()
matches = bf.knnMatch(des1,des2, k=2)

# Apply ratio test
good = []
for m,n in matches:
    if m.distance < 0.75*n.distance:
        good.append([m])

# cv2.drawMatchesKnn expects list of lists as matches.
img3 = cv2.drawMatchesKnn(img1,kp1,img2,kp2,good,None,flags=2)

plt.imshow(img3),plt.show()