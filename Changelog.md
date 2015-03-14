### 1.3.1 (May 16, 2013) ###
  * Bug fix: Fix a memory leak in pacparser\_find\_proxy(). ([Issue 22](https://code.google.com/p/pacparser/issues/detail?id=22))
  * Enhancement: Use PACPARSER\_DEBUG environment variable rather than just 'DEBUG' to specify verbose logging. ([Issue 23](https://code.google.com/p/pacparser/issues/detail?id=23))
  * Enhancement: Improve error handling. Allow applications to control error reporting. ([Issue 24](https://code.google.com/p/pacparser/issues/detail?id=24))
  * Enhancement: Make pacparser python module compile on Python 3 as well. ([Issue 21](https://code.google.com/p/pacparser/issues/detail?id=21))

### 1.3.0 (Sep 10, 2011) ###
  * Bug fix: pactester returns with wrong exit status if it fails during the execution of FindProxyForURL ([Issue 12](https://code.google.com/p/pacparser/issues/detail?id=12)).
  * Build: Make pacparser build work on Mac OS X 10.6 ([Issue 11](https://code.google.com/p/pacparser/issues/detail?id=11)).
  * Build: Fix build for systems with python < 2.5 ([Issue 13](https://code.google.com/p/pacparser/issues/detail?id=13)).
  * Build: Fix build for systems not connected to internet ([Issue 14](https://code.google.com/p/pacparser/issues/detail?id=14)).
  * Feature: Enclose pacparser headers in extern C {} to reduce work for C++ developers.

### 1.2.9 (Apr 22, 2011) ###
  * Feature: Add a feature to pacparser to allow working with proxy auto-config (PAC) script directly (in string form) instead of requiring it to be in a file. For this, added 2 new functions to the pacparser API: pacparser\_parse\_pac\_string and pacparser\_parse\_pac\_file.
  * Feature: With the help of the above API changes, add a feature to pactester to read pac files from stdin as well - this will now allow pactester to take pac files as piped input from other programs like curl. (For background see: http://code.google.com/p/pacparser/issues/detail?id=9)
  * Portability: Change pacparser's build scripts to allow building on non-Linux GNU systems - kFreeBSD and GNU Hurd. With this change, pacparser should now build on all Debian ports.
  * Some small documentation related fixes.

### 1.2.8 (Apr 22, 2011) ###
  * Same as 1.2.9 (see above). Missed some docs in this one.

### 1.2.7 (Dec 13, 2010) ###
  * Bug: On Windows, initialize WinSock DLL before calling getaddrinfo. ( http://goo.gl/uuWZ5)
  * Development: Add tests for DNS functionality and run python tests on Windows also.
  * Bug: freeaddrinfo should be called on the argument of getaddrinfo, not on any 'ai' node. (http://goo.gl/HpIeA)
  * Bug: Truncate ipaddr\_list before sprinting strings into it. (http://goo.gl/ww69d)
  * Bug: Fix a bug in testdata which makes tests fail on 192.168.0.0 network hosts.(http://goo.gl/eoo0F).

### 1.2.6 (Sep 17, 2010) ###
  * Feature: Add a feature to record current version in the compiled pacparser library and make it available through -v option in pactester.
  * Build: Support for PowerPC. Use va\_copy for Linux on all architectures. This fixes build for Linux on PowerPC.
  * Build: Fix a major bug because of which pacparser was broken on ARM architecture. (http://code.google.com/p/pacparser/source/detail?r=faf5a0a7eeee6913e2d551f59d214c7f6adc8345)
  * Development: Simplify build on windows. Compile spidermonkey from the included source (hg logs -r 153:155)

### 1.2.1 (Aug 10, 2010) ###
  * Feature: Added support for Microsoft IPv6 PAC extensions. pacparser now supports following additional functions: dnsResolveEx, myIpAddressEx and isResolvableEx. To find more about this change: http://code.google.com/p/pacparser/issues/detail?id=4.
  * Bug fix: Exclude unnecessary `libjs` symbols while creating `libpacparser`.
  * Development: Moved to mercurial (hg) version control system from subversion (svn).
  * Development: Add tests for pacparser and run them after each build.

### 1.1.1 (June 19, 2010) ###
  * Lot of build system changes, triggered by disappearance of libmozjs on debian systems.
  * Ship spidermonkey source code along with pacparser source tarball.
  * Compile pacparser library against static spidermonkey library (libjs.a). This removes our dependence on spidermonkey shared library (libmozjs).
  * Much simpler build system overall: No expectations to find spidermonkey library on the system, no directions to user to build/get spidermonkey library.

### 1.1.0 (June 19, 2010) ###
  * Bad release. Look at 1.1.1 for real changes.

### 1.0.9 (Dec 4, 2009) ###
  * Very minor release. Remove 'debian' directory from pacparser release tarball.

### 1.0.8 (Dec 2, 2009) ###
  * Bug fix: Fixed the bug reported in Issues (2): weekdayRange() utility function doesn't handle 'SAT' properly.
  * Removed SpiderMonkey source code from pacparser release. Instead added a helper script to download and install SpiderMonkey library.
  * Modified build scripts to make pacparser build successfully on Mac OS (yay!).

### 1.0.7 (Mar 1, 2009) ###
  * Bug fix: Modified Makefile to produce PIC code for shared library, even on i386. (See http://code.google.com/p/pacparser/source/detail?r=100 for detailed list of changes).
  * Some more changes in order to make lintian happy and package more debian friendly.

### 1.0.6 (Oct 13, 2008) ###
  * Bug fix: Fix some memory leaks in pactester.c (patch by Phil Randal on pacparser mailing list).
  * Feature: Make pactester independent of protocol field in URL.
  * Copyright/License fixes: Fix LGPL version in copyright headers and add copyright headers to pacparser.h.

### 1.0.5 (May 18, 2008) ###
  * Feature: Now pacparser packages includes an implementation of [pactester](http://code.google.com/p/pactester). Yay! :) Compiled binaries for this version of pactester are included with debian package and windows binaries package.

### 1.0.4 (Apr 18, 2008) ###
  * Feature: Added a feature to set my ip address to a custom IP address. This is the IP returned by myIpAddress() JavaScript function.
  * Bug fix: Fixed the bug reported in Issues (1): myIpAddress function generates reference error on Windows platforms.
  * Bug fix: pacparser doesn't parse DOS mode PAC files (with \r\n as line separator) on Windows platforms.

### 1.0.3 (Jan 22, 2008) ###
  * Bug fix: Fixes a small bug in python module wrapper code. The bug is revealed when a malformed URL is passed to find\_proxy or just\_find\_proxy functions.

### 1.0.2 (Jan 22, 2008) ###
  * Feature: pacparse has its own **python module** now :). It's been confirmed to work with python 2.2-2.5.
  * Feature: Added building instructions for python module.
  * Feature: Some other documents update.

### 1.0.1 (Dec 18, 2007) ###
  * Bug fix: Fix a bug in Makefile. Make it use -fPIC only on x86\_64 systems. -fPIC is a problem on other systems (confirmed the problem on Ubuntu gutsy i386).
  * Feature: Add HTML documentation that will install in /usr/share/doc/libpacparser/html/.
  * Feature: Make Makefile packaging friendly. Change install paths to use DESTDIR prefix.

### 1.0.0 (Dec 15, 2007) ###
  * First release