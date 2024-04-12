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

We can also group IO devices in two categories: **block devices** and **character devices**. 

**Block devices** store the information in units that are fixed-size. These units are called blocks. The size of these blocks is predetermined (e.g., 512 bytes). Here even if only a small portion of data is needed, the whole block that consists that portion is retrieved. Each of these blocks has a unique address. And these addresses identify the location of these blocks on the device. Through this way, blocks can be accessed. 

When reading from a block, the system specifies the starting block address and also how many blocks to read. Then the IO device transfers the requested blocks to the system's memory. And when writing to the block, the system specifies the startinb block address. Then the IO device writes the data to the specified block.

**Hard disks**, **CD-ROMs**, **USB sticks** can be given as examples of block devices because these devices store the data in fixed-size blocks. 

**Character devices**, on the other hand, processes the data in a sequential manner. Unlike block devices, they do not store the information in fixed-size units. And because data is processed one character or one byte at a time sequentially and it is not stored in fixed-size units, these devices do not have addressing scheme. And that's why they are not addressable. You can't access a specific charcater or byte by its address for example.

Some examples of character devices are: **keyboards**, **mice**, **printers**, **network interfaces (?)**

One note is that IO devices are separate hardware components. These are connected to the CPU through a bus or other communication channels. But there are also some other devices that are directly integrated to the CPU. These are called accelerators. 

Unlike IO devices that are typically accessed through an interface such as APIs, the accelerators can be invoked by applications with CPU instructions or registers without utilizing the traditional IO path through the operating system. 

In addition, the IO devices such as keyboards, mouses, etc. are designed for data input, output and storage of the data while accelerators are the devices that are designed to perform specific computational tasks. For example, an encryiption device which is an accelerator can generate secure keys using random number generators. 
A compression device, which is another accelerator, applies a specific compression algorithm to the input data.

So in summary, we can think the accelerators more like a functional unit in the CPU and less like an IO device. 

Okay but who is managing these devices and the IO operations ? 

# Operating System and IO 

All these IO devices are controlled by the operating system. But how ? 
- The operating system sends commands to the IO devices to start an operation. These operations might be reading data from a USB key, writing data to the disk drive, or may be reading data from a mouse. These commands are sent through device drivers. Device drivers can be seen as software/programs/code that allows the operating system to interact with the external device without having to know the hardware of the external devices.
- Once these operations are done in the IO devices, these devices send a signal (interrupts) to the CPU to get its attention and warn it that the operation is done. The operating system is responsible from catching and handling these interrupts. But what if an error (e.g., communication timeouts, data corruption, device failures, etc.) happens and the IO operations are not completed as a result of this error ?

In those cases the operating system is responsible from detecting and handling these errors as well. Some ways to handle these errors might be retrying the operation, notifying the user about the error, etc.

Operating system plays the role of an interface/layer (set of rules, and protocols that govern the exchange of data and commands between the operating system, applications and hardware devices) between the devices and the rest of the system. 

```
-------------------
   Applications     
-------------------
  read(), write()   
-------------------
   File System*
-------------------
 Operating System
-------------------
Low-Level Interface
-------------------
    IO Devices
-------------------

At the top level of this hieararchy, there are applications which are basically programs that perform specific tasks and interact with the file system to read and write data. And this reading and writing operations are done with the read() and write() system calls.

File system is a data structure that is used by the operating system to organize, store, and retrieve files/directories on a storage device. It provides a set of rules for these kinds of operations. It handles some tasks such as file creation, deletion, renaming, and permissions management. It also maintains metadata about files/directories. When read or write request is made, the file system translates these operations into a low-level operations that the operating system can understand.

And the operating system provides commands to the low-level interface. It allows the file system to interact with the hardware. Memory management, process scheduling are handled in here.

Low-level interface is responsible from communicating with the IO devices such as monitors, mouses, disk drives.

```
Now let's talk about the challenges behind managing IO devices.

# IO Devices: Challenges

Different IO devices perform a wide range of different tasks. 

Some of these devices might be input devices such as keyboard, mouse, or scanner since they receive input from the user. Some of them, such as printers, speakers, display might be labeled as output devices since they show some kind of output to the users. 

And some of these devices such as hard disk drive, solid state drive, etc. might be storage devices.

In addition the components with wich these IO devices communicate with may show great differences as well. For example, we can observe device-to-device, device-to-system, device-to-application, or device-to-user partnerships. 

The rate at which they transfer data may be different across different IO devices as well. 

All of these diversities makes it very hard to design a single interface and management system valid for all the IO devices (expandability).

Another challenge is designing an IO system. For instance, it is hard to design an IO system that is flexible and that can accept the new devices or that can scale as needed (expandability). 

Adding the ability to handle device failures and maintain data integrity to the IO system (resilience) is difficult as well. 

Also, different IO devices are used by different users. And each of these users may have different requirements. Designing an IO system that meets all of these requirements and expectations might be challenging. 

The performance of the IO is affected by many different factors: 
- the time it takes to access data from an IO device (access latency)
- the amount of data transferred from the IO device to the system or from system to the IO device in a given time period (throughput)
- the type and speed of the communication channel (e.g., bus, network) between the IO devices and the system.
- the organization and management of different memory channels (e.g., cache, main memory, storage) (memory hierarchy)
- the operating system (it plays an important role in terms of managing IO devices, and scheduling IO operations)

```
-------------                  Interrupts
| Processor |----------------------------------------------          
-------------          |                 |                |       
      |                |                 |                |        
-------------          |                 |                |
|   Cache   |          |                 |                |
-------------          |                 |                |
      |                |                 |                |
------------------------------------------------------------------
|                     Memory IO Interconnect                     |          
------------------------------------------------------------------
      |              |  |              |  |              | | 
------------    --------------    --------------    --------------
|   Main   |    |    I/O     |    |    I/O     |    |    I/O     |
|  Memory  |    | Controller |    | Controller |    | Controller | 
------------    --------------    --------------    --------------
                  |       |             |                 |
                  |       |             |                 |
                Disk     Disk        Graphics          Network
                                      Output                            

```

Memory IO interconnect is a data communication channel (like bus). It is a hardware component and it consists of a set of parallel wires on the motherboard along with supporting circuitry and protocols. These wires carry electrical signals and through these signals data, address, and signals are carried between the CPU, memory, and IO devices, and communication between these components is handled this way. 

IO controller, also known as peripheral controller, is another hardware component. It manages the communication and data transfer between the CPU and IO devices such as disk, network. It acts like an intermediate layer between the IO devices and CPU and through this way the CPU doesn't have to control & communicate with the IO devices directly. 

```

                                  --------------    ---------------    ----------------
                                  |  Monitor   |    |  Keyboard   |    |  Hard Disk   |  
                                  |            |    |             |    |    Drive     | 
                                  --------------    ---------------    ----------------
                                         |                 |                  | 
------------    --------------    --------------    --------------    ----------------
|   Main   |    |    CPU     |    |   Video    |    |  Keyboard  |    |   Hard Disk  |
|  Memory  |    |            |    | Controller |    | Controller |    |   Controller |  
------------    --------------    --------------    --------------    ----------------
     |                |                  |                 |                  |
     |                |                  |                 |                  |
-------------------------------------------------------------------------------------------
|                                            Bus                                          |
-------------------------------------------------------------------------------------------

```

As we can see above, IO controllers are physically connected to the memory IO interconnect (bus) on the motherboard. They have dedicated interfaces and ports that plug into the bus and this allows the IO controllers to send and receive signals over the bus. They communicate with the memory and CPU through this bus. The bus in here enables the exchange of data and signals between IO controllers and the rest of the system.

When the CPU needs to communicate with keyboard, for instance, it sends commands and data to the keyboard controller over the bus. The keyboard controller receives these commands and data from the bus and translates them into the keyboard-specific signals and protocols. Similarly, when the keyboard needs to send data to the CPU or memory, the keyboard controller receives the data from the keyboard and sends it over the bus to the CPU or main memory.

One note is that IO controllers can generate interrupts to notify the CPU about important events. For example, while a code is running in the program, if the user clicks the interrupt button with his mouse and interrupts the running of the program, or if an IO operation is completed naturally, the interrupts are generated and the IO controllers send these interrupt signals to the CPU using the bus. Once the CPU receives these interrupt signals, it invokes the appropriate interrupt handler routine to process the interrupt and then communicate with the IO controller.















