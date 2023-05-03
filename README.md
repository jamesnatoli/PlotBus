# PlotBus
Plotting framework for fast samples with ROOT (ROOT Version: 6.19/01)

# Quick Hits
To make plots first create a runner script, which can be stored in runners/.

Then, compile the runner with ROOT. The following are all different ways you can do this:
```
g++ runners/TestVar.cc $RCOMP -o bin/testvar
g++ runners/TestVar.cc `root-config --cflags --glibs` -o bin/testvar
g++ runners/TestVar.cc -stdlib=libc++ -pthread -std=c++11 -m64 -I/Users/jamesnatoli/root/builddir/include -L/Users/jamesnatoli/root/builddir/lib -lGui -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -stdlib=libc++ -lpthread -lm -ldl -o bin/testvar
```

where this should provide all the requisite dependancies. You can set an environment variable in your `.bashrc` or `.bash_profile` for convenience:
```
RCOMP=`root-config --cflags --glibs`
```

Lastly, execute the binary that you've generated:
```
./bin/testvar
```

Plots will be saved in directories here, this repo is set up to ignore any directories that begin with plots.


