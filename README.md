# IO Scheduler

IO devices are the components that allow the computer to communicate/inteact with the outside environment. 

```

          Application  Monitor
              \         /
               \       /
Keyboard - Operating System - Mouse 
               /       \
              /         \
          Printer   Disk Drive

```

We can group the external devices that engage in IO operations in 3 categories: 

#### Human Readable #### 
Printers, keyboards, mouses, terminals can all be read by humans. That's why they can be grouped under this category. As we might guess, these external devices are suitable for communicating with the user. 

#### Machine Readable #### 
Disk drives can be seen as IO devices as well because they read data from the disk platters and transfer this data to the CPU or main memory whenever this transfer is requested. And disk drives can be seen as a machine readable device because they store and retrieve data in a format that can be processed by a computer (machine).

Other examples of machine readable external devices might be USB keys, sensors, and controllers. 

#### Communication #### 
