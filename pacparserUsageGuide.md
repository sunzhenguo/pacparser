### Using pacparser in C ###

Determining proxy string for a set of PAC file, URL and host is as easy as:

```
#include <pacparser.h>
char *proxystring = pacparser_just_find_proxy("examples/wpad.dat",
                                              "http://www.manugarg.com",
                                              "www.manugarg.com")
```

This function initializes javascript context, loads pac file, determines proxy and finally destroys javascript context.

As you can see, if you want to find out proxy string for multiple URLs, this is not the recommended method. In that case, you first

  1. initialize pac parser engine:
```
#include <pacparser.h>
pacparser_init()
```
  1. and then, parse pac file:
```
if(!pacparser_parse_pac_file("examples/wpad.dat")){
  error("could not parse pac file");
}
```
  1. determine proxy string for a URL:
```
char *proxystring = pacparser_find_proxy("http://www.manugarg.com", "www.manugarg.com");
```
  1. do other things and find proxy for another URL:
```
...
proxystring = pacparser_find_proxy("http://www.google.com", "www.google.com");
```
  1. do some other things and in the end shutdown pacparser engine:
```
...
pacparser_cleanup()
```

### Using pacparser in Python: ###
pacparser comes as a python module also. It can be imported in python programs like any other python module.
```
import pacparser
pacparser.init()
pacparser.parse_pac("examples/wpad.dat")
proxy = pacparser.find_proxy("http://www.manugarg.com",
                                  "www.manugarg.com")
print proxy
pacparser.cleanup()
```

or, simply just
```
import pacparser
print pacparser.just_find_proxy("examples/wpad.dat",
               "http://www.manugarg.com", "www.manugarg.com")
```

### Functions Reference ###
  * [pacparser\_init](http://pacparser.googlecode.com/hg/docs/html/pacparser_init.3.html)
  * [pacparser\_parse\_pac\_file](http://pacparser.googlecode.com/hg/docs/html/pacparser_parse_pac_file.3.html)
  * [pacparser\_find\_proxy](http://pacparser.googlecode.com/hg/docs/html/pacparser_find_proxy.3.html)
  * [pacparser\_cleanup](http://pacparser.googlecode.com/hg/docs/html/pacparser_cleanup.3.html)
  * [pacparser\_just\_find\_proxy](http://pacparser.googlecode.com/hg/docs/html/pacparser_just_find_proxy.3.html)