## jls - simple file list

jls is a simple utility I created because I
cannot remember ls(1) options between various
[Unix](https://en.wikipedia.org/wiki/Unix)
Systems.

It also avoids command line size by reading
the files to process from stdin or a Text File.
Some
[Unix](https://en.wikipedia.org/wiki/Unix)
Systems have a rather short Command Line Buffer.

To build, execute build.sh to generate a Makefile from
Makefile.template on most BSD/Linux systems and IBM AIX.
For MS-DOS, it should be rather easy to create a Makefile.

This requires [j\_lib2](https://github.com/jmcunx/j_lib2) to build.

[GNU automake](https://en.wikipedia.org/wiki/Automake)
only confuses me, so I came up with my own method which
is a real hack.  But works for me.
