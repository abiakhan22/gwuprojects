# Threading in `xv6`

`xv6` is designed to be a "modern" version of Unix Version 6 (V6) as described in [Lyons Commentary](http://www.lemis.com/grog/Documentation/Lions/).
V6 was designed when processes were strictly seen as an address space plus a thread.
In the late 70s and early 80s, threads [started to be pushed](http://www.faqs.org/faqs/os-research/part1/section-10.html) into systems, but it took a while till they were standardized under [POSIX.1c-1995](https://standards.ieee.org/findstds/interps/1003-1c-95_int/index.html) (yes, that's '95).
In this homework, you'll take the first step toward bringing this modern standard to `xv6` by implementing *1-to-1* threading!

As with all of your homeworks, you *must* ensure that your implementation (not your test files) do not print anything.
You can *never* commit code to a repository for a company that includes debugging print outs.
Doing so will likely mess up our grading programs and result in you getting zero credit.

## Specification for `xv6` Threading

In this assignment, you'll enable the *creation* of 1-to-1 threads, their *exit*ing, and termination coordination between parent and children via *join*-based synchronization.
This API should be placed in the `gwthd.h` header file, and should look like:

```
typedef int     gwthd_t;
typedef void *(*gwthd_fn_t)(void *);

int     gwthd_create(gwthd_t *childid, gwthd_fn_t fn, void *data);
void    gwthd_exit(void);
int     gwthd_join(gwthd_t child);
gwthd_t gwthd_id(void);
```

This is a simplified version of the `pthread`s API.
Please read the `man` pages for the corresponding `pthread` functions to get an intuition for this API.
You can also use google to find good examples of many of the uses of `pthread`s.

`gwthd_create` creates a new thread that executes the function pointer passed in (`fn`), and passes the `data` to it as an argument.
It returns `0` on success, and `-1` otherwise (in cases similar to when `fork` returns error).
If it returns success, the `childid` variable is set to the new thread's (the child's) identifier.
Each thread shares the address space of the thread that created it.

`gwthd_exit` kills the current thread.
You should *never* return from the function executed for a thread.
Instead, always call `gwthd_exit` to terminate the thread.

`gwthd_join` is executed by a parent, who passes the `gwthd_id` of the child they want to wait to terminate execution.
Joining is similar to `wait` in xv6 (though it is closer to `waitpid` in systems like Linux) in that the parent either allows child that has already `gwthd_exit`ed to be reclaimed and reused, or allows the parent to block waiting for the child to terminate at which point the parent will continue executing.
This returns `0` when successful, and `-1` if you pass in a `gwthd_t` that is not appropriate.

`gwthd_id` is simple: return the current thread's `gwthd_t` identifier.
You should be able to call this function from both processes and threads, and it should always return a unique id (i.e. no other process or thread has the same id).

**Using `gwthd`s.**
These functions, definitions, and typedefs should all be in `gwthd.h` which can be included and used by user-level code.
All that a user-level process needs to do is include this file, and it should be able to use `gwthd`s.

**Simplifying assumptions.**

- For this assignment, you can assume that the parent will not `exit` until all of the children have `gwthd_exit`ed, and the parent has done a `gwthd_join` on all of them.
	I suggest adding code to validate this assumption so that you can detect if you write your test code incorrectly, but this isn't required.

### Example API Usage

A simple example of using this API follows:

```
void *
thread_fn(void *data)
{
	int arg = (int)data;

	printf(stdout, "argument to new thread %d is %d\n", gwthd_id(), (int)arg);

	gwthd_exit();
	return NULL;
}

int
main(void)
{
	gwthd_t gwt;

	printf(stdout, "Starting up the main thread\n");

	if (gwthd_create(&gwt, thread_fn, (void *)42)) exit();
	gwthd_join(gwt);

	printf(stdout, "back in main thread\n");
	exit();
}
```

### Leveling Up!

This homework is specified as a number of *levels* that you're implementation will reach.
If you only *level up* to a specific point, you'll get a corresponding amount of credit.
This allows for partial credit, but this is the *only* way that you get partial credit (so make sure that a level is *complete* before moving on).
I've also spelled out the levels as they give you hints on how to develop your solution iteratively, instead of as one monolithic chunk that is impossible to debug.
Failing to provide functionality according to specification for level *N* will likely mean that you get zero credit for level *N* and all higher levels.
Each level should be accompanied with a test file *only if* you have completed that level.
Test files for levels you *have not* completed do not need to be provided.

- **Level 0 (5%):**
	Code that uses the `gwthd` functions compiles.
	Make sure that your function prototypes exactly match the requirements.
	Though we won't necessarily use it, please provide a `gwthd_lvl0.c` test file.
- **Level 1 (5%):**
	`gwthd_id` works to return a thread's id.
	Though we won't necessarily use it, please provide a `gwthd_lvl1.c` test file.
- **Level 2 (30%):**
	`gwthd_create` works to properly creates a new thread that executes at the correct function, but might not properly pass the `data` argument to it.
	Though we won't necessarily use it, please provide a `gwthd_lvl2.c` test file.
- **Level 3 (5%):**
	`gwthd_create` works to properly creates a new thread, *and* correctly passes `data`.
	Though we won't necessarily use it, please provide a `gwthd_lvl3.c` test file.
- **Level 4 (10%):**
	`malloc`s in separate threads properly use the same heap.
- **Level 5 (30%):**
	`gwthd_exit` and `gwthd_join` properly synchronize between child thread exit, and parent thread blocking and resumption.
	Though we won't necessarily use it, please provide a `gwthd_lvl5.c` test file.
- **Level 6 (15%):**
	Correct error values are passed when processes call thread functions, and threads call process functions.
	This includes (but is not limited to) processes calling `gwthd_exit`, and threads calling `exit`.
	Though we won't necessarily use it, please provide a `gwthd_lvl6.c` test file.

### Hints

One of the most important aspects of this assignment is *reading* and *understanding* how `xv6` performs many of the operations similar to what you're trying to do.
Expect to spend a fair amount of time on this.
This is part of the expected work for this assignment, so questions that demonstrate that you haven't read the source will yield replies that you must do so.
Questions in office hours such as, "I don't understand what `fork` does; please tell me" will not be met with replies other than, "please ask more specific questions".

Most importantly, you should read, study, and understand how `fork`, `wait`, and `exit` work in `xv6`.
Remember to rely on the `xv6` book for the high-level design.
After you have a handle on this, ask yourself how your implementation needs to differ from this.
What parts of the current process API need to change for your implementation?

### Stack Management, and Function/Argument Passing

One of the most conceptually complicated parts of this implementation is figuring out

1. how to start a new thread that executes on a new stack (remember, this is very different than how `fork` normally functions),
2. how control (the instruction pointer) is transferred to your function, and
2. how the argument (`data`) is properly passed to it.

You'll need to allocate a stack for the thread to execute on (a stack of `4096` bytes should be a good size), and then set up the stack so that when you start the new thread executing and using that stack, it will be able to find the `data` argument, and properly execute in memory.
To understand this, some background:

**`x86` stacks.**
Stacks in x86 grow *downward*.
That is to say, when functions are called and *push* to a new invocation frame, the stack pointer goes from larger addresses, to lower addresses.
When a function is called, the *calling convention* determines how arguments are passed, and return values are returned in some combination of the stack, and registers.
Our compiler, by default, uses [`cdecl` calling conventions](https://en.wikipedia.org/wiki/X86_calling_conventions#cdecl).
Note that this `cdecl` is not to be mistaken with the `cdecl` tool for turning a C definition into English.
You must understand how `cdecl` works.
You might use `objdump -S` on some `.o` file that you provide (I suggest compiling using the `-g` flag), and you can see the generated assembly for each function.
You can provide a simple function that takes a few arguments, inspect the assembly that is generated when the function is called, and when it executes to understand how the stack is used.
It will help you understand `cdecl`, by example.

In short, before calling a function, the arguments are pushed by the *caller* of a function in the opposite order to their occurrence in the argument list, then the address the function should return to is pushed onto the stack.
Only then is the function jumped to.
This is how a new function that starts executing assumes that the stack is set up.

If you're examining x86 assembly, you'll notice that what I just described doesn't seem true.
You won't see the address to return to from the function, nor the jump to the function.
In x86, the `call` instruction performs *both* of these functions.
Correspondingly, when returning from a function, the `ret` instruction both pops the address to return to, and jumps to it.

**Separating your implementation into user-level library logic, and kernel logic.**
I suggest allocating the new thread's stack in your user-level library, and setting up the stack explicitly with the required arguments and "return pointer" (which might just be `NULL` as we shouldn't return from a thread's function).
Thus, a new thread with its instruction pointer and stack pointer properly initialized, will use the stack correctly.
Stacks are just data-structures like any other, so can be allocated and accessed directly using C (i.e. you can treat the stack as an array).
Use this fact to set up the thread to be ready to execute the thread's initial function.

To actually create a new thread, you'll need to create a new system call that at the very least takes the instruction pointer and the stack pointer that you want to start the thread executing at.

### Kernel Implementation

You are going to create your *threads* as `xv6` `proc`s with a few key exceptions:

1. Threads behave different than processes.
    Threads can call `pthread_exit`, processes can call `fork`, etc...
	Thus, you will modify the kernel so that some `struct proc`s can be used as threads.
	This means that you'll need to track which of the `proc`s are threads, and which are normal processes.
2. Threads must use the virtual address space with the thread that `gwthd_create`d them.
	All `proc`s that are threads must use the address space (and all relevant information) for the original *parent* thread (i.e. the thread that created the first threads in a process).
	The parts of `struct proc` that are relevant to the process' virtual address space (VAS) are `pgdir` which is the mapping structure to provide the VAS, and the `sz` which is essentially the heap pointer for a process (i.e. the end of the allocated memory).
	Since all `gwthd` processes must *share* these values, I highly recommend that each thread in a process maintains a pointer to the original process, and that you modify `xv6` to use that process' values for these variables for all of its functions.
	This *does* mean changing a fair number of places in the kernel, but the changes should be relatively formulaic.

Note that there are some aspects of processes that you can directly reuse.
For example, your implementation of `gwthd_id` should be able to directly use `getpid`.

**Thread register setup.**
In `xv6`, the `struct trapframe` contains the registers that will be used when returning to user-space for a newly created process.
To understand this a little better, look through the `fork` code to see how the registers for the new processes are set up to make sure that `fork` returns the right values for child, and for the parent.
You'll have to understand this when trying to figure out how to control the stack pointer and instruction pointer that are used for the new thread.

**Kernel dynamic memory.**
Remember that you generally do not want to do memory allocation within the `xv6` kernel.
You might need to get creative to use the already existing structures in intelligent ways.

**`xv6` event notification and blocking/wakeup APIs.**
To properly implement `gwthd_exit` and `gwthd_join`, you'll need to understand the `xv6` APIs for blocking and waking up processes.
You can understand these by reading how they are used in `exit` and `wait`.

## Extra Credit

There are two opportunities for extra-credit on this assignment.

### Passing Data Between `gwthd_exit` and `gwthd_join`

Add two more functions to your `gwthd.h` header:

```
void gwthd_exit2(void *data);
int  gwthd_join2(gwthd_t child, void **data);
```

These are used to pass data from the exiting child, to the joining parent in a manner similar to `pthread_exit` and `pthread_join`.

Notice that the `gwthd_fn_t` returns a `void *`.
Now ensure that when you return from the `gwthd_fn_t`, you return a `void *` that gets transparently passed to a call to `gwthd_exit`.

- **Level 7a (10%):**
	Enable the thread function to return a value (instead of explicitly calling `gwthd_exit`), and pass that argument between exit, and join.
	Though we won't necessarily use it, please provide a `gwthd_lvl7a.c` test file.

### Shared File Descriptor Namespace

The specification up to this point shares the *address space* between threads.
Another aspect to processes is the *file descriptor* namespace that belongs to the process.

- **Level 7b (5%):**
	Two processes should share the same file-descriptor namespace, thus a file opened in one thread should be able to be read in another.
	Though we won't necessarily use it, please provide a `gwthd_lvl7b.c` test file.

## Academic Integrity

As with any of the assignments for this class, you *cannot ever* share your code for this class, or view other's code.
Please remember the academic integrity contract you signed.
Cheating is the fastest and easiest way to fail this class.

Note that I might ask you to *explain* your implementation.
If you cannot do so, then it will be interpreted as a break of academic integrity.
