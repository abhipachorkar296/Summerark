import numpy as np
import cv2
from matplotlib import pyplot as plt

# Load image
img = cv2.imread('helipadH3.jpg',1)
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY);

# Initiate FAST object with default values
fast = cv2.FastFeatureDetector_create();

# find and draw the keypoints
kp = fast.detect(gray, None);

#Print all default params
print("Threshold: ", fast.getThreshold());
print("nonmaxSuppression: ", fast.getNonmaxSuppression());
print("neighborhood: ", fast.getType());
print("Total Keypoints with nonmaxSuppression: ", len(kp));


# Disable nonmaxSuppression
fast.setNonmaxSuppression(False);
kp = fast.detect(gray,None);
print("Total Keypoints without nonmaxSuppression: ", len(kp));

# Output the points on the mats
img2 = cv2.drawKeypoints(img, kp, None, color=(255,0,0))
img3 = cv2.drawKeypoints(img, kp, None, color=(255,0,0));

# Show the mats
cv2.imshow("img1", img); # Original mat
cv2.imshow("img2", img2); # With nonmaxSuppression
cv2.imshow("img3", img3); # Without nonmaxSuppression
cv2.waitKey();