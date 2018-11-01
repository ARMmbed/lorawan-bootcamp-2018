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

We need to program some keys in the device. LoRaWAN uses an end-to-end encryption scheme that uses two session keys. The network server holds one key, and the application server holds the other. (In this tutorial, TTN fulfils both roles). These session keys are created when the device joins the network. For the initial authentication with the network, the application needs its device EUI, the EUI of the application it wants to join (referred to as the application EUI) and a preshared key (the application key).


### Connecting to Multitech Conduit AEP

Change AppKey
Change NetworkKey


#### Pasting them in the Online Compiler

In the Online Compiler now open `firmware/src/ttn_config.h`, and paste the Application EUI and Application Key in:

![Put in the keys](media/mbed7.png)

**Note:** Do not forget the `;` after pasting.

Now click *Compile* and flash the application to your board again. The board should now connect to The Things Network. Inspect the *Data* tab in the TTN console to see the device connecting. You should first see a 'join request', then a 'join accept', and then data flowing in.

![console-data](media/console-data.png)

**Note:** Device not joining? Maybe your EUI is wrong, they're hard to read. On the serial console the EUI is printed. Check if it's the same as in the TTN console. Wrong? Click *Edit* in the TTN console and update the EUI.

### Extra credit - relaying data back to the device

We only *send* messages to the network. But you can also relay data back to the device. Note that LoRaWAN devices can only receive messages when a RX window is open. This RX window opens right after a transmission, so you can only relay data back to the device right after sending.

To send some data to the device:

1. Open the device page in the TTN console.
1. Under 'Downlink', enter some data under 'Payload' and click *Send*.
1. Inspect the logs on the device to see the device receive the message - note that messages are not guaranteed to end up at the device. The 'Confirmed' flag can help if this is a necessity.

Now let's do something useful... Control the LED on the board over LoRaWAN.

Look at `RadioEvent.h` to the line where the messages are received. Now change the behavior so that the LED toggles on/off quickly after a message is received.

*Disabling LED sleep behavior*

The LED still turns off when the device goes into sleep. This is a power-saving measurement. To disable sleep behavior for the LED:

1. In `dot_util.cpp` change:

    ```cpp
        if (dot->getWakePin() != GPIO0 || dot->getWakeMode() == mDot::RTC_ALARM) {
            GPIO_InitStruct.Pin = GPIO_PIN_4;
            GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        }
    ```

    into:

    ```cpp
        if (dot->getWakePin() != GPIO0 || dot->getWakeMode() == mDot::RTC_ALARM) {
            // GPIO_InitStruct.Pin = GPIO_PIN_4;
            // GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
            // GPIO_InitStruct.Pull = GPIO_NOPULL;
            // HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        }
    ```

1. In `dot_util.cpp` change:

    ```cpp
    // PB_0, PB_1, PB_3 & PB_4 to analog nopull
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    ```

    into:

    ```cpp
    // PB_0, PB_1, PB_3 & PB_4 to analog nopull
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3; // | GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    ```

1. Those changes will no longer shut down the LED when the device is asleep.

### Extra credit (2) - Sending temperature and humidity data

Particle count is just one thing. Change the code so that it also sends temperature and humidity data off another sensor. More information can be found in the extra credit section in 3.

CayenneLPP format already knows about temperature and humidity, so you can do:

```cpp
payload.addTemperature(2, 23.21f); // on channel 2, send temperature 23.21 degrees celcius
payload.addRelativeHumidity(3, 48.12f); // on channel 3, send 48.12 humidity
```

**Extra credit (2) - Temperature / humidity data**

Remember the temperature and humidity sensors from 3. and 4.? Add that information to the map as well. Look in `maps.js` to see how we do the graphing (it's pretty simple). Data is being sent over a websocket to the browser (see `server.js`). Handle the events and update the graph accordingly.



Done already? Go do some extra credit work!

**Add coverage**

Setting up a gateway is easy. The recommended option is the highly configurable [MultiTech Conduit](https://www.digikey.com/en/product-highlight/m/multi-tech-systems/iot-platform); you need an `MTAC-LORA-915` or `MTAC-LORA-868` depending [on your country](https://www.thethingsnetwork.org/docs/lorawan/frequencies-by-country.html), as well as a `MTCDT` Conduit;

