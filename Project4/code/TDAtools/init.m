% This script initializes the various variables required, and enables
%the interaction of the MATLAB session and the java code stored in
%bin/tda.jar.

%Written by Rann Bar-On, Dept of Mathematics, Duke University

% The following section gets the directory in which this script is run, and
% stores it in the global variable TLDIR.

mypath = which(mfilename('fullpath'));
% splitpathwithfile = strsplit(mypath,'/');
% pathlength = length(splitpathwithfile)-1;
% splitpath=splitpathwithfile(1:pathlength);
% joinedpath=strjoin(splitpath,'/');
joinedpath = fileparts(mypath);

global TLDIR;
% TLDIR=strcat(joinedpath,'/');
TLDIR=strcat(joinedpath,filesep);
cd(TLDIR);

% clear mypath splitpathwithfile pathlength joinedpath splitpath
clear mypath joinedpath 

% Add current directory and all its subdirectories to path
addpath(genpath(TLDIR));

% Save TLDIR, as for some reason, javaclasspath clears global variables

TLDIRbak=TLDIR;

% Set Java class path
%javaclasspath(TLDIR,'bin/tda.jar');
javaclasspath(TLDIR,['bin', filesep, 'tda.jar']);

% Bring back TLDIR
global TLDIR
TLDIR=TLDIRbak;
clear TLDIRbak;

% Import Java functions required
% Note: the scope of this is only the workspace.  Any functions using Tda objects need to
% rerun this command.

import tda/api.*;


