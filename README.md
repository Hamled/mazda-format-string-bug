## `printf` format string bug in Mazda Connect Infotainment System
### Bug Description
The Infotainment System's UI (and possibly other software elements) crashes when a Bluetooth audio source sends
track metadata wherein the track name (at least) includes a "%n" conversion specifier.

### Example Case
When the track's title includes the string "99% Invisible" this triggers a crash.

#### How the string is understood by the C code
To better understand why it crashes, we need to break down the string into its component parts (ordinary characters
and conversion specifications). Each character explained:
* '9' - ordinary character
* '9' - ordinary character
* '%' - start of conversion specification
* ' ' (space) - formatting flag, says that if a number needs to be padded with extra character, use a space instead of a 0. So you get "&nbsp;&nbsp;&nbsp;123" instead of "000123".
* 'I' - length modifier, says to treat the number in its 'raw' form as using a certain number of bits (this one is platform specific, so 32 bits for 32-bit machines, 64 for 64-bit). ([Details here.][1])
* 'n' - conversion specifier, in order to interpolate a number you'd usually use 'i' or 'd'. 'n' has a completely different meaning, discussed below.
* "visible" - all ordinary characters

#### What the 'n' means in "% In"
Unlike every other conversion specifier (e.g. 'i' and 'd' for numbers, 's' for a string), the 'n' conversion specifier does not output information.

Instead, it's used to calculate the total number of characters in the string prior to the %n. It then tries to store that number in a variable. This is the source of the crash (and the [source of some software vulnerabilities][2]).

#### Why the "%n" crashes the program
When the program tries to store the calculated number in a variable, and the coder never /intended/ for this to happen, then they haven't provided a variable to store the number.

In that case the program (for reasons that are too much to get into) ends up trying to store it in a place where it's not allowed to (this is called a segmentation fault). Usually this results in a crash because it's unspecified how to recover from that error condition.

#### Proof of Concept
I wrote up a quick example of how this kind of bug looks in C code, and how the behavior lines up with what was described in the Reply All episode.
* [Description](./proof_of_concept.md)
* [Code](./proof_of_concept.c)

#### Additional notes
* Perhaps the most unusual aspect of this from a coder's perspective (this kind of bug isn't all that uncommon, unfortunately), is actually the 'I' itself. This is a Microsoft-invented 'upgrade' to the ISO standard C format specifiers, but it's almost certainly the case that Mazda's Infotainment System does not use Windows as its operating system.

    It turns out that GCC and Clang (the two major compilers for open source software) have included the 'I' specifier as well, presumably for compatibility so people can easily move their code from Microsoft's VC++ compiler to them (and back).

* Talking about code using natural languages like English is really fraught with problems! The Reply All episode that discussed this bug involved the hosts speaking with some coders about using the phrase "percent I" -- but maybe everyone was assuming "%i" which is much more common.

    However for the computer, in its infinitely pedantic manner, "%i" and "%I" have nothing in common... which means we as coders have to be aware of that kind of difference. Without that key info, we wouldn't know to look past the 'I' and see that the 'n' is what was causing the crash.

[1]: https://docs.microsoft.com/en-us/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions?view=vs-2019#argument-size-specification
[2]: https://www.youtube.com/watch?v=0WvrSfcdq1I
