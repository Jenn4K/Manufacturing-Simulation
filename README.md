# Manufacturing-Simulation
A program in C, which simulates the manufacturing of Items, using 8 processes, shared memory and semaphores.

Simulation

Each Item is made out of 3 Parts. Each type of part(1,2,3) is created by a different process and all of them must be sent to the PainShop in order to be painted.
The PaintShop(process) can paint one Part at a time. Then every painted Part must be checked by an Inspector(process) of the same type as the Part(1,2,3) and at 
last an Assembler must combine all 3 inspected Parts to form an Item.

For the "communation" between processes we use shared memory segments and semaphores.

Compilation and Running

$ make
$ ./project <number of items to produce>
