# Queues Round Robin

A C application that implements queues using linked list with main functionality of scheduling processes that the processor executes using the Round robin Algorithm executed in FIFO order.

# What I Learned

* Implementing queues using linked list.
* Understanding Round Robin Algorithm and its use in process scheduling.

# User Manual

* The input file will have the watching time slots in the first line, then in the successive lines
the name of the process, time it enters the queue, and the needed time for
execution respectively.
* Output should is the scheduling of the processes, showing when does each process abort
and when does the processor is idle (no processes in the queue).
* Each process enters the queue whenever its execution time comes.
* Each process will be grant 1 time slot on execution, if its execution time finishes it will abort,
else it will be sent again to the queue and its execution time will be subtracted by 1.
