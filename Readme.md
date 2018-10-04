# musicFilesApp

This is a script program I wrote in C++ for my Dad. The prgram reads from the XML file that itunes go to the file for
each individual path and copies each song file to a single directory. It's purpose was to take itunes playlists and turn
them into image files but the program only goes as far as to copy all the files to a single directory so from there a program
like imgburn can grab the folder and turn it into an ISO file.

# Why did I use C++ instead of scripting language like Python?

I did it for the sake of Windows protability and didn't want him to have to install Python


# Why did I choose C++ over C# since it's API would've made the task easier to code for?

I chose C++ over C# because I didn't want to have to deal compatitability between versions of .NET frameworks


+-------------------+          +------------------+
|                   |          |                  |
|   main            |          |   searcher       |
|                   +----------+                  |
|                   |          ^                  |
|                   |          |                  |
|                   |          |                  |
+-------^-----------+          +------+-----------+
        |                             |
        |                             |
        |                             |
        |                             |
        +-----------------------------+
