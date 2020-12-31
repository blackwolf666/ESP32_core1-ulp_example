# ESP32_core1-ulp_example
How to set up and execute tasks on ULP core while both cores are active

The Ultra Low Processor (ULP) it's normally off. You can use it to perform (simple) tasks, while the main cores are busy.

It is possible to program the ULP via C macros, defined in the standard toolchain, or via the dedicated ESP-IDF ULP toolchain.


In this example, we create two task, one per core, to blink a LED on GPIO [0] and GPIO[4], while the ULP blinks the onboard GPIO[2]
