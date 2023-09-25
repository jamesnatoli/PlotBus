// Class to store information specific to a sample
#idndef SAMPLE
#define SAMPLE

// ROOT includes

// C++ includes

// Personal includes

class Sample {
public:
  // Constructor
  Sample();
  Sample( std::string name);

  std::string name;
  std::string title;
  std::string cutstring;
  std::string weight;
  int color;
  int linestyle;

  bool drawfilled;
  
  TH1F* hist;
  TChain* files;

  // Member Functions
  // Getters
  
  // Setters
  
};

// Constructor 
Sample::Sample( std::string name) {
  

  // Set some defaults
  
  
}

// Signal, Background, and Data classes, which inherit from Sample
class Signal : public Sample {
public:
  Signal();

  // Member Functions

};

class Background : public Sample {
public:
  Background();

  // Member Functions
  
};

class Data : public Sample {
public:
  Data();
  
  // Member Functions

};


#endif
