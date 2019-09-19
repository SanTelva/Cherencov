# .bashrc

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

# Uncomment the following line if you don't like systemctl's auto-paging feature:
# export SYSTEMD_PAGER=

# User specific aliases and functions
# 23.06.19 export ROOTSYS=/usr/local
export ROOTSYS=/usr/local/lib/root
export PATH=$PATH:$ROOTSYS/bin
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ROOTSYS/lib/root              
export LD_LIBRARY_PATH=$ROOTSYS/lib/root
export DYLD_LIBRARY_PATH=/usr/local/lib/root
export LIBPATH=/usr/lib64/root
#export PYTHONPATH=/usr/lib64/python2.7
export PYTHONPATH=/usr/lib64/python3.5
export PYTHIA6=/usr/v6_428/lib
export PATH=$PATH:$GENIE/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$GENIE/lib        
export LHAPATH=/usr/lib64

export LD_LIBRARY_PATH=/usr/lib64:$LD_LIBRARY_PATH        
export LD_LIBRARY_PATH=$PYTHIA6:$LD_LIBRARY_PATH

. /home/koshka/GEANT4/geant4.10.05-install/share/Geant4-10.5.0/geant4make/geant4make.sh

export DAWN_PS_PREVIEWER=gv