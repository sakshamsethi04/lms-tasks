fault : the esp32 may restart when the motors start.

PROBABLE CAUSES:

the esp 32 may reset when the motors start due to a voltage dip caused by the motors as the motors draw a high current when starting .
the wires of the motors and the wires connected to esp might be strapped to each other which might cause electrical noise and might cause the restarting ..
loose connections too might cause the same.


DIAGNOSTIC CHECKS: 

i would first disconnect the motor's pwoer supply and then start the bot (as withot motors whenever the motor starts the l298N also makes a sound through which we can confirm if the esp is restarting or not)
once this diagnostic check is done , i would check for loose connections , and measure the esp32 supply voltage before and after the motors start using a multimeter..


FIXES: 

to fix this i would first correct all lose connections.. i would then make different bundles of gpio wires and wires connected to the motors 
i would use a seperate buck converter to power the esp 32 to provide a better power supply independent of motor related dips .. 