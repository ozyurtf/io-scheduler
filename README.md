# IO Scheduler

Before starting, let's first explain the concept of IO operation. 

**IO operation** is basically the process of **moving data** from **some external devices** to the **processor (CPU)** and from the **processor (CPU)** to the **external devices** using **modules (codes)** and **buffers (temporary storage location in the CPU).** That's why we can call these external devices as IO devices as well because they do an IO operation. 

In addition, **IO devices** are the components that **allow** the computer to **communicate/interact with the outside environment**. The CPU interacts with the outside world through this way. 

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

And based on the **type of operations they make**, we can **group** these devices in **three categories**: 

### 1) Human Readable ###
**Printers, keyboards, mouses, terminals, video displays** are some of the IO devices that can be managed/read by humans directly. That's why these devices can be grouped under this category. As we might guess, these IO devices are **suitable for communicating with the user**. 

### 2) Machine Readable ### 
Some of the examples of machine readable external devices are **USB keys, sensors, IO device controllers, and disk drives.** 

Disk drive can be seen as an IO device because they **read data from the disk platters** and **transfer this data to the CPU** or **main memory** whenever this transfer is requested. And disk drives can be seen as a **machine readable** device because **they store and retrieve data in a format that can be processed by a computer (machine) without human intervention**.

### 3) Communication ###
The IO devices that are used for the **communication between the computers and remote devices** can be grouped under this category. An example of these devices might be **modems** or **digital line servers** 

Aside from these 3 categories, we can group the IO devices under two categories depending on how they process the information: **block devices** and **character devices**.

**Block devices**, for example, **store** the **information in units that are fixed-size**. And **these fixed-size units are called blocks**. The **size** of these blocks is **predetermined** (e.g., 512 bytes). Even if only a small portion of data is needed, the **whole block** that consists that portion is retrieved. **Each** of these **blocks** has a **unique address**. And these **addresses** **identify** the **location of these blocks on the IO device**. The blocks can be accessed through this way. 

For instance, when reading from a block, the **system specifies the starting block address** and also **how many blocks to read** after the starting block. Then **the IO device transfers the requested blocks to the system's memory**. 

When **writing to the block**, on the other hand, the system **specifies the starting block address**. Then the **IO device writes the data** to the **specified block**.

**Hard disks**, **CD-ROMs**, **USB sticks** can be given as examples of **block devices** because **these devices** **store the data** in **fixed-size blocks**. 

**Character devices**, on the other hand, **processes the data** in a **sequential manner**. Unlike block devices, they **do not store the information in fixed-size units**. **Data** is **processed one character** or **one byte at a time** sequentially and it is **not stored in fixed-size units**. Therefore, **these devices do not have addressing scheme**. In other words, they are **not addressable**. So you **can't access a specific charcater or byte by its address** for example.

Some examples of character devices are: **keyboards**, **mice**, **printers**, **network interfaces** _(Network interface is a hardware component. It provides a physical interface between the device and Wi-Fi signals and allows the computer to connect to a network)_

One note is that **IO devices** are **separate hardware components**. These are **connected** to the **CPU** through a **bus** or **other communication channels**. But there are also some **other devices that are integrated to the CPU**. These are called **accelerators**. They contain **arithmetic logic unit** (it performs arithmetic & logical operations), **control unit** (it fetches and decodes instructions and controls the operation of the CPU), **registers** (these are temporary storage locations for data and addresses that are used during the execution of an instruction) and **cache** (small and fast storing unit that is used to store frequently accessed data and instructions). 

**Accelerators** are **more tightly integrated** to the **CPU** through a **high-speed interconnects or buses** and they can be **invoked** by **applications** with **CPU instructions** (?) or **registers** (?) without utilizing the traditional IO path through the operating system. 

In addition, the **traditional** **IO devices** such as **keyboards**, **mouses**, etc. are **designed** for **data input, output** and **storage of the data** while **accelerators** are the devices that are designed to **perform specific computational** tasks. 

For example, an **encryiption device**, which is an accelerator, can **generate secure keys** using random number generators. A **compression device**, which is another accelerator, **applies a specific compression algorithm to the input data**. Other examples of accelerators are GPUs and TPUs.

So in summary, we can think the **accelerators** more like a **functional unit** **in the CPU** and **less like an IO device**. 

Okay but who is managing the IO operations and all of these devices ? 

# Operating System and IO 

Operating system plays the role of an **interface/layer** _(set of rules, and protocols that govern the exchange of data and commands between the operating system, applications and hardware devices)_ **between the devices and the rest of the system**. 

And basically all these **IO devices** that are mentioned in previous section are **controlled** **by** the **operating system**. 

But how ? 
- The **operating system** **sends commands** to the **IO devices** to **start an operation**. These operations might be **reading data** from a USB key, **writing data to the disk drive**, or may be **reading data from a mouse**. These **commands** are **sent through device drivers**. Device drivers can be seen as **software/programs/code that allows the operating system** to **interact** with the **external device** **without having to know the hardware of the external devices**.
- Once these **operations are done** in the IO devices, these devices **send** a signal **(interrupts)** to the **CPU** to get its attention and warn it that the operation is done. The operating system is responsible from catching and handling these interrupts. But **what if an error** (e.g., communication timeouts, data corruption, device failures, etc.) **happens** and the **IO operations are not completed** as a result of this error ?

In those cases the operating system is responsible from **detecting** and **handling these errors** as well. Some ways to handle these errors might be **retrying the operation**, **notifying the user** about the error, etc.

```
-------------------
   Applications     
-------------------
  read(), write()   
-------------------
    File System 
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
+-----------+                  Interrupts
| Processor |----------------------------------------------          
+-----------+          |                 |                |       
      |                |                 |                |        
+-----------+          |                 |                |
|   Cache   |          |                 |                |
+-----------+          |                 |                |
      |                |                 |                |
+----------------------------------------------------------------+
|                     Memory IO Interconnect                     |          
+----------------------------------------------------------------+
      |              |  |              |  |              | | 
+----------+    +------------+    +------------+    +------------+
|   Main   |    |    I/O     |    |    I/O     |    |    I/O     |
|  Memory  |    | Controller |    | Controller |    | Controller | 
+----------+    +------------+    +------------+    +------------+
                  |       |             |                 |
                  |       |             |                 |
                Disk     Disk        Graphics          Network
                                      Output                            

```

Memory IO interconnect is a data communication channel (like bus). It is a hardware component and it consists of a set of parallel wires on the motherboard along with supporting circuitry and protocols. These wires carry electrical signals and through these signals data, address, and signals are carried between the CPU, memory, and IO devices, and communication between these components is handled this way. 

IO controller, also known as peripheral controller, is another hardware component. It manages the communication and data transfer between the CPU and IO devices such as disk, network. It acts like an intermediate layer between the IO devices and CPU and through this way the CPU doesn't have to control & communicate with the IO devices directly. 

```

                                  +------------+    +-------------+    +--------------+
                                  |  Monitor   |    |  Keyboard   |    |  Hard Disk   |  
                                  |            |    |             |    |    Drive     | 
                                  +------------+    +-------------+    +--------------+
                                         |                 |                  | 
+----------+    +------------+    +------------+    +------------+    +--------------+
|   Main   |    |    CPU     |    |   Video    |    |  Keyboard  |    |   Hard Disk  |
|  Memory  |    |            |    | Controller |    | Controller |    |   Controller |  
+----------+    +------------+    +------------+    +------------+    +--------------+
     |                |                  |                 |                  |
     |                |                  |                 |                  |
+-----------------------------------------------------------------------------------------+
|                                            Bus                                          |
+-----------------------------------------------------------------------------------------+

```

As we can see above, IO controllers are physically connected to the memory IO interconnect (bus) on the motherboard. They have dedicated interfaces and ports that plug into the bus and this allows the IO controllers to send and receive signals over the bus. They communicate with the memory and CPU through this bus. The bus in here enables the exchange of data and signals between IO controllers and the rest of the system.

When the CPU needs to communicate with keyboard, for instance, it sends commands and data to the keyboard controller over the bus. The keyboard controller receives these commands and data from the bus and translates them into the keyboard-specific signals and protocols. Similarly, when the keyboard needs to send data to the CPU or memory, the keyboard controller receives the data from the keyboard and sends it over the bus to the CPU or main memory.

One note is that IO controllers can generate interrupts to notify the CPU about important events. For example, while a code is running in the program, if the user clicks the interrupt button with his mouse and interrupts the running of the program, or if an IO operation is completed naturally, the interrupts are generated and the IO controllers send these interrupt signals to the CPU using the bus. Once the CPU receives these interrupt signals, it invokes the appropriate interrupt handler routine to process the interrupt and then communicate with the IO controller.

So if we consider the IO controller to be part of an IO device, we can say that an IO device has two main components: **mechanical component** and **electronic component** 

Mechanical components are the physical components that are used in the IO devices to perform some functions. Mouse ball, scroll wheel can be given as examples of mechanical components. But as we might guess, many modern IO devices don't have these kinds of mechanical components anymore since they are replaced with electronic equivalents 

Electronic component consists of the electronic circuitry and IO controllers that manage the functionality of the device and handle the communication between the device and the rest of the system. 

# Controller and Device

So we talked about IO controllers. Each of these controllers has few registers. By writing data to registers and reading data from them, the operating system can control the IO device. 

There are also buffers in the IO device. They are the sections of memory within the device and they play the role of temporary storage areas. They hold the data that is transferred from the IO device to the operating system or from the operating system to the IO device. And the operating system can read data from these buffers or write data to them. 

The operating system needs to know a couple of things to manage the data transfers from/to these buffers: 

- location address of the buffer: This specifies where the buffer is located in the memory
- location address of the IO object: IO devices often work with specific units of data. These can be disk sectors (each sector is a fixed-size block of data that can be read or written as a single unit), video frames (each frame represents a single image or a portion of image displayed on the screen), etc. and they are called IO objects. The location of an IO object refers to the address that identifies where the IO object (e.g. disk sector, video frame, etc.) are located within the IO device's address space.
- size of data to transfer: When data is transferred from the operating system to the IO device or from the IO device to the operating system, the size/the amount of the data that will be transferred from/to buffers must be known by the operating system. Because this ensures that the appropriate amount of data is transferred and prevents buffer overflows or underflows.

Okay but how does this communication happen between the registers and buffers ? There are two ways: 

1) IO Port Space
2) Memory-Mapped IO

# IO Port Space

IO port is a physical or logical interface and the data is transferred from the CPU to the IO device or from the IO device to the CPU through this interface. A physical interface in here refers to the actual and physical hardware connection and the data is transferred through this connection. USB ports, ethernal ports, HDMI ports can be given examples of physical interfaces. 

Logical interface, on the other hand, refers to a representation of the connection between the CPU and IO devices. It defines the rules, protocols, and formats used for data exchange between the IO devices and CPU. 

Each IO port is associated with a specific IO device. For example, we observe separate IO ports for keyboard, mouse, display output etc. These IO ports are associated with registers, and the CPU communicates with the IO devices using these registers. 

And the set of all possible IO port numbers assigned to the control registers of the IO devices in the system form the IO port space. The IO port space is an address space separate from the memory address space that is used by the CPU. Each IO device has its own range of IO port numbers allocated within the IO port space.

IO ports are accessed with specialized IO instructions or commands that are provided by the CPU. These instructions or commands specify the address of the port to be accessed and direction of data transfer. An IO port number is a **numerical identifier** that is assigned to the a specific IO port. CPU uses these IO port numbers to identify and access a specific IO port.

Control registers are special registers that are located within the IO device's internal circuitry. They are used for configuring, controlling, and monitoring the behavior of the IO device. They cannot ba accessed by the CPU directly. For the communication to happen, the CPU uses specific IO port numbers within the IO port space that are assigned to each control register. 

Control registers may store information such as 
- current state/status of the device
- commands/instructions
- configuration parameters that determine how the device operates
- data that is transferred between the CPU and IO device
- etc.

In addition, one note is that IO port space is protected and only the kernel can access to the IO port space. And the kernel uses special privileged instructions to access to the IO port space. These instructions can only be executed in the kernel mode. We can see some examples of the privileged instructions in below: 
- in portnum, target: It reads data from the IO port portnum and stores it in the target register or memory location.
- out portnum, source: This writes data from the source register or memory location to the IO port portnum.

Here portnum parameter represents the IO port number of the control register that is accessed. 

User-level applications and programs cannot access to the IO port space directly. They must do a system call. This protection is necessary because we want to prevent unauthorizied access to the IO devices and see that IO operations are done in a controlled manner. 

# Memory-Mapped IO

This is another method of handling communication between the IO devices and CPU. The communication is done by mapping the IO device's control registers and status registers into the same address space with the system's address space. 

So in this method, a portion of the address space is reserved for the registers of the IO devices. The operating system basically assigns some specific memory addresses to these registers and then CPU can be able to read and write to these addresses in the address space using regular memory load and store instructions. 

When we were using IO port space method, we were using separate instructions that are designed for the IO operations specifically. These instructions were distinct from the instructions of accessing to the regular memory address space and they were being used to communicate with the IO devices. However, these separate instructions are not needed anymore when we reserve a portion of the address space for the IO operations in memory-mapped IO method. Also in the IO port space, an address space that is separate from the memory address space was reserved for the IO devices and each IO device was being assigned an IO port numbers within this IO port space. And when CPU wanted to access the device registers, it was using special IO instructions (e.g. in and out instructions) specifying the IO port address. In memory-mapped IO, each IO device's registers are mapped to a specific address in the memory address space through pagetable and with this way, no special IO instructions are required in this method. 

When the CPU wants to perform a load operation or store operation on IO device's corresponding control registers in the memory address space, the IO device itselfs monitors these memory accesses. And the range of memory addresses IO device should monitor is predetermined. When a load or store operation is requested within this range, the IO device acts accordingly. 

The modern computers today use memory-mapped IO method in general.

# Advantages of Memory-Mapped IO 

1) Because IO devices can be accessed using a regular load and store instructions, device drivers (in other words software/programs that control and communicate with hardware devices) can be written entirely in a high-level language like C and there is no need to use specialized assembly instructions/code to interact with devices.
2) As long as we keep the memory addresses assigned to the IO devices' registers out of the memory addresses assigned to the user-level applications, no special protection is needed.
3) Because we map the IO devices' registers to the memory address space, any CPU instruction that reference to these address spaces (e.g., read, write, load, store etc.) can be used to access/manipulate the IO devices' control registers as well. This basically simplifies the programming model because developers can now use the same instructions for both memory operations and IO device communication.


# The Potential Issue of Caching Device Control Registers

As we explained previously, memory mapped IO treats IO devices' control registers as memory addresses. Therefore, CPU caches can try to cache the values of these registers from the memory address space. And these cached values may not reflect the actual state of the IO device. In that kind of case, we observe data corruption and incorrect behavior. 

To solve this problem, we can use a mechanism that disable caching operation for certain memory regions. We can use a "cache disabled bit" in the PTE and make the memory addresses that correspond to IO device registers non-cachable. Through this way, we can ensure that CPU does not cache the values read from these addresses.

# Interrupts

```
+------+     CPU responds to the interrupt     +-------------+    
|      |-------------------------------------->|  Interrupt  |<-------- Disk
| CPU  |                                       |  Controller |<-------- Clock  
|      |      Controller issues interrupt      |             |<-------- Keyboard 
|      |<------------------------------------- |             |<-------- Printer
+------+                                       +-------------+
    |                                                 |
    |                                                 | 
+-----------------------------------------------------------------------------------------+
|                                            Bus                                          |
+-----------------------------------------------------------------------------------------+
```

Anytime an IO device wants attention, it causes an interrupt. And one of the times when the IO device wants attention is when the IO device finishes its operation.

When the CPU receives an interrupt, it detects the interrupt, and saves the current state of the execution. 

```
       +-----+
       | CPU |
       +--+--+
         Ʌ  |
         |  |
     IRQ |  | ACK 
         |  v
+-------------------+
|        PIC        |
| 0 1 2 3 4  ...  7 |      
+-------------------+   
  Ʌ Ʌ Ʌ Ʌ Ʌ  ...  Ʌ        
  | | | | |       |
  | | | | |       +--------------------------+ 
  | | | | +------------------------+         |     
  | | | +--------------------+     |         |     
  | | +----------------+     |     |         |    
  | |                  |     |     |         |   
  | +--------------+   |     |     |         |    
  +---------+      |   |     |     |         |  
            |      |   |     |     |         | 
         +--+--+   |   |     |     |         |   
         | DC_a|   |   |     |     |         |   
         +-----+   |   |     |     |         |   
                   |   |     |     |         |   
         +-----+   |   |     |     |         |          
         | DC_b|----   |     |     |         |   
         +-----+       |     |     |         |   
                       |     |     |         |   
         +-----+       |     |     |         |   
         | DC_c|--------     |     |         |   
         +-----+             |     |         |   
                             |     |         |   
         +-----+             |     |         |        
         | DC_d|--------------     |         |   
         +-----+                   |         |    
                                   |         |     
         +-----+                   |         |         
         | DC_e|-------------------          |    
         +-----+                             |     
                                             |           
            .                                |   
            .                                |           
            .                                |   
                                             |   
         +-----+                             |     
         | DC_h|-----------------------------+
         +-----+

```
PIC in here an programmable interrupt controller. It is basically responsible from receiving interrupt requests from various device controllers and forwarding them to the CPU. 

When an IO device controller wants to send an interrupt, it sends an interrupt request to this programmabe interrupt controller. All the interrupt requests coming from device controllers are sent to the programmable interrupt controller.

The PIC then sends the interrupt request that has the highest priority to the CPU. And the CPU acknowledges that it received interrupt request and applies necessary actions. 

# Message Signaled Interrupts

So the hardware lines, physical electrical connection or a signal path, between the IO device and programmable interrupt controller are too limited because of pin count restrictions on the CPU and motherboard. Because of this, as the number of devices in a system increases, the limited number of interrupt lines becomes a bottleneck.

So there is another mechanism in which the IO device writes the data that describes the interrupt to the designated memory-mapped IO address. And the act of writing the data to this specific memory address triggers the interrupt. This mechanism is called Message signaled interrupts. 

The PCI (bus) detects this write operation and then delivers the interrupt to the appropriate CPU based on the information written to the memory address. 

Message signalled interrupts provide high degree of programmability in interrupt handling. In other words the IO devices can be configured to create specific interrupts based on their requirements when we use message signalled interrupts. 

# Issues with Interrupt Processing 

In old systems, whether or not there was a pending interrupt was being checked after each instruction was finished its execution. So after executing some instructions, if an interrupt occurred, this means that all the instructions up to that instruction after which interrupt was generated had been executed completely and no instructions were executed yet after that instruction.

This may not be the case in modern computers. 

Today, modern CPUs use a method that is called pipelining. Basically, the execution of an instruction is broken into multiple stages (e.g., fetching, decoding, executing, etc.) These stages are overlapped and this allows the execution of multiple instructions simultaneously. 


```
Fetch unit -> Decode unit -> Execute unit

```

And when an interrupt occurs, we might see some instructions that have completed their executions, some instructions waiting to enter the pipeline of fetching + decoding + executing, and some others that are in the middle of their executions etc.

In these cases, when an interrupt occurs, the value of the program counter will be pointing to the address of the next instruction that will be fetched instead of pointing to the address of the instruction that has just completed its execution.

In the situation like below

```
Fetch unit -> Decode unit                          Execute Unit
                          \                     /
                            --- Holding Buffer  -  Execute Unit                     
                          /                     \  
Fetch unit -> Decode unit                          Execute Unit
```

some instructions that started a long time ago may still be in the holding buffer or waiting to enter the execute unit and that's why they may not have started. Other instructions that started recently may be almost done and when the interrupt occurs, many instructions may be at various states of completeness and the relationship between them and the program counter might be weak because the program counter may not directly correspond to the instruction that caused the interrupt.

An interrupt after which we can observe a well-defined state is called a precise interrupt. These kinds of interrupts have the following 4 features: 

1) The program counter is saved in a known place (e.g., a special register that is only accessible through kernel mode. _(Saving program counter allows the CPU to know where to continue execution after interrupt is handled)_
2) All instructions before the instruction that is pointed by the program counter have finished their executions. _(This means that any changes these instructions made to the CPU's registers or memory are completed. And no incomplete modifications exist at that moment)_
3) There is no instruction beyond the instruction that is pointed by the program counter that started its execution. _(This ensures that the interrupt does not affect the execution of the next instructions)_
4) The execution state of the instruction that is pointed by the program counter is known. _(In other words CPU knows whether the instruction completed its execution, just started its execution, etc. Knowing these is helpful for handling the execution after the interrupt is handled)_

If the CPU handles parallel and out-of-order execution, if it can execute multiple instructions simultaneously, ensuring that interrupts are precise is crucial. Because precise interrupts can help us to maintain a consistent and predictable state even when the instructions are executed out-of-order or in parallel.

If an interrupt does not meet these requirements, it is called imprecise interrupt. And we can see how they look like in below:

```
                    +----------------------+                       +----------------------+
                    |     Not executed     |                       |     Not executed     |    
                    +----------------------+                       +----------------------+
                    |     Not executed     |                       |     10% executed     |     
                    +----------------------+                       +----------------------+
                    |     Not executed     |                       |     40% executed     |                          
                    +----------------------+                       +----------------------+
                    |     Not executed     |                       |     35% executed     |
Program Counter --> +----------------------+  Program Counter -->  +----------------------+
                    |    Fully executed    |                       |     20% executed     |                      
                    +----------------------+                       +----------------------+
                    |    Fully executed    |                       |     60% executed     |                         
                    +----------------------+                       +----------------------+
                    |    Fully executed    |                       |     80% executed     |                          
                    +----------------------+                       +----------------------+
                    |    Fully executed    |                       |    Fully executed    |                               
                    +----------------------+                       +----------------------+
                       Precise Interrupt                              Imprecise Interrupt

```

# IO Software

After reviewing the IO hardware, now let's take a look at the IO software. We can start with the goals of the IO software. 

### Goals of the IO Software
- **Device independence**: We should be able to write programs that can access to any of the IO device without having to specify the device in advance. For instance, a program should be able to read a file from DVD, hard disk, USB stick etc. without being modified for each of them separately. Or when someone type ```sort <input> output``` this should work with all kinds of disks or keyboard and the output should go to any kind of disk or screen. If problems occur due to the underlying differences in these IO devices, it is the operating system's responsibility to take care of these problems.
- **Uniform naming**: The name of a file/device should be string/integer and it should not depend on the IO device. Through this way, users can access files using the same naming convention without having to know which specific device corresponds to that file. For example, if a USB stick is mounted on top of _/usr/documents/_, copying a file to the _/usr/documents/_ basically copies that file to the USB stick. Through this way, all files are addressed with a path name which makes everything convenient.
- **Error handling**: The goal is to handle the errors as close to the hardware as possible. If IO device controller detects an error, it should first try to fix the error. If it is something that it cannot solve, then the IO device driver should try to handle the problem. One way to handle it might be reading the block again if the error is a read error since sometimes some problems may go away if the operation is repeated. Most of the times, errors can be recovered at a low level without users being aware of them.
- **Handling shared and dedicated devices**: Some IO devices (e.g., disks) can be used by many users at the same time. These are called sharable devices. But this is not valid for some other IO devices (e.g., printers) which are called dedicated devices. The operating system must be able to manage both shared devices and dedicated devices properly.

One of the issues of IO software is synchronous (blocking) and asynchronous transfers that are driven by interrupts. Most of the times, the CPU starts the transfer and starts doing another task until an interrupt notification comes to it. This is asynchronous transfer because it is driven by interrupts.

And another issue of IO software is buffering. Most of the times, the data coming from the IO device cannot be stored in wherever its final destination is directly. So in those cases, we should store these data in temporary locations which are called buffers.


# Three Ways of Performing IO 

## Programmed IO 
The simplest form of IO is to make the CPU all the IO operations. This method is called **programmed IO**.

Let's give an example. Assume that you want to print the string "ABCDEFGH" with printer. 

In the first step, the software stores this string in buffer in user space. Then the user process makes a system call to open the printer. If the printer is currently being used by another process, this system call will fail and either return an error to the user process or will block its system call until the printer becomes available depending on the OS. 

Once the printer is available to use, the user process makes a system call and asks the printer to print the string on the printer. After this system call, the OS copies the buffer that contains the string of "ABCDEFGH" from user space to an array in kernel space. Let's call this array `p`. 

It then checks if the printer is available at that moment. If the printer is not available, the operating system waits until it becomes available. Once the printer is available, the OS copies the first character to the printer's data register using memory mapped IO. 

Copying the first character to the printer's data register activates the printer. And after that printer prints the first character "A" and marks the second character "B" as the next character to be printed.

The key feature of programmed IO is that the CPU continuously checks the device to see whether it can accept a new character. This behavior is called busy waiting or polling. The process is visualized in below:

```
copy_from_user(buffer, p, count);
for (i = 0; i < count; i++) {
    while (*printer_status_reg != READY) {};
    *printer_data_register = p[i];
}
return_to_user();                

+--------------------+
|     User Space     |
|                    |
|                    |
|                    |
|    +--------+      |
|    |ABCDEFGH|      |
|    +--------+      |              Page
| (String to print)  |          +----------+
+--------------------+          |          |
|   Kernel Space     |          |          |
|                    |          |          |
|                    |          |          |
+--------------------+          +----------+



+--------------------+
|     User Space     |
|                    |
|                    |
|                    |
|                    |
|                    |              Page
|                    |          +----------+
+--------------------+          |  A       |
|   Kernel Space     |          |          |
|                    |          |          |
|     |              |          |          |
|     v              |          |          |
|    +--------+      |          |          |    
|    |ABCDEFGH|      |          |          |
|    +--------+      |          |          |   
+--------------------+          +----------+



+--------------------+
|     User Space     |
|                    |
|                    |
|                    |
|                    |
|                    |              Page
|                    |          +----------+
+--------------------+          |  AB      |
|   Kernel Space     |          |          |
|                    |          |          |
|      |             |          |          |
|      v             |          |          |
|    +--------+      |          |          |    
|    |ABCDEFGH|      |          |          |
|    +--------+      |          |          |   
+--------------------+          +----------+



+--------------------+
|     User Space     |
|                    |
|                    |
|                    |
|                    |
|                    |              Page
|                    |          +----------+
+--------------------+          |  ABC     |
|   Kernel Space     |          |          |
|                    |          |          |
|       |            |          |          |
|       v            |          |          |
|    +--------+      |          |          |    
|    |ABCDEFGH|      |          |          |
|    +--------+      |          |          |   
+--------------------+          +----------+

...

```

Even though the programmed IO is a simple method to handle IO operations, it is inefficient in systems where CPU has other works to do due to busy waiting. But if the time that is needed to print a character is short, or in other systems where CPU does not have other things to do, busy waiting and programmed IO is okay to use.

## Interrupt Driven IO

When the IO device is ready for data transfer or when it completes the IO operation, CPU can be notified about these with interrupts. We call this method interrupt driven IO. And with this method, the CPU won't have to do busy waiting and it can handle other tasks while waiting for the IO device and this increases the efficiency. 

Basically when an IO operation is initiated by a process, system call is made to the operating system. And if the IO device is not ready to do the required IO operation, the system call is blocked and marked as waiting by the operating system. In the mean time, the operating system continues executing and scheduling other processes while the IO operation is waiting.  Once the IO device becomes ready to run the IO operation,  it raises an interrupt and this interrupt is sent to the CPU which indicates that the IO device requires attention. After CPU is notified about the fact that IO device is ready to run the IO operation, CPU first saves its current execution context. Then the interrupt handler determines which IO device raised the interrupt and then takes appropriate actions. If the interrupt handler decides that the IO device is ready for data transfer, the CPU initiates the transfer between the IO device and memory and it copies the data from memory to IO device or IO device to memory. 

Using interrupts in this scenario prevents CPU from busy waiting which would waste CPU cycles.

After the data transfer is completed by the CPU from the memory to IO device or IO device to memory, the process is unblocked and scheduler is invoked. And scheduler then determines which process should be executed by the CPU next based on scheduling algorithm.

## Direct Memory Access (DMA) 

But the thing is it is not efficient for the CPU to request data from the IO device one byte or one character at a time since this is time-consuming and inefficient. 

DMA is a technique that is used to allow the IO devices to transfer data to/from the main memory directly. In this scenario, CPU is not used during the data transfer. And this process is handled by the DMA controller. 

DMA controller is a hardware component. It is typically integrated into the motherbaord. In some cases, we can see them as integrated to the IO devices such as disk controllers. 

DMA controller is connected to the system bus and therefore it can access to the main memory directly. And through this way, it can initiate and manage data transfers between IO devices and main memory directly. 

DMA controller contains several key components: 
- Address registers: Holds the address the data will come from and destination address.
- Data registers: It stores the transferred data temporarily. 
- Data count : Keeps track of the number of characters or bytes remaining to be transferred.
- Control unit: This is used to control the overall operation of the DMA controller. The control unit receives DMA request and sends DMA acknowledge. It generates interrupts when the data transfer is completed
- Bus interface: The bus in here allows the DMA controller to communicate with the CPU, memory, and IO devices.

When transfer is initiated, CPU programs the DMA controller by writing the necessary information into the control registers of the DMA controller. 

Then the DMA controller sends a request to the disk controller to transfer data from disk to the main memory. Next, the disk controller acknowledges this request and prepares the data to transfer it to main memory. The data is stored in the temporary storage in the mean time. Then the data is transferred from the buffer in the disk to the main memory. As the data is being transferred, CPU can continue executing other tasks because it is not involved in this transfer process. And lastly, when the data transfer is completed, an interrupt is generated by the DMA controller and CPU takes any necessary actions after learning that the data transfer is completed.

We can see the visualization of this process in below:

```
                                                                          +-------+
                                                                          | Drive |
                                                                          +-------+
                                                                              |  
                                                                              |            
+----------+                    +-------------+                    +--------------------+          +-------------+
|   CPU    |                    |     DMA     |                    |        Disk        |          |     Main    |
|          |                    |  Controller |                    |     Controller     |          |    Memory   |
|          |                    |             |                    |                    |          |             |                                         
|          |   1) CPU programs  |             |                    |    +----------+    |          |             |      
|          |   DMA controller   |             |                    |    |  Buffer  |    |          |             |
|          |                    |  +-------+  |                    |    |          |    |          |             |
|          |---------------------->|Address|  |                    |    +----------+    |          |             |
|          |                    |  |Regist |  |                    |             |      |          |             |                                        
|          |                    |  +-------+  |                    |             |      |          |             |
|          |                    |  |Data   |  |                    |             |      |          |             |
|          |                    |  |Regist |  |                    |             |      |          |             |           
|          |                    |  +-------+  |                    |             |      |          |             |
|          |                    |  |Data   |  |                    |             |      |          |             |
|    Ʌ     |                    |  |Count  |  |                    |      Ʌ      |      |          |    Ʌ        |
|    |     |                    |  +-------+  |                    |      |      |      |          |    |        |                
|    |     |                    |  |Control|  |                    |      |      |      |          |    |        |
|    |     |                    |  |Logic  |  |    Acknowledge     |      |      |      |          |    |        |
|    |     |                    |  ||     ||<-------------------------    |      |      |          |    |        |                                   
|    |     |                    |  +|-----|+  |                    |      |      |      |          |    |        |   
+----|-----+                    +---|--+--|---+                    +------|--+---|------+          +----|--+-----+
   | |                              |  |  |                               |  |   |                      |  | 
   | +------------------------------+  |  +-------------------------------+  |   +----------------------+  |   
   |       Interrupt when done         |      2) DMA requests transfer       |      3) Data transferred    |      
   |                                   |             to memory               |                             |  
   +-----------------------------------+-------------------------------------+-----------------------------+       
                                                   BUS
```

# Alternative DMA Configurations

## Single Bus - Detached DMA

## Single Bus - Integrated DMA 

## IO Bus 

# DMA and Memory Protection

As we learned previously, DMA allows the IO devices to access to main memory directly. Therefore, we may observe unauthorized access to memory regions, and data corruption if the process is not properly managed. 

To address these issues, we use a method called IOMMU. IOMMU is a hardware component. It acts as a memory protection and translation layer for the DMA operations. But how ? 

The operating system creates a translation table in the IOMMU. This translation table maps the virtual addresses that are used by the IO devices to the physical memory addresses.

If IO device DMA to an address and there is no translation, an interrupt/exception is raised.

The idea in here is similar how applications are restricted to what memory they can access using pagetable (MMU). 

```
       +---------------------------+
       |        Main Memory        |
       +---------------------------+    
          Ʌ                      Ʌ 
          |                      |
          |                      |
      +-------+             +--------+
      | IOMMU |             |  MMU   |
      +-------+             +--------+
          Ʌ                      Ʌ
          |                      |  
   Device | addresses    Virtual | addresses
          |                      | 
          |                      |            
      IO Device                 CPU       
```

# Software Layers for IO

```
         
    +--------------------------------+
    |     User-level IO software     |
    +--------------------------------+
    | Device-independent OS software |       
    +--------------------------------+
    |         Device Drivers         |
    |         +----------------------+        
    |         |  Interrupt handlers  |
+---+---------+----------------------+---+
|               Hardware                 |
+----------------------------------------+
```

## Device Drivers 

Device drivers are software modules and they are prepared specifically for each IO device. They basically provide an interface so that the operating system can interact with the devices through this interface. The codes in the device drivers are tailored to control and communicate with a particular IO device. They encapsulate the low-level details of the device and abstract them from the operating system.

They are responsible from reading data from the IO devices' registers and writing data to them. They include interrupt handlers which are the procedures (e.g., processing the interrupt, communicating with the IO device, performing any other necessary actions etc.) that are followed after an interrupt is generated.

Device drivers are provided by the manufacturer of the IO devices and integrated to the operating system's kernel. They are integrated either as built-in components or as loadable modules which basically allow the device drivers to be loaded into the kernel. If they are integrated as built-in, however, they are compiled to the kernel directly and they are always available.

In addition, the device drivers must follow standard interfaces that are defined by the operating systems. These interfaces are different in block devices and character devices because how these devices process the data is different. 

The drivers of the block devices (e.g., hard drives, USB storage devices) must follow a specific interface that includes operations like reading and writing blocks of data. 

The drivers of the character devices (e.g., keyboards, serial ports) must follow another type of interface that deals with individual characters of bytes of data.

```
               User process       
                    |
+-------------------|--------------------+----------------
|           +----------------+           | 
|           |  User program  |           |  User space
|           +----------------+           |
+-------------------|--------------------+----------------
|                   |                    |
|   +--------------------------------+   |
|   |  Rest of the operating system  |   |
|   +--------------------------------+   |
|       |           |            |       |
|   +-------+   +---------+   +------+   |  Kernel space
|   |Printer|   |Camcorder|   |CDRom |   |
|   |driver |   |driver   |   |driver|   |  
|   +-------+   +---------+   +------+   |
|       |           |            |       |
+-------|-----------|------------|-------+----------------
|       |           |            |       |    
|       V           V            V       |
|   Printer     Camcorder    CD-Rom      |  Hardware
|   controller  controller   controller  | 
|       |           |            |       |
+-------|-----------|------------|-------+----------------
|       |           |            |       | 
|       V           V            V       |  Devices  
|   Printer     Camcorder    CD-Rom      |    
+----------------------------------------+----------------

```

When an IO device is detected/connected, the IO device is initialized by the IO device driver. The initialization may include setting up the necessary data structures, preparing the device for operations, etc. Device drivers also receive read and write requests from higher-level software layers such as the operating system or applications. These requests come in abstract and standardized in general and they are independent from the specific details of the IO device. 

The IO device drivers translates these requests into a form that is suitable for IO device, executes them, and facilitates the data transfer between the device and the system.

When the IO devices generate interrupt, these interrupts are handled in the interrupt handler in the device driver.

The device drivers may include logging mechanisms for the purpose of recording important events or status information that is related to the IO device. 

They are also responsible from managing the power requirements of the devices they control. (e.g., putting the device into low-power state when necessary)

One note is that device drivers must be able to deal with multiple devices of the same type simultaneously. This means that device driver code must be able to allow multiple threads/processes to execute the same driver concurrently.

Lastly, device drivers should also be prepared for the events like device removal or device plugging. When a device is removed, for instance, its device driver should release the resources associated with that device for instance. 

```
   Abstract
   commands
      |
      |
      V      
  +--------+
  | Device |           
  | Driver | 
  +--------+
      Ʌ
      |
      | Detailed
      | commands
      | 
      V
+------------+
|   Device   |
| Controller |
+------------+
      Ʌ
      |
      |
      V
 +--------+
 | Device |
 +--------+
```

## Device Independent IO Software

There are several capabilites that should be provided by the device independent IO software: 

1) The software should provide an interface through which different device drivers can interact _(uniform interfacing for device drvers)_. The main goal in here is to make all the devices appear the same to the operating system regardless of their specific hardware characteristics. And we can do this by functions for each group of devices that share similar properties (e.g., display devices, storage devices, network devices, etc.) By providing this uniform interface, the operating system can interact with different IO devices using the same functions and this simplifies the device management. Also, the device independent IO software layer maps the symbolic device names (e.g., "printer", "disk", et.c) to the appropriate device drivers. When the operating system wants to communicate with a device, it uses its symbolic name and this symbolic name is translated to the corresponding driver. Through this way, the operating system can refer to  devices using logical names instead of hardware specific details. 
2) It should handle buffering of data transfer between the IO device and operating system _(buffering)_
3) It should report any errors when they occur with the use of IO devices _(error reporting)_
4) It should be able to allocate and also release the dedicated devices when needed.
5) The size of the blocks provided by the IO software for data transfer should be standardized and independent from the IO devices.

# Examples of IO Devices

## Clocks 

### Clock Hardware

In older computer systems, the clock was directly tied to the alternating current power line frequency and the alternating current power line frequency was determining the clock speed of the computer. In these systems, an interrupt was being sent to the CPU on every voltage cycle of the power line. In other words, the CPU was interrupted at a fixed frequency based on the power line. This method is simple but inflexible. It can reduce the CPU utilization because CPU might be interrupted very frequently.

In modern computer systems, a crystal oscillator is used instead of relying on the power line frequency. The crystal oscillator generates a stable and high-frequency clock signal. It produces a consistent oscillation at a specific frequency. This signal is fed to the counter which is decremented at each pulse. Once the counter gets to 0, it generates interrupt.

### Clock Software

So basically, the main thing clock hardware does is to generate interrupts at known intervals Everything else must be done by the software -- clock driver. The duties of the clock driver are like these: 

- Maintaining the time of day
- Preventing processes from running longer than they are allowed to
- Accounting for CPU usage
- Handling alarm system call that are made by the processes
- Providing timers that monitor microcontroller (?) programs to see if they are out of control or have stopped operating. These timers are called watchdog timers.
- Gathering statistics, monitoring and profiling.

## User Interfaces

### Keyboard
Keyboards contain simplified a processor that handles the basic functions of the keyboard. This processor communicates with the keyboard controller in the motherboard using a port.

When a key is pressed by the user in the keyboard and when a key is released, an interrupt is generated and is sent to the IO port of the keyboard.

And then the information from the IO port of the keyboard is extracted by the keyboard driver which is basically a software component of the keyboard and which interacts with the hardware of the keyboard

The number that is stored in the IO port when a key event occurs is called the **scan code** which typically 8 bits long. 7 bits of this for the code and 1 bit to indicate whether the key was pressed or released. 

When a key is pressed in the keyboard, an ASCII code is generated and it is immediately sent to the program without any further-processing. And the program interprets and handle these raw ASCII codes. This is called **raw mode** or **noncanonical mode**. In the raw mode, the program handles all the low-level details such as interpreting special keys, handling backspaces, etc. In the raw mode, the program maintains its own buffer to store the received ASCII codes until they are processed. 

If the keyboard driver handles the raw ASCII code and it processes the intraline editing and delivers the corrected lines to the user program, we call this **cooked mode** or **canonical mode**.

When a user presses a key in the keyboard, for instance, the keyboard driver stores it in a buffer, handles backspaces, deletes characters, etc., and waits until the user presses the enter or until any other line terminating event before sending the complete line to the program.

In either way, a **buffer** is **needed** to store characters.

### Mouse 

Mouse only indicates **changes in position** (delta x, delta y). 

# IO Software Layer

We want the operating system to operate without being concerned/bothered about the low-level details of the interrupt handling process. In other words, the goal is to minimize the impact of interrupts on the overall system and keep the interrupt handling process confined to a specific part of the operating system. That's why interrupts are hidden from most of the operating system so that as little of the operating system as possible knows about them. But how to hide interrupts ? 

Well the execution of the thread in the IO device driver that initiates an IO operation can be suspended until the IO operating finishes and the interrupt is handled. In other words, after initializing the necessary data structures and registers for the IO operation, the a thread in the IO device driver can start an IO operation by sending commands to the IO device controller and block until the IO operation is completed. 

And in the meantime, the IO operation is handled by the IO device controller (not CPU). Once the IO operation is completed, it generates an interrupt. 

After this interrupt is generated, the interrupt handler is invoked to handle the interrupt and perform post IO processing. Then the interrupt handler unblocks the thread in the IO device driver that initiated the IO operation so that it can continue its execution from where it lefts off.

This method allows the device driver to wait for the IO operation to complete without constantly checking for its completion. 

And for this method to work, IO device drivers should be structured as kernel threads or processes. Each driver should have its own state, stack, program counter, etc. so that they can operate independently and handle IO operations concurrently.

# Main Functionalities and Responsibilities of Device Drivers 

## Character Drivers
- **Discovery**: Character drivers are responsible from discovering/identifying character-based devices that are connected to the system.
- **Read/write data**: Character drivers provide functions to read characters from  and write characters to the device.

## Disk Storage
- **Discovery**: Disk storage drivers are responsible from discovering/identifying disk storage-based devices (e.g, hard disk drives, solid state drives, USB storage devices, etc.) that are connected to the system
- **Read block**: Disk storage drivers provide functions to read a block of data from a specific location on the storage device.
- **Write block**: Disk storage drivers provide functions to write a block of data to a specific location on the storage device.
- **Interrupt management**: Disk storage drivers handle the interrupts that are generated by the disk storage device.
  
## Network Cards
- **Discovery**
- **Send packet**
- **Receive packet**
- **Interrupt management**
- **Throttling**

# Summary 
- Operating system provides an interface between the devices and the rest of the system.
- The IO part of the operating system is divided into several layers.
  - Hardware: CPU, programmable interrupt controller, DMA, device controller, and the device itself.
  - Software: Interrupt handlers, device drivers, device-independent IO software, user-level IO software.
- Operating system must expand as new IO devices are added. 

# Hard Disk (Magnetic) Architecture 

- Surface: We see one or more surfaces (platters) in a hard disk. Each surface is divided into a group of circular tracks.
- Track: A track is a group of sectors that are arranged in a circular pattern on the surface of the disk. Each track is further divided into smaller units that are called sectors. 
- Sector: A sector is a group of bytes and the smallest unit of data that can be read from the disk or written into the disk.
- Cylinder: It is the collection of tracks located at the same position across all surfaces of the disk. If a vertical line passes through the tracks at the same location on each surface, it forms a cylindrical shape for example. That's why we call this cylinder.

```
Surface 1
+--------------------+--------------------+
|   Track 1                               | 
|   +----------------+----------------+   |
|   |   Track 2                       |   | 
|   |   +------------+------------+   |   |
|   |   |   Track 3               |   |   | 
|   |   |   +--------+--------+   |   |   |
|   |   |   | Sector |        |   |   |   |
|   |   |   +--------+        |   |   |   | 
|   |   |   |                 |   |   |   |   
|   |   |   +--------+--------+   |   |   |
|   |   |                         |   |   |
|   |   +------------+------------+   |   |   
|   |                                 |   |   
|   +----------------+----------------+   |
|                                         |
+---------------------+-------------------+

Surface 2
+--------------------+--------------------+
|   Track 1                               | 
|   +----------------+----------------+   |
|   |   Track 2                       |   | 
|   |   +------------+------------+   |   |
|   |   |   Track 3               |   |   | 
|   |   |   +--------+--------+   |   |   |
|   |   |   |                 |   |   |   |
|   |   |   |                 |   |   |   | 
|   |   |   |                 |   |   |   |   
|   |   |   +--------+--------+   |   |   |
|   |   |                         |   |   |
|   |   +------------+------------+   |   |   
|   |                                 |   |   
|   +----------------+----------------+   |
|                                         |
+---------------------+-------------------+

Surface 3
+--------------------+--------------------+
|   Track 1                               | 
|   +----------------+----------------+   |
|   |   Track 2                       |   | 
|   |   +------------+------------+   |   |
|   |   |   Track 3               |   |   | 
|   |   |   +--------+--------+   |   |   |
|   |   |   |                 |   |   |   |
|   |   |   |                 |   |   |   | 
|   |   |   |                 |   |   |   |   
|   |   |   +--------+--------+   |   |   |
|   |   |                         |   |   |
|   |   +------------+------------+   |   |   
|   |                                 |   |   
|   +----------------+----------------+   |
|                                         |
+---------------------+-------------------+


In here Track 2 in Surface 1, 2 and 3 create cylinder for instance.

```

```
                                                     Direction of disk rotation
                              <--------------------------------------------------------------------------

               |              1 Sector                   |   Intersector gap   |              1 Sector                   |    
  Ʌ -----------|-----------------------------------------|---------------------|-----------------------------------------|---
  |            |                                         |      +---------+    |                                         | 
  |            |                                         |     / RW Head /|    |                                         | 
  |            |                                         |    +---------+ |    |                                         |
  |            +-----------------------------------------+    | +-----+ | |    +-----------------------------------------+
Track   ...    | Preamble |    4096 Data bits    | E C C |    | |     | | |    | Preamble |    4096 Data bits    | E C C | ... 
  |            +-----------------------------------------+    | +-+ +-+ |/     +-----------------------------------------+
  |                                                           +---|-|---+  
  |                                                               | |
  |                                                               | |
  V --------------------------------------------------------------|-|--------------------------------------------------------
                                                        Direction | | Disk
                                                               of | | arm
                                                              arm | | 
                                                           motion | |  
                                                                  | |
                                                                    
```
RW (Read-write) head is an electromagnetic device. It consists of a tiny metal coil and a magnetic pole that generates or senses the magnetic fields on the disk surface. It is responsible from reading data from and writing data to the surface of the disk. During the read operation, the RW head senses the magnetic patterns on the disk and converts them into electrical signals that represent stored data. During the write operation, the RW head receives electrical signals from the disk storage controller and generates magnetic fields to record the data onto the disk surface. The RW head is mounted on the disk arm and flies very close to the disk surface without touching it.

The disk arm is a mechanical component that holds and positions the RW head over the desired track on the disk surface. The disk arm moves the RW head radially. 

And the direction of arm motion refers to the path along which the disk arm moves the RW head across the disk surface. 

# Hard Disk Performance

**Seek time**: It is the time that is required to put the RW head over the desired cylinder (track) on the disk surface.
**Rotational delay**: It is the time that is required for the desired sector to rotate underneath the RW heads. It depends on the disk's rotational speed which is measured in the number of revolutions per minute (rpm)
**Transfer bytes**: It is the amount of data in bytes that is read/writen from/to the disk surface. 

To calculate the total time data, for instace, we sum up the seek time, half of the rotational delay, and the transfer time. 

When the RW head is put on the desired track (cylinder), it needs to wait for the specific sector that contains the requested data before it starts reading/writing operation. And the actual rotational delay can vary. Therefore, we generally assume that the RW head will need to wait for half a rotation to reach the desired sector. That's why we used half of the rotational delay when we give the calculatation of total time to transfer data. 

As we can imagine, there are more sectors in the sectors that are located in more outside tracks compared to the tracks that are located in more inner side. That's why data transfer rate is higher when we read from outer tracks compared to inner tracks.

Disk transfer bandwith, which is also known as disk transfer rate, refers to the amount of data that can be read/written to/from a disk in a given amount of time. 

When the data we want to read is small, the seek time and rotational delay affect the performance the most because the amount of data that is transferred is quite small. That's why a significant portion of the disk transfer bandwitdh is wasted because the time that is spent on seeking and rotating is much larger compared to the actual data transfer time. To improve the performance we need disk scheduling algorithms to reduce seek time.

On the other hand, the rate of disk transfer bandwith that is utilized increases as the size of data that will be transferred increases because larger block size means more data that is transferred in a single operation. 

# Observations 

# Disk Scheduling 

## FIFO (FCFS) 

## Shortest Seek Time First (SSTF) 

## Elevator (Scan) 

## Look 

## Circular Scan (C-Scan) 

## Circular Look (C-Look)



