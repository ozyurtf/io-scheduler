# IO Scheduler

Before starting, let's first explain the concept of IO operation. 

IO operation is basically the process of moving data from some external devices to the processor (CPU) and from the processor (CPU) to the external devices using some modules (codes) and buffers (temporary storage location in the CPU). That's why we can call these external devices as IO devices as well. 

In other words, IO devices are the components that allow the computer to communicate/interact with the outside environment. And CPU interacts with the outside world through this way. 

We can see the illustration of the IO devices below:

```

          Application  Monitor
              \         /
               \       /
Keyboard - Operating System - Mouse 
               /       \
              /         \
          Printer   Disk Drive

```

Some of the examples of IO devices are mouse, display, keyboard, disks, network, scanners, speakers, accelerators, GPUs, etc. 

And based on the type of operations they make, we can group these devices in three categories: 

#### Human Readable #### 
Printers, keyboards, mouses, terminals are some of the external devices that can be managed/read by humans directly. That's why these devices can be grouped under this category. As we might guess, these external devices are suitable for communicating with the user. 

#### Machine Readable #### 
Some of the machine readable external devices might be USB keys, sensors, controllers (?), and disk drives. Disk drives can be seen as IO devices because they read data from the disk platters and transfer this data to the CPU or main memory whenever this transfer is requested. And disk drives can be seen as a machine readable device because they store and retrieve data in a format that can be processed by a computer (machine) without human intervention.

#### Communication #### 
The external devices that are used for the communication between the computers and remote devices (?) can be grouped under this category. An example of these devices might be modems or digital line servers (?) 

Okay but who is managing these devices and the IO operations ? 

# Operating System and IO 

All these IO devices are controlled by the operating system. But how ? 
- The operating system sends commands to the IO devices to start an operation. These operations might be reading data from a USB key, writing data to the disk drive, or may be reading data from a mouse. These commands are sent through device drivers. Device drivers can be seen as software/programs/code that allows the operating system to interact with the external device without having to know the hardware of the external devices.
- Once these operations are done in the IO devices, these devices send a signal (interrupts) to the CPU to get its attention and warn it that the operation is done. The operating system is responsible from catching and handling these interrupts. But what if an error (e.g., communication timeouts, data corruption, device failures, etc.) happens and the IO operations are not completed as a result of this error ?

In those cases the operating system is responsible from detecting and handling these errors as well. Some ways to handle these errors might be retrying the operation, notifying the user about the error, etc.

