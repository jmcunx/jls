## jls - simple file list

jls is a simple utility I created because I
cannot remember ls(1) options between various
[Unix](https://en.wikipedia.org/wiki/Unix)
Systems.
I also wanted a default of printing only Last
Modification Date/Time and File Name.

It also avoids command line size by reading
the files to process from stdin or a Text File.
Some
[Unix](https://en.wikipedia.org/wiki/Unix)
Systems have a rather short Command Line Buffer.

[j\_lib2](https://github.com/jmcunx/j_lib2) is an **optional** dependency.

[GNU automake](https://en.wikipedia.org/wiki/Automake)
only confuses me, but this seems to be good enough for me.

**To compile:**
* If "DESTDIR" is not set, will install under /usr/local
* Execute ./build.sh to create a Makefile
* Works on Linux, BSD and AIX

_To uninstall_, execute
"make uninstall"
from the source directory
