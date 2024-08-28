# cpsc351project

**Collaborators:**
Ismail Peracha, Matthew Villanueva, Samir Shivji

**Email Addresses:**
ismailperacha@csu.fullerton.edu, msvillanueva13@csu.fullerton.edu, samir0shivji@csu.fullerton.edu

**Contributions:**

Ismail: Coded shell file, answered performance comparison questions, worked on parallel fetcher file.

Matthew: Worked on parallel fetcher file.

Samir: Coded serial fetcher file, worked on parallel fetcher file.

**Each team member is familiar with all functionality in this project.**

**We used C++ throughout this project.**

**How to Execute Files**

Shell.cpp is a standalone file that runs on its own. When you run it, you as a user can input ps or ls or any other command, and the output will be given by fork(), wait(), and excelp().

Serial_Fetcher.cpp, as well as Parallel_fetcher.cpp need to be ran with the locations.txt file, in order for it to work. Parallel_fetcher.cpp also needs the "time Parallel_fetcher.cpp" command to be run in the shell to give the real, user, and system times.


**Execution Times**

Parallel Fetcher: Real time is 2.537 seconds, User time is 1.093 seconds, and System time is 0.105 seconds.

Serial Fetcher: Real time is 2.846 seconds, User time is 0.149 seconds, and System time is 0.002 seconds.

**Answers to Performance Comparison Questions**
1. In the output of time, the difference between real, user, and sys times is that real is actual elapsed time, user time is the amount of CPU time spent in user-mode code within the process, while sys time is the amount of CPU time spent in the kernel within the process.

2. User time is greater than sys time because in a GC event, most of the time is spent within the virtual machine code and only very less time is spent in the kernel.

3. When fetching all of the locations in the file, the parallel fetcher is faster than the serial fetcher, as the serial fetcher would distribute the task across multiple CPUs, while the parallel fetcher can fork multiple at a time.

4. If one fetcher child crashes, it should not affect the other children in a well-designed concurrent system, because each child process runs in its own address space with isolated memory. Advantages of isolating each fetch task within a different process is fault tolerance, where one task’s failure does not compromise the others. Disadvantages of isolating each fetch task within a different process is how it would be costly in terms of system resources.


**Extra Credit was not implemented.**

