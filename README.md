# IO Operation
Before starting, let's first explain the concept of IO operation. 

**IO operation** is basically the process of **moving data** from **some external devices** to the **processor (CPU)** and from the **processor (CPU)** to the **external devices** using **modules (codes)** and **buffers (temporary storage location in the CPU).** That's why we can call these external devices as IO devices as well because they do an IO operation. 

# IO Devices

**IO devices** are the components that **allow** the computer to **communicate/interact with the outside environment**. The CPU interacts with the outside world through this way. 

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


Some of the examples of IO devices are mouse, display, keyboard, disks, network, SCANners, speakers, accelerators, GPUs, etc. 

And based on the **type of operations they make**, we can **group** these devices in **three categories**: 

## 1) Human Readable Devices ###
**Printers, keyboards, mouses, terminals, video displays** are some of the IO devices that can be managed/read by humans directly. That's why these devices can be grouped under this category. As we might guess, these IO devices are **suitable for communicating with the user**. 

## 2) Machine Readable Devices ### 
Some of the examples of machine readable external devices are **USB keys, sensors, IO device controllers, and disk drives.** 

Disk drive can be seen as an IO device because they **read data from the disk platters** and **transfer this data to the CPU** or **main memory** whenever this transfer is requested. And disk drives can be seen as a **machine readable** device because **they store and retrieve data in a format that can be processed by a computer (machine) without human intervention**.

## 3) Communication Devices ###
The IO devices that are used for the **communication between the computers and remote devices** can be grouped under this category. An example of these devices might be **modems** or **digital line servers** 

Aside from these 3 categories, we can group the IO devices under two categories depending on how they process the information: **block devices** and **character devices**.

**Block devices**, for example, **store** the **information in units that are fixed-size**. And **these fixed-size units are called blocks**. The **size** of these blocks is **predetermined** (e.g., 512 bytes). Even if only a small portion of data is needed, the **whole block** that consists that portion is retrieved. **Each** of these **blocks** has a **unique address**. And these **addresses** **identify** the **location of these blocks on the IO device**. The blocks can be accessed through this way. 

For instance, when reading from a block, the **system specifies the starting block address** and also **how many blocks to read** after the starting block. Then **the IO device transfers the requested blocks to the system's memory**. 

When **writing to the block**, on the other hand, the system **specifies the starting block address**. Then the **IO device writes the data** to the **specified block**.

**Hard disks**, **CD-ROMs**, **USB sticks** can be given as examples of **block devices** because **these devices** **store the data** in **fixed-size blocks**. 

**Character devices**, on the other hand, **processes the data** in a **sequential manner**. Unlike block devices, they **do not store the information in fixed-size units**. **Data** is **processed one character** or **one byte at a time** sequentially and it is **not stored in fixed-size units**. Therefore, **these devices do not have addressing scheme**. In other words, they are **not addressable**. So you **can't access a specific charcater or byte by its address** for example.

Some examples of character devices are: **keyboards**, **mice**, **printers**, **network interfaces** _(Network interface is a hardware component. It provides a physical interface between the device and Wi-Fi signals and allows the computer to connect to a network)_

One note is that **IO devices** are **separate hardware components**. These are **connected** to the **CPU** through a **bus** or **other communication channels**. But there are also some **other devices that are integrated to the CPU**. These are called **accelerators**. They contain **arithmetic logic unit** (it performs arithmetic & logical operations), **control unit** (it fetches and decodes instructions and controls the operation of the CPU), **registers** (these are temporary storage locations for data and addresses that are used during the execution of an instruction) and **cache** (small and fast storing unit that is used to store frequently accessed data and instructions). 

**Accelerators** are **more tightly integrated** to the **CPU** through a **high-speed interconnects or buses** and they can be **invoked** by **applications** with **CPU instructions** or **registers**  without utilizing the traditional IO path through the operating system. 

In addition, the **traditional** **IO devices** such as **keyboards**, **mouses**, etc. are **designed** for **data input, output** and **storage of the data** while **accelerators** are the devices that are designed to **perform specific computational** tasks. 

For example, an **encryiption device**, which is an accelerator, can **generate secure keys** using random number generators. A **compression device**, which is another accelerator, **applies a specific compression algorithm to the input data**. Other examples of accelerators are GPUs and TPUs.

So in summary, we can think the **accelerators** more like a **functional unit** **in the CPU** and **less like an IO device**. 

Okay but who is managing the IO operations and all of these devices ? 

# Operating System and IO 

**Operating system** plays the role of an **interface/layer** _(set of rules, and protocols that govern the exchange of data and commands between the applications and hardware devices)_ **between the devices and the rest of the system**. 

And basically all the **IO devices** that are mentioned in previous section are **controlled** **by** the **operating system**. 

But how ? 
- The **operating system** **sends commands** to the **IO devices** to **start an operation**. These operations might be **reading data** from a USB key, **writing data to the disk drive**, or may be **reading data from a mouse**. These **commands** are **sent through device drivers**. _(Device drivers can be seen as **software/programs/code that allows the operating system** to **interact** with the **external device without having to know the hardware of the external devices**.)_
- Once these **operations are done** in the IO devices, these IO devices **send** a signal **(interrupts)** to the **interrupt handler** to get its attention and warn it that the operation is basically done. Then the **interrupt handler** **takes** the necessary **actions** and **notifies the CPU abpout this interrupt**. 

But **what if an error** (e.g., communication timeouts, data corruption, device failures, etc.) **happens** and the **IO operations are not completed** as a result of this error ?

In those cases the operating system is responsible from **detecting** and **handling these errors** as well. Some ways to handle these errors might be **retrying the operation**, **notifying the user** about the error, etc.

We can see the position of the operating system in the figure below: 

```
-------------------------
   Applications     
-------------------------
   read(), write()   
-------------------------
   File System 
-------------------------
   Operating System
-------------------------
   Low-Level Interface
   (Device drivers,
    direct memory
    access controllers,
    interrupt controllers,
    hardware interfaces
    and communication
    protocols)
-------------------------
   IO Devices
-------------------------
```

At the top level of this hieararchy, there are **applications** which are basically programs that perform specific tasks and **interact with the file system** to **read and write data**. And this reading and writing operations are done with the **read() and write() system calls.**

**File system** is a **data structure** that is **used by the operating system** to **organize, store, and retrieve files/directories** on a **storage device**. 

It **provides** a **set of rules** for these kinds of **operations**. It handles some tasks such as **file creation, deletion, renaming, and permissions management**. It also **maintains metadata about files/directories**. When **read or write request is made**, the **file system translates these operations into a low-level operations that the operating system can understand**.

And the **operating system**, as we mentioned earlier, acts like an **intermediate layer** between the **programs** and **hardware devices**. It provides **commands to the low-level interface** and **allows the file system** to **interact with the hardware**. **Memory management, process scheduling** are also **handled in here**.

**Low-level interface** refers to the **low-level software components** that **enable communication with the IO devices** such as monitors, mouses, disk drives. It contains components such as **device drivers, hardware interfaces and communication protocols, direct memory access controllers, interrupt controllers**.

Now let's talk about the challenges behind managing IO devices.

# IO Devices: Challenges

Different IO devices perform a wide range of different tasks. 

**Some** of these **devices** might be **input devices** such as keyboard, mouse, or SCANner since they receive input from the user. **Some** of them, such as printers, speakers, display might be labeled as **output devices** since they show some kind of output to the users. 

And **some** of these devices such as hard disk drive, solid state drive, etc. might be **storage devices**.

In addition the **components with wich these IO devices communicate** with may **show great differences** as well. For example, we can observe **device-to-device, device-to-system, device-to-application,** or **device-to-user partnerships**. 

The **rate** at which they **transfer data** may be **different across different IO devices** as well. 

All of these diversities **makes it very hard to design a single interface and management system** that is **valid for all the IO devices** and that can **accept the new devices** or that can **scale as needed (expandability).**

Another **challenge** is **designing an IO system**. For instance, it is **hard to design an IO system that is** flexible and that can accept the new devices or that can scale as needed (expandability). 

Adding the **ability to handle device failures** and **maintain data integrity to the IO system (resilience)** is difficult as well. 

Also, **different IO devices** are **used by different users**. And **each of these users may have different requirements**. **Designing an IO system** that **meets all of these requirements and expectations might be challenging**. 

The **performance** of the **IO operation** is **affected by** many different factors: 
- the **time** it **takes to access data** from an IO device **(access latency)**
- the **amount of data transferred from the IO device to the system** or **from system to the IO device** in a given time period **(throughput)**
- the **type** and **speed of the communication channel** (e.g., bus, network) **between the IO devices and the system**.
- the **organization and management of different memory channels** (e.g., cache, main memory, storage) **(memory hierarchy)**
- the **operating system** (it plays an important role in terms of managing IO devices, and scheduling IO operations)

```
+-----------+                  Interrupts
|    CPU    |<---------+-----------------+----------------+          
+-----------+          |                 |                |       
      |                |                 |                |        
+-----------+          |                 |                |
|   Cache   |          |                 |                |
+-----------+          |                 |                |
      |                |                 |                |
+----------------------------------------------------------------+
|                              Bus                               |          
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

Bus in here there is a hardware component and it consists of a set of parallel wires on the motherboard along with supporting circuitry and protocols. These wires carry electrical signals and through these signals data, address, and signals are carried between the CPU, memory, and IO devices, and communication between these components is handled this way. 

**IO controller**, also known as peripheral controller, is another **hardware component**. It **manages the communication and data transfer between the CPU and IO devices such as disk, network**. It acts like an **intermediate layer between the IO devices and CPU** and thanks to these IO controllers, the CPU doesn't have to control & communicate with the IO devices directly. 

```

                                  +------------+    +-------------+    +--------------+
                                  |  Monitor   |    |  Keyboard   |    |  Hard Disk   |  
                                  |            |    |             |    |    Drive     | 
                                  +------------+    +-------------+    +--------------+
                                         |                 |                  | 
+----------+    +------------+    +------------+    +------------+     +--------------+
|   Main   |    |    CPU     |    |   Video    |    |  Keyboard  |     |   Hard Disk  |
|  Memory  |    |            |    | Controller |    | Controller |     |   Controller |  
+----------+    +------------+    +------------+    +------------+     +--------------+
     |                |                  |                 |                  |
     |                |                  |                 |                  |
+-----------------------------------------------------------------------------------------+
|                                            Bus                                          |
+-----------------------------------------------------------------------------------------+

```

As we can see above, **IO controllers** are **physically connected** to the **memory IO interconnect (bus)** on the motherboard. They have **dedicated interfaces and ports** that **plug into the bus** and **this allows the IO controllers to send and receive signals over the bus**. They **communicate with the memory and CPU through this bus**. The **bus** in here **enables** the **exchange of data and signals between IO controllers and the rest of the system**.

When the CPU needs to communicate with keyboard, for instance, it sends commands and data to the keyboard controller over the bus. The keyboard controller receives these commands and data from the bus and translates them into the keyboard-specific signals and protocols. Similarly, when the keyboard needs to send data to the CPU or memory, the keyboard controller receives the data from the keyboard and sends it over the bus to the CPU or main memory.

Here is more detailed data flow between different components: 

1) When the CPU executes an instruction or tries to access data, it checks the registers first.
2) If the data that is required by the CPU is not found in these registers, then the CPU checks the cache.
3) If the data that is required by the CPU is found in the cache, this data is retrieved from the cache to the CPU so that the CPU can processes it.
4) If the data that is required by the CPU is not found in the cache, the CPU requests the dat from the main memory. And then the main memory sends the requested data to the CPU. The copy of the data is stored in the cache as well so that it can be accessed faster in the future.
5) If the CPU wants to communicate with an IO device, it sends commands and data to the IO controller of that device. And the IO controller handles the data transfer between the CPU and IO device.
6) Data is sent to the CPU with IO controller. And then the CPU processes this data and store it in registers, cache or main memory.

One note is that **IO device controllers** can **generate interrupts** to **notify the CPU** about **important events**. For example, while a code is running in the program, if the user clicks the interrupt button with his mouse and interrupts the running of the program, or if an IO operation is completed naturally, the interrupts are generated and the **IO device controllers send these interrupt signals to the CPU using the bus**. **Once the CPU receives these interrupt signals**, it **invokes the appropriate interrupt handler** routine to **process the interrupt** and then **communicate with the IO device controller**.

So if we consider the IO controller to be part of an IO device, we can say that an IO device has two main components: **mechanical component** and **electronic component** 

**Mechanical components** are the **physical components** that are **used in the IO devices** to **perform some functions**. Mouse ball, scroll wheel can be given as examples of mechanical components. But as we might guess, many modern IO devices don't have these kinds of mechanical components anymore since they are replaced with electronic equivalents 

**Electronic component** consists of the **electronic circuitry** and **IO device controllers** that manage the functionality of the device and handle the communication between the device and the rest of the system. 

# Controller and Device

So we talked about IO device controllers. Each of these **IO device controllers has few registers**. By **writing data to registers** and **reading data from them**, the **operating system can control the IO device**. 

There are also **buffers in the IO device**. They are the **sections of memory within the device** and they play the role of **temporary storage areas**. They **hold the data that is transferred from the IO device to the operating system or from the operating system to the IO device**. And the **operating system can read data from these buffers or write data to them**. 

The **operating system** **needs to know** a couple of things **to manage the data transfers from/to these buffers**: 

- **location address of the buffer**: This specifies where the buffer is located in the memory.
- **location address of the IO object**: IO devices often work with specific units of data. These can be disk sectors (each sector is a fixed-size block of data that can be read or written as a single unit), video frames (each frame represents a single image or a portion of image displayed on the screen), etc. and they are called IO objects. The location of an IO object refers to the address that identifies where the IO object (e.g. disk sector, video frame, etc.) are located within the IO device's address space.
- **size of data to transfer**: When data is transferred from the operating system to the IO device or from the IO device to the operating system, the size/the amount of the data that will be transferred from/to buffers must be known by the operating system. Because this ensures that the appropriate amount of data is transferred and prevents buffer overflows or underflows.

Okay but how does this **communication** happen **between** the **control registers and buffers** ? There are two ways: 

1) **IO Port Space**
2) **Memory-Mapped IO**

## IO Port Space

**IO port** is a **physical or logical interface** and the **data** is **transferred from the CPU to the IO device** or **from the IO device to the CPU through this interface**. A physical interface in here refers to the actual and physical hardware connection and the data is transferred through this connection. **USB ports, ethernal ports, HDMI ports** can be given examples of physical interfaces. 

Logical interface, on the other hand, refers to a representation of the connection between the CPU and IO devices. It defines the rules, protocols, and formats used for data exchange between the IO devices and CPU. 

**Each IO port** is **associated with** a **specific IO device**. For example, we observe separate IO ports for keyboard, mouse, display output etc. **These IO ports are associated with registers**, and the **CPU communicates with the IO devices using these registers**. 

And the **set of all possible IO port numbers** **assigned to the control registers of the IO devices in the system form the IO port space**. The **IO port space is an address space** **separate from the memory address space** that is used by the CPU. Each IO device has its own range of IO port numbers allocated within the IO port space.

**IO ports** are **accessed** with **specialized IO instructions** or **commands** that are **provided by the CPU**. These **instructions** or commands **specify** the **address of the port** to be **accessed** and **direction of data transfer**. 

We can see some examples of these instructions in below: 

```
MOV DX, 0x3F8 :  Set the IO port number.
IN AL, DX     :  Read a byte from the IO port into AL
```

```
MOV DX, 0x3F8  ; Set the IO port number 
MOV AL, 0x42   ; Set the data to be written
OUT DX, AL     ; Write the byte from AL to the IO port
```

Note that an **IO port number** in here refers to a **numerical identifier** that is **assigned to the a specific IO port**. **CPU uses these IO port numbers to identify and access a specific IO port.**

**Control registers** are **special registers** that are **located within the IO device controller**. They are used for configuring, controlling, and monitoring the behavior of the IO device. They cannot ba accessed by the CPU directly. For the communication to happen, the CPU uses specific IO port numbers within the IO port space that are assigned to each control register. 

In summary, IO Port Space is a method that is used to handle the communication between the CPU and IO device. It is an address space that is separate from main memory address space. And in this address space, there are IO Port Numbers. When CPU wants to write data to an IO device, for instance, it chooses the specific IO Port Number from IO Port Space, sends this data to that IO Port. Because each IO Port is associated with the registers of the IO device (including control registers), we can write data to the IO device from the CPU by sending the data to the IO Port. Through this way, the data can be written to the control register that is associated with the IO Port and can be part of the IO device this way. We can handle the other IO operations in a similar way. 

When IO request is made, CPU writes instructions to the control registers in the IO device controller. These instructions refer to the operation that should be performed. The IO device controller interprets these instructions from its control registers and starts executing these instructions. If data needs to be transferred between the IO device and main memory, the IO device can interact with the main memory through various methods: IO port space, memory mapped IO, or direct memory access (DMA). And once the data transfer and IO operation is done, the IO device controller updates its status registers to indicate that the operation is done and notifies the CPU by generating an interrupt. 

So there is a control register in the IO device controller and basically the instructions of an IO operation is written to here by the CPU and then the IO device controller uses whatever the instruction is in its control registers and execute it. And the IO operation is executed by the IO device controller (not by the CPU). And CPU writes the information to the control register of IO device controller through the IO port that is associated with that specific IO device controller. Here is how this process works in step by step: 

1) The CPU prepares the instructions and data required for the IO operation.
2) The CPU determines the IO port number associated with the target I/O device controller.
3) The CPU performs a write operation to the specified IO port.
4) The write operation transfers the instructions and data from the CPU to the IO port.
5) The IO device controller, which is connected to the IO port, receives the information.
6) The information is stored in the appropriate control registers within the IO device controller.
7) The IO device controller interprets the instructions and data from its control registers and executes the requested IO operation accordingly.

Control registers may store information such as 
- current state/status of the IO device
- commands/instructions for the IO device
- configuration parameters that determine how the device operates (e.g., information about operating mode such as input mode, output mode, or bidirectional mode, communication protocols, timing-related aspects, etc.)
- interrupt configuration and status
- etc.

In addition, one note is that IO port space is protected and only the kernel can access to the IO port space. And the kernel uses special privileged instructions to access to the IO port space. These instructions can only be executed in the kernel mode. We can see some examples of the privileged instructions in below: 
- `in portnum, target`: It reads data from the IO port portnum and stores it in the target register or memory location.
- `out portnum, source`: This writes data from the source register or memory location to the IO port portnum.

Here portnum parameter represents the IO port number of the control register that is accessed. 

User-level applications and programs cannot access to the IO port space directly. They must do a system call. This protection is necessary because we want to prevent unauthorizied access to the IO devices and see that IO operations are done in a controlled manner. 

## Memory-Mapped IO

This is another method of handling **communication** between the **IO devices** and **CPU**. The communication is done by **mapping** the **IO device's control registers** and **status registers** into the **main memory address space** **of** the **CPU**.

So in this method, **a portion of the main memory address space** is **reserved for the control registers** of the **IO devices**. The operating system basically assigns some specific memory addresses to these control registers and then **CPU can be able to read and write to these addresses in the main memory address space using regular memory load and store instructions**. 

When we were using **IO port space method**, we were using **separate instructions** that are **designed for the IO operations specifically**. These **instructions** were **distinct** **from** the **instructions of accessing to the main memory address space** and they were being **used to communicate with the IO devices**. 

However, **these separate instructions are not needed anymore** when we **reserve a portion of the address space for the IO operations** in **memory-mapped IO method**. Also **in the IO port space**, an **address space that is separate from the memory address space was reserved for the IO devices** and **each IO device** was **being assigned an IO port numbers within this IO port space**. So **when CPU** **wanted to access the control registers** **of the IO devices**, it was **using special IO instructions** (e.g. in and out instructions) to **specify the IO port addresses**. 

In **memory-mapped IO**, each IO device's registers are mapped to a specific address in the main memory address space through pagetable and with this way, **no special IO instructions are required in this method**. 

When the CPU wants to perform a load operation or store operation on IO device's corresponding control registers in the memory address space, the IO device itselfs monitors these memory accesses. And the range of memory addresses IO device should monitor is predetermined. When a load or store operation is requested within this range, the IO device acts accordingly. 

One note is that: as we explained, **memory mapped IO** **treats control registers** of the IO devices **as memory addresses**. Therefore, **CPU caches can try to cache the values of these control registers from the main memory address space**. And **these cached values** **may not reflect the actual state of the IO device**. This is because **IO devices can update their control registers independently of the CPU, and the cached values in the CPU may not be aware of these updates**. In that kind of case, we **observe data corruption** and **incorrect behavior**. 

To solve this problem, we can use a mechanism that **disable caching operation** **for certain memory regions**. We can use a **"cache disabled bit"** in the **PTE** and **make the memory addresses that correspond to IO device registers non-cachable**. Through this way, we can ensure that **CPU does not cache the values read from these addresses.** and it will always **read the latest values directly from the IO device instead of relying on cached copies**.

The modern computers today use memory-mapped IO method in general.

### Advantages of Memory-Mapped IO 

1) Because **IO devices can be accessed using a regular load and store instructions**, **device drivers** (in other words software/programs that control and communicate with hardware devices) **can be written entirely in a high-level language like C** and there is **no need to use specialized assembly instructions/code to interact with devices**.
2) **As long as we keep the memory addresses assigned to the control registers of the IO device controllers out of the memory addresses** that assigned to the user-level applications, **no special protection is needed**.
3) Because we map the control registers of the IO device controllers to the memory address space, **any CPU instruction that reference to these address spaces** (e.g., read, write, load, store etc.) can be used to access/manipulate the control registers of the IO device controllers as well. This basically simplifies the programming model because developers can now use the same instructions for both memory operations and IO device communication.

# Interrupts

```
+-----+   3) CPU responds to the interrupt    +--------------+   1) IO operation is finished 
|     |-------------------------------------->|  Interrupt   |<-------------------------------- Disk
| CPU |                                       |  Controller  |<-------------------------------- Clock  
|     |   2) Controller issues interrupt      |              |<-------------------------------- Keyboard 
|     |<------------------------------------- |              |<-------------------------------- Printer
+-----+                                       +--------------+
   |                                                 |
   |                                                 | 
+-----------------------------------------------------------------------------------------+
|                                            Bus                                          |
+-----------------------------------------------------------------------------------------+
```

**Anytime an IO device wants attention**, it **causes an interrupt**. And one of the times when the IO device wants attention is **when the IO device finishes its operation**.

## Interrupt Controller

When an interrupt is generated, it is sent to interrupt controller which is basically a hardware component that manages the interrupts coming from different devices and sources. And the interrupt controller issues the interrupt and sends it to the CPU. And **CPU detects the interrupt**, **saves the current state of the execution**, and **responds appropriately** for that interrupt. 

Note that **interrupt controller** and **interrupt handler** are **not the same thing**. The **interrupt controller is a hardware component** that **manages and prioritizes interrupts coming from various devices and other sources**. **Interrupt handler**, on the other hand, is a **software routine** that is **executed** by the **CPU** when it **receives an interrupt**.

### Advanced Programmable Interrupt Controller (APIC)

PIC is a type of **interrupt controller** that is basically **responsible from receiving interrupt requests** from various device controllers and **forwarding them to the CPU**. 

When an **IO device controller** wants to **send an interrupt**, it **sends an interrupt request to this programmabe interrupt controller**. All the interrupt requests coming from device controllers are sent to the programmable interrupt controller.

The programmable interrupt controller then **sends the interrupt request** that has the **highest priority** **to the CPU**. And the **CPU acknowledges that it received interrupt request and takes some necessary actions**. 

```
       +-----+
       | CPU |
       +--+--+
         Ʌ |
         | |
     IRQ | | ACK 
         | v
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
         | DCa |   |   |     |     |         |   
         +-----+   |   |     |     |         |   
                   |   |     |     |         |   
         +-----+   |   |     |     |         |          
         | DCb |----   |     |     |         |   
         +-----+       |     |     |         |   
                       |     |     |         |   
         +-----+       |     |     |         |   
         | DCc |--------     |     |         |   
         +-----+             |     |         |   
                             |     |         |   
         +-----+             |     |         |        
         | DCd |--------------     |         |   
         +-----+                   |         |    
                                   |         |     
         +-----+                   |         |         
         | DCe |-------------------          |    
         +-----+                             |     
                                             |           
            .                                |   
            .                                |           
            .                                |   
                                             |   
         +-----+                             |     
         | DCh |-----------------------------+
         +-----+

```

But the **issue** with the PIC is that the **hardware lines, physical electrical connection or a signal path between the IO device and programmable interrupt controller are too limited** because of pin count restrictions on the CPU and motherboard. Because of this, as the **number of devices in a system increases**, the **limited number of interrupt lines becomes a bottleneck**.

That's why we can take a look at **another mechanism/method that can handle the interrupts.**

### Message Signaled Interrupts

In traditional interrupt systems, IO devices send a physical interrupt line to the CPU when to notify it about the interrupt. With message signaled interrupts, however, a special message is sent to the CPU by the IO device.

In message signaled interrupts, the **IO device writes the data that describes the interrupt to the designated memory-mapped IO address**. And the **act of writing the data to this specific memory address triggers the interrupt**. This mechanism is called **message signaled interrupts**. 

The **PCI (bus)** **detects** this **write operation** and then **delivers the interrupt to the appropriate CPU** based on the information written to the memory address. 

**Message signalled interrupts provide high degree of programmability in interrupt handling.** In other words the **IO devices can be configured to create specific interrupts based on their requirements when we use message signalled interrupts**. 

### Complete Interrupt System 

## Issues with Interrupt Processing 

In old systems, **whether or not there was a pending interrupt** was being **checked** **after** **each instruction was finished** its execution. So **after executing some instructions**, **if an interrupt occurred**, this means that **all the instructions up to that instruction after which interrupt was generated had been executed completely** and **no instructions were executed yet after that instruction.**

This may not be the case in modern computers. 

Today, modern CPUs use a method that is called **pipelining**. Basically, **the execution of an instruction is broken into multiple stages** (e.g., fetching, decoding, executing, etc.) **These stages** are **overlapped** and **this allows the execution of multiple instructions simultaneously.** 

```
Fetch unit -> Decode unit -> Execute unit
```

And **when** an **interrupt occurs**, we might **see some instructions that have completed their executions**, **some instructions waiting to enter the pipeline of fetching + decoding + executing**, and **some others that are in the middle of their executions** etc.

**When an interrupt occurs**, **the value of the program counter will be pointing to the address of the next instruction** **that will be fetched** **instead of pointing to the address of the instruction that has just completed its execution**. Because, the program counter is incremented to point to the next instruction to be fetched before the current instruction completes its execution. The PC is not updated to point to the instruction that has just completed execution.


In the situation like below,

```
Fetch unit -> Decode unit                        Execute Unit
                          \                    /
                           -- Holding Buffer --  Execute Unit                     
                          /                    \  
Fetch unit -> Decode unit                        Execute Unit
```

**some instructions that started a long time ago** may **still be in the holding buffer** or **waiting to enter the execute unit** and that's why **they may not have started**. **Other instructions** that **started recently** may be **almost done** and **when the interrupt occurs**, **many instructions may be at various states of completeness** and **the relationship between them and the program counter might be weak because the program counter may not directly correspond to the instruction that caused the interrupt.**

**An interrupt after which we can observe a well-defined state is called a precise interrupt**. These kinds of interrupts have the following 4 features: 

1) **The program counter is saved in a known place** (e.g., a special register that is only accessible through kernel mode. _(Saving program counter allows the CPU to know where to continue execution after interrupt is handled)_
2) **All instructions before the instruction that is pointed by the program counter have finished their executions.** _(This means that any changes these instructions made to the CPU's registers or memory are completed. And no incomplete modifications exist at that moment)_
3) **There is no instruction beyond the instruction that is pointed by the program counter that started its execution**. _(This ensures that the interrupt does not affect the execution of the next instructions)_
4) **The execution state of the instruction that is pointed by the program counter is known**. _(In other words CPU knows whether the instruction completed its execution, just started its execution, etc. Knowing these is helpful for handling the execution after the interrupt is handled)_

**If** the **CPU** **handles** **parallel** and **out-of-order execution**, if it can **execute multiple instructions simultaneously**, ensuring that **interrupts** are **precise** is **crucial**. Because **precise interrupts can help us to maintain a consistent and predictable state even when the instructions are executed out-of-order or in parallel**.

If an interrupt does **not meet these requirements**, it is called **imprecise interrupt**. And we can see how they look like in below:

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

## Goals of the IO Software
- **Device independence**: We should be able to **write programs** that can **access to any of the IO device** **without having to specify the device in advance**. For instance, a program should be able to **read** a file **from** **DVD**, **hard disk**, **USB stick** etc. **without being modified for each of them separately**. Or when someone type ```sort <input> output``` this **should work with all kinds of disks or keyboard** and the **output should go to any kind of disk or screen**. **If problems occur** due to the **underlying differences** in these IO devices, it is the **operating system's responsibility to take care of these problems.**
- **Uniform naming**: The **name** of a file/device should be **string/integer** and it should **not depend on the IO device**. Through this way, users can access files using the **same naming convention** **without having to know which specific device corresponds to that file**. For example, if a USB stick is mounted on top of _/usr/documents/_, copying a file to the _/usr/documents/_ basically copies that file to the USB stick. Through this way, **all files are addressed with a path name which makes everything convenient.**
- **Error handling**: The goal is to **handle** the **errors** as **close to the hardware as possible**. If **IO device controller detects an error**, it should **first try to fix the error**. If it is something that it **cannot solve**, then the **IO device driver should try to handle the problem**. One way to handle it might be **reading the block again** if the error is a read error since sometimes some problems may go away if the operation is repeated. Most of the times, **errors can be recovered at a low level without users being aware of them.** And handling the errors close to the hardware allows for quick detection and resolution of issues.
- **Handling shared and dedicated devices**: **Some IO devices** (e.g., disks) can be **used by many users at the same time**. These are called **sharable devices**. But this is **not valid for some other IO devices** (e.g., printers) which are called **dedicated devices**. An IO software must ensure **proper synchronization** and **coordination** among **competing processes/threads** for **shared devices**. And for dedicated devices, IO software should provide exclusive access and prevent conflicts from other processes.

Also, if the **IO software initiates an IO operation** and then **waits for this IO operation to complete before proceeding further**, this is called **synchronous** IO. If the IO software **initiates an IO operation**, and then **continue executing other tasks instead of waiting** for that IO operation to be finished, this is called **asynchronous** IO. 

And another note is that most of the times, the **data coming from the IO device cannot be stored in wherever its final destination is directly**. So in those cases, we should **store** these data in **temporary** **locations** which are called **buffers**. Buffers are also useful since they help the IO software to perform IO operations in large chunks instead of doing small data fransfers frequently.

# Three Ways of Performing IO 

## Programmed IO 
The simplest form of handling IO operations is to **make the CPU to do all of these IO operations**. This method is called **programmed IO**.

Here is how programmed IO works step by step:
1) CPU initiates the IO operation by sending a command to the IO device. This command is about specifying the IO operation (e.g., read, write)
2) CPU then continuously checks if the IO device is ready for data transfer (busy-waiting)
3) Once the IO device becomes available, data transfer is made by the CPU.
4) This process (checking the availability of IO device continuously and performing data transfer) continues until entire IO operation is complete.
5) Once the entire IO operation is complete, CPU resumes the execution of the main program.

Let's no give an example. Assume that you want to **print** the string **"ABCDEFGH"** with printer. 

**In the first step**, the **IO software stores this string in buffer in user space**. Then the **user process makes a system call to open the printer**. **If** the **printer** is **currently being used** by another process, this **system call will fail** and either **return an error** to the user process **or will block its system call** **until the printer becomes available** depending on the OS. 

**Once** the **printer** is **available** to use, the **user process makes a system call** and **asks the printer to print the string on the printer**. After this system call, **the OS copies the buffer** that **contains** the string of **"ABCDEFGH"** **from user space to an array in kernel space**. Let's call this array `p`. 

It then checks if the printer is available at that moment. If the printer is not available, the operating system **waits** **until it becomes available**. **Once** the printer is **available**, the **OS copies the first character to the printer's data register using memory mapped IO**. 

**Copying the first character to the printer's data register activates the printer**. And after that **printer prints the first character "A" and marks the second character "B" as the next character to be printed**.

The key feature of **programmed IO** is that the **CPU continuously checks the IO device (printer) to see whether it (printer) can accept a new character to print** after outputting a character. This behavior is called **busy waiting** or polling. The process is visualized in below:

```
copy_from_user(buffer, p, count);
for (i = 0; i < count; i++) {
    while (*printer->status_register != READY) {};
    *printer->data_register = p[i];
}
return_to_user();                

+--------------------+
|     User Space     |
|                    |
|                    |
|                    |
|     +--------+     |
|     |ABCDEFGH|     |
|     +--------+     |              Page
|  (String to print) |          +----------+
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

Therefore, even though the programmed IO is a simple method to handle IO operations, it is **inefficient** in **systems** where **CPU has other works to do due to busy waiting**. But **if the time** that is **needed to print a character is short**, or **in other systems where CPU does not have other things to do**, **busy waiting and programmed IO is okay to use**.

## Interrupt Driven IO

**When the IO device is ready for data transfer** or **when it completes the IO operation**, **CPU can be notified about these with interrupts**. We call this method **interrupt driven IO**. And with this method, the **CPU won't have to do busy waiting** and it can **handle other tasks while waiting for the IO device** and **this increases the efficiency**. 

Basically **when an IO operation is initiated by a process**, **system call is made to the operating system**. And **if the IO device is not ready to do the required IO operation**, the **system call is blocked** and **marked as waiting** by the operating system. In the mean time, the **operating system continues executing and scheduling other processes** **while the IO operation is waiting**.  

Once the **IO device becomes ready** to run the IO operation,  **it raises an interrupt** and **this interrupt is sent to the CPU** which indicates that the IO device requires attention. **After CPU** is **notified** about the fact that **IO device is ready to run** the IO operation, **CPU first saves its current execution context**. Then the **interrupt handler determines which IO device raised the interrupt** and then **takes appropriate actions**. If the **interrupt handler decides** that the **IO device is ready for data transfer**, the **CPU initiates the transfer between the IO device and memory** and it **copies the data from memory to IO device or IO device to memory**. 

**Using interrupts** in this scenario **prevents CPU from busy waiting** which would waste CPU cycles.

**After the data transfer is completed** **by** the **CPU** from the memory to IO device or IO device to memory, **the process is unblocked** and **scheduler is invoked**. And then the scheduler **decides which process should run next** based on the scheduling algorithm and other factors, such as process priorities and resource availability. 

## Direct Memory Access (DMA) 

In **programmed IO** and **interrupt-driven IO**, the **IO device controller was relying on the CPU** to **initiate** and **control** the **data transfer** between the **IO device** and **memory**. 

The reason why the CPU is involved in these data transfers is that the IO devices themselves do not have the capability to autonomously transfer data to or from memory without the CPU's control and coordination in these system. IO devices are designed to perform specific tasks and rely on the CPU to manage and orchestrate the overall system operation.

But the thing is **it is not efficient for the CPU to request data from the IO device one byte or one character at a time** and handle the data transfer this way since this is quite **time-consuming** and **inefficient**. 

And **DMA** is a method that is used to **allow the IO devices to transfer data** **to/from the main memory directly**. In this scenario, **CPU** is **not used during the data transfer**. And this process is **handled by the DMA controller**. 

**DMA controller is a hardware component**. It is typically **integrated** into the **motherbaord**. In some cases, we can see them **integrated to the IO devices such as disk controllers**. 

**DMA controller is connected to the system bus** and therefore **it can access to the main memory directly**. And through this way, it can **initiate and manage data transfers between IO devices and main memory directly.** 

When an IO request is made, the process typically involves the following steps:

1) The **CPU initiates an IO request** by **writing instructions and parameters to the control registers of the IO device controller**. These instructions specify the operation to be performed, such as reading from or writing to the device.
2) The **IO device controller interprets the instructions stored in its control registers** and **starts executing the requested operation**.
3) If the **IO operation involves transferring data between the IO device and main memory**, the **IO device controller interacts directly with the main memory**. And it does this through **direct memory access (DMA).**
4) With **DMA**, the **IO device controller can access the main memory independently**, **without the constant intervention of the CPU**. The **CPU sets up the DMA operation by providing the necessary information**, such as the **memory address** and the **amount of data to be transferred**.
5) The **IO device controller** performs the **data transfer between the IO device and main memory**. It reads data from the IO device and writes it to the designated memory location through DMA, or reads data from memory and sends it to the device, depending on the IO operation.
6) **Once** the **data transfer** is **complete**, the **IO device controller updates its status registers** to **indicate** the **completion of the operation** and may **generate an interrupt to notify the CPU**.

**DMA controller** contains **several key components**: 
- **Address registers**: Holds the address the data will come from and destination address.
- **Data registers**: It stores the transferred data temporarily. 
- **Data count** : Keeps track of the number of characters or bytes remaining to be transferred.
- **Control logic**: This is used to control the overall operation of the DMA controller. The control unit receives DMA request and sends DMA acknowledge. It generates interrupts when the data transfer is completed.
- **Bus interface**: The bus in here allows the DMA controller to communicate with the CPU, main memory, and IO devices.

Here is an example of how DMA works:

**When data transfer** is **initiated**, **CPU programs** **the DMA controller** by **writing the necessary information into the control registers of the DMA controller.** _(The control registers in the DMA controller contains bits for direction of the data transfer, data transfer size, interrupt enable, transfer mode -- single transfer mode for transferring one byte at a time or block transfer mode for transferring a block of data), etc.)_

Then the **DMA controller sends** a **request** to the **disk controller** to **transfer** **data** **from disk** **to the main memory**. 

Next, the **disk controller acknowledges this request** and **prepares the data to transfer it to main memory**. And the **data** is **stored** in the **temporary storage in the mean time**. 

Then the **data** is **transferred** **from the buffer in the disk to the main memory**. As the data is being transferred, **CPU can continue executing other tasks because it is not involved in this transfer process**. 

And **lastly**, **when the data transfer is completed**, an **interrupt is generated by the DMA controller** and **CPU takes any necessary actions** **after learning that the data transfer is completed**.

We can see the **visualization of this process** in below:

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
|    |     |                    |  | |   | |<-------------------------    |      |      |          |    |        |
|    |     |                    |  +-|---|-+  |                    |      |      |      |          |    |        |   
+----|-----+                    +----|-+-|----+                    +------|--+---|------+          +----|--+-----+
   | |                               | | |                                |  |   |                      |  | 
   | +-------------------------------+ | +--------------------------------+  |   +----------------------+  |   
   |    4) Interrupt when data         |       2) DMA requests data          |     3) Data transferred     |      
   |        transfer is done           |        transfer to memory           |                             |  
   +-----------------------------------+-------------------------------------+-----------------------------+       
                                                   BUS
```

# Alternative DMA Configurations

## Single Bus - Detached DMA

```
----------+--------------------+--------------------+--------------------+---------------------+--------------------+----------
          |                    |                    |                    |                     |                    |          
         CPU                  DMA                  I/O                  I/O                   I/O                 Memory
```

## Single Bus - Integrated DMA 

```
----------+--------------------+--------------------+--------------------+-----------
          |                    |                    |                    |   
         CPU                  DMA                  DMA                 Memory
                               |                   / \ 
                              I/O                I/O I/O   
```

## IO Bus 

```
                                             SYSTEM BUS
----------+--------------------+-----------------------------------------+-----------
          |                    |                                         |   
         CPU                  DMA                                      Memory
                               |              I/O BUS
-------------+-----------------+---+--------------------+----------------------------
             |                     |                    |
            I/O                   I/O                  I/O  
                             
```

# DMA and Memory Protection

As we learned previously, **DMA allows the IO devices** to **access to main memory directly**. Therefore, **we may observe unauthorized access to memory regions**, and **data corruption** **if** the **process is not properly managed**. 

**To address these issues**, we **use** a method called **IOMMU**. IOMMU is a component that **acts as a memory protection** and **translation layer** for the **DMA operations**. But how ? 

The operating system creates a **translation table** in the IOMMU. This **translation table maps the virtual addresses** that are **used** by the **IO devices** **to** the **physical memory addresses**.

If IO device tries to map the DMA to an address and there is no translation in the translation table, an interrupt/exception is raised.

The idea in here is similar the way **applications** are **restricted** **to specific addresses** in main memory address space **using pagetable** and **main memory unit** (MMU). 

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

# Operating System Software Layers for IO

```
         
    +--------------------------------+
    |     User-level IO software     |
    +--------------------------------+
    | Device-independent OS software |       
    +--------------------------------+
    |         Device drivers         |
    |         +----------------------+        
    |         |  Interrupt handlers  |
+---+---------+----------------------+---+
|               Hardware                 |
+----------------------------------------+
```

If we want to look from more detailed perspective: 

```
               User process       
                    |
+-------------------|--------------------------+----------------
|           +----------------+                 | 
|           |  User program  |                 |  User space
|           +----------------+                 |
+-------------------|--------------------------+----------------
|                   |                          |
|   +----------------------------------+       |
|   |   Rest of the operating system   |       |
|   +----------------------------------+       |
|       |           |               |          |
|   +-------+   +---------+     +------+       |  Kernel space
|   |Printer|   |Camcorder|     |CDRom |       |
|   |driver |   |driver   |     |driver|       |  
|   +-------+   +---------+     +------+       |
|       |           |               |          |
+-------|-----------|---------------|----------+----------------
|       |           |               |          |    
|       V           V               V          |
|  +----------+ +----------+  +-----------+    |
|  |Printer   | |Camcorder |  | CD-Rom    |    |  Hardware
|  |controller| |controller|  | controller|    |
|  +----------+ +----------+  +-----------+    |
|       |           |               |          |
+-------|-----------|---------------|----------+----------------
|       |           |               |          | 
|       V           V               V          |  Devices  
|    Printer    Camcorder         CD-Rom       |    
+----------------------------------------------+----------------

```

And here is the **how the workflow looks like** between the **IO software** and the **hardware of the IO device**: 

1) The **IO software initiates an IO request** by making a system call.
2) The **operating system receives the IO request** and **determines which device driver is responsible for handling the request** based on the device type and the nature of the operation.
3) The **operating system forwards the IO request to the appropriate device driver**.
4) The **device driver translates the IO request into device-specific commands** and **communicates with the device controller**.
5) The **device controller receives the commands from the device driver** and **interacts directly with the IO device to perform the requested operation**.
6) The **device controller transfers data between the IO device and main memory**, either **through direct memory access (DMA),** or programmed IO.
7) If the IO operation **generates an interrupt**, the **device controller notifies the device driver through the interrupt mechanism**.
8) The **device driver handles the interrupt**, **performs any necessary processing**, and **communicates the result or status back to the operating system**.
9) The operating system receives the result or status from the device driver and returns it to the IO software.
10) The **IO software receives the result or status and continues its execution**.

## Device Drivers 

**Device drivers** are **software modules** and they are **prepared specifically for each IO device**. They basically **provide an interface** so that the **operating system can interact with the devices through this interface**. 

The **codes in the device drivers are tailored to control and communicate with a particular IO device**. **They encapsulate the low-level details of the IO device (hardware)** and **abstract them from the operating system**.

They are **responsible** from **reading data** from the **registers in the IO device controllers** and **writing data** to them. They **include** **interrupt handlers** which are the **procedures** (e.g., processing the interrupt, communicating with the IO device, performing any other necessary actions etc.) that are **followed after an interrupt** is **generated**.

**Device drivers** are provided by the manufacturer of the IO devices and **integrated** to the **operating system's kernel**. They are integrated either **as built-in components** or as **loadable modules** which basically **allow the device drivers to be loaded into the kernel**. **If** they are **integrated as built-in**, however, they are **compiled** **to the kernel** directly and they are **always available**.

In addition, the **device drivers** must **follow** **standard interfaces** that are **defined by the operating systems**. 

These **interfaces** are **different in block devices** and **character devices** because the way these devices **process the data** is **different**. 

The **drivers** of the **block devices** (e.g., hard drives, USB storage devices) must **follow a specific interface** that **includes operations like reading and writing blocks of data**. 

The **drivers** of the **character devices** (e.g., keyboards, serial ports) must **follow another type of interface that deals with individual characters of bytes of data**.

Main functions of IO device drivers:
- IO device drivers are responsible from initializing the IO device they control. Initialization in here basically means setting up the necessary configurations, registers, and parameters that are required for the IO device to function properly. Initialization in here ensures that the IO device is in ready condition before it can be used by the operationg system & applications. 
- IO device drivers provide an abstraction layer between the operating system and the IO device. And the operating system commnuicates with the device driver using abstract read/write operations. And device driver receives these operations from the layer above (e.g., operating system) and translates these operations into commands that are specific to IO device. The device driver then executes these commands by communicating with the IO device controller
- Device drivers are responsible from handling interrupts that are generated by the IO devices as well.
- The interrupt is received by the IO device driver. And the IO device driver executes the interrupt handler routine. The interrupt handler performs tasks such as acknowledging the interrupt, retrieving data from the device, updating device status, or notifying the operating system about the interrupt event.
- IO device drivers also log events (e.g., status changes, errors, performance metrics, etc.) that are related to the IO device they control.
- IO device drivers is responsible from implementing & controlling power management features such as low-power modes or sleep states to conserve energy when the device is not used actively.

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

# Device Independent IO Software

There are **several capabilites** that **should be provided by** the **device independent IO software**: 

1) The **software should provide an interface** through which **different device drivers can interact** _(uniform interfacing for device drvers)_. The main goal in here is to **make all the devices appear the same to the operating system** **regardless of their specific hardware characteristics**. And we can do this by **functions for each group of devices that share similar properties** (e.g., **display devices, storage devices, network devices**, etc.) By **providing this uniform interface**, the **operating system** can **interact** with **different IO devices** **using the same functions** and this **simplifies** the **device management**. Also, the **device independent IO software layer maps the symbolic device names** (e.g., "printer", "disk", et.c) **to the appropriate device drivers**. When the **operating system** wants to **communicate** with a **device**, it uses its **symbolic name** and this **symbolic name** is **translated** to the **corresponding driver**. Through this way, the operating system can **refer** to  **devices** using **logical names** **instead of hardware specific details.**
2) It should **handle** **buffering of data transfer** between the IO device and operating system _(buffering)_
3) It should **report any errors** when they occur with the use of IO devices _(error reporting)_
4) It should be able to **allocate and also release the dedicated devices** when needed.
5) The **size of the blocks** provided by the IO software **for data transfer** should be **standardized** and **independent from the IO devices**.

# Examples of IO Devices

## Clocks 

### Clock Hardware

In **older computer systems**, the **clock was directly tied to the alternating current power line frequency**. 

The **alternating current power line frequency** was **determining the clock speed of the computer**. In these systems, **an interrupt was being sent to the CPU on every voltage cycle of the power line**. 

In other words, the **CPU was interrupted at a fixed frequency based on the power line**. This method is **simple** but **inflexible**. 

**It can reduce the CPU utilization because CPU might be interrupted very frequently**.

In modern computer systems, a **crystal oscillator** is **used** instead of relying on the power line frequency. The crystal oscillator **generates** a **stable** and **high-frequency clock signal**. 

It **produces** a **consistent oscillation** **at a specific frequency**. **This signal** is **fed** to the **counter** which is **decremented at each pulse**. **Once** the **counter gets to 0**, it **generates interrupt**.

### Clock Software

So basically, the main thing clock **hardware** does is to **generate interrupts at known intervals**. **Everything** **else** must be **done by the software** -- clock driver. The duties of the clock driver are like these: 

- Maintaining the time of day.
- Preventing processes from running longer than they are allowed to.
- Accounting for CPU usage.
- Handling alarm system call that are made by the processes.
- Providing timers that monitor microcontroller (?) programs to see if they are out of control or have stopped operating. These timers are called watchdog timers.
- Gathering statistics, monitoring and profiling.

## User Interfaces

### Keyboard

There is a microprocessor or microcontroller that is built-in in the keyboards. This microprocessor handles the functionality of the keyboard. An example of the functionality might be SCANning the key matrix which is basically an arrangement of keys in the keyboard in the row/column form. When a key is pressed, for instance, we see electrical connection between the corresponding row and column of the key matrix. 

When a key is pressed by the user or released, an interrupt is generated by the microprocessor of the keyboard. This interrupt is then sent to the motherboard's controller to indicate that an event has occurred that needs attention. And the keyboard driver reads the data from the IO port that is assigned to the keyboard to determine which key is pressed or released and any other information about this event. 

The data that is retrieved by the keyboard driver from the IO port is called SCAN code which typically contains 8 bits of information (7 bits in here are used to represent which specific key is pressed or released. The remaining 1 bit indicates whether the event is a key press or key release. 0 means that key is pressed and 1 means that key is released).

There are two main methods a keyboard software/program might follow to handle the keyboard input. These methods define how the program receives and processes the characters that are typed on the keyboard. 

In raw (noncanonical) mode, the program receives raw ASCII codes directly from the keyboard. In this method, when the key is pressed, the corresponding ASCII code is not preprocessed or interpreted and it is sent to the program directly. That's why the program has full control over the handling of each individual character. These characters can be processed in real-time as they are received. 

In cooked (canonical) mode, when the key is pressed, the keyboard driver handles intraline editing, backspace handling, etc. and then send the corrected lines to the program. In this mode, the program receives complete lines of input when the user presses enter instead of receiving the raw ASCII characters individually. When the input doesn't need to be handled as character by character individually, and when the program expects well formatted lines of input, this method is used.

And regardless of which mode is used, a buffer is needed to store the characters coming from the keybard temporarily.

### Mouse 

Mouse only indicates **changes in position** (delta x, delta y). 

# IO Software Layer

We want the **operating system** to **operate** **without being concerned/bothered** about the **low-level details of the interrupt handling process**. 

In other words, the goal is to **minimize the impact of interrupts** on the **overall system** and **keep the interrupt handling process confined to a specific part of the operating system**. 

That's why **interrupts are hidden** from most of the operating system so that **as little of the operating system as possible knows about them.** But **how to hide interrupts** ? 

Well the **execution of the thread** in the IO device driver **that initiates an IO operation can be suspended until the IO operation finishes** and **the interrupt is handled**. In other words, **after initializing the necessary data structures and registers for the IO operation**, **a thread in the IO device driver can start an IO operation** by sending commands to the IO device controller and **is blocked until the IO operation is completed**  and an interrupt is sent.

And **in the meantime**, the **IO operation is handled by the IO device controller** (not CPU). **Once** the IO operation is **completed**, it **generates an interrupt**. 

**After** this **interrupt is generated**, the **interrupt handler is invoked** to **handle the interrupt** and **perform post IO processing**. 

Then the **interrupt handler unblocks the thread in the IO device driver** that initiated the IO operation so that it can continue its execution from where it lefts off.

So in summary, thread in the IO device driver starts an IO operation, is suspended until IO operation is completed, and unblocked with an interrupt after IO operation is completed.

This method allows the **device driver** to **wait for the IO operation** **to complete without constantly checking for its completion**. 

And **for this method** to work, **IO device drivers should be structured as kernel threads or processes**. **Each driver should have** its **own state**, **stack**, **program counter**, etc. so that they can **operate independently** and **handle IO operations concurrently**.

# Main Functionalities and Responsibilities of Device Drivers 

## Character Drivers
- **Discovery**: Character drivers are responsible from discovering/identifying character-based devices that are connected to the system.
- **Read data**: Character drivers provide functions to read characters from the device.
- **Write data**: Character drivers provide functions to write characters to the device.
- **Interrupt management**: Interrupt management in character drivers is often much simpler compared to the interrupt management in disk storage and network cards. They are more like interrupt handling.

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
- **Throttling**: To control the consumption of resources, and managing traffic low, the speed, rate, or frequency of data transfer is limited/regulated intentionally.

# Summary 
- **Operating system** provides an **interface between the IO devices** and the **rest of the system**.
- The **IO** part of the operating system is **divided into several layers**.
  - **Hardware**: CPU, programmable interrupt controller, DMA, device controller, and the device itself.
  - **Software**: Interrupt handlers, device drivers (low-level software components that directly interact with and control specific IO devices), device-independent IO software, user-level IO software.
- Operating system **must expand as new IO devices are added**.

Device drivers vs IO software: 

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

This is one of the simplest algorithms that is used to determine the order of the IO operation to be processed. Basically, when a new IO request arrives, it is added to the end of a queue which is basically a data structure that stores IO requests in the order these requests are received. Each of these IO requests typically includes information like the block address in the disk that includes the required information, the type of operation (e.g., whether it is a read or write operation), etc.

And the disk controller processes the requests in this queue in order (e.g., the IO request that was added to the queue first is processed first). When an IO request is processed, the disk head moves to the location to the block address specified in the request and performs the operation (e.g., read, write). Upon the completion of this request, the disk controller moves to the next IO request in the queue

### Pros 

In FIFO, all IO requests are given equal priority and they are treated fairly. Even if a very urgent IO request arrives, it is not given a higher priority. 

Also, applications that submit IO requests in some specific order can expect these IO requests to be processed in the same order. In other words, the execution of IO requests is highly predictable and consistent.

### Cons 

Because IO requests are processed strictly based on their arrival time in FIFO, the physical location of the incoming IO request are not taken into account when determining which IO request should be processed next. That's why the disk head continuously moves between the innermost and outermost tracks. This continous moving back and forth across the disk surface is called **wild swing**. And because of this, the time it takes for the disk head to move from its current location to the requested disk block (this is also called seek time) tends to be high. Data that is accessed together or that is close to each other is likely to be accessed together in the future again but this is ignored in FIFO algorithm. The IO requests that are physically close to the current position of the disk head are not prioritized.

## Shortest Seek Time First (SSTF) 

In Shortest Seek Time First algorithm, the IO request that is closest to the current position of the head and that requires smallest time for the disk to rotate and position the requested sector under the disk head is chosen to be prcoessed in the next step. The way it works is that the IO requests are placed in a queue and each IO request contains information such as block address or the track number that needs to be accessed. And for each request in the queue, SSTF algorithm computes the seek time required to move the disk head from the current position to the requested track and computes how long it takes to rotate and position the requested track under the disk head. These two times are summed and then the IO request that has the shortest time is chosen from the current head position. 

### Pros

Because the IO requests that have the shortest seek time are always prioritized and processed first, the time that is spent for moving head from one location to another location is minimized. And this leads to improved disk performance and reduced time to access and retrieve requested data, in other words, faster access compared to FIFO. 

### Cons

If there are always IO requests that have short seek time, the IO requests for tracks that are far away from the current track may never get a chance to be processed. This causes unfairness and starvation and can be seen as a con.

In addition, unlike FIFO, the order in which the IO requests will be processed is not predictable since this order depends on the arrival time of these requests, the current location of the head and the seek time of these IO requests.

Also, we observe frequent switching and that may slow down the algorithm a little bit.

## SCAN

The behavior of the SCAN algorithm and the way it works is similar to the way an elevator works. The algorithm works by starting to move the disk head in one direction (either towards the inner edge or outer edge of the disk), processsing the IO requests in these directions until no IO request is left in that direction, reversing the direction and processing the IO requests in the reverse direction. 

After reversing the direction, it services the requests in in the reverse direction. When processing the IO requests in a direction, the IO request that is closest to the current position of the head is chosen. And once the last request is serviced in the reversed direction, the disk head reverses its direction again. 

One note is that the disk head always go to the end of the disk before reversing direction, regardless of whether there are pending requests at the end or not.

### Pros

Since the disk head moves in a specific direction and processes the IO requests in that direction, each IO request is processed in a certain timeframe without being starved for an extended period. 

Moving the head in one direction, handling the IO requests in that direction, and then reversing the head again and handling the IO request in this opposite direction, and following this cycle provides a more predictable performance compared to FIFO and SSTF. 

The variance in the waiting time is reduced compared to FIFO and SSTF algorithms.

### Cons

If there IO requests keep coming to the one of the end of the disk, the IO requests that are located at the other end may experience starvation. 
 
## Circular Scan (C-SCAN)

In C-SCAN the head moves only in one direction. After the head starts in a direction, it services the IO requests in that direction based on the shortest seek time. After reaching the last IO request in that direction, it basically returns back to the IO request at the beginning and continue servicing the IO requests in the original direction again. 

### Pros

The main advantage of C-SCAN algorithm over the SCAN is that C-SCAN provides more uniform waiting for the IO requests. By returning to the first IO request in the disk instead of reversing the direction, the algorithm ensures that thew waiting time for the IO requests is more evenly distributed. This feature is especially beneficial when there is a high number of IO requests in one end of the disk. 

By returning to the beginning of the disk after each sweep, the C-SCAN algorithm ensures that requests located at the beginning or middle of the disk have a chance to be serviced sooner.

The C-SCAN algorithm maintains the advantages of the SCAN algorithm as well such as reduced average seek time and fair servicing to the IO requests

### Cons 

We see that the disk head makes more movements compared to SCAN algorithm because it doesn't reverse the its direction after reaching the last IO request and it just turns back all the way up to the first point.

Just like SCAN algorithm, even if there are no requests that are left to be serviced at the end of the direction, the disk head moves to the end of the disk turnin back to the first IO request in the original direction.

## LOOK 

This is similar to the SCAN algorithm except that the head goes as far as the last request in the current direction unlike SCAN which basically tries to go to the end of the direction before reversing even if there are no IO requests at the end. 

Assume that the disk has tracks that are numbered from 0 to 99, and the disk head is currently at track 50. And let's say that the pending requests are for tracks: 10, 20, 30, 70, 80, 90.

In the SCAN algorithm:

The disk head moves from track 50 to track 99 (end of the disk), servicing requests for tracks 70, 80, and 90 along the way. At track 99, the disk head reverses direction and moves towards track 0, servicing requests for tracks 30, 20, and 10 along the way.

In the LOOK algorithm:

The disk head moves from track 50 to track 90 (last pending request in the current direction), servicing requests for tracks 70, 80, and 90 along the way.

At track 90, the disk head reverses direction and moves towards track 10 (last pending request in the opposite direction), servicing requests for tracks 30 and 20 along the way.

### Pros
The main advantage of LOOK algorithm over SCAN is that unnecessary disk head movement is avoided in here. And this tends to result in better performance and shorter seek time compared to SCAN algorithm.

Aside from this, the LOOK algorithm has the advantages of the SCAN algorithm as well and these are reduced average seek time, and more fair servicing to the IO requests.

### Cons

Finding the last IO request.

## C-LOOK 

It is similar to the LOOK algorithm in which the disk head moves in one direction and reverses after reaching the last IO request in that direction. But in C-LOOK, instead of reversing, the head returns back to the IO request at the beginning of the disk after reaching the last IO request and then services the IO requests in the original direction again. 

### Pros 

The disk head does not have to move until the end of the disk. This is beneficial when there is no IO requests at the end of the disk. 

We observe less waiting time for the cylinders that are just visited by the disk head. 

In addition to these, the C-LOOK algorithm has the advantages of the LOOK algorithm as well which are reduced average seek time, more fair servicing, low variance in waiting time.

### Cons

Finding the last IO request.

## FSCAN

The idea behind FSCAN is quite similar to the SCAN. The only difference is that the algorithm operates with two queues: active queue and add queue. We can see add queue as waiting queue. 

Any new IO request is basically added to this add queue. And IO is scheduled only from the active queue. If the active queue is empty, this means that there is no active IO operation and the IO requests that are waiting in the add queue is transferred to the active queue. Next, an IO is scheduled from the active queue depending on the current direction of the disk head and shortest seek time. 

Once the disk head reaches the end of the disk, the direction is reversed and IO requests keep being scheduled based on shortest seek time but this time in reverse order.

### Pros 

### Cons

## FLOOK 
This is similar to the FSCAN. Here we have maintain two queues as well. The only difference is that the disk only goes to the last IO request in th disk and only then reverses its direction.

### Pros

### Cons

## Deadline Scheduler

The algorithm assigns a deadline to an IO request whenever it receives that IO request. This deadline basically means the maximum time until which the IO request should be serviced. Through this way, the algorithm guarantees that each IO request will be processed within a specific time limit. 

For example, for read operations, the deadline scheduler typically gives the expiration time of 500ms since the read operations are generally more urgent. Write operationsm, on the other hand, are typically given 5 seconds of expiration time. 

The deadline scheduler algorithm maintains 3 different queues: read queue, write queue, and sorted queue. The IO requests in the sorted queue are sorted based on the sector numbers of the IO requests on the disk. The sorted queue allows the scheduler to optimize the seek time by servicing the IO requests that are physically closer to each other. 

If an IO requet is expired, the deadlien scheduler services that IO request immediately. If there is no IO request that is expired, the scheduler selectes a batch of IO requests from the sorted queue. 

## Completely Fair Queueing (CFQ)

The algorithm maintains a queue for each process separately. And when an IO request comes, it puts the IO request into its corresponding process queue. That way, the algorithm ensures that the IO requests coming from different processes are treated independently and fairly.

An example of a process might be web server process, database server process, video encoding process, etc. 

After that, the algorithm assigns a timeslice to each of these process queues. This timeslice determines the amount of time that a queue can access the disk. By allocating these timeslices, the algorithm ensrues that all processes get a fair share of disk access time and this prevents one process from using the disk excessively. 

And to determine the length of timeslice to assign these queues, the algorithm takes the IO priority of each process into account. As we might expect, if a process has higher priority, its queue gets larger timeslice. 

Also note that, the algorithm introduces a small delay after serving an IO request from a process queue. Through this delay, the algorithm can issue the next IO requests and merge some of those IO requests with each other if possible to improve efficiency and reduce the overall number of disk operations. 

By providing this implicit idle time/delay, the algorithm encourages processes to submit their IO requests in a timely manner, and this enables better request bundling and improves disk efficiency.

# Common Hard Drive Errors
- When the operating system or an application attempts to access a sector that doesn't exist in the hard drive, **programming error** occurs. 
- If the expected checksum value does not match with the data read from a sector in the hard drive, **checksum error** occurs. If this error happens temporarily as a result of some dust on the head, for instance, this is called **transient checksum error** and these errors can be recovered by retrying the read operation. If there is a physcial damage in the disk block and as a result of this we observe checksum error, this is called **permanent checksum error**.
- When the drive head fails to position itself over the requested cylinder/track on the disk platters, we call this **seek error**. If the drive arm is isntructed to move to cylinder 7 but it is positioned over cylinder 6, for example, we observe seek error.
- When the device controller, which is responsible from from receiving commands from the operating system and translating these commands into low-level instructions, encounters an error or malfunction, it may refuse to accept commands from the operating system. In that case the device controller fails to accept or process commands and we call this **controller error**. These problems may occur because of firmware issues, hardware failures, or compatibility problems between the controller and other system components.

# RAID (Redundant Array of Independent Disks)

RAID is a method that combines multiple disk drives into a single logical unit. That's why RAID system presents itself to the operating system as a single, large, and expensive disk (SLED). From the perspective of operating system, a RAID system appears as a single, large, and expensive disk (SLED). _(Note: A group of hard drives that are combined and that are configured to work together as a single logical unit is called **array**)_

Therefore, the operating system interacts with the RAID system as if it were a single disk, abstracting the underlying complexity of multiple disks and their coordination.

Because the data is distributed across multiple disks, this allows for concurrent read and write operations and significantly improves overall system performance because the system can handle multiple IO requests simultaneously and this reduces the bottleneck of a single disk. By distributing data across multiple disks, RAID can achieve higher read and write speeds in comparison with a single disk. 

In addition, RAID provides the ability to store redundant data across multiple disks and this allows the system to continue operating even if one or more disks fail. 

In summary, RAID offers several advantages:

- **Improved performance**: RAID can significantly enhance read and write speeds by distributing IO operations across multiple disks.
- **Increased reliability**: RAID provides fault tolerance by storing redundant data across multiple disks, allowing the system to recover from disk failures.
- **Increased storage capacity**: RAID combines the storage capacity of multiple physical disks into a single logical unit, providing a larger total storage capacity.

There are different RAID levels (e.g., RAID 0, RAID 1, RAID 2, ..., RAID 6) that offer different combinations of performance, reliability, and capacity. Each RAID level employs different techniques for data distribution, redundancy, and fault tolerance.

## RAID - Level 0 

In this configuration, the **data** is **divided into blocks** and **distributed across multiple disks**. For example, if there are 4 disks, after the data is divided into blocks, the 1st block is written to the 1st disk, the 2nd block is written to the 2nd disk, the 3rd block is written to the 3rd disk, the 4th block is written to the 4th disk, and the 5th block is written to the 1st disk, etc. Because data is distributed across multiple disks, it **can be read from multiple disks synchronously** and **we observe faster read/write operations compared to single disk**. 

In RAID 0, the **data is not duplicated across multiple disks**. And because there is no redundancy, RAID 0 is **not seen as a true RAID**. **If one disk fails**, the **data in that disk is lost** and as a result the **entire data becomes inaccessible**. As we increase the number of disks, the probability of data loss increases. 

It is generally considered that RAID 0 offers the best performance because: 

1) RAID 0 divides the data into small strips and distributes them across all the disks
2) Unlike other RAID levels that include redundacy, RAID 0 does not introduce any additional overhead like this and it focueses solely on performance optimization
3) Because of lack of redundancy, we have higher storage capacity

This **configuration is generally used in situations** that **require high performance and fast data access** and the **lost data can easily recreated with other ways**. Because the data is not duplicated across multiple disks, RAID 0 configuration utilizes the **full capacity of all the disks in the array** and this provides a **larger total storage space.**

## RAID - Level 1 (Mirrored)

In this configuration, **there are at least two disks** and the **exact copy of the data is created on two or more disks.** That's why this configuration is also known as **mirroring**. 

The **duplication of data provides fault tolerance** because **if one disk fails**, the **data can still be accessed from another disk** in the array because the RAID controller automatically detects the failed disk and continues to serve data from the surviving disk(s) without interruption.

The main drawback of RAID 1 is the **cost of duplicating the data**. RAID 1 **requires twice or more the number of disks compared to a single disk setup** **to achieve the same usable storage capacity.**

RAID 1 can offer improved read performance compared to a single disk. **When a read request is made**, the **RAID 1 controller can retrieve the data from either disk in the array**. This **allows for parallel read operations,** potentially **increasing the read speed**.

The **additional disks and the cost of duplicating the data in multiple disks makes RAID 1 more expensive** compared to other RAID levels or a single disk configuration. That's why **writing operation is slower in RAID 1 comapred to single disk**.

Also note that during the process of writing data, if additional operations such as **calculating parity information** (for error checking mechanism) are involved, these operations can slow down the write performance. This is called **'write penalty'.**

In RAID 1, because data is just copied to another drive, and **parity information is not calculated**, there is **no need for these kinds of extra calculations**. Therefore, there is **no significant write penalty**.

## RAID - Level 2 (Redundancy Through Hamming Code)

In RAID 2 configuration, **data is divided into bits** and **distributed across all the disks**. Therefore **all disks participate to read and write operations** and **each disk can be accessed in parallel**. That's why we observe **faster data transfer rates**.

RAID 2 generates **parity information** as an error-checking mechanism. And **this parity information is distributed across all the disks as well**. And **Hamming code is used for error detection/correction**. 

By utilizing the Hamming code, **RAID 2 can correct single-bit errors and detect double-bit errors** in the data stored across the disks (without correcting). During read operations, **data is read from all disks in the array** and **error detection and correction is done with Hamming code during these read operations**. 

If there are many disk errors in environment, RAID 2 might be a good choice. 

## RAID - Level 3 (Bit-Interleaved Parity)

The **data** is **divided into bits** and **distributed dacross all the disks** like RAID 2. But the **difference is that** it **requires only a single disk that is dedicated for parity** (error checking mechanism) regardless of the size of the disk array. 

In RAID 2, **the parity information was being distrubted across all disks**. In RAID 3, it is **stored in one dedicated disk in case of a disk failure**. 

Since the **data** is **distributed across all the disks**, **all disks participate in reading and writing operations simultaneously** like in RAID 2. And this **allows high data transfer rates** **especially for large sequential data transfers** because **the parallel access to multiple disks allows for faster reading and writing**.  

Note that **even though there is a parallel access capability**, **RAID 3 can only handle one read or one write operation at a time** because of single parity disk which is involved in every read and write operation. **If multiple IO operations were allowed simultaneously**, **the parity information could become inconsistent, leading to data integrity issues**.

The **key advantage of RAID Level 3 over RAID Level 2 is that it requires only a single parity disk, which reduces the overhead and complexity associated with distributed parity information**. However, the **limitation of handling only one IO at a time can be a bottleneck, especially for workloads with many random access operations**.

RAID Level 3 was primarily designed for applications that require high data transfer rates for large sequential data operations, such as multimedia or video editing systems. However, it has largely been superseded by other RAID levels, such as RAID Level 5 and RAID Level 6, which offer better performance and fault tolerance for a wider range of workloads.

## RAID - Level 4 (Block-Level Parity)

In RAID 4, data is **divided into blocks** and **distributed across the disks** like in RAID 0. But **unlike RAID 0**, now the **parity information of all disks is computed. And the parity information is stored in a separate disk** that is **dedicated for parity information**. 

For instance, **let's say that there are 3 disks in an array**: D1, D2, D3 and **one parity disk** P. **Assume** that the **blocks are represented in binary forms** 

```
D1: 10101010
D2: 01010101
D3: 11001100
```

**To calculate the parity block for the parity disk** (P), the **RAID controller performs the following bit-by-bit XOR operation for all disks**:

```
P = D1 ⨁ D2 ⨁ D3
  = 10101010 ⨁ 01010101 ⨁ 11001100
  = 00110011
```

During a read operation, **if one of the disks fails**, **the missing data can be reconstructed by performing the XOR operation on the remaining data blocks and the parity block**. However, **if the parity disk fails**, **data cannot be recovered**, which is a limitation of RAID 4.

**Calculating parity bit-by-bit across corresponding bit positions ensures that the parity information accurately represents the redundant information needed to recover data in case of a single disk failure**.

Also **when the size of the IO write request is small**, **a small write penalty** is observed. **Because when a small IO write request occurs**, **RAID 4 needs** to 
- **read the old data block** from the disk
- **read the corresponding parity block** from the disk
- **calculate the new parity**
- **write the new data block and updated parity block back to the disks**

**Repeating reading + calculating + writing for every small data reduces write performance**. That's why **small IO write requests are penalized.** 

While RAID Level 4 was an improvement over earlier RAID levels in some aspects, it has largely been superseded by RAID Level 5, which distributes the parity information across all disks, eliminating the write penalty and providing better performance for various workloads.

## RAID - Level 5 (Block-Level Distributed Parity)

In RAID 5, data is **divided into blocks** and **distributed across the disks** like in RAID 0 and 4. **Unlike RAID 0**, the **parity information of all disks is computed** And Unlike RAID 4, the parity information is distributed across all the disks in the array instead of storing it in one dedicated disk.

Also RAID 5 typically uses a round-robin algorithm for allocating data and parity across disks so that parity is distributed evenly and no single disk becomes a bottleneck.

Because the array continue functioning even if one of the disks fails, there is a fault tolerance in RAID 5. So if one disk fails, the missing data can be reconstructed using the parity information that is stored on the remaining disks. 

**Compared to RAID 4**, **RAID 5 offers** **improved performance** and **load balancing** **due to the distributed parity**. It **eliminates the write penalty associated with a dedicated parity disk** and **provides better overall throughput**. However, **RAID 5 still requires the calculation of parity for each write operation, which can impact write performance compared to RAID 0** (striping without parity).

RAID 5 is commonly used in enterprise storage systems and servers that require a balance of good performance, fault tolerance, and efficient storage utilization. It is well-suited for read-intensive workloads and provides protection against single disk failures.

## RAID - Level 6 (Dual Redundancy)

In RAID 5, data is **divided into blocks** and **distributed across the disks** like in RAID 0, 4, and 5. **Unlike RAID 0**, the **parity information of all disks is computed**.  Unlike RAID 4, and 5 two seaparte parity information are calculated. And unlike RAID 4, and 5, the two parity information are distributed across all the disks.

**RAID 6 offers a higher level of data protection and availability in comparison with RAID 5**. It can **tolerate the simultaneous failure of any two disks in the array without losing data** with two parity blocks per stripe. Even if two disks fail, the missing data can be reconstructed using the remaining disks and the two parity blocks. That's why RAID 6 is suitable for environments where data availability is very important.

But note that **RAID 6 causes a significant write penalty compared to RAID 5 because of the additional parity calculations and writes.** So whenever write operation occurs, **RAID 6 needs to update not only the data block but also the two corresponding parity blocks**.  In other words, **every write operation requires 3 separate write operations: one for the data block and two for the parity blocks.** 

Despite the write penalty, RAID 6 is often **used in scenarios where data integrity and availability are critical**, such as in large-scale storage systems, enterprise databases, and high-availability applications. The added protection against double-disk failures justifies the trade-off in write performance for these use cases.

Overall, RAID 6 provides a higher level of data protection and availability compared to RAID 5, making it suitable for environments that require resilience against multiple disk failures. However, it comes with the trade-off of increased write overhead due to the additional parity calculations and writes.

## Comparison of RAID Levels 

```
+---------------+-------+-----------------------------+---------------+----------------------+----------------------+---------------------------+
|   Category    | Level |        Description          |     Disks     |   Data availability  |    Large IO data     |   Small IO request rate   |
|               |       |                             |    required   |                      |  transfer capacity   |                           |
+---------------+-------+-----------------------------+---------------+----------------------+----------------------+---------------------------+
|   Striping    |   0   |       Nonredundant          |       N       |   Lower than single  |      Very high       |  Very high for both read  |
|               |       |                             |               |         disk         |                      |        and write          |
+---------------+-------+-----------------------------+---------------+----------------------+----------------------+---------------------------+
|   Mirroring   |   1   |         Mirrored            |      2N       |     Higher than      |  Higher than single  |   Up to twice that of a   |
|               |       |                             |               |  RAID 2, 3, 4, or 5; |    disk for read;    | similar to single disk for|
|               |       |                             |               |   lower than RAID 6  |  similar to single   |  read; similar to single  |
|               |       |                             |               |                      |    disk for write    |     disk for write        |
+---------------+-------+-----------------------------+---------------+----------------------+----------------------+---------------------------+
|   Parallel    |   2   |    Redundant via Hamming    |     N + m     |   Much higher than   |    Highest of all    |   Approximately twice that|
|    access     |       |            code             |               |     single disk;     |  listed alternatives |      of a single disk     |
|               |       |                             |               |     comparable to    |                      |                           |
|               |       |                             |               |    RAID 3, 4, or 5   |                      |                           |
|               +-------+-----------------------------+---------------+----------------------+----------------------+---------------------------+
|               |   3   |   Bit-interleaved parity    |     N + 1     |   Much higher than   |    Highest of all    |  Approximately twice that |
|               |       |                             |               |     single disk;     |  listed alternatives |      of a single disk     |
|               |       |                             |               |    comparable to     |                      |                           |
|               |       |                             |               |    RAID 2, 4, or 5   |                      |                           |
|               +-------+-----------------------------+---------------+----------------------+----------------------+---------------------------+
|               |   4   |   Block-interleaved parity  |     N + 1     |   Much higher than   |   Similar to RAID 0  |   Similar to RAID 0 for   |
|               |       |                             |               |     single disk;     |      for read;       |    read; significantly    |
|               |       |                             |               |    comparable to     | significantly lower  |   lower than single disk  |
|               |       |                             |               |    RAID 2, 3, or 5   | than single disk for |         for write         |
|               |       |                             |               |                      |        write         |                           |
+---------------+-------+-----------------------------+---------------+----------------------+----------------------+---------------------------+
|  Independent  |   5   |     Block-interleaved       |     N + 1     |   Much higher than   |   Similar to RAID 0  |    Similar to RAID 0 for  |
|    access     |       |     distributed parity      |               |     single disk;     |      for read;       |   read; generally lower   |
|               |       |                             |               |    comparable to     |      lower than      |  than single disk for     |
|               |       |                             |               |   RAID 2, 3, or 4    | single disk for write|           write           |
|               +-------+-----------------------------+---------------+----------------------+----------------------+---------------------------+
|               |   6   |   Block-interleaved dual    |     N + 2     |    Highest of all    |   Similar to RAID 0  |    Similar to RAID 0 for  |
|               |       |    distributed parity       |               |  listed alternatives |      for read;       |   read; significantly     |
|               |       |                             |               |                      |      lower than      |   lower than RAID 5 for   |
|               |       |                             |               |                      |   RAID 5 for write   |           write           |
+---------------+-------+-----------------------------+---------------+----------------------+----------------------+---------------------------+
```

As mentioned previously: 

In RAID 0, data is divided into blocks and distributed across disks without duplicating the blocks in multiple disks and calculating parity information. 
In RAID 1, data is not divided. Instead, it is copied to at least one disk so that the data is replicated across two or more disks. Parity information is not calculated.
In RAID 2, data is divided into bits and distributed across all disks. Parity information is calculated and distributed across all disks as well.
In RAID 3, data is divided into bits and distributed across all disks. Parity information is calculated and put into one disk that is dedicated for storing parity information.
In RAID 4, data is divided into blocks and distributed across disks without duplicating the blocks in multiple disks. Parity information of all disks is stored in a separate disk. 
In RAID 5, data is divided into blocks and distributed across disks without duplicating the blocks in multiple disks. Parity information of all disks is distributed to all disks.
In RAID 6, data is divided into blocks and distributed across disks without duplicating the blocks in multiple disks. Two separate parity information of all disks are distributed to all disks.

### Data Availability

In single disk, if the disk fails, only the data in that disk is lost.  

In RAID 0, **if a disk fails**, **all the data across all the disks is lost** because there is no redundancy. That's why **data availability is lower in RAID 0 compared to single disk**. 

In RAID 1, data availability is higher than RAID 2, 3, 4, and 5 because the whole data is copied to each disk separately. If one disk fails, the other still has a complete copy of the data. In RAID 2, 3, 4, and 5, however, the data is divided into smaller units and parity information is either stored in a separate disk or distributed across all disks. If the parity information is stored in a separate disk, the whole data is lost if something happens to that disk. If the parity information is distributed across all disks and if one of the disk fails the array operates in a degraded state until the failed disk is replaced. During that time, another disk failure could cause data loss. However, RAID 6 provides even higher availability than RAID 1. RAID 6 is similar to RAID 5 but adds a second distributed parity block. It can tolerate up to two disk failures without data loss, whereas RAID 1 can only tolerate one disk failure per mirrored pair.

In RAID 2, 3, 4, and 5, data availability is much higher than single level disk because in these RAID configurations, the data is divided into smaller units, distributed to all disks along with the parity information. But the data availability in these disks is comparable with each other.

In RAID 6, data availability is the highest because parity information is computed twice separately and distributed to all disks. In previous RAID levels, the parity information was either not calculated or calculated once. 

### Large IO  Data Transfer Capacity

**IO data transfer** is simply **transfering the data from IO device to disk or other components of the computer** or **from the disk or other components of the computer to IO device.** 

**In RAID 0**, because **data is divided into smaller chunks** and **distributed across multiple disks in the array**, when a large IO request is made **each disk can read/write its designated portion of the data simultaneously** and the **data chunks are combined to fulfill IO request**. That's why **very large amount of IO data can be transferred in both read and write operations**.

**In RAID 1**, data is simply copied to each disk so larger amount of IO data can be transferred from the disk to other computer components (via read operation) compared to single disk. However, because the incoming data has to be written to each disk, lower amount of IO data can be transferred to the disk from the other computer components (via write operation) compared to single disk. 

**In RAID 2 and 3** in which data is divided into bits and distributed acorss all disks, the amount of data that can be transferred from the disk to other computer components (via read operation) and that can be transferred from the other components to the disk (via write operation) is at the highest level.

**In  RAID 4 5 and 6** in which data is divided into blocks and distributed across all disks, the amount of data that can be transferred from the disk to other compnents (via read operation) is similar to RAID 0. For write operation, however, significantly lower amount of data can be written to the disks via write operation for RAID 4 and lower amount of data can be written to the disks via write operation for RAID 5 and RAID 6 in comparison with the single disk. However, the amount of data that can be written to the disks via write operation is even lower in RAID 6 compared to RAID 5. 

The conclusion we can arrive in here is that distributing data across the disks increases the data transfer amount for read operations. Similarly as we divide data into smaller and smaller units before distributing them, we obtain higher data transfer amount for read operations. In addition, putting the parity blocks across multiple disks is something that decreases the data transfer amount in write operations. In RAID 2 and 3, we distribute the parity blocks across disks as well but the unit of data is bit in those cases. That's why thye data transfer amount is still highest in these configurations.

### Small IO Request Rate

# Logical Volume Manager (LVM) 

LVM is a **storage management system**. It basically **creates a logical view of the storage devices** and **provides abstracted way to manage disk storage**.

**LVM operates on top of physical storage devices** and **allows you to create virtual storage entities** that are independent from the **underlying physical storage layout**. **These virtual storage entities are called logical volumes** and **these volumes can span across multiple devices**. And **this provides a unified storage space that can be easily managed and resized**. 

**Key components** of LVM: 
1) **Physical Volumes:** **Physical storage devices** that LVM uses as the **building blocks** to **create logical volumes**. The physical volumes can be **entire disks** or **partitions on a disk**. Physical volume can be seen as the **lowest level of abstraction in LVM** and it **represents the actual physical storage devices that LVM will engage/manage**.
2) **Volume Groups**: A **collection of one or more physical volumes**. And the **logical volumes can be created from this collection**. **Volume groups allow you to combine multiple physical volumes into a single logical unit** and **this provide flexibility and scalability**. The **volume group acts as a pool of storage that can be divided into logical volumes.** 
3) **Logical Volumes**: **Virtual partitions that are created from a volume group**. They are the **entities that are used to store data, create file systems, and mount them**. Logical volumes can be **created, resized, and managed independently of the underlying storage layout**.

When **operating system performs IO operations on a logical volume**, **LVM maps these IO requests to the appropriate physical volumes**. And **when an IO request is made to the logical volume**, **LVM uses this metadata** and **determines which physical volume(s) contain the requested data**. 

**After finding the physical volume(s) that contain the requested data**, **it directs the IO operation accordingly**. Through this abstraction, **the operating system and applications can interact with logical volumes as if they are regular disks** while **LVM handles the underlying physical storage management**.

The main advantages of using LVM include:
- **Flexibility**: LVM allows you to **create**, **resize**, and **manage** **logical volumes** dynamically without disrupting the system or data and **without worrying about the underlying physical storage layout.**
- **Scalability**: You can easily **add more physical volumes to a volume group to expand the storage capacity.**
- **Abstraction**: LVM provides a **layer of abstraction that separates the logical view of storage from the physical devices**, making storage management easier.
- **Snapshots**: LVM supports creating snapshots of logical volumes, which are point-in-time copies useful for backup, testing, or reverting changes.

# Disk Cache (Buffer Cache)

**Cache memory** is a type of **high-speed memory**. It is **placed between the CPU and main memory (RAM).** It's size is **smaller than the main memory** but it is **much faster to access data in cache**. The **main purpose** of the cache is **to store frequently accessed data/instructions so that CPU can retrieve them quickly without having to access the main memory which is slower**. **Placing cache memory between the CPU and main memory** makes it **intermediary** to **speed up memory access**.

Cache memory takes advantage of the **principle of locality**. And **locality** in here **refers to the tendency of programs to access the same/nearby memory locations repeatedly.** By storing **frequently accessed data** or **instructions** in **cache memory**, the **average memory access time is reduced because the processor can **retrieve** the data from the faster cache instead of accessing the slower main memory**.

**Disk cache** is also known as **buffer cache**. It can be seen as **a portion of the main memory that is reserved for caching disk sectors**. In other words, **when data is read from the disk or written to the disk**, that **data is stored in the disk cache first**. And the **disk cache acts as a buffer between the disk and the CPY** because **it stores the disk sectors in main memory temporarily**. 

**By caching disk sectors in the main memory**, the **next access to the same sectors can be served from the cache instead of retrieving them from the slower disk and this improves performance.** When the **CPU requests data from a specific sector on the disk**, the **operating system checks** if the **sector is already present in the disk cache**. **If the data is found** in the cache, it is **retrieved from the cache**. If **not**, it is **retrieved from the disk, and saved into the cache**.

```
+--------------------+
| When IO request is |    +------> If Yes ----> The IO request is satisfied via cache
| made for a         |    |
| particular sector, |    |      
| whether or not     |----+     
| the sector is in   |    | 
| the disk cache     |    |
| is checked         |    +------> If No -----> The requested sector is read into the disk
+--------------------+
```

# Solid State Drive and Flash Memory 

**Solid State Drive (SSD) is a storage device**. It **doesn't contain any mechanical parts** unlike hard disk drives and it is **entirely electronic.** It is **made out of** **FLASH memory** which is basically **non-volatile memory that retains data even when power is turned off**.

Flash memory is evolved from 
- **RAM (Random Access Memory):** The **power needs to be turned on to maintain the contents** and **whenever the power is turned off**, the **data** in the RAM is **lost**. 
- **EPROM (Erasable Programmable Read-Only Memory):** It does **not require the power to be turned on to maintain its conents**. Therefore, it **can keep the data even after the power is turned off**. But **it can be programmed only once**. **When** an **EPROM** is **produced**, all the **memory cells are initialized to '1'** and **this is the default state**. And the **"programmed" means selectively changing the state of memory cells from '1' to '0' to represent the desired data or instructions.** The **EPROM can store data for 10-20 years** and the **data can be erased with ultraviolet (UV) light**, not **electrically** 
- **EEPROM (Electrically Erasable Programmable Read-Only Memory):** It is the **improved version of EPROM**. Unlike EPROM, it **can be erased and the reprogrammed multiple times without the power**. And it **can maintain the programmed value without power being turned on**.

**Flash memory** is a **specific type of EEPROM** and it is **used in many different electronic devices** such as **smartphones**, **tablets**, **digital cameras**, **USB flash drives**, and **solid state drives (SSDs).**

**Note**: **ROM** in here refers to **Read-Only Memory**. As we might understand from its name, the data **can be read from ROM** and it is **not easy to write data to it**. Also, ROM retains data after the power is turned off. Since the data in the ROM is permanent and not easily modifiable, the data that is essential for proper functioning of the system and that does not require frequent updates is generally stored in the ROM. **It stores the firmware** (low-level software that is closely tied to the hardware), **bootloaders**(small program that is responsible for initializing system and loading operating system when computer/device is turned on), etc. **The data that is in the ROM is typically programmed during the manufacturing process of the computer/device and it remains permanent after this**. 

**Although individual memory locations can be read arbitrarily**, an **entire block of memory needs to be erased at once before it can be reprogrammed**. The reason behind this is due to the underlying technology and the way flash memory cells work. A flash memory cell consists of a floating gate transistor, which has two gates: a control gate and a floating gate. The floating gate is insulated by an oxide layer, which allows it to trap and hold electrons. The presence or absence of electrons on the floating gate determines the cell's state, which is interpreted as a binary 0 or 1. 

When a cell is erased, electrons are removed from the floating gate, setting the cell's state to 1. To program a cell (change its state to 0), electrons are injected onto the floating gate. The key point is that the process of injecting electrons onto the floating gate is unidirectional. You can add electrons to the floating gate (program the cell), but you cannot remove electrons from an individual cell's floating gate without affecting the other cells in the same block.

To remove electrons from the floating gate and change a cell's state back to 1, you must apply a high voltage to the entire block, which removes electrons from all the cells in that block simultaneously. This process is called block erasure.

The block erasure process is a hardware limitation of flash memory technology. It is designed this way to simplify the circuitry and keep the cost low, as having the ability to erase individual cells would require more complex and expensive circuitry.

In summary, changing a single cell back to a 1 requires erasing the entire block containing that cell because of the unidirectional nature of the cell programming process and the design of flash memory technology, which optimizes for simplicity and lower cost.

That's why the term ROM (Read-Only Memory) is used because we can read any arbitrary location but an entire block needs to be erasted to update a single cell.

## Usage of EEPROMs
EEPROMs might be suitable to use in a systems that need to be programmed occasionally. One example of this systems is embedded processors. And because the embedded systems did not require frequent updates, programming an EEPROM was not time-critical event in the past. The number of times EEPROMs could be programs were limited but this was not a big problem for embedded systems since they were programmed only small amount of times during their lifetime.

## Evolution of Technology 
EEPROMs have some limitations such as slow programming, byte-by-byte erasure process, limited number of write/erase cycles, higher cost per bit compared to other non-volatile memory technologies like ROM, or FLASH, and lower storage density (the architecture of EEPROMs required more space per memory cell due to the additional circuitry needed for byte-level erasure and programming). 

To overcome these limitations and enable faster and more frequent programming and erasing, FLASH memory is developed. FLASH memory consists of thousands of EEPROM circuits. These circuits are called blocks and t hey are arranged in an array. This array structure allows for random programming and erasing of individual blocks and this provdes more flexible and better performance compared to traditional EEPROMs.

In summary, SSDs are electronic storage devices that use FLASH memory, which evolved from earlier memory technologies like RAM, EPROM, and EEPROM. FLASH memory addressed the limitations of EEPROMs by allowing random programming and erasing of blocks, making it suitable for faster and more frequent data updates. The term 'ROM' is used because entire blocks need to be erased before they can be reprogrammed, even though individual memory locations can be read arbitrarily. The evolution of technology has led to the widespread adoption of SSDs as a high-performance and reliable storage solution.

# Flash Chip 
In flash memory, the **smallest programmable unit of data is called page**. It is a **contiguous block of memory cells that can be written to in a single programming operation**. In other words, all the memory cells in a page are written to at the same time. The size of page might be around 2KB, 4KB, 8KB, or 16KB. 

In FLASH memory, the **programming operation** involves **changing the state of individual memory cells from 1** (erased state) **to 0** (programmed state). This is **done by applying a high voltage to the memory cell**, which **causes electrons to be injected into the floating gate of the cell**, **changing its threshold voltage**.

When you want to **write data to flash memory**, you **must do so one page at a time**. This means that **all the memory cells within a page are programmed together**, **in a single operation**, **regardless of whether you want to change all the bits or just a subset of them**.

- The **collection of the pages is called block**. **Block is the unit of erasure in flash memory**. While data is programmed at the page level, the erase operation is performed at the block level. A **block is a collection of multiple pages**, and **all the pages within a block must be erased together before they can be reprogrammed** with new data. And the reason for this is explained in previous section.
- The **collection of the blocks is called plane**.
- The **collection of the planes ids called die**.
- The **collection of the die is called flash chip**.

The flash chip supports three basic functions: 
- **read: retrieves data from a spceific page in the flash memory.**
- **erase: clears data in a block and sets all bits in that block to 1 (default).**
- **program: writes data to a specific page in the flash memory.**

And **write** operation is basically the **combination of erase and program operations.**

# Difference Between SSDs and Hard Drives

**Construction/Data Organization**: **Hard disk drives use mechanical components** such as **disk heads**, **cylinders**, **spindles**, etc. And **data is organized as tracks and sectors**. 

**SSDs**, however, **use flash memory chips**. **Data is organized as blocks** and there is **no spinning component**. **Reading and writing are handled electronically**. 

**Read Performance**: **Accessing data** from **non-contiguous** or **non-sequential** **locations on the storage device** is called **random read**. And **accessing data from contiguous or sequential locations on the storage device** is called **sequential read**. 

Because **hard disk drives use spinning disks and moving read/write heads**, **the heads have to move and seek to different locations** on the disk platters. In addition, **the head may still need to wait for the desired sector to rotate under the head** once the head is over the right track. That's why **hard disk drives have slow random reads**. 

In addition, pre-fetching is a technique where the hard drive controller or the operating system anticipates that the next data to be read will be the one following the current block being read. In other words, it predicts that the read operation will continue sequentially.

Pre-fetching can be initiated by the operating system. In this case, the OS keeps track of the read patterns and notices when an application is performing sequential reads. It then instructs the hard drive to **pre-fetch the next block of data in advance, so that it's readily available when needed.**

**Pre-fetching can also be implemented within the hard drive itself.** **Modern hard drives have built-in caches and intelligent controllers** that can detect sequential read patterns. **When the controller identifies a sequential read operation**, **it automatically pre-fetches the next block of data** and **stores it in the drive's cache**, **anticipating that it will be requested next.**

**SSDs are based on flash memory** which **don't have any moving mechanical components**. Because **data can be read electronically from any location with similar latencies**, and **because** there is **no mechanical seek time involved** since data locations are addressed electronically by the SSD controller, and lastly **because SSDs don't have rotating disks and rotational latency delays**, **SSDs have fast random and sequential reads**.

**Write Performance**: Just like random reads, **writing to random non-contiguous locations requires the disk heads to move and seek to different locations on the disk platters.** And similarly, **the head may need to wait for the desired sector to rotate under the head** once the head is over the right track. That's why **hard disk drives have slow random writes.** 

Although **SSDs have fast random and sequential reads**, it has **slow random writes as well**. Because of flash memory, **if we want to write data to SSD,** **an entire block must be erased before this**. **This erase operation takes time.** And because of this erase operation, the **writing process is slower in SSDs compared to HDDs.** 

A disk cache is a small amount of fast memory (usually RAM) built into the hard drive controller or the disk itself. When the operating system or an application sends data to be written to the hard drive, the data is first stored in the disk cache. The disk cache acts as a buffer, allowing the hard drive to quickly accept the write request and temporarily store the data. The actual writing of data from the cache to the physical disk platters happens asynchronously, at a later time, when the disk is not busy with other tasks. By caching the write requests, the hard drive can optimize the write operations and minimize the impact on overall system performance.

Write coalescing is a technique employed by the operating system to combine multiple small write requests into fewer, larger write operations. When applications perform many small, scattered write operations, the operating system may buffer these write requests in memory (RAM) instead of immediately sending them to the hard drive. The operating system waits for a certain amount of data to accumulate or for a specific time interval before flushing the buffered write requests to the hard drive in a single, larger write operation. By coalescing the writes, the operating system reduces the number of I/O operations required, which can improve overall write performance.

The combination of disk caching and write coalescing helps buffer a few writes by:

1. Temporarily storing write requests in the disk cache, allowing the hard drive to quickly accept the data without immediately writing it to the physical platters.
2. Combining multiple small write requests into larger, more efficient write operations through OS coalescing, reducing the total number of IO operations.

These techniques help mitigate the performance impact of write operations, especially when dealing with many small, random writes. By buffering the writes in the disk cache and coalescing them at the OS level, the hard drive can optimize the write operations and improve overall system performance.

**Failures**: HDDs can experience complete disk failure. If a **mechanical component of HDDs such as spindle motors, arms, read/write heads**, etc. **fail** (if the read/write heads make physical contact with the disk platters it can cause a big damage and complete disk failure) the **entire disk can become unusable.**

Since **SSDs do not have moving mechanical components**, **they are built with electronic Flash memory**, and **data is stored in individual blocks**, **SSDs experience block failures which means a failure affects individual blocks rather than entire SSD**.

**Recovery/Failure Prevention**: For HDDs, **recovery/failure prevention is implemented at the array** (a group of multiple HDDs that are combined to work together as a single logical unit) **level**. This is commonly known as a **RAID configuration**. So **when a drive in the RAID array fails**, the **array can continue to function and data can be reconstructed or recovered using the redundant information that is stored in other drives**. This is what is meant by "recovery is implemented at the array level".

For SSDs, **the recovery** can be done at **disk level** or **array level**. 

**Disk level methods** refer to the **techniques and mechanisms implemented within an individual SSD** to **ensure data integrity**, **prevent failures**, and **facilitate data recovery**. **These methods are specific to each SSD** and are **handled by the SSD controller and firmware**. Examples of disk level methods include:
 - **Error Correction Codes (ECC):** SSDs use ECC (e.g., hamming code) to **detect and correct bit errors that may occur during data storage or retrieval**. **ECC helps maintain data integrity** and **prevents data corruption**.
 - **Wear Leveling**: **SSD controllers** **employ** **wear leveling algorithms** to **distribute write operations evenly across all the flash memory cells**. **This prevents certain cells from wearing out faster than others** and **extends the lifespan of the SSD**.

**Array level methods** refer to the **techniques** and **mechanisms** **implemented at the level of multiple SSDs working together in a storage array or system**. These methods **involve coordinating the operation and data distribution across multiple SSDs to ensure data integrity, fault tolerance, and performance**. **Examples of array level methods** include:
  - **RAID** (Redundant Array of Independent Disks): RAID configurations, such as RAID 1 (mirroring) or RAID 5 (striping with parity), can be used to distribute data across multiple SSDs. RAID provides data redundancy and helps protect against data loss due to SSD failures.
  - **Data Replication**: In storage systems with multiple SSDs, data can be replicated across different drives to ensure data availability and recoverability in case of SSD failures.
  - **Logical Volume Management**: Storage systems can use **logical volume management** to **create logical volumes** that **span across multiple SSDs**. This allows for **flexible data allocation**, **load balancing**, and **easier data migration or recovery**.

At the time it was written, the focus and advancements in recovery and failure prevention methods for SSDs were primarily at the individual disk level. SSD manufacturers were concentrating on improving the reliability and resilience of each SSD through advanced error correction, wear leveling, bad block management, and other disk-level techniques.

However, it's important to note that array level methods are equally important and are commonly used in enterprise storage systems and data centers. The combination of disk level and array level methods provides a comprehensive approach to data recovery and failure prevention in SSD-based storage systems.

As SSD technology continues to evolve, both disk level and array level methods are being continuously improved and new techniques are being developed to enhance the reliability, performance, and data protection capabilities of SSDs and storage systems.

**Striping for Arrays**: Because **HDDs have mechanical components** and **these mechanical components require some time to move from location A to location B**, **HDDs typically prefer large stripe size** because **if it chooses small stripe** size, the **disk head has to move quite frequently** for small amount of data and **this would not be convenient and efficient**. 

**SSDs**, on the other hand, **prefer smaller stripe sizes**. **With smaller stripe sizes**, **IO operations can be spread across multiple disks more effectively**, **enabling higher levels of parallelism and improved overall performance**. **When data is written to an SSD in a RAID array**, **only the affected stripes need to be updated**. **With smaller stripe sizes**, **the amount of data that needs to be rewritten during an update operation is minimized**.

# IO Scheduler Changes

In **SSDs**, there is **no read/write head**, that's why there is **no seek time**. Also, **regardless of the location of the block**, **accessing to any block takes nearly same time**. That's why **IO schedulers focus on reducing the amount of time that is spent for write operation rather than optimizing for seek time**.

Imagine **writing a multiple 4KB blocks**. 
- **Writing to 1st 4KB block**: **SSD needs to read the entire 128KB block that contains the target page**, **erase the block**, and then **write the updated 128KB block back to the SSD**
- **Writing to 2nd 4KB block**: **SSD repeats the same process**: **reading the entire 128KB block that contains the target page**, **erase the block**, and then **write the updated 128KB block back to the SSD**.

And **this process is repeated for each write request**. **This leads to inefficient usage of the SSDs resources and potential write amplification**. To solve this inefficiency, **IO schedulers should store incoming write requests in a buffer temporarily and delay the writing process slightly**. Through this way, **the scheduler can wait for subsequent write requests and this allows the scedhuler to group multiple small write requests into fewer, larger write operations**. 

Also **by buffering and combining multiple write requests**, **IO scheduler can reduce the number of read/erase/program cycles that are required to write the data to the SSD**. **Instead of performing a read/erase/program cycle for each 4KB write request**, **the scheduler can coalesce the requests into a single, larger write operation that aligns with the SSD's erase block size** (e.g., 128KB).

**Here's an example of how write coalescing can improve efficiency**:

- **Without** **coalescing**: **Writing two consecutive 4KB blocks would require 2 read/erase/program cycles**, each **processing 128KB of data** (2 * (128KB read + 128KB erase + 128KB program)).

- **With coalescing**: The **IO scheduler buffers the two 4KB write requests and combines them into a single 8KB write operation**. **This requires only 1 read/erase/program cycle**, **processing 128KB of data** (1 * (128KB read + 128KB erase + 128KB program)).
