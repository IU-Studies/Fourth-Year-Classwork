

# 1. Navigation Commands

## `pwd` — Print Working Directory

Shows your current location.

```bash
pwd
````

Example:

```text
/home/mayur
```

---

## `ls` — List Files and Directories

List files and directories:

```bash
ls
```

Show detailed information:

```bash
ls -l
```

Show hidden files:

```bash
ls -a
```

Show hidden files with detailed information:

```bash
ls -la
```

---

## `cd` — Change Directory

Go into a folder:

```bash
cd Documents
```

Go back one directory:

```bash
cd ..
```

Go to the home directory:

```bash
cd ~
```

Go to the root directory:

```bash
cd /
```

Example:

```bash
cd ~/Documents
```

---

# 2. File and Directory Operations

## `touch` — Create a File

Create a file:

```bash
touch file.txt
```

Create multiple files:

```bash
touch file1.txt file2.txt file3.txt
```

Check the files:

```bash
ls
```

---

## `mkdir` — Create a Directory

Create a directory:

```bash
mkdir test
```

Create multiple directories:

```bash
mkdir folder1 folder2
```

Create nested directories:

```bash
mkdir -p project/src/code
```

The `-p` option creates the parent directories if they do not already exist.

---

## `rm` — Remove Files or Directories

Delete a file:

```bash
rm file.txt
```

Delete an empty directory:

```bash
rmdir test
```

Delete a directory and its contents:

```bash
rm -r test
```

> **Warning:** Be careful with `rm -r` because it can delete an entire directory and its contents.

---

## `cp` — Copy Files and Directories

Copy a file:

```bash
cp file.txt backup.txt
```

Copy a file into a directory:

```bash
cp file.txt Documents/
```

Copy a directory:

```bash
cp -r folder1 folder2
```

The `-r` option allows directories and their contents to be copied recursively.

---

## `mv` — Move or Rename

Rename a file:

```bash
mv old.txt new.txt
```

Move a file into a directory:

```bash
mv file.txt Documents/
```

---

# 3. Permission Management

Linux permissions are commonly displayed like this:

```text
-rwxr-xr--
```

There are three groups:

```text
Owner     Group     Others
rwx       r-x       r--
```

Where:

```text
r = read
w = write
x = execute
```

---

## `ls -l` — View Permissions

Run:

```bash
ls -l
```

Example:

```text
-rw-r--r-- 1 mayur mayur 100 Sep 9 file.txt
```

The permission section is:

```text
-rw-r--r--
```

---

## `chmod` — Change Permissions

Give the owner execute permission:

```bash
chmod u+x file.sh
```

Give everyone execute permission:

```bash
chmod +x file.sh
```

Using numeric permissions:

```bash
chmod 755 file.sh
```

Common permissions:

```text
755 → rwxr-xr-x
644 → rw-r--r--
777 → rwxrwxrwx
```

### Permission Number Meaning

Each permission has a numeric value:

```text
r = 4
w = 2
x = 1
```

For example:

```text
755
```

means:

```text
Owner  → 7 = 4 + 2 + 1 = rwx
Group  → 5 = 4 + 1     = r-x
Others → 5 = 4 + 1     = r-x
```

Therefore:

```text
755 → rwxr-xr-x
```

---

## `chown` — Change Owner

Usually requires `sudo`.

Change the owner:

```bash
sudo chown user file.txt
```

Change owner and group:

```bash
sudo chown user:group file.txt
```

For example:

```bash
sudo chown mayur:mayur file.txt
```

---

# 4. Text Processing

## `cat` — Display File Contents

Display the contents of a file:

```bash
cat file.txt
```

### Create a File Using `cat`

Run:

```bash
cat > file.txt
```

Type:

```text
Hello World
Linux Practical
```

Press:

```text
Ctrl + D
```

to save and exit.

---

## `less` — View a File Page by Page

Useful for large files:

```bash
less file.txt
```

Useful keys:

```text
Space → Next page
b     → Previous page
q     → Quit
```

---

## `more` — View a File Page by Page

```bash
more file.txt
```

---

## `grep` — Search Text

Suppose `file.txt` contains:

```text
Hello World
Linux is an operating system
Hello Linux
Python Programming
```

Search for `Linux`:

```bash
grep "Linux" file.txt
```

Output:

```text
Linux is an operating system
Hello Linux
```

### Case-Insensitive Search

```bash
grep -i "linux" file.txt
```

The `-i` option makes the search case-insensitive.

---

## `awk` — Process Columns

`awk` is commonly used to process text and columns.

Create a file:

```bash
cat > students.txt
```

Enter:

```text
101 Mayur 85
102 Rahul 90
103 Amit 78
```

Press:

```text
Ctrl + D
```

### Print the First Column

```bash
awk '{print $1}' students.txt
```

Output:

```text
101
102
103
```

### Print the Second Column

```bash
awk '{print $2}' students.txt
```

Output:

```text
Mayur
Rahul
Amit
```

---

## `sed` — Search and Replace Text

Replace the first occurrence of `Linux` on each line:

```bash
sed 's/Linux/Ubuntu/' file.txt
```

This displays the modified output but does **not** change the original file.

### Modify the File

To actually modify the file:

```bash
sed -i 's/Linux/Ubuntu/g' file.txt
```

The `g` means replace all matching occurrences on each line.

---

# 5. System Monitoring

## `top` — Monitor Processes

Shows currently running processes:

```bash
top
```

Press:

```text
q
```

to quit.

---

## `ps` — Display Processes

Display processes for the current shell:

```bash
ps
```

Display detailed information:

```bash
ps aux
```

Search for a specific process:

```bash
ps aux | grep firefox
```

The `|` is called a **pipe**. It sends the output of one command to another command.

---

## `df` — Check Disk Space

Show disk space:

```bash
df
```

Human-readable format:

```bash
df -h
```

Example:

```text
Filesystem   Size   Used   Avail   Use%
/dev/sda1    100G   40G    60G     40%
```

---

## `du` — Check Directory Usage

Show disk usage:

```bash
du
```

Human-readable format:

```bash
du -h
```

Check a particular folder:

```bash
du -sh Documents
```

The `-s` option gives a summary.

The `-h` option makes the output human-readable.

---

# 6. Networking Commands

## `ping` — Check Network Connectivity

Check connectivity to a website:

```bash
ping google.com
```

Stop the command with:

```text
Ctrl + C
```

Send only 4 packets:

```bash
ping -c 4 google.com
```

---

## `ip addr` — Display Network Interfaces

Modern Linux command:

```bash
ip addr
```

Short version:

```bash
ip a
```

You may see interfaces such as:

```text
lo
eth0
wlan0
```

The exact interface names depend on your system.

---

## `ifconfig` — Display Network Information

`ifconfig` is an older command:

```bash
ifconfig
```

If you see:

```text
command not found
```

this is normal on many modern Ubuntu installations.

Use:

```bash
ip addr
```

instead.

If you specifically need `ifconfig`, install the `net-tools` package:

```bash
sudo apt update
sudo apt install net-tools
```

Then run:

```bash
ifconfig
```

---

## `netstat` — Network Connections

Run:

```bash
netstat
```

`netstat` may not be installed by default on modern Ubuntu.

Install it with:

```bash
sudo apt update
sudo apt install net-tools
```

Then:

```bash
netstat -tuln
```

This can show listening TCP/UDP ports.

---

## `ssh` — Remote Login

SSH is used to remotely connect to another Linux machine:

```bash
ssh username@192.168.1.10
```

For example:

```bash
ssh mayur@192.168.1.20
```

You will generally be asked for authentication credentials.

---

# 7. Shell Scripting Basics

Shell scripts allow you to automate Linux commands.

---

## Create a Shell Script

Create a file:

```bash
gedit hello.sh
```

Write the following:

```bash
#!/bin/bash

echo "Enter your name:"
read name

echo "Hello $name"
```

Save the file as:

```text
hello.sh
```

---

## Give Execute Permission

```bash
chmod +x hello.sh
```

---

## Run the Script

```bash
./hello.sh
```

Example:

```text
Enter your name:
Mayur
Hello Mayur
```

---

# 8. `if` Statement

Example:

```bash
#!/bin/bash

read number

if [ $number -gt 10 ]
then
    echo "Number is greater than 10"
else
    echo "Number is 10 or less"
fi
```

Save it as:

```text
test.sh
```

Give execute permission:

```bash
chmod +x test.sh
```

Run:

```bash
./test.sh
```

Example:

```text
15
Number is greater than 10
```

---

# 9. `for` Loop

Example:

```bash
#!/bin/bash

for i in 1 2 3 4 5
do
    echo $i
done
```

Output:

```text
1
2
3
4
5
```

---

# 10. `while` Loop

Example:

```bash
#!/bin/bash

i=1

while [ $i -le 5 ]
do
    echo $i
    i=$((i+1))
done
```

Output:

```text
1
2
3
4
5
```

---

# Quick Command Reference

| Command    | Purpose                             |
| ---------- | ----------------------------------- |
| `pwd`      | Show current directory              |
| `ls`       | List files and directories          |
| `cd`       | Change directory                    |
| `touch`    | Create a file                       |
| `mkdir`    | Create a directory                  |
| `rm`       | Remove files/directories            |
| `rmdir`    | Remove empty directory              |
| `cp`       | Copy files/directories              |
| `mv`       | Move or rename files                |
| `chmod`    | Change permissions                  |
| `chown`    | Change file owner                   |
| `cat`      | Display file contents               |
| `less`     | View files page by page             |
| `more`     | View files page by page             |
| `grep`     | Search text                         |
| `awk`      | Process text/columns                |
| `sed`      | Search and replace text             |
| `top`      | Monitor running processes           |
| `ps`       | Display processes                   |
| `df`       | Show disk space                     |
| `du`       | Show directory/file usage           |
| `ping`     | Test network connectivity           |
| `ip`       | Display network information         |
| `ifconfig` | Older network configuration command |
| `netstat`  | Display network connections         |
| `ssh`      | Connect to a remote machine         |

---


