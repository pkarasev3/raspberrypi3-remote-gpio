# raspberrypi3-remote-gpio
simple demo project with remotely set GPIO output on pi3 controlled via tcpip server + client.

authors:  Daniel Greidinger & Peter Karasev,  October 2017

# # #
  # # #
      Basic Instructions: install prerequisites (boost, wiringPi) on the raspi3. Build with cmake. 
      On pi3:  run LEDServer executable. 
      On another PC:  run LEDClient executable. 
      Note: if building on a non-raspi3 platform, the LEDServer will insert dummy functions in place of wiringPi calls. 
  # # #
# # #
