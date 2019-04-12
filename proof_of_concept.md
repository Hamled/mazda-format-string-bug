# Proof of Concept
Below is the output from my terminal after I wrote the [proof_of_concept.c](./proof_of_concept.c) file using a code editor.

What this is showing is that the `printf` bug behavior described in the README lines up exactly with what was described by Ben in the Reply All episode. It also shows that if the 'n' is removed from "Invisible" the crash should stop occurring. Verifying that behavior would, to my mind, constitute a positive confirmation that this was the issue even without having access to actual Mazda Firmware.

The bit about "Segmentation fault" is the operating system's way of indicating to me that the program crashed.

```
[charles@noho tmp]$ clang proof_of_concept.c -o proof_of_concept
[charles@noho tmp]$ ./proof_of_concept "100% Related"
100% Related
[charles@noho tmp]$ ./proof_of_concept "88% Parentheticals"
88% Parentheticals
[charles@noho tmp]$ ./proof_of_concept "99% Invisible"
Segmentation fault (core dumped)
[charles@noho tmp]$ ./proof_of_concept "99% Ivisible"
99% Ivisible
[charles@noho tmp]$ 
```
