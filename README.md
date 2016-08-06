# filetype-visualizer
Visualize file type by byte order patterns

This essentially reads a file byte by byte and creates a 2D histogram plot to show
which byte values follow which byte values how often. The inspiration for this
project stems from a TED talk which I cannot seem to find, in which the talker
demonstrated how different types of files -- JPEGs, source code, binary
executables -- produced radically different patterns when visalized this way.
The talk was essentially about hacking into people's phones, for example to
defuse home-built bombs, if I recall correctly. I would be thankful if someone
could point me to the talk in question.

# Example
Using a _log+1_ normalizer, we visualize the byte to byte transitions of all
.cpp files from this project. As can be seen, the transitions mostly exist
between characters in the lower seven bits, which is naturally the case for
text files:  
![cppfiles](doc/cpp_code.bmp)

The `main` binary file. We can still see some patterns here that we recognize
as text fragments. This has two reasons: First, we have strings in the code 
for exceptions, file paths and the like. Second, we have enabled the creation 
of debug symbols in our binaries (`-g`):  
![mainbinary](doc/main_binary.bmp)

An arbitrary PNG file. We can see that it uses all byte values more evenly 
distributed, but there are some clusters. I do not know enough about how PNG
files are actually stored to explain them:  
![pngfile](doc/png_file.bmp)
