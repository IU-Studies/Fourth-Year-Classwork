# OpenMP Hello World Program

This guide explains how to install the required software, create an OpenMP program, compile it, and run it on Ubuntu/Linux.

---

## 1. Update the Package List

Open the Terminal using **Ctrl + Alt + T**.

First, update the package list:

```bash
sudo apt update
```

---

## 2. Install Required Software

Install **GCC** and **gedit**:

```bash
sudo apt install gcc gedit
```

> **Note:** OpenMP support is included with GCC through the OpenMP runtime (`libgomp`), so you normally do not need to install a separate OpenMP package.

### Check GCC Installation

Verify that GCC is installed:

```bash
gcc --version
```

You should see output similar to:

```text
gcc (Ubuntu ...) ...
```

### Check Gedit Installation

Verify that gedit is installed:

```bash
gedit --version
```

You should see the installed gedit version.

---

## 3. Create a Folder for the Program

Create a directory called `OpenMP` in your home directory:

```bash
mkdir -p ~/OpenMP
```

Move into the directory:

```bash
cd ~/OpenMP
```

You can verify your current location with:

```bash
pwd
```

It should show something similar to:

```text
/home/your-username/OpenMP
```

---

## 4. Create the C Program

Open `gedit` and create a file called `hello.c`:

```bash
gedit hello.c
```

When the editor opens, write your OpenMP program.

For example:

```c
#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp parallel
    {
        printf("Hello World from Thread %d\n", omp_get_thread_num());
    }

    return 0;
}
```

Save the file as:

```text
hello.c
```

---

## 5. Compile the OpenMP Program

Return to the Terminal.

Make sure you are inside the `OpenMP` directory:

```bash
cd ~/OpenMP
```

Compile the program using GCC with OpenMP support:

```bash
gcc -fopenmp hello.c -o hello
```

### What does `-fopenmp` do?

The `-fopenmp` option tells GCC to:

* Enable OpenMP support
* Compile OpenMP directives such as `#pragma omp parallel`
* Link the OpenMP runtime library

If there are no errors, the compilation was successful.

You can check that the executable was created:

```bash
ls
```

You should see:

```text
hello
hello.c
```

---

## 6. Run the Program

Run the compiled program:

```bash
./hello
```

You may get output similar to:

```text
Hello World from Thread 0
Hello World from Thread 3
Hello World from Thread 1
Hello World from Thread 2
```

The order of the threads can change every time you run the program because the threads execute concurrently.

For example, another run might produce:

```text
Hello World from Thread 2
Hello World from Thread 0
Hello World from Thread 3
Hello World from Thread 1
```

This is normal behavior.

---

## 7. Specify the Number of Threads

You can explicitly tell OpenMP how many threads to use.

For example, to use **4 threads**:

```bash
export OMP_NUM_THREADS=4
```

Then run the program:

```bash
./hello
```

You may get:

```text
Hello World from Thread 0
Hello World from Thread 1
Hello World from Thread 2
Hello World from Thread 3
```

> **Note:** The order of the output is not guaranteed. The thread numbers may appear in a different order.

---

## 8. Run with Different Numbers of Threads

You can change the number of threads whenever you want.

### Use 2 threads

```bash
export OMP_NUM_THREADS=2
./hello
```

### Use 4 threads

```bash
export OMP_NUM_THREADS=4
./hello
```

### Use 8 threads

```bash
export OMP_NUM_THREADS=8
./hello
```

---

## 9. Check the Number of Threads

You can modify the program to print the total number of threads:

```c
#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp parallel
    {
        printf(
            "Hello World from Thread %d of %d\n",
            omp_get_thread_num(),
            omp_get_num_threads()
        );
    }

    return 0;
}
```

Compile it again:

```bash
gcc -fopenmp hello.c -o hello
```

Set the number of threads:

```bash
export OMP_NUM_THREADS=4
```

Run:

```bash
./hello
```

Example output:

```text
Hello World from Thread 0 of 4
Hello World from Thread 2 of 4
Hello World from Thread 1 of 4
Hello World from Thread 3 of 4
```

---

## 10. Complete Command Sequence

If everything is being done from scratch, you can use the following commands:

```bash
sudo apt update
sudo apt install gcc gedit

gcc --version
gedit --version

mkdir -p ~/OpenMP
cd ~/OpenMP

gedit hello.c
```

After saving `hello.c`, compile it:

```bash
cd ~/OpenMP
gcc -fopenmp hello.c -o hello
```

Run it:

```bash
./hello
```

To run with 4 threads:

```bash
export OMP_NUM_THREADS=4
./hello
```

---

## 11. Troubleshooting

### `gcc: command not found`

Install GCC:

```bash
sudo apt update
sudo apt install gcc
```

### `gedit: command not found`

Install gedit:

```bash
sudo apt install gedit
```

### `hello.c: No such file or directory`

Make sure you are in the correct directory:

```bash
cd ~/OpenMP
ls
```

You should see:

```text
hello.c
```

### `./hello: No such file or directory`

The program may not have been compiled successfully.

Compile it again:

```bash
gcc -fopenmp hello.c -o hello
```

Then run:

```bash
./hello
```

### OpenMP functions are not recognized

Make sure you compile with the `-fopenmp` option:

```bash
gcc -fopenmp hello.c -o hello
```

Do not compile using only:

```bash
gcc hello.c -o hello
```

because that does not enable OpenMP support.

