# Flight Recorder for

# Rocket

```
By Kirk Perkins and Walter Guevara
Designed for Physics and Electronics Class
```

## What is a flight recorder?

```
● A flight recorder observes the data from when a plane take off to when lands
● The recorder uses sensors to be able to tell how far the aircraft has flown and how fast
● It is often used to find out reasons for aircraft crashes
```

## Why did we do this?

```
● Students in the Star Prep Academy Physics class wanted to record the distance traveled
from a bottle rocket based on its acceleration
● To do this, we wanted to save the rocket's acceleration onto an SD card using an
acceleration
```

## The Sensor we are using

We have chosen the MPU6050 Accelerometer to be able to measure acceleration in Least
Significant Bit (LSB) to calculate how fast and how far the rocket has traveled.


## Problems with the MPU

```
● LSB is difficult to translate into real world data
● Raw data from the accelerometer is too sensitive
● Limit of 100 readings per second
```

## Solutions to these issues

```
● By collecting samples and averaging them we can smooth the data into something
readable
● We can also convert LSB to Gforce to create real world data
```




## Board Code

1. Accesses SD card and creates a CSV file
2. Tells the MPU which axis to read and the frequency of reading using memory addresses
3. Beeps to confirm that SD card was successfully detected
4. Waits for the button to be pressed to record data
5. Plays tone to mark that data will begin to record
6. Averages MPU accelerometer data and matches each reading with a corresponding
    microsecond and than prints the values to the SD card
7. It will beep if the SD card fails or is no longer detected
8. If you push the button again the readings will stop and a tone will play letting the user
    know that the MPU has stopped printing to the SD card


## Issues with the code

```
● At first, one of the clear things that needed to happen was propper averaging. An issue
arose where the system could only do so many readings at one time.
● This was solved by changing the clock speed of the MPU and use its built in averaging
function which was much more simple instead of making the function from scratch using
data from Kurt Seifert and Oscar Camacho from Freescale Semiconductor, Inc
```

## Test Data Results and Conclusion

```
● After a long and grueling school year of testing, recoding, and bug fixing, we were finally
able to get the system working and recording all relevant data
```

