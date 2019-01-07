C ######################################################################
      subroutine SOLSTEP(Status)
C ######################################################################
      implicit none
      include 'cpipe_parm.inc'
      include 'cpipe_vars.inc'
c *      
      integer Status
c *
      integer  IPIV(NDOF*NM), INFO
      external DGBSV
      external DHE
      real     DHE
c *
      integer II, JJ, I, J, J1, J2, KIDX, NMAX, IB, IDOF
c *
      NMAX = NDOF*NM
c * build system matrix
      do JJ=1,NMAX
         do II=1,BDWDT
            SYSMAT(KBAND+II,JJ) = MMAT(II,JJ)
     &           +TimeStep*(AMAT(II,JJ)+SMAT(II,JJ)+GMAT(II,JJ))
         enddo
      enddo
c * build system load
      do I=1,NMAX
         J1 = MAX(1,I-KBAND)
         J2 = MIN(NMAX,I+KBAND)
         do J=J1,J2
            KIDX = KBAND+I-J+1
            SYSLOD(I) = SYSLOD(I)
     &           -SYSVAR(J)*(AMAT(KIDX,J)+SMAT(KIDX,J)+GMAT(KIDX,J))
         enddo
         SYSLOD(I) = TimeStep*SYSLOD(I)
      enddo
c *
      IB = 2
      do II=1,BDWDT
         SYSMAT(KBAND+II,IB) = 0.0 
      enddo
      SYSMAT(2*KBAND + 1,IB) = 1.0
      SYSLOD(IB) = PBIN - PRE(1)
      if (VEL(1).gt.0.0) then
         IB = 3
         do II=1,BDWDT
            SYSMAT(KBAND+II,IB) = 0.0
         enddo
         SYSMAT(2*KBAND + 1,IB) = 1.0
         SYSLOD(IB) = TBIN - TEM(1)
      endif
      IB = NDOF*(NM-1) + 2
      do II=1,BDWDT
         SYSMAT(KBAND+II,IB) = 0.0 
      enddo
      SYSMAT(2*KBAND + 1,IB) = 1.0
      SYSLOD(IB) = PBOUT - PRE(NM)
      if (VEL(NM).lt.0.0) then
         IB = NDOF*(NM-1) + 3
         do II=1,BDWDT
            SYSMAT(KBAND+II,IB) = 0.0
         enddo
         SYSMAT(2*KBAND + 1,IB) = 1.0
         SYSLOD(IB) = TBOUT - TEM(NM)
      endif
      
c * solve band matrix
      call DGBSV(NMAX,KBAND,KBAND,1,SYSMAT,LDBD,IPIV,SYSLOD,NMAX,INFO)
 
c * recover system variables
      do II=1,NMAX
         SYSVAR(II) = SYSVAR(II)+SYSLOD(II)
      enddo
c *
      do II=1,NM
         IDOF = NDOF*(II-1) 
         PREV_VEL(II) = VEL(II)
         PREV_PRE(II) = PRE(II)
         PREV_TEM(II) = TEM(II)
         VEL(II) = SYSVAR(IDOF+1)/AREA
         PRE(II) = SYSVAR(IDOF+2)
         TEM(II) = SYSVAR(IDOF+3)
      enddo
      Prev_Time = Time
      Time = Time + TimeStep
c * compute the output for extern I/O	  
      MDOTIN = VEL(1)*DHE(PRE(1),TEM(1))*AREA
      MDOTOUT = -VEL(NM)*DHE(PRE(NM),TEM(NM))*AREA
      TRIN = TEM(1)
      TROUT = TEM(NM)
      DELTAIN = 2.*TimeStep**2*AREA/3./XLEN*(NM-1)
      DELTAOUT = 2.*TimeStep**2*AREA/3./XLEN*(NM-1)
      end    
