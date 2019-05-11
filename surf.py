import numpy as np
import cv2
import time
from matplotlib import pyplot as plt
img = cv2.imread('helipadH3.jpg',1)

start = time.time()
# gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
ret, gray = cv2.threshold(img,127,255,cv2.THRESH_BINARY)
# Create SURF object. You can specify params here or later.
# Here I set Hessian Threshold to 400
surf = cv2.xfeatures2d.SURF_create(400)

# Find keypoints and descriptors directly
kp, des = surf.detectAndCompute(gray,None)

#print len(kp)

 # Check present Hessian threshold
#print surf.hessianThreshold
#400.0

# We set it to some 50000. Remember, it is just for representing in picture.
# In actual cases, it is better to have a value 300-500
#surf.hessianThreshold = 50000

# Again compute keypoints and check its number.
kp, des = surf.detectAndCompute(gray,None)

#print len(kp)

img2 = cv2.drawKeypoints(gray,kp,None,(255,0,0))
end = time.time()
print(end-start)
#plt.imshow(img2),plt.show()