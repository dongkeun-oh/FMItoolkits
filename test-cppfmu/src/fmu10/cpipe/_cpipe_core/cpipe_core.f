      program cpipe_core
c *
      implicit none
	  include 'cpipe_parm.inc'
      integer nIOData, Status, Dummy
      REAL*8 CurrTime, CurrStep
      logical GoOn
c *
      Status = 0
      GoOn = .true.
c *	  
      call GETINPUT(Status)
	  if (Status.ne.0) then
		return
	  endif
c *	  
      call OPENOFILE(Status)
	  
	  do while (Status.eq.0.and.GoOn)
	     call GETDATA(CurrTime, CurrStep, GoOn, Status)
		 call DOSTEP(CurrTime, CurrStep, Status)
		 call SENDDATA(GoOn, Status)
	  enddo
	  
	  CLOSE(OUNIT)
	  if (LOGUNIT.eq.LOGUNIT0) CLOSE(LOGUNIT)
c * 	  
      end
	  
	  
C ######################################################################
      subroutine GETINPUT(Status)
C ######################################################################
      implicit none
      include 'cpipe_parm.inc'
	  integer Status
c *	  
      character*256 WorkDir
      integer Dummy
c *	  
	  call IORDSTR(IFILENAME, Status)
	  if (Status.eq.0) then
         call INIT(Status)
         if (Status.ne.0) then
            Status = 2
            write(LOGUNIT,*) 'INIT : error in input file'
  		 endif
      else
         Status = -1
         write(LOGUNIT,*) 'I/O error in getting filename'
      endif 
c *	  
	  call IORDSTR(WorkDir, Status)
	  if (Status.eq.0) then
         call ChWorkDir(WorkDir, Status)
         if (Status.ne.0) then
            Status = 2
            write(LOGUNIT,*) 'CHWORKDIR : error in changing directory'
  		 endif
      else
         Status = -1
         write(LOGUNIT,*) 'I/O error in getting work dir. name'
      endif 
c *	  
      call IOWTINT(Status, Dummy)
      if (Status.ne.0) call IOCLEAR  
	  return
c *	  
	  end
		

C ######################################################################
      subroutine OPENOFILE(Status)
C ######################################################################
      implicit none
      include 'cpipe_parm.inc'
	  integer Status	  
c *	  
	  if (LOGFILE.eq.'.') then 
	     LOGUNIT = 0
	  else 
	     open(LOGUNIT0,file=LOGFILE,action='write',status='replace',
     &        iostat=Status)
	     if (status.eq.0) then
		    LOGUNIT = LOGUNIT0
	     else
		    LOGUNIT = 0
			Status = 0
	     endif
	  endif
c *	  
	  if (OFILENAME.ne.'.') then
         open(OUNIT,file=OFILENAME,action='write',status='replace',
     &        iostat=Status)
	     if (status.ne.0) write(LOGUNIT,*) 
     &                   'MAIN : cannot open out file'
	  else
	     write(LOGUNIT,*) 'MAIN : out file is not given'
		 status = -10
	  endif
      end
		
		
C ######################################################################
      subroutine INIT(Status)
C ######################################################################
      implicit none
      include 'cpipe_parm.inc'
      include 'cpipe_vars.inc'
c *
      integer Status
c *      
      real PDROP, RHO, VIS, P, T, MDOT, f
      integer DIR, I
c *
      real DHE, VISCHE
c * setting default values    
      AREA = 3.14E-5
      DH = 6.32E-3
      PERH = 0.01986
      XLEN = 10.
      TMBEG = 0.0
      TMEND = 10.0
      TMSTEP = 1E-3
      PINL = 5.0E5
      TINL = 4.5
      POUT = 5.0E5
      TOUT = 4.5
      Q0 = 1.0
      N = 25   
	  OFILENAME='.'
	  LOGFILE='.'
      Status = 0
c * read input file      
      open(10, FILE=IFILENAME, STATUS='OLD', IOSTAT=Status)
      if (Status.eq.0) then
         read(10, NML=INDATA, IOSTAT=Status)
         if (Status.ne.0) then
		    write(LOGUNIT,*) "INIT : error reading input file"
			return
	     endif
         close(10)
      else
         close(10)
         write(LOGUNIT,*) "INIT : cannot open file"
         return
      endif    
	  OutputTime = TMBEG
c * initialize 1-d flow 
      NM = N + 1
      if (PINL.ge.POUT) then
         DIR = 1
      else
         DIR = -1
      endif
      PDROP = ABS(PINL - POUT)
      if (DIR.gt.0) then
         P = PINL
         T = TINL
      else
         P = POUT
         T = TOUT
      endif
      RHO = DHE(P, T)
      VIS = VISCHE(P, T)
      call FINDMDOT(PDROP, RHO, VIS, MDOT, Status)
      MDOT = DIR*MDOT
c *
      do I = 1,NM
         f = 1.*(I-1)/(NM-1)
         PRE(I) = PINL*(1.-f) + POUT*f
         TEM(I) = T
         RHO = DHE(PRE(I),TEM(I))
         VEL(I) = MDOT/AREA/RHO
      enddo
	  
      PBIN  = PINL
      PBOUT = PBOUT
      TBIN  = TINL
      TBOUT = TOUT
	  
	  MDOTIN = MDOT
	  MDOTOUT = MDOT
	  TRIN = T
	  TROUT = T
c *      
      end
				
		
C ######################################################################
      subroutine GETDATA(CurrTime, CurrStep, GoON, Status)
C ######################################################################
      implicit none
      include 'cpipe_parm.inc'
	  real*8 CurrTime, CurrStep
	  logical GoON
	  integer Status
c *	  
      integer NTOT
	  parameter (NTOT = NREAD +2)
      real*8 RARRAY(NTOT)
	 
      call IORDDATA(RARRAY, NTOT, Status)
	  CurrTime = RARRAY(NREAD+1)
	  CurrStep = RARRAY(NREAD+2)
	  if (CurrTime.lt.0.or.Status.ne.0) then
	     GoOn = .false.
	  else
         call SETVARS(RARRAY(1:NREAD))	  
	  endif
c * 	  
	  end

	  
C ######################################################################
      subroutine SENDDATA(GoON, Status)
C ######################################################################
      implicit none
      include 'cpipe_parm.inc'
	  real*8 CurrTime, CurrStep
	  logical GoON
	  integer Status
c *	  
      integer NTOT
	  parameter (NTOT = NWRITE +1)
      real*8 WARRAY(NTOT)
c *
	  if (.not.GoON) then 
	     WARRAY(NWRITE+1) = -1.
	  elseif (Status.ne.0) then
	     WARRAY(NWRITE+1) = -2.
	  else 
	     WARRAY(NWRITE+1) = 0.
	  endif
	  
	  call GETVARS(WARRAY(1:NWRITE))
      call IOWTDATA(WARRAY, NTOT, Status)
c * 	  
	  end			
      

C ######################################################################
      subroutine DOSTEP(CurrTime, CurrTStep, Status)
C ###################################################################### 
      implicit none
      include 'cpipe_parm.inc' 
      include 'cpipe_vars.inc'            
c *
      real*8  CurrTime, CurrTStep
      integer Status
c *
      real TSTep, f, LE
      integer II
c *      
      Status = 0
      LE = XLEN/(NM-1)
      TimeStep = CurrTStep

      do while (CurrTime.gt.Time) 
         call SETMAT(Status)
         if (Status.ne.0) then
            write(LOGUNIT,*) 'DOSTEP : error in matrix setup'
            return
         endif
         call SOLSTEP(Status)
         if (Status.ne.0) then
            write(LOGUNIT,*) 'DOSTEP : error in solution step'
            return
         endif
      enddo
c *      
      if (Time.eq.Prev_Time) then
         f = 1.
      else
         f = (CurrTime-Prev_Time)/(Time-Prev_Time)
      endif
      Time = CurrTime
      do II=1,NM
         VEL(II) = (1.-f)*PREV_VEL(II) + f*VEL(II)
         PRE(II) = (1.-f)*PREV_PRE(II) + f*PRE(II)
         TEM(II) = (1.-f)*PREV_TEM(II) + f*TEM(II)
      enddo
c *	  
      call SETMAT(Status)
      if (Status.ne.0) then
         write(LOGUNIT,*) 'DOSTEP : error in matrix setup'
         return
      endif
      call SOLSTEP(Status)
      if (Status.ne.0) then
         write(LOGUNIT,*) 'DOSTEP : error in solution step'
         return
      endif
	  
	  if (Time.gt.OutputTime) then
	     write(OUNIT,*) "Time = ", Time
		 do II=1,NM
		    write(OUNIT,*) LE*(II-1), VEL(II), PRE(II), TEM(II)
		 enddo
		 OutputTime = OutputTime + OutStep
	  endif
c * 	  
      return
      end

      
C ######################################################################
      subroutine SETVARS(RARRAY)
C ###################################################################### 
      implicit none
      include 'cpipe_parm.inc' 
      include 'cpipe_vars.inc'            
c *
      real*8  RARRAY(*)
c *
      PBIN  = RARRAY(1)
      PBOUT = RARRAY(2)
      TBIN  = RARRAY(3)
      TBOUT = RARRAY(4)
c * 	  
      return
      end
	  
	  
C ######################################################################
	  subroutine GETVARS(WARRAY)
C ###################################################################### 
      implicit none
      include 'cpipe_parm.inc' 
      include 'cpipe_vars.inc'            
c *
      real*8  WARRAY(*)
c *  
      WARRAY(1) = MDOTIN
      WARRAY(2) = MDOTOUT
      WARRAY(3) = TRIN
      WARRAY(4) = TROUT
      WARRAY(5) = DELTAIN
      WARRAY(6) = DELTAOUT
c *	  
      return
      end	  
	  
	  
C ######################################################################
      subroutine FINDMDOT(PDROP, RHO, VIS, MDOT, Status)
C ######################################################################
      implicit none
      include 'cpipe_parm.inc'            
c *
      real PDROP, RHO, VIS
      integer Status
      real MDOT
c *      
      logical NOTCONV
      integer NIT
      real PREVMDOT, RR, ERR, REYNOLDS
      integer MAXNIT
      real MDOTTOL
      parameter (MAXNIT = 100, MDOTTOL = 1E-5)
      external BlasiusFrict
      real BlasiusFrict
c *
      Status = 0
      NIT = 0
      NOTCONV = .true.
      do while(NOTCONV)
         NIT = NIT + 1
         PREVMDOT = MDOT
         REYNOLDS = MDOT*DH/AREA/VIS
         RR = 2*BlasiusFrict(REYNOLDS)*XLEN/(AREA*AREA*DH*RHO)
         MDOT = SQRT(PDROP/RR)
         ERR = ABS(MDOT-PREVMDOT)/ABS(MDOT)
         if (ERR.gt.MDOTTOL.and.NIT.lt.MAXNIT) then
            NOTCONV = .true.
         else
            NOTCONV = .false.
         endif
      enddo
c *
      if (ERR.gt.MDOTTOL) then
         Status = 1
      endif
      return
      end
      
