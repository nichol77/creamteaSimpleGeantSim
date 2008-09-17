######################################
#
# Clean all G4 envs
unset  CLHEP_BASE_DIR
unset  CLHEP_INCLUDE_DIR
unset  CLHEP_LIB
unset  CLHEP_LIB_DIR

unset  G4ANALYSIS_USE
unset  G4DEBUG
unset  G4INCLUDE
unset  G4INSTALL

unset  G4LEDATA
unset  G4LEVELGAMMADATA
unset  G4NEUTRONHPDATA
unset  G4RADIOACTIVEDATA
unset  G4ABLADATA

unset  G4LIB
unset  G4LIB_BUILD_G3TOG4
unset  G4LIB_BUILD_SHARED
unset  G4LIB_BUILD_STATIC
unset  G4LIB_BUILD_ZLIB
unset  G4LIB_BUILD_GDML
unset  G4LIB_USE_G3TOG4
unset  G4LIB_USE_GRANULAR
unset  G4LIB_USE_ZLIB

unset  G4SYSTEM

unset  G4UI_BUILD_WIN32_SESSION
unset  G4UI_BUILD_XAW_SESSION
unset  G4UI_BUILD_XM_SESSION
unset  G4UI_USE_TCSH
unset  G4UI_USE_WIN32
unset  G4UI_USE_XAW
unset  G4UI_USE_XM
unset  G4UI_USE_QT

unset  G4VIS_BUILD_DAWN_DRIVER
unset  G4VIS_BUILD_OIWIN32_DRIVER
unset  G4VIS_BUILD_OIX_DRIVER
unset  G4VIS_BUILD_OPENGLWIN32_DRIVER
unset  G4VIS_BUILD_OPENGLXM_DRIVER
unset  G4VIS_BUILD_OPENGLX_DRIVER
unset  G4VIS_BUILD_RAYTRACERX_DRIVER
unset  G4VIS_BUILD_VRML_DRIVER
unset  G4VIS_BUILD_OPENGLQT_DRIVER

unset  G4VIS_USE_DAWN
unset  G4VIS_USE_OIWIN32
unset  G4VIS_USE_OIX
unset  G4VIS_USE_OPENGLWIN32
unset  G4VIS_USE_OPENGLX
unset  G4VIS_USE_OPENGLXM
unset  G4VIS_USE_RAYTRACERX
unset  G4VIS_USE_VRML
unset  G4VIS_USE_OPENGLQT


#
# g4system.U
#
#+
G4SYSTEM="Linux-g++"
export G4SYSTEM
if [ X$g4non_display = X ] ; then
echo "On this machine the G4SYSTEM=$G4SYSTEM"
fi

#
# g4dirs.U
#
#+
if [ X/home/waugh/apps/32bit/geant4.9.1.p02 != X/usr/local/geant4.9.1.p02 ] ; then
G4INSTALL="/usr/local/geant4.9.1.p02/src/geant4"
else
G4INSTALL="/home/waugh/apps/32bit/geant4.9.1.p02"
fi
export G4INSTALL
if [ X$g4non_display = X ] ; then
echo "On this machine the G4INSTALL=$G4INSTALL"
fi

#+
if [ Xy != Xn ] ; then 
if [ X/home/waugh/apps/32bit/geant4.9.1.p02 != X/usr/local/geant4.9.1.p02 ] ; then
G4INCLUDE="/usr/local/geant4.9.1.p02/include/geant4"
else
G4INCLUDE="/home/waugh/apps/32bit/geant4.9.1.p02/include/"
fi
export G4INCLUDE
if [ X$g4non_display = X ] ; then
echo "On this machine the G4INCLUDE=$G4INCLUDE"
fi
#else
#G4BASE="/usr/local/geant4.9.1.p02/include/geant4/source"
#export G4BASE
#if [ X$g4non_display = X ] ; then
#echo "On this machine the G4BASE=$G4BASE"
#fi
fi

#+
if [ X/home/waugh/apps/32bit/geant4.9.1.p02/lib != X ] ; then 
if [ X/home/waugh/apps/32bit/geant4.9.1.p02 != X/usr/local/geant4.9.1.p02 ] ; then
G4LIB="/usr/local/geant4.9.1.p02/lib/geant4"
else
G4LIB="/home/waugh/apps/32bit/geant4.9.1.p02/lib"
fi
export G4LIB
if [ X$g4non_display = X ] ; then
echo "On this machine the G4LIB=$G4LIB"
fi
fi

#+
if [ X/usr/local/geant4.9.1.p02/data/PhotonEvaporation2.0 != X ] ; then 
G4LEVELGAMMADATA="/usr/local/geant4.9.1.p02/data/PhotonEvaporation2.0"
export G4LEVELGAMMADATA
if [ X$g4non_display = X ] ; then
echo "On this machine the G4LEVELGAMMADATA=$G4LEVELGAMMADATA"
fi
fi

#+
if [ X/usr/local/geant4.9.1.p02/data/RadioactiveDecay3.2 != X ] ; then 
G4RADIOACTIVEDATA="/usr/local/geant4.9.1.p02/data/RadioactiveDecay3.2"
export G4RADIOACTIVEDATA
if [ X$g4non_display = X ] ; then
echo "On this machine the G4RADIOACTIVEDATA=$G4RADIOACTIVEDATA"
fi
fi

#+
if [ X/usr/local/geant4.9.1.p02/data/G4EMLOW5.1 != X ] ; then 
G4LEDATA="/usr/local/geant4.9.1.p02/data/G4EMLOW5.1"
export G4LEDATA
if [ X$g4non_display = X ] ; then
echo "On this machine the G4LEDATA=$G4LEDATA"
fi
fi

#+
if [ X/usr/local/geant4.9.1.p02/data/G4NDL3.12 != X ] ; then 
G4NEUTRONHPDATA="/usr/local/geant4.9.1.p02/data/G4NDL3.12"
export G4NEUTRONHPDATA
if [ X$g4non_display = X ] ; then
echo "On this machine the G4NEUTRONHPDATA=$G4NEUTRONHPDATA"
fi
fi

#+
if [ X/usr/local/geant4.9.1.p02/data/G4ABLA3.0 != X ] ; then 
G4ABLADATA="/usr/local/geant4.9.1.p02/data/G4ABLA3.0"
export G4ABLADATA
if [ X$g4non_display = X ] ; then
echo "On this machine the G4ABLADATA=$G4ABLADATA"
fi
fi




#+
#if [ X != X ] ; then 
#G4ELASTICDATA=""
#export G4ELASTICDATA
#if [ X$g4non_display = X ] ; then
#echo "On this machine the G4ELASTICDATA=$G4ELASTICDATA"
#fi
#fi

#
# g4clhep.U
#
if [ X/usr/local/clhep-2.0.3.3 != X ] ; then 
CLHEP_BASE_DIR="/usr/local/clhep-2.0.3.3"
export CLHEP_BASE_DIR
if [ X$g4non_display = X ] ; then
echo "On this machine the CLHEP_BASE_DIR=$CLHEP_BASE_DIR"
fi
fi

#+
if [ X/usr/local/clhep-2.0.3.3/include != X ] ; then 
CLHEP_INCLUDE_DIR="/usr/local/clhep-2.0.3.3/include"
export CLHEP_INCLUDE_DIR
if [ X$g4non_display = X ] ; then
echo "On this machine the CLHEP_INCLUDE_DIR=$CLHEP_INCLUDE_DIR"
fi
fi

#+
if [ X/usr/local/clhep-2.0.3.3/lib != X ] ; then 
CLHEP_LIB_DIR="/usr/local/clhep-2.0.3.3/lib"
export CLHEP_LIB_DIR
if [ X$g4non_display = X ] ; then
echo "On this machine the CLHEP_LIB_DIR=$CLHEP_LIB_DIR"
fi
fi

#+
if [ XCLHEP != X ] ; then 
CLHEP_LIB="CLHEP"
export CLHEP_LIB
if [ X$g4non_display = X ] ; then
echo "On this machine the CLHEP_LIB=$CLHEP_LIB"
fi
fi

#+
#
# g4debug
#
if [ Xn = Xy ] ; then 
G4DEBUG=1
export G4DEBUG
if [ X$g4non_display = X ] ; then
echo "On this machine the G4DEBUG=$G4DEBUG"
fi
fi

#
# g4analysis
#
#+
if [ Xy = Xy ] ; then
G4ANALYSIS_USE=1
export G4ANALYSIS_USE
if [ X$g4non_display = X ] ; then
echo "On this machine the G4ANALYSIS_USE=$G4ANALYSIS_USE"
fi
fi 

#
# g4ui
#
#+
if [ Xy = Xy ] ; then
G4UI_BUILD_XAW_SESSION=1
export G4UI_BUILD_XAW_SESSION
if [ X$g4non_display = X ] ; then
echo "On this machine the G4UI_BUILD_XAW_SESSION=$G4UI_BUILD_XAW_SESSION"
fi
fi 

#+
if [ Xy = Xy ] ; then
G4UI_USE_XAW=1
export G4UI_USE_XAW
if [ X$g4non_display = X ] ; then
echo "On this machine the G4UI_USE_XAW=$G4UI_USE_XAW"
fi
fi 

#+
if [ Xy = Xy ] ; then
G4UI_BUILD_XM_SESSION=1
export G4UI_BUILD_XM_SESSION
if [ X$g4non_display = X ] ; then
echo "On this machine the G4UI_BUILD_XM_SESSION=$G4UI_BUILD_XM_SESSION"
fi
fi 

#+
if [ Xy = Xy ] ; then
G4UI_USE_XM=1
export G4UI_USE_XM
if [ X$g4non_display = X ] ; then
echo "On this machine the G4UI_USE_XM=$G4UI_USE_XM"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4UI_BUILD_WIN32_SESSION=1
export G4UI_BUILD_WIN32_SESSION
if [ X$g4non_display = X ] ; then
echo "On this machine the G4UI_BUILD_WIN32_SESSION=$G4UI_BUILD_WIN32_SESSION"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4UI_USE_WIN32=1
export G4UI_USE_WIN32
if [ X$g4non_display = X ] ; then
echo "On this machine the G4UI_USE_WIN32=$G4UI_USE_WIN32"
fi
fi 


#+
if [ Xn = Xy ] ; then
G4UI_BUILD_QT_SESSION=1
export G4UI_BUILD_QT_SESSION
if [ X$g4non_display = X ] ; then
echo "On this machine the G4UI_BUILD_QT_SESSION=$G4UI_BUILD_QT_SESSION"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4UI_USE_QT=1
export G4UI_USE_QT
if [ X$g4non_display = X ] ; then
echo "On this machine the G4UI_USE_QT=$G4UI_USE_QT"
fi
fi 



#
# g4vis
#
#+
if [ Xy = Xy ] ; then
G4VIS_BUILD_DAWN_DRIVER=1
export G4VIS_BUILD_DAWN_DRIVER
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_BUILD_DAWN_DRIVER=$G4VIS_BUILD_DAWN_DRIVER"
fi
fi 

#+
if [ Xy = Xy ] ; then
G4VIS_BUILD_OPENGLX_DRIVER=1
export G4VIS_BUILD_OPENGLX_DRIVER
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_BUILD_OPENGLX_DRIVER=$G4VIS_BUILD_OPENGLX_DRIVER"
fi
fi 

#+
if [ Xy = Xy ] ; then
G4VIS_BUILD_OPENGLXM_DRIVER=1
export G4VIS_BUILD_OPENGLXM_DRIVER
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_BUILD_OPENGLXM_DRIVER=$G4VIS_BUILD_OPENGLXM_DRIVER"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4VIS_BUILD_OPENGLWIN32_DRIVER=1
export G4VIS_BUILD_OPENGLWIN32_DRIVER
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_BUILD_OPENGLWIN32_DRIVER=$G4VIS_BUILD_OPENGLWIN32_DRIVER"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4VIS_BUILD_OIX_DRIVER=1
export G4VIS_BUILD_OIX_DRIVER
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_BUILD_OIX_DRIVER=$G4VIS_BUILD_OIX_DRIVER"
fi
fi 

#+
if [ Xy = Xy ] ; then
G4VIS_BUILD_RAYTRACERX_DRIVER=1
export G4VIS_BUILD_RAYTRACERX_DRIVER
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_BUILD_RAYTRACERX_DRIVER=$G4VIS_BUILD_RAYTRACERX_DRIVER"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4VIS_BUILD_OIWIN32_DRIVER=1
export G4VIS_BUILD_OIWIN32_DRIVER
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_BUILD_OIWIN32_DRIVER=$G4VIS_BUILD_OIWIN32_DRIVER"
fi
fi 

#+
if [ Xy = Xy ] ; then
G4VIS_BUILD_VRML_DRIVER=1
export G4VIS_BUILD_VRML_DRIVER
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_BUILD_VRML_DRIVER=$G4VIS_BUILD_VRML_DRIVER"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4VIS_BUILD_OPENGLQT_DRIVER=1
export G4VIS_BUILD_OPENGLQT_DRIVER
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_BUILD_OPENGLQT_DRIVER=$G4VIS_BUILD_OPENGLQT_DRIVER"
fi
fi 



#+
if [ Xy = Xy ] ; then
G4VIS_USE_DAWN=1
export G4VIS_USE_DAWN
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_USE_DAWN=$G4VIS_USE_DAWN"
fi
fi 

#+
if [ Xy = Xy ] ; then
G4VIS_USE_OPENGLX=1
export G4VIS_USE_OPENGLX
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_USE_OPENGLX=$G4VIS_USE_OPENGLX"
fi
fi 

#+
if [ Xy = Xy ] ; then
G4VIS_USE_OPENGLXM=1
export G4VIS_USE_OPENGLXM
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_USE_OPENGLXM=$G4VIS_USE_OPENGLXM"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4VIS_USE_OPENGLWIN32=1
export G4VIS_USE_OPENGLWIN32
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_USE_OPENGLWIN32=$G4VIS_USE_OPENGLWIN32"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4VIS_USE_OIX=1
export G4VIS_USE_OIX
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_USE_OIX=$G4VIS_USE_OIX"
fi
fi 

#+
if [ Xy = Xy ] ; then
G4VIS_USE_RAYTRACERX=1
export G4VIS_USE_RAYTRACERX
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_USE_RAYTRACERX=$G4VIS_USE_RAYTRACERX"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4VIS_USE_OIWIN32=1
export G4VIS_USE_OIWIN32
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_USE_OIWIN32=$G4VIS_USE_OIWIN32"
fi
fi 

#+
if [ Xy = Xy ] ; then
G4VIS_USE_VRML=1
export G4VIS_USE_VRML
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_USE_VRML=$G4VIS_USE_VRML"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4VIS_USE_OPENGLQT=1
export G4VIS_USE_OPENGLQT
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_USE_OPENGLQT=$G4VIS_USE_OPENGLQT"
fi
fi



#+
if [ X != X ] ; then
OGLHOME=""
export OGLHOME
if [ X$g4non_display = X ] ; then
echo "On this machine the OGLHOME=$OGLHOME"
fi
fi 

#+
if [ X != X ] ; then
OIVHOME=""
export OIVHOME
if [ X$g4non_display = X ] ; then
echo "On this machine the OIVHOME=$OIVHOME"
fi
fi 

#+
if [ X != X ] ; then
QTHOME=
export QTHOME
if [ X$g4non_display = X ] ; then
echo "On this machine the QTHOME=$QTHOME"
fi 
fi


#+
if [ Xy != X ] ; then
XMFLAGS=" -I/usr/X11R6/include "
export XMFLAGS
if [ X$g4non_display = X ] ; then
echo "On this machine the XMFLAGS=$XMFLAGS"
fi
fi 

#+
if [ Xy != X ] ; then
XMLIBS=" -lXm -lXpm "
export XMLIBS
if [ X$g4non_display = X ] ; then
echo "On this machine the XMLIBS=$XMLIBS"
fi
fi 

#+
if [ Xy != X ] ; then
XMFLAGS=" -I/usr/X11R6/include "
export XMFLAGS
if [ X$g4non_display = X ] ; then
echo "On this machine the XMFLAGS=$XMFLAGS"
fi
fi 

#+
if [ X != X ] ; then
XMLIBS=" -lXm -lXpm "
export XMLIBS
if [ X$g4non_display = X ] ; then
echo "On this machine the XMLIBS=$XMLIBS"
fi
fi 

#+
if [ Xy != X ] ; then
XAWFLAGS=" -I/usr/X11R6/include "
export XAWFLAGS
if [ X$g4non_display = X ] ; then
echo "On this machine the XAWFLAGS=$XAWFLAGS"
fi
fi 

#+
if [ Xy != X ] ; then
XAWLIBS=" -lXaw "
export XAWLIBS
if [ X$g4non_display = X ] ; then
echo "On this machine the XAWLIBS=$XAWLIBS"
fi
fi 


#
# Use GDML module
#
#+
if [ Xy = Xy ] ; then
G4LIB_BUILD_GDML=1
export G4LIB_BUILD_GDML
echo "On this machine the G4LIB_BUILD_GDML=$G4LIB_BUILD_GDML"
fi 

if [ Xy = Xy ] ; then
XERCESCROOT=
export XERCESCROOT
echo "On this machine the XERCESCROOT=$XERCESCROOT"
fi 



#
# Use G3TOG4 module
#
#+
if [ Xy = Xy ] ; then
G4LIB_BUILD_G3TOG4=1
export G4LIB_BUILD_G3TOG4
if [ X$g4non_display = X ] ; then
echo "On this machine the G4LIB_BUILD_G3TOG4=$G4LIB_BUILD_G3TOG4"
fi
fi 

if [ Xy = Xy ] ; then
G4LIB_USE_G3TOG4=1
export G4LIB_USE_G3TOG4
if [ X$g4non_display = X ] ; then
echo "On this machine the G4LIB_USE_G3TOG4=$G4LIB_USE_G3TOG4"
fi
fi 

#
# Use ZLIB module
#
#+
if [ Xy = Xy ] ; then
G4LIB_BUILD_ZLIB=1
export G4LIB_BUILD_ZLIB
if [ X$g4non_display = X ] ; then
echo "On this machine the G4LIB_BUILD_ZLIB=$G4LIB_BUILD_ZLIB"
fi
fi 

if [ Xy = Xy ] ; then
G4LIB_USE_ZLIB=1
export G4LIB_USE_ZLIB
if [ X$g4non_display = X ] ; then
echo "On this machine the G4LIB_USE_ZLIB=$G4LIB_USE_ZLIB"
fi
fi 


#+
#
# g4shared
#
if [ Xy = Xy ] ; then
G4LIB_BUILD_SHARED=1
export G4LIB_BUILD_SHARED
if [ X$g4non_display = X ] ; then
echo "On this machine the G4LIB_BUILD_SHARED=$G4LIB_BUILD_SHARED"
fi
fi 

if [ Xn = Xy ] ; then
G4LIB_BUILD_STATIC=1
export G4LIB_BUILD_STATIC
if [ X$g4non_display = X ] ; then
echo "On this machine the G4LIB_BUILD_STATIC=$G4LIB_BUILD_STATIC"
fi
fi 

#+
#
# g4granular
#
if [ Xy = Xy ] ; then
G4LIB_USE_GRANULAR=1
export G4LIB_USE_GRANULAR
if [ X$g4non_display = X ] ; then
echo "On this machine the G4LIB_USE_GRANULAR=$G4LIB_USE_GRANULAR"
fi
fi 

# Check for Windows!
if test "X$G4SYSTEM" != "XWIN32-VC" -a "X$G4SYSTEM" != "XWIN32-VC7"; then
#+
#
# UI_USE_TCSH for Unix
#
G4UI_USE_TCSH=1
export G4UI_USE_TCSH
if [ X$g4non_display = X ] ; then
echo "On this machine the G4UI_USE_TCSH=$G4UI_USE_TCSH"
fi 
fi

#####################################################################



#+
#
# G4WORKDIR
#
if [ $G4WORKDIR ] ; then

if [ X\$g4non_display = X ] ; then
echo "In your environment you have the G4WORKDIR=$G4WORKDIR"
fi

else

# Check for Windows!
if test "X$G4SYSTEM" = "XWIN32-VC" -o "X$G4SYSTEM" = "XWIN32-VC7"; then

if [ X\$g4non_display = X ] ; then
echo "G4WORKDIR will be set to c:/geant4 (in "native" Windows syntax)"
fi

G4WORKDIR="c:/geant4"
export G4WORKDIR

else # if Unix

if [ X\$g4non_display = X ] ; then
echo "G4WORKDIR will be set to HOME/geant4=$HOME/geant4"
fi

G4WORKDIR=$HOME/geant4
export G4WORKDIR

fi # if platforms

fi




#
# Shared libraries
#
if [ $G4LIB_BUILD_SHARED ] ; then
#
# Warning about LD_LIBRARY_PATH
#
echo ''
echo 'LD_LIBRARY_PATH is set to include CLHEP and Geant4 libraries. '
echo ''
echo 'NOTE : verify that the correct path for the CLHEP library'
echo '- $CLHEP_BASE_DIR/lib - is included in the $LD_LIBRARY_PATH'
echo 'variable in your environment, and no other outdated installations'
echo 'of CLHEP are by chance referenced through $LD_LIBRARY_PATH and'
echo 'present in your system !'
echo ''

if [ $LD_LIBRARY_PATH ] ; then
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${G4LIB}/${G4SYSTEM}
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${CLHEP_BASE_DIR}/lib

if [ $G4LIB_BUILD_GDML ] ; then
   LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${XERCESCROOT}/lib
fi
export LD_LIBRARY_PATH

else
LD_LIBRARY_PATH=${G4LIB}/${G4SYSTEM}
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${CLHEP_BASE_DIR}/lib

if [ $G4LIB_BUILD_GDML ] ; then
   LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${XERCESCROOT}/lib
fi

export LD_LIBRARY_PATH
fi
fi

#
# Shared libraries for Mac
#
if test "X$G4SYSTEM" = "XDarwin-g++" ; then

if [ $G4LIB_BUILD_SHARED ] ; then
if [ $DYLD_LIBRARY_PATH ] ; then
DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}:${G4LIB}/${G4SYSTEM}
DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}:${CLHEP_BASE_DIR}/lib

if [ $G4LIB_BUILD_GDML ] ; then
   DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}:${XERCESCROOT}/lib
fi

export DYLD_LIBRARY_PATH
else
DYLD_LIBRARY_PATH=${G4LIB}/${G4SYSTEM}
DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}:${CLHEP_BASE_DIR}/lib

if [ $G4LIB_BUILD_GDML ] ; then
   DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}:${XERCESCROOT}/lib
fi

export DYLD_LIBRARY_PATH
fi
fi

fi

#
# For BIN
#
PATH=${PATH}:${G4WORKDIR}/bin/${G4SYSTEM}
export PATH

