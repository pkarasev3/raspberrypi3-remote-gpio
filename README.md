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
  Connecting the pins is slightly non-trivial; the raspi3 pin 17 corresponds to GPIO "0" as in the photo here:
  ![raspi3 pin17 == gpio0](https://github.com/pkarasev3/raspberrypi3-remote-gpio/blob/master/images/raspi3-pin17-gpio0.jpg)

# # #
