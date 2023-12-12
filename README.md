# MicroKernel for LPC2105 ARMv4 
## About The Project
Microkernel to enable the execution of the game Conecta4 on the LPC2105 processor written in C and Assembly language for the ARM4 architecture, all running on the Keil µVision5 emulator.

Conecta4 is a board game for two players, in which they place tokens on a vertical board with the objective of aligning four consecutive tokens of the same color. The goal of Conecta4 is to align four tokens on a 6x7 board, consisting of six rows and seven columns. Players take turns inserting a token into the column of their choice (provided it is not full), and it will fall to the lowest position. The player who successfully aligns four consecutive tokens of the same color in a horizontal, vertical, or diagonal direction wins the game. If all columns are filled, but no player has created a valid row, the game is a draw.

To achieve this system, a three-level abstraction architecture has been implemented. At the lowest level is the Hardware Abstraction Layer (HAL), responsible for managing the hardware. The intermediate level contains the managers, responsible for peripheral logic and interaction with the game, along with a Middleware that manages game interaction. The highest level features the application executing the microkernel through the scheduler, in this case, the game. The scheduler consists of two queues: an event queue and a message queue. The user interacts with the game and receives feedback through the serial line (UART0) and GPIO. Various peripherals such as TIMER0, TIMER1, the WATCH DOG, and the REAL TIME CLOCK are utilized, along with different types of interrupts and system calls.

The scheduler is the central element of the system, as it takes necessary actions based on received events and messages. It has two queues: one for managing system events and another for communication between different system modules through message passing. The scheduler controls peripherals, alarms, timing, system shutdown or restart, and other game actions through the abstraction interface provided by the managers. If there are no events or messages to process, the scheduler enters IDLE mode to conserve energy; if more than 10 seconds pass without activity, it enters PowerDown mode. In the event of a system hang, the WatchDog automatically triggers a system reboot.

The Hardware Abstraction Layer (HAL) is used to abstract higher layers from the configuration and usage of peripherals. Peripherals used in this case include Timer0, used for periodic event queuing; Timer1, used to measure elapsed time; WatchDog, used to monitor system hangs and restart if necessary; RTC (Real Time Clock), used to measure elapsed time during the game; buttons, used for making and canceling moves through GPIO interrupts; GPIO, used for connecting input and output elements like LEDs or buttons; and UART0, used to control serial ports and devices and display a game interface


This project was made for the Hardware Project Subject of Universidad de Zaragoza.


![Microkernel](./microkernel.png)


### Installation and usage

1. Download the Keil µVision5 IDE.
2. Put all files in the same directory.
3. Run and check the IDE [Documentation](https://developer.arm.com/documentation/101407/latest/) for usage.


## Version History 

* 0.1
    * Initial Release

## Authors 

* **Raúl.D**
* **Ibón Cañete**
* **Universidad de Zaragoza**

## License

This project is [LICENSED](LICENSE) check the file for details.

