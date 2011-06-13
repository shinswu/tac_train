Okay,
  Lets write a program that will calculate
the up to the 93rd fibonacci number. 
The f(30) = 832040
Why is it hard to write a program
to get past the f(47) and f(93)?
f(47) = 2971215073

Hint what is the hex value of f(30)?


If your new to gcc and you are writing your
C program in a file called main.c, you can do
the following:
  gcc -c main.c -o main.o
  gcc -o main main.o

If you would like to compile your program with
debug, do the following:
  gcc -g -O0 -c main.c -o main.o
  gcc -o main main.o

to run your program under the debugger do the following:
   gdb main
   set args <the command line args to run your program>
   b main
   run

   To print out the value of a variable:
     p <a variable name>  
     p /x <a variable name>
   To step into a function call:
     s
   To step over a function or just to the next line:
     n
   To set a breakpoint on a function:
     b <function name>
   To set a breakpoint on a line number:
     b <line number>
     b <file name>:<line number>

This should get you started.
Try writing a program by using a recursive
function. If you need help there are implementations
in dga_src.

