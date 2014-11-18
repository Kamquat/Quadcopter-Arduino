NOTE: The updated code will require a change in the following location:
Program Files (x86)\Arduino\hardware\arduino\sam\variants\arduino_due_x\variant.h
change PWM_FREQUENCY from 1000 to 500, otherwise the motors will not output good signals




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
		DO NOT RUN ESC'S AT LOW POWER
		top - signal
		middle - power
		bottom - ground
		only need 1 power and 1 ground
				

		min - 1.0ms (dependent on trim setting for channels 1-4)	
		max - 1.8ms (dependent on trim setting for channels 1-4)
		period 20ms
		Heli1 mode	
		Stick setting mode 2
		Throttle reverse - False
		Channel 1 - RS Left/Right - TBD
		Channel 2 - RS Up/Down - max/min   
		Channel 3 - LS Up/Down - max/min
		Channel 4 - LS Left/Right - min/max
		Channel 5 - Defined
		Channel 6 - Flight Mode/Aux3
		Channel 7 - Defined
		Channel 8 - Defined
		Channel 9 - Battery level (not for LiPo)

		Gear/Right Bumper  		Up/Down - 1ms/1.84ms
		Pitch Trim/Aux2  		cw/ccw - 1.28/1.44
		Throttle Hold/Left Trigger  	Up/Down - 1.84/1.00
		Hover Throttle/Right Knob	cc/ccw - 1.84/1.00
		Hover Pitch/TL Knob		cc/ccw - 1.84/1.00
		/Left Bumper
		Flight Mode/Aux3		N/1/2  - 1.00/1.44/1.84