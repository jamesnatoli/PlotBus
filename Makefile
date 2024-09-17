ODIR=obj
RCOMP=`root-config --cflags`
RCOMPLIB=`root-config --cflags --glibs`
CXXFLAGS=-g -std=c++17 -Wall -pedantic -Wno-unused-variable -I/usr/local/opt/libomp/include

_OBJ = PlotBus.o SetWeights.o FillFiles.o PlotTrain.o Colors.o PlotUtils.o Analyzers.o SimplePlot.o doQCDestimation.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))	

# Executables
invmass: runners/InvMass.cc $(OBJ)
	g++ $(CXXFLAGS) $(RCOMPLIB) -o bin/invmass $^
jetpt:   runners/JetpT.cc $(OBJ)
	g++ $(CXXFLAGS) $(RCOMPLIB) -o bin/jetpt $^
validation:   runners/multijetValidation.cc $(OBJ)
	g++ $(CXXFLAGS) $(RCOMPLIB) -o bin/val $^
test:    runners/test.cc $(OBJ)
	g++ $(CXXFLAGS) $(RCOMPLIB) -o bin/test $^
plot2d:  runners/plot2D.cc $(OBJ)
	g++ $(CXXFLAGS) $(RCOMPLIB) -o bin/plot2d $^	

# PlotBus 
$(ODIR)/PlotBus.o: PlotBus.cc PlotBus.h
	g++ $(CXXFLAGS) $(RCOMP) -c -o $@ $<
$(ODIR)/SetWeights.o: SetWeights.cc PlotBus.h
	g++ $(CXXFLAGS) $(RCOMP) -c -o $@ $<
$(ODIR)/FillFiles.o: FillFiles.cc PlotBus.h
	g++ $(CXXFLAGS) $(RCOMP) -c -o $@ $<
$(ODIR)/Colors.o: Colors.cc PlotBus.h
	g++ $(CXXFLAGS) $(RCOMP) -c -o $@ $<
$(ODIR)/PlotTrain.o: PlotTrain.cc PlotTrain.h $(ODIR)/PlotBus.o PlotBus.h
	g++ $(CXXFLAGS) $(RCOMP) -c -o $@ $<


# Plotting Things
$(ODIR)/PlotUtils.o: PlotUtils.cc PlotUtils.h $(ODIR)/PlotBus.o
	g++ $(CXXFLAGS) $(RCOMP) -c -o $@ $<
$(ODIR)/Analyzers.o: Analyzers.cc Analyzers.h $(ODIR)/PlotBus.o
	g++ $(CXXFLAGS) $(RCOMP) -c -o $@ $<
$(ODIR)/SimplePlot.o: SimplePlot.cc PlotBus.h $(ODIR)/PlotBus.o $(ODIR)/doQCDestimation.o $(ODIR)/PlotUtils.o
	g++ $(CXXFLAGS) $(RCOMP) -c -o $@ $<
$(ODIR)/doQCDestimation.o: doQCDestimation.cc PlotBus.h $(ODIR)/PlotBus.o
	g++ $(CXXFLAGS) $(RCOMP) -c -o $@ $<

# and clean
clean:
	rm -rf bin/*
	rm $(ODIR)/*.o

