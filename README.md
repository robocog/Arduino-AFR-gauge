# Arduino-AFR-gauge
Arduino AFR gage and screen for wideband controller


I wanted to see what the output was from my Spartan2 wideband controller without the need for laptop or logging


This has been installed in my car for a few months and has worked flawlessly and seems to be accurate and fast enough


I wanted initially to just drive an inexpensive narrowband analog gauge, but it evolved to also drive an SSD1306 screen to show the AFR and the controllers output voltage


This is my first project on here - so please be gentle whilst I work my way round the navigation

The code needs a good clean up as there is stuff in there from when I was trying to make it work 

(intially used a PWM output direct from the arduino to drive the gauge, but the gauge let me know it wasn't entirely happy with that situation, which is why I went with the DAC)

I have a couple of int's in there that are not used, along with old code from when I drove the gauge direct

I will get round to cleaning stuff up and making the comments a bit more comprehensive

I would also like to add more functionality to aid setting up the min and max for the gauge, and "calibrating" the input from the Spartan2 wideband as it puts out 2 known voltages when the unit is first powered up (1.666v for 3 secs, then 3.333v for another 3 seconds before showing the sensors data)
...I am sure something clever could be done with this to try and reduce voltage offsets that may occur between the sensor/controller and this ... rather than fudging values and re trying till it shows values as expected
