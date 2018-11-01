# LoRa Bootcamp 2018 - Open, Long-Range IoT

Welcome to the LoRa Bootcamp hosted in conjunction with Semtech, MultiTech and Microsoft in Minneapolis on Nov 1st 2018. If you have any questions, please just give a shout. We are here to help.

The online reference for this document can be found at [bit.ly/lorabootcamp2018](bit.ly/lorabootcamp2018).

In this session you'll be building 3 examples:

1. Build a Blinky program with [Arm Mbed OS](https://os.mbed.com/).
1. Hooking up an optical particle sensor to a development board.
1. Connecting your device to Multitech Conduit AEP using LoRaWAN.

In the following sessions Microsoft and Multitech will show you how to send data to the Microsoft cloud service and then back down to the device by using the LoRa Class C device profile. 

In case you're stuck this document will help you get back on track. If you're a fast learner, there are 'extra credit'-assignments at the end of each section. Please help your neighbours as well :-)

## Prerequisites

1. Create an **Arm Mbed online account** [os.mbed.com/signup](https://os.mbed.com/account/signup/).
1. **Serial Terminal** - [Cool Term](https://freeware.the-meiers.org/). It works well on OSX / Windows. If you're on Linux you know what to do. baud rate is 115200, 8-n-1.

## Building the circuit

We're using the [L-TEK FF1705](https://os.mbed.com/platforms/L-TEK-FF1705/) development board, which contains the Multi-Tech xDot module and an optical particle sensor. Let's connect thes sensor and verify that the board works.

Grab the following items:

* Development board.
* Micro-USB cable.
* Optical particle sensor.
* 3x jumper wires.

The particle sensor needs to be placed upright and may need to be in a covered environment. In this workshop we can cover it with a piece of tape, so let us know if your readings are a little wonky. 

![Dust sensor ](https://www.github.com/armmbed/sxsw2018/raw/master/media/dust1.jpg)

To connect the particle sensor you use the yellow, red and black wires. We'll use the jumper wires to connect the sensor to the board (because we don't have Grove base shields).

Plug the jumper wires into the Grove connector, and connect:

* Red -> 5V
* Black -> GND
* Yellow -> GPIO3

![Wires](https://www.github.com/armmbed/sxsw2018/raw/master/media/dust2.jpg) 
![Wires](https://www.github.com/armmbed/sxsw2018/raw/master/media/dust3.jpg)


## 1. Blink the LED!

Now let's build a simple application which blinks the LED and prints it to the serial console. 

1. Go to [https://os.mbed.com](https://os.mbed.com) and sign up (or sign in).
1. Go to the [L-TEK FF1705](https://os.mbed.com/platforms/L-TEK-FF1705/) platform page and click *Add to your Mbed compiler*. OR just click [Here](https://os.mbed.com/platforms/L-TEK-FF1705/add/)

    ![Add to your Mbed compiler](https://www.github.com/armmbed/sxsw2018/raw/master/media/mbed1.png)

1. Import the example program into the Arm Mbed Compiler by clicking [this link](https://os.mbed.com/compiler/#import:https://github.com/armmbed/lorawan-bootcamp-2018).
1. Click *Import*.

    ![Importing the SXSW2018 repo](https://www.github.com/armmbed/sxsw2018/raw/master/media/mbed6.png)

1. In the top right corner make sure you selected 'L-TEK FF1705'.

    ![Select right platform](https://www.github.com/armmbed/sxsw2018/raw/master/media/mbed3.png)

This has cloned the repository. There are a few examples here, so let's switch between them.

1. Open `firmware/select_project.h`.
1. Change the project to `1`.

    ![Changing project](https://www.github.com/armmbed/sxsw2018/raw/master/media/mbed10.png)

1. To see the code, see `1_blinky/main.cpp`, it's pretty straight forward!
1. Click *Compile*.

    ![Compile](media/mbed4.png)

1. 1. A binary (.bin) file downloads, use drag-and-drop to drag the file to the DAPLINK device (like a USB mass storage device).

    **Note:** Here's a [video](https://youtu.be/L5TcmFFD0iw?t=1m25s).

1. When flashing is complete, hit the **RESET** button on the board (next to USB).

You should see the blue LED blink very fast. Your first program is running! Let's look at the logs now.

### Extra credit

The LED blinks automatically. But you can also make it user controlled through the push button on the board. To handle events coming from a physical device you can use interrupts. These fire off when the state of a physical switch changes. You can handle them as follows:

```cpp
void fall_handler() {
    // button is pressed
}

void rise_handler() {
    // button is no longer pressed
}

InterruptIn btn(BUTTON1);

int main() {
    btn.fall(&fall_handler);
    btn.rise(&rise_handler);
}
```

Change the code so that the LED responds to the button instead of through a timer.

## 1.5 Show Debug Printf logs

If all is well, you should see something similar to:

```
Blink! LED is now 1
Blink! LED is now 0
Blink! LED is now 1
Blink! LED is now 0
Blink! LED is now 1
```

#### Windows

To see debug messages, install:

1. [Arm Mbed Windows serial driver](http://os.mbed.com/media/downloads/drivers/mbedWinSerial_16466.exe) - serial driver for the board.
    * See above for more instructions.
    * No need to install this if you're on Windows 10.
1. **Serial Terminal** - [Cool Term](https://freeware.the-meiers.org/). 

Make sure to change the baudrate under **Options**->**Baudrate** then press the **Connect** button at the top. 

#### OS/X

No need to install a driver. Use [Cool Term](https://freeware.the-meiers.org/). Make sure to change the port under **Options**->**Port** and change the baudrate to 115200. Then press Connect. 

#### Linux

If you're on linux you should know what to do, either use screen or minicom. The boards usually show up under `/dev/tty...`, make sure to use a baudrate of 115200 at 8-n-1 . 

## 2. Getting data from the dust sensor

Now let's grab some data from the dust sensor. Make sure you've connected it properly to your device, and that it's in an upright position (I feel like I'm an airline steward) in the box.

1. Go into `select_project.h` and change the project to `2`.
1. Inspect the code in `2_dust_sensor/main.cpp`.
1. Click *Compile*.
1. A file downloads, use drag-and-drop to drag the file to the DAPLINK device (like a USB mass storage device).

Inspect the logs on the device, and see the sensor counting dust particles. Blow into the sensor or spray something around the air to change it around. A measurement takes 30 seconds.

Your log messages should look like:

```
Start measuring...
lpo = 589396, r = 1.964653, c = 1015.913879 pcs/0.01cf
Start measuring...
lpo = 401956, r = 1.339853, c = 693.167725 pcs/0.01cf
```

The `c` value is the concentration of particles.

### Extra credit

Dust particles is just one of the things we can measure. How about temperature and humidity? We have some extra sensors with us that can do this. Grab one and see if you can change the program so that it measures both dust + temperature + humidity. The component page - which contains drivers and example code - for the sensor is [here](https://os.mbed.com/components/Grove-TempHumi-Sensor/).

### Extra credit (2)

We're blocking the main thread right now while we're waiting for the dust measurement to come in. That gets complicated very quickly when dealing with multiple sensors. To deal with this Mbed contains an RTOS - a real-time operating system - where you can spawn threads. That's very useful in these contexts. To spin up a new thread do this:

```cpp
void new_thread_main() {
    // run your code here
}

Thread new_thread;

int main() {
    new_thread.start(&new_thread_main);
}
```

Change the code so it runs the temperature and humidity measurements in a different thread.

## 3. Connecting to Multitech Conduit AEP

Now it's time to send this data to the internet over LoRaWAN.

1. Open `select_project.h` and change the project to 3.

Normally you would need an APP key and a session key, but in this instance for simplicities sake we are just going to hard code the keys into the example as 
```C
static std::string network_name = "MTS-DEMO";
static std::string network_passphrase = "MTS-DEMO";
static lora::NetworkType network_type = lora::PUBLIC_LORAWAN;
```

This is obviously bad practice, dont do this in real life. In real life for actual deployments you would use an app key and an EUI key and store them on secure storage so no one can hack you. Buuuuuuuuut, this is a workshop, so we're going with a simplification that just works. :-P

### Connecting to Multitech Conduit AEP

Do nothing, just compile and load the program. it should 'just work'. You can verify your device is working by checking the terminal output and asking the workshop lead to check for your device ID on the gateway. 


### Extra credit - relaying data back to the device

We only *send* messages to the network. But you can also relay data back to the device. To do this you have 2 options, if your device is class A then you can only send down to the device when its just sent something up. In this example we are using class C, so we can send data back down to the device whenever we want. The configuration changes to do that are as below:

```C
// Class C so multicast downlinks can be heard - Can be changed back to "A" for class A
dot->setClass("C");
        
```
**NOTE** the code in example 3 is already configured with the above, so dont change anything, just run compile and it'll work. 

### Extra Credit (2) - Multicast
Now that we have the device setup in class C mode we need to enable multicast (one sender many receivers). The code below enables this (again, this has already been enabled in your project, so this is just for reference)

```C
// add multicast keys
static uint8_t multicast_nsk[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static uint8_t multicast_dsk[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

// create multicast session information.
dot->setMulticastSession(1, 1, multicast_nsk, multicast_dsk);
```

In the `RadioEvents.h` file we have added handling code to handle multicast events. Specifically in this project if the gateway sends a `0xFF` or `0x00` it will turn the LED on or off respectively. Nothing fancy, but it demonstrates the point. The code snippet that enables that behavior is below. 

```C
if (flags->Bits.Rx) {

            printf("[INFO] Received %d bytes\n", info->RxBufferSize);
            if (info->RxBufferSize > 0) {
                // print RX data as string and hexadecimal
                std::string rx((const char*)info->RxBuffer, info->RxBufferSize);
                printf("[INFO] Rx data: [ %s ]\r\n", mts::Text::bin2hexString(info->RxBuffer, info->RxBufferSize).c_str());
                DigitalOut LED(PA_4);
                LED = ((0xFF & (info->RxBuffer[0] & 1)) > 0);
            }
        }
```

### Extra credit (3) - Sending temperature and humidity data

Particle count is just one thing. Change the code so that it also sends temperature and humidity data off another sensor. More information can be found in the extra credit section in 3.

CayenneLPP format already knows about temperature and humidity, so you can do:

```cpp
payload.addTemperature(2, 23.21f); // on channel 2, send temperature 23.21 degrees celcius
payload.addRelativeHumidity(3, 48.12f); // on channel 3, send 48.12 humidity
```
