      INTEGER MAXNOD
      PARAMETER(MAXNOD=5000)
      INTEGER NDOF,ELDOF,BDWDT,KBAND,LDBD
      PARAMETER(NDOF=3,ELDOF=2*NDOF)
      PARAMETER(KBAND=2*NDOF-1,BDWDT=4*NDOF-1,LDBD=3*KBAND+1)
      INTEGER MAXDOF
      PARAMETER(MAXDOF=MAXNOD*NDOF)
c *
      REAL    VEL(MAXNOD),PRE(MAXNOD),TEM(MAXNOD)
      REAL    PREV_VEL(MAXNOD),PREV_PRE(MAXNOD),PREV_TEM(MAXNOD)
      REAL*8  MMAT(BDWDT,MAXDOF),AMAT(BDWDT,MAXDOF),
     &        SMAT(BDWDT,MAXDOF),GMAT(BDWDT,MAXDOF)
      REAL*8  SYSMAT(LDBD,MAXDOF),SYSVAR(MAXDOF),SYSLOD(MAXDOF)
      REAL*8  PBIN,PBOUT,TBIN,TBOUT
      REAL*8  MDOTIN,MDOTOUT,TRIN,TROUT,DELTAIN,DELTAOUT
      INTEGER NM      
      REAL    Time,Prev_Time,TimeStep,OutputTime
      COMMON  /VARS/  
     &            PBIN,PBOUT,TBIN,TBOUT,
     &            MDOTIN,MDOTOUT,TRIN,TROUT,DELTAIN,DELTAOUT,
     &            VEL,PRE,TEM,
     &            PREV_VEL,PREV_PRE,PREV_TEM,
     &            MMAT,AMAT,SMAT,GMAT, 
     &            SYSMAT,SYSVAR,SYSLOD,NM,
     &		  Time,Prev_Time,TimeStep,OutputTime
