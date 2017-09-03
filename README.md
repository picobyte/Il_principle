# Il_principle
School Management game

A HHS+ clone, rewritten in Qt/C++


This is work in progress - not playable yet..


If you want to help, git clone the repository, and send a pull request when you have something. The stable branch should compile and run.

You need to download the HHS+ package and link the HHS+ Schools directory in the Il_principle project directory, and 
convert the xml files to json; e.g.

```bash
git clone --recursive -j8 https://github.com/picobyte/Il_principle.git
cd Il_principle
ln -s /path/to/HHS+1.8.5-1797-Release/Schools/
./do_xml2json.sh
```

To compile, import the project in Qt creator, build and run. See Qt requirements:

http://doc.qt.io/qt-5/supported-platforms.html

Of course you also need a C++ compiler, just follow the links for your OS. Also required is qt5-charts:

https://doc.qt.io/qt-5/qtcharts-index.html

The source for HHS+ is not available, but with ilspy or dnspy it is possible to decompile the HHS+ binary if you
want to know about the HHS+ internal structure. Trying to compile the result in monodevelop failed, after fixing many issues
it compiled but still didn't run since mono does not support the WPF in use by HHS+. Don't know how to fix it in csharp.


(c) picobyte, 2017, GPL2
