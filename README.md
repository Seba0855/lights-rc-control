# Outdoor lighting control unit
### A control unit based on Arduino Nano, that can be controlled either by RC remote or motion sensor.

<br>

## Summary
A simple project that I made to control my outdoor lights when it's dark outside.


## How it works
The project was designed to be controled by a motion sensor or a RC remote.

Motion sensor here is for detecting a person or a car moving around yard in order to switch on the lights. For practical reasons, the duration of how long lights are on is fully based on motion sensor output. Light intensity on which motion sensor starts detecting objects and the duration can be set directly on the sensor itself, so there was no need to include it in code.

There are two light rails on my yard (under a shed and on a terrace) which I can control individually by using RC remote, or both rails are powered when an object is detected by a motion sensor.

## How it looks inside
<details>
  <img src='https://i.imgur.com/igzxbFq.jpg'>
</details>

## Components used
* <a href='https://botland.com.pl/moduly-radiowe/3698-modul-radiowy-cc1101-433-mhz-transceiver-tht-z-antena-5904422359393.html'>CC1101 433 MHz RC Module</a>
* <a href='https://botland.com.pl/arduino-seria-nano-oryginalne-plytki/12960-arduino-nano-a000005-7630049200173.html'>Arduino Nano</a>
* <a href='https://botland.com.pl/moduly-przekaznikow/14266-modul-przekaznikow-iduino-2-kanaly-z-optoizolacja-styki-10a250vac-cewka-5v-5903351242332.html'>Double channel relay module</a>
* Outdoor PIR motion sensor
* Some voltage regulators and breakers 

---

#### About
This was one of my first practical projects on Arduino that I actually use on a daily basis. I made it in November 2020, but uploaded on GitHub in 2022. 
