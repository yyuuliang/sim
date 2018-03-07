Send command

Now it is time to send OBD request. Real-time parameters are accessed through Mode 1 (also called “Service $01”), and each parameter has a Parameter ID, or PID for short. All commands can be found in the following page’s Mode 1 list. 
https://en.wikipedia.org/wiki/OBD-II_PIDs

For example, we want to know vehicle speed. First search the list for “Vehicle speed”, we found this:
0D	13	1	Vehicle speed	0	255	km/h	A

0D is the command to send, since we are using mode 1, the complete command is: “010D”, 13 is decimal conversion of “0D”, 1 is the Data bytes returned, which means we are expecting 1 byte data return. 

>010D
1 0D FF

We send “010D” and get a response 1 0D FF. Again, 1 is the mode number, 0D is the PID, the last byte FF is the return value. Convert it to decimal value, we get 0xFF = 255 km/h.

Another example, let’s request RPM. first search the mode 1 list for “RPM”, we get 
0C	12	2	Engine RPM	0	16,383.75	rpm	(256A+B)/4
We notice the command is 12, and it will return 2 bye. The last column is the equation to calculate the final value. 

>010C
41 0C 0F A0

In the above example, we get A = 0F and B = A0, the final rpm is (256x15 + 160)/4 = 1000 rpm


node sim.js


sim2.js is modified to be used in terminal environment

        
To start the simulation, open a new ternimal, then type 
node sim2.js

It will start a socket server. Address is localhost, port is 35000.

Start another terminal, using the following command to start a socket connection
nc localhost 35000

Try the commands we discussed above, e.g., 010D. The return value is 10D61. So the vehicle speed is 61 km/h.

Try command “ 010C”, the return value is 10C1485, then RPM is 1313.25 rpm. 


