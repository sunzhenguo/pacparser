Linking in pacparser on VisualStudio 2005 is as easy as linking in any other C library. I could do it in following steps;

  1. Download compiled binaries (version >=1.0.1) for Win32 from pacparser [download page](http://code.google.com/p/pacparser/downloads/list). Direct link to 1.3.0 binaries: [click here](http://pacparser.googlecode.com/files/pacparser-1.3.0-win32.zip).
  1. Extract these files on your machine. On extracting it will create a folder named pacparser-x.y.z (pacparser-1.3.0 for version 1.3.0). Here are some important files inside it and their function:
    * pacparser.dll -> This file is needed to run any application linked against pacparser. This file should be in your path somewhere or in the same directory as your executable.
    * pacparser.lib -> Import library. This file is needed to link in pacparser on Visual Studio.

  1. Copy pacparser.lib and pacparser.h to your Visual Studio project directory.
  1. Modify your project's properties in Visual Studio so that compiler can find and use pacparser.h and pacparser.lib. If you don't know Visual Studio that well (I don't, for example), then follow steps 3 and 4 in the document [here](http://www.learncpp.com/cpp-tutorial/a2-using-libraries-with-visual-studio-2005-express/).
  1. And then just compile (F7).

Now if you get an error during execution that pacpaser.dll could not be found in your path, that means that your dlls are not in path. To make your application run, you can simply copy pacparser.dll to the directory where your application's executable is. Alternatively, you can add pacparser's directory (e.g. C:\tools\libs\pacparser-1.3.0) to %PATH% environment variable in "My Computers -> Right Click -> Properties -> Advanced ->
Environment Variables".

There should not be any issues with it. Please let me know if there are any.

Cheers!