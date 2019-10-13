# Arduino code for the BOX

![The BOX](https://github.com/dolby360/Temperature-distance-screen-Arduino/blob/master/The%20BOX.jpeg?raw=true)

### link to youtube video (Hebrew)
[link to youtube](https://www.youtube.com/watch?v=Jsip-A6hjkM&t=2s)

<br/>
I develop this program on visual studio and I used platformIO so if you try to run this I recommend to do the same setup.<br/>

## Short brief about the architecture and implementation 

### main
Initialize all components and handle the interrupt, also call the main notification function, we will get to the design pattern latter, but notice that in the main loop we call just one method.

### distanceSensor
In every loop I sample the sensor and save the result in a circular buffer, and every time I fill the buffer the avg recalculated.

### led
Check if the temperature is out of threshold, if so turn on a red led.

### screen
Screen is sort of the manager of the program, it have states and always asks for data to show.

### temperature
Well store the temperature and humidity 

### wifi
Handle all the remote queries from the phone, singleton design pattern.

### timer
Observer design pattern to simulate a scheduler you can learn more about the observer DP here:
[observer](https://sourcemaking.com/design_patterns/observer)

