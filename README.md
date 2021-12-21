# Seam-Carving-Project

For the Bonus part (i.e. finding horizontal seams to reduce the image both in height and width), we implemented
one primary function called flip_RGB_image() which, as the name suggests, rotates the image by 90 degrees.
Thanks to this function we were able to apply the same processes we as before but this time with a rotated image. This
allowed us to find the usual vertical seams for the flipped images which corresponded to the horizontal seams on the
original image.

To implement this process we split it in two parts: the first one in which we identified the vertical seams on the original image
and the second where we did the same thing but with the flipped image. By rotating again the image and combining it with the first
one, we obtained a final image with both horizontal and vertical seams highlighted.

The process was very similar for removing these seams to scale the image. Again, we split the process in two parts: during the first
one we found and removed the vertical seams on the original image and then, in the second part, we flipped the resulting image
and applied the same process again to find and remove horizontal seams. Finally we flipped again the image to restore its former
orientation.



In the files extension.cpp and extension.h you will find quite some code that has been commented out. This is because, not satisfied
with the efficiency of our program, we tried to work out a better (faster) solution but didn't have enough time to obtain any
valuable result.
