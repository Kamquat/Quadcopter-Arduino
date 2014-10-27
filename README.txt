Quadcopter-Arduino
===================
To properly use these files using the arduino IDE:

NOTE: Changed Project folder structure. To get running in the Arduino IDE, copy files from Github
repository to Documents -> Arduino. Replace all files after doing this.


------- Notable mile-stones


In Progress:
	[X]Reading from IMU
	[]Calculating Orientation from IMU

TODO:
	[]Send motor outputs
	[]Convert difference between orientation/desired orientation to motor outputs
	
--------[]Stable Flight

	[]Interpret Remote inputs

--------[]Controlled Flight

Stretch goals:

	[]Include compass to help control Azimuth
	[]Include barometer to help control altitude
	[]Add sonar sensor to add height reading


--------[]Add auto-land feature

	[]Add video transmitter / camera

	[]Add data transceiver

--------[]Add GPS



NOTES:

	ESC's
------------------------------------------------------------------------------------
	1ms pulse = 0% throttle.
	2ms pulse = 100% throttle.
	This is true regardless of what frequency the esc is updated at.
	Four our purposes, updating at 480Hz would be best, though no higher than 500Hz 
	THE ABOVE MAY CHANGE WITH THE SIMONK FLASH, WILL NEED TO TEST AGAIN. Video tutorial on flashing SimonK https://www.youtube.com/watch?v=I7a0vK7a7aA
	The red wire in the center of the logic cables of each ESC is the 5V rail. Apparently these are known to fail
		and output 11V-15V. DO NOT CONNECT TO ARDUINO OR OTHER DEVICES.

--------------------------------------------------------------------------------------

	
	
	