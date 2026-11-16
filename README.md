# Lab11
# By: Jackie Herrick
# Date: 11/05/26 
  # a. Overview 
    # Lab11
      # A program in the starter repository (mandel) has been provided that features a command-line interface which allows 
      # adjustment of various parameters and will then generate a Mandelbrot set visualization and save it to a jpeg file. 
    # mandel
      # creates a picture of the Mandelbrot fractal and saves it as a JPEG image.
    # jpegrw
      # a  program in the starter repository (mandel) has been provided that features a command line interface which allows 
      # adjustment of various parameters and will then generate a Mandelbrot set visualization and save it to a jpeg file. 
  # b. How to build the program
    # Lab11
      # 
    # mandel
      # 
    # jpegrw
      # 
      
  # c. How to run the program – available command-line options
    # Lab11
      #  gcc Lab11.c -o Lab11 -lm
      # time ./Lab11 Number_Processors
      # ffmpeg -i mandel%d.jpg mandel.mpg
      # i = frames per seconds
    # mandel
      # gcc -o mandel mandel.c  jpegrw -ljpeg
    # jpegrw
      # gcc -o mandel mandel.c  jpegrw.c -ljpeg
      # ./mandel
