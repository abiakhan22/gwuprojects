# Operating Systems 3411, Homework 3

As you dive further into the inner workings of `xv6`, you'll get experience with an increasing number of subsystems.
A significant challenge in these homeworks (and the labs preceding them) is *reading* and *understanding* the `xv6` source.
Be prepared that this is a huge amount of the time you'll spend during the homework.
The amount of code you finally end up writing will likely be small, but slogging through the code will take a lot of time.
Please remember that the `xv6` book is a great resource for better understanding most aspects of the source code.

You should view the first four hours of this assignment as a scavenger hunt to find the relevant parts of the code to

1. learn context about how `xv6` performs specific operations, and
2. find the parts of the code that you'll need to interact with.

# Specification

In this assignment, you'll provide a functionality similar to the `ps axjf` (read `man ps`, and experiment with the command to understand the output).
This will involve a number of tasks:

1. Add a system call called `procstat`.
1. Enable that system call to populate a user-level structure with process information.
1. Find the structures in the kernel that hold the process information for all processes in the system.
1. Iterate through all process structures, and populate the user-level structure with the process' information.
1. Add a function at user-level that can use your system call to print out some information about each process in the system (similar to the `ps` program).
1. Write a few tests to ensure that all preceding tests work.

## `procstat` System Call

You've already implemented a system call in lab.
You'll replicate the same procedure by adding a `procstat` system call with the prototype:

```
int procstat(int which, struct pstat *ps);
```

The `which` argument specifies which of the active processes in the system, the caller wants to get information about.
It is intended to allow the caller to iterate through each process in the system.
For example, `which` of `0` means that you want information about the "0th" process that is active in the system, while `which` of `1` should give you information about the "1st".

The return value will be `0` while the system call returns information about the process in the `struct pstat` argument.
However, after `which` gets as large as the number of active processes in the system, then this function should return `1` to indicate that the caller has iterated through each process in the system.

The `struct pstat` argument is how the information about the chosen process is returned.
It should be defined *exactly* as:

```
struct pstat {
	int pid, ppid;
	char state;
	char name[16];
};
```

Each of the fields of this struct convey some information about the chosen process.
The `pid` is the process id of the process you're printing information for.
`ppid` is that process' parent's process id (pid).
`name` is the process' name that is stored in its structure.
The `state` is the process state (i.e. the `procstate`).
Each process' state should be printed as:

- `E` for `EMBRYO`
- `S` for `SLEEPING`
- `N` for `RUNNABLE`
- `R` for `RUNNING`
- `Z` for `ZOMBIE`

Note that if a process is in the `UNUSED` state, then it is freed, and you should *not* print out information for it.

**Recommendation.**
I'd strongly recommend that you read and understand how the `fstat` system call passes the `struct stat`, and how the kernel populates it.
How the pointer to the structure is passed to the kernel, and how the kernel populates the structure are very similar to how you will need to do it.
Of course, that system call is populating file information, not process information, so *how* the structure with specific data is completely different (i.e. file information vs process information).

**Files.**
You will add a `pstat.h` file that can be included both in user-level and in the kernel (for example, see how `stat.h` is used)
It should only include the definition of the `struct pstat` structure.
You should add your `procstat` system call as normal in the `user.h` file.
Additionally, you'll add a `ps` function at user-level in `ulib.c` that uses your `procstat` system call and prints out information about all of the system's processes.
Add its prototype in `user.h` (just as the system does with, for example, `memset`).

All our test files that call your system call or the `ps` function should be able to compile by simply using:
```
#include "user.h"
#include "pstat.h"
```
Please test this.

## Implementing the `ps`

You'll implement a simple user-level `ps` function in `ulib.c` that uses your system call, and prints out the information.
Its prototype is

```
void ps(void);
```

### `ps` Output

Your `ps` function must print out a line of information for each process in the system (including the process calling `ps`).

The format for *each* process that is executing on the system is:

```
pid ppid state name
```

Each of these items has an identical meaning as they do in the `struct pstat` structure as defined above.

An example output of `ps` for a system might include:

```
3 2 N pstest
4 3 R pstest
```

Here, the second entry is the child of the first, and the second is running on the CPU while the second one is runnable, but not chosen by the scheduler to be currently running.
Note they have the same name which might mean that they are forks of the same initial program called `pstest`.

**Recommendation.**
You should use the `printf` function to print your output in the `ps` function.
Note that the first argument to `printf` is the "file descriptor" to print to.
You want to print to "standard output", which is `1` (as opposed to "standard input" which is `0` or "standard error" which is `2`).

### Important Printing Information

I want to be very clear here:
You are *not* to add any print output to the system in your final submission.
This means that you are *not* to print in the kernel, and not to have prints anywhere other than in your `ps` implementation.

You should generally **never** have debugging output in your final products.
Get used to this as it is normal practice in jobs.

# Testing Your Implementation

We will test your system by forking processes using a number of patterns, then calling your `ps` before `wait`ing on the children.
If these tests yield a fault, we will *not* debug your system for you.
Our program must compile on your system, so please don't change any existing APIs, and use the `ps` API above.
The three patterns of forking we will use to test your implementation are:

- Parent forks 8 children, then calls `ps`.
- Parent forks a single child, that forks a single child, and so on until there are 8 processes in the ancestry from the original parent, then call `ps`.
- Parent forks two children, and they each fork two children, then call `ps`.

You must test your program with these configurations of processes to validate that the `ps` outputs are correct, thus you must practice using the `fork` API.
Please submit these three test programs, respectively, as

- pstest1.c
- pstest2.c
- pstest3.c

# Academic Integrity

As with any of the assignments for this class, you *cannot* share your code, or view other's code.
Please remember the academic integrity contract you signed.
Cheating is the fastest and easiest way to fail this class.
