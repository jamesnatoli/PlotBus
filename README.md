# PlotBus
Plotting framework for fast samples with ROOT (ROOT Version: 6.19/01)

# Quick Hits
To make plots first create a runner script, which can be stored in runners/. These are small scripts which just create a Plotbus object, set some parameters for a specific plot, and then pass a reference to your Plotbus object to the plotting function. You can make runners for each variable that you want, or have a main runner with which you just change the variable that you're plotting (or both even).

The general idea is that the runners can be quickly changed for plotting preferences (binning, log/lin scale, specific processes, etc). Cuts can be added here as whole strings, but the Plotbus class expects a few types of cuts, and in this case you'll just need to set the value of the cut.

## Note on Cuts
There are 2 main ways to provide cuts to the plot, described [below](https://github.com/jamesnatoli/PlotBus#plotbus-constructor). The actual plots are made with the [`TTree::Draw()`](https://root.cern.ch/doc/master/classTTree.html#a73450649dc6e54b5b94516c468523e45) function, and so cuts should be formatted according to the documentation. 

### Manual Cut String
To bypass the hardcoded cuts that the Plotbus expects, set the variable `plotbus->manualCutString` to a string with your cuts. This will override **all** of the default cuts in the class, using **only** this string as the argument for `TTree::Draw()`

### Default Cuts
As the cuts from an analysis become more established, you can add them as variables to the Plotbus class. All of these are set to some default value by the object constructor. These cuts and their default values are described in the following table:


| Variable            | Description      | Value |
| ------------------- | ---------------- | ----: |
| chargereq              |      Triplet charge   | 1 |
| deepTauVsEl | DeepTau descriminant score (>=) vs Electrons | 3 (VVLoose) |
| deepTauVsMu | DeepTau descriminant score (>=) vs Muons | 15 (Tight) |
| deepTauVsJet | DeepTau descriminant score (>=) vs Jets | 31 (Medium) |
| IsoTrack_iso | Isolation cut (<) for IsoTrack | 0.1 |
| Dxy | Transverse Impact Parameter (<) | 1.0 |
| Dz | Longitudinal Impact Parameter (<) | 1.0 |
| bjetVeto | cut events with B Jets | false |
| SRcut1_scale | Signal Region cut to invert for scale (normalization) (ABCD Method) | `PionTriplet_pion3_iso < 0.1` |
| SRcut2_shape | Signal Region cut to invert for shape (ABCD Method) | `PionTriplet_LowestDeepTauVsJet >= 31` |
| eventCuts | cuts that apply to the whole event | `Trigger_ditau && !LeptonVeto` |
| tripletCuts | cuts that apply to every triplet | `(abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack)` |

## How to Run
Once you have a runner written, compile with ROOT in one of the following ways:
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

# Main Components
Breakdown of the main components to the plotting framework

## Plotbus.cc
This is the class which will hold all of the information about the fit. Most of these parameters are stored as public member variables and so can be easily accessed. Any additional parameters you want to add for convenience of functionality can be added to the class as well.

### Plotbus constructor
The constructor takes a year as a parameter and sets some preferences to default values. These can all be changed in the runner file that you make. These defaults are listed here:


| Variable | Description | Value |
| -------- | ----------- | ----: |
| bkgsToPlot | Backgrounds you want shown on the plot | QCD, DY, TT, VV |
| processes | All processes to plot over | QCD, DY, DY10, ST, TT, ttV, VV, VVV, W+Jets |
| procsToStack | Processes that you want stacked together | bkgsToPlot |
| era | Identifier from TauFW specifying which ntuple version | Wto3pi_2018_cont2 |
| mainpath | Where the code looks for your samples | `"/Volumes/WineCellar/KState/analysis/" + era + "/"` |
| year | Which year of samples you want to load | passed to constructor |
| filepath | Where the plots will be saved | `"plots_" + era + "/"` |
| logy | Make y axis in log scale | false |
| logandlin | Save plots for log and linear scale | false |
| mergeOthers | ??? | false;
| saveHists   | Save a .C version of the histogram for inspection to `histMacros/`| false |
| plotData    | Draw the data plot| true |
| plotDataSR  | Draw the data in your Signal Region (**be careful**)| false |
| plotSignal  | Draw the Signal on the plot| true |
| normalize   | Normalize the histograms to unity| false |
| stack       | Make a stack| true |
| fillHists   | Draw the histograms with the colors filled in| true |
| doQCD       | Estimate QCD from Data using the ABCD Method| true |
| overflow    | Include the overflow bin in the yields calculation| false |
| verbosity   | How much information should be printed out, turn up for debugging| 0 |
| SignalScale | Factor of 10 to multiply signal by | 5 |
| stdMCweight | Weight to be applied to MC samples | `XSecMCweight * Generator_weight * PUweight * PionTriplet_TauSFweight` |
| qcdMCweight | Weight for QCD MC samples | `XSecMCweight * Generator_weight * PUweight * PionTriplet_TauSFweight * 0.5` |
| stichMCweight | Wight for samples that are stitched (DY, W+Jets) | `PUweight * PionTriplet_TauSFweight` |
| title | Title for the plot | the variable you're plotting (branch name) |
| xtitle | Title for xaxis | the variable you're plotting (branch name) |

**NB**: the notation of "bkgs (backgrounds)" and "processes" may be confusing. This is more for convenience, as referring to everything as "processes" allows us to loop over backgrounds, sigal, and data all at once without worrying about which are present. Usually we only want to display the processes which are non-negligible, as many minor backgrounds will be reduced quickly to irrelevancy.

We still load and draw them for the purposes of completion (it's doesn't slow down the code very much). Additionally, in case we are estimating QCD from data, all backgrounds must be subtracted and we want this to be as accurate as possible. The yields are printed to terminal and displayed in the legend (this might be bad though...)

### Getters
There are many functions of this class which take the values of the cuts or weights and return a string formatted for `TTree::Draw`

### UnsetSignalRegionVars
This function sets the Signal Region variables to dummy values, which will have no effect. This allows you to plot these variables, or play around with the values. For Wto3pi, `deepTauVsJet` is set to 1 (VVVLoose), and `IsoTrack_iso` is set to <= 0.

### MergeFiles
This sets up the the object member `files` (`std::map<std::string, std::vector<std::string>>`)such that it has strings for each processes mapped to vectors containing the paths (as strings) for that sample. It's convenient to have one data structure to loop over. Signal and data are mapped as "signal" and "data" respectively.

## SimplePlot.cc

## PlotUtils.h

## Analyzers.h

## FillFiles.cc

## Colors.h

## QCDestimation.cc
