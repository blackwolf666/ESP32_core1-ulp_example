# ESP32_core1-ulp_example
How to set up and execute tasks on ULP core while core1 is active

The Ultra Low Processor (ULP) it's normally off. You can use it to perform (simple) tasks, while the main cores are busy.

It is possible to program the ULP via C macros, defined in the standard toolchain, or via the dedicated ESP-IDF ULP toolchain.
