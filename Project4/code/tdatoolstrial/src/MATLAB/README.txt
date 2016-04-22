This is the MATLAB source code. 
It's divided into four (important) directories:

Topology: this contains all the code for producing diagarms from point clouds, distance matrices, and the like.
The functions rca1*.m and LSD.m interact with tda.jar; everything else does not.

FeatureVectorsFromDiagrams: this contains code to turn persistence diagrams into feature vectors.
Two main paradigms are used here:
     
1) skewing and then binning to produce count data:
  Commands in this category are binnedMorse.m, binDiagram.m. There is also
plotBinnedDiagram.m, which shows the bin counts as a heat map.


2) sorting bars by length, and then using their birth and length info to create vectors.
  This is just BarHeightFVCreator.m

StatsandMachineLearning: In addition to a bunch of machine-learning techniques tailored
to bin-count data, there is also two implementations of "permutation test."

Samplers: a few sampler functions, mainly needed to do things in the tutorials and labs (see /examples/labs)

 