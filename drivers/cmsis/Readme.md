# CMSIS Version Version 5.7.0

Thin clone of https://github.com/ARM-software/CMSIS_5/  

The [documentation](http://arm-software.github.io/CMSIS_5/General/html/index.html) is available under http://arm-software.github.io/CMSIS_5/General/html/index.html  

## Overview of CMSIS Components

The following is an list of all CMSIS components are part of this "thin clone"

| CMSIS-... | Target Processors   | Description  |
|:----------|:--------------------|:-------------|
|[Core(M)](http://arm-software.github.io/CMSIS_5/Core/html/index.html)  | All Cortex-M, SecurCore | Standardized API for the Cortex-M processor core and peripherals. Includes intrinsic functions for Cortex-M4/M7/M33/M35P SIMD instructions.|
|[Driver](http://arm-software.github.io/CMSIS_5/Driver/html/index.html) | All Cortex-M, SecurCore | Generic peripheral driver interfaces for middleware. Connects microcontroller peripherals with middleware that implements for example communication stacks, file systems, or graphic user interfaces.|
|[DSP](http://arm-software.github.io/CMSIS_5/DSP/html/index.html)       | All Cortex-M | DSP library collection with over 60 Functions for various data types: fixed-point (fractional q7, q15, q31) and single precision floating-point (32-bit). Implementations optimized for the SIMD instruction set are available for Cortex-M4/M7/M33/M35P.|
|[NN](http://arm-software.github.io/CMSIS_5/NN/html/index.html)        | All Cortex-M | Collection of efficient neural network kernels developed to maximize the performance and minimize the memory footprint on Cortex-M processor cores.|
|[RTOS v1](http://arm-software.github.io/CMSIS_5/RTOS/html/index.html) | Cortex-M0/M0+/M3/M4/M7 | Common API for real-time operating systems along with a reference implementation based on RTX. It enables software components that can work across multiple RTOS systems.|
|[DAP](http://arm-software.github.io/CMSIS_5/DAP/html/index.html)      | All Cortex | Firmware for a debug unit that interfaces to the CoreSight Debug Access Port. |