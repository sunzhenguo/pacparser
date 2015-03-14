_**pacparser**_ is a library to parse [proxy auto-config](http://en.wikipedia.org/wiki/Proxy_auto-config) (PAC) files. Proxy auto-config files are a vastly used proxy configuration method these days. Web browsers can use a PAC file to determine  which proxy server to use or whether to go direct for a given URL. PAC files are written in JavaScript and can be programmed to return different proxy methods (e.g. "PROXY proxy1:port; DIRECT") depending upon URL, source IP address, protocol, time of the day etc. PAC files introduce a lot of possibilities. Look at the wikipedia link above to find out more about them.

Needless to say, PAC files are now a widely accepted method for proxy configuration management and companies all over are using them in corporate environment. Almost all popular web browsers support PAC files. The idea behind pacparser is to make it easy to add this PAC file parsing capability to any program (C and python supported right now). It comes as a shared C library and a python module which can be used to make any C or python program PAC scripts intelligent. Some very useful targets could be popular web software like wget, curl and python-urllib.

Please look at the [README](http://pacparser.googlecode.com/svn/trunk/README) and other links for more information.

### Support Pacparser ###
<p>If you like this program, you can donate here. Thanks for support!</p>
[![](https://www.paypal.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=manugarg%40gmail%2ecom&lc=US&item_name=pacparser&currency_code=USD&bn=PP%2dDonationsBF%3abtn_donateCC_LG%2egif%3aNonHosted)


---

### Installation ###
**On debian based systems (including Ubuntu):**
```
apt-get install libpacparser1 python-pacparser libpacparser-dev
```

**For Mac OS X:**<br>
Download .dmg file from <a href='http://code.google.com/p/pacparser/downloads/list'>here</a>.<br>
<br>
<b>For Windows Systems:</b><br>
Download .zip files from <a href='http://code.google.com/p/pacparser/downloads/list'>here</a> and      follow the <a href='http://pacparser.googlecode.com/svn/trunk/INSTALL'>instructions</a>.<br>
<hr />
<h3>Usage Examples</h3>

<b>Using it with python:</b>
<pre><code>&gt;&gt;&gt; import pacparser<br>
&gt;&gt;&gt; pacparser.init()<br>
&gt;&gt;&gt; pacparser.parse_pac_file('examples/wpad.dat')<br>
&gt;&gt;&gt; pacparser.find_proxy('http://www.google.com', 'www.google.com')<br>
'PROXY proxy1.manugarg.com:3128; PROXY proxy2.manugarg.com:3128; DIRECT'<br>
&gt;&gt;&gt; pacparser.find_proxy('http://www2.manugarg.com', 'www2.manugarg.com')<br>
'DIRECT'<br>
&gt;&gt;&gt; pacparser.cleanup()<br>
&gt;&gt;&gt;<br>
</code></pre>
<b>Using it in C:</b>
<pre><code>manugarg@hobbiton:~$ cat pactest.c<br>
#include &lt;stdio.h&gt;<br>
#include &lt;pacparser.h&gt;<br>
<br>
int main(int argc, char* argv[])<br>
{<br>
  char *proxy;<br>
  pacparser_init();<br>
  pacparser_parse_pac_file(argv[1]);<br>
  proxy = pacparser_find_proxy(argv[2], argv[3]);<br>
  printf("%s\n", proxy);<br>
  pacparser_cleanup();<br>
}<br>
<br>
manugarg@hobbiton:~$ gcc -o pactest pactest.c -lpacparser<br>
manugarg@hobbiton:~$ ./pactest wpad.dat http://www.google.com www.google.com<br>
PROXY proxy1.manugarg.com:3128; PROXY proxy2.manugarg.com:3128; DIRECT<br>
</code></pre>