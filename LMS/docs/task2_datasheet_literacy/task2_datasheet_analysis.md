DATASHEET ANALYSIS OF ESP32 WROOM 

esp32 from robu.in
Document: ESP32-WROOM-32 Datasheet
Source: https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf

the recommended operating conditions of esp32 wroom is 
minimum of 3V and maximum of 3.6V , with a typical of 3.3V

the operating ambient temperature is minimum of -40 and maximum
of 85 degree celsius 

the minimum voltage for digitalHIGH is 0.75 times of the reference, take 3.3V supply so it is 0.75*3.3=2.475V
and atmost 0.25 times of the 3.3V supply is called digitalLOW
that is 3.3*0.25=0.825V

Supplying a voltage above the esp32's permitted limit can damage the module. This may happen due to an incorrectly selected power supply or a voltage spike.

there is a voltage regulator already in the esp32(AMS1117) but it may also fry if voltage is too much 
To prevent this, use a suitable power supply and ensure that its voltage remains within the board's specified limits.