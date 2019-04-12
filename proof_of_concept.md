# Proof of Concept
Below is the output from my terminal after I wrote the [format_string_bug.c](./format_string_bug.c) file using a code editor.

What this is showing is that the `printf` bug behavior described in the README lines up exactly with what was described by Ben in the Reply All episode.

The bit about "Segmentation fault" is the operating system's way of indicating to me that the program crashed.

```
[charles@noho tmp]$ clang format_string_bug.c -o format_string_bug.c
[charles@noho tmp]$ ./format_string_bug.c "88% Parentheticals"
88% Parentheticals
[charles@noho tmp]$ ./format_string_bug.c "100% Related"
100% Related
[charles@noho tmp]$ ./format_string_bug.c "99% Invisible"
Segmentation fault (core dumped)
[charles@noho tmp]$  
```
