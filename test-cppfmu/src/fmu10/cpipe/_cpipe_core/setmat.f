C ######################################################################
      subroutine SETMAT(Status)
C ######################################################################
      implicit none
      include 'cpipe_parm.inc'
      include 'cpipe_vars.inc'
c *      
      integer Status
c *
      real getNodalFrict
c *      
      real*8 M(NDOF,NDOF),A(NDOF,NDOF),G(NDOF,NDOF),S(NDOF,NDOF),Q(NDOF)
      real*8 MEL(ELDOF,ELDOF),AEL(ELDOF,ELDOF),GEL(ELDOF,ELDOF),
     &     SEL(ELDOF,ELDOF),QEL(ELDOF)
      real LE
      real VA, PA, TA, dTdx, RHOA, CVA, SA, PHIA, FSFA
      real frct1, frct2, FFA, kgm
      integer II, JJ, KK, IDOF, N1, N2, I, J, NOFF
c *
      real DHE, CVHE, SNDHE, GRUNHE, SUPFLDHE        
c *
      Status = 0
      LE = XLEN/(NM-1)
c * make arrays empty
      do JJ = 1,NDOF
         do II = 1,NDOF
            M(II,JJ) = 0.0
            A(II,JJ) = 0.0
            S(II,JJ) = 0.0            
            G(II,JJ) = 0.0
         enddo
         Q(JJ) = 0.0
      enddo
      do JJ = 1,ELDOF
         do II = 1,ELDOF
            MEL(II,JJ) = 0.0
            AEL(II,JJ) = 0.0
            SEL(II,JJ) = 0.0            
            GEL(II,JJ) = 0.0
         enddo
         QEL(JJ) = 0.0
      enddo      
      do JJ = 1,NM*NDOF
         do II = 1,BDWDT
            SYSMAT(KBAND+II,JJ) = 0.0
            MMAT(II,JJ) = 0.0
            AMAT(II,JJ) = 0.0
            GMAT(II,JJ) = 0.0
            SMAT(II,JJ) = 0.0            
         enddo
         SYSLOD(JJ) = 0.0
      enddo
c * get dof variables
      do II=1,NM
         IDOF = NDOF*(II-1)
         SYSVAR(IDOF+1) = VEL(II)*AREA
         SYSVAR(IDOF+2) = PRE(II)
         SYSVAR(IDOF+3) = TEM(II)
!         write(*,*) LE*(II-1), VEL(II), PRE(II), TEM(II)
      enddo
!      write(*,*) ' '
c * generate matrices
      frct1 = getNodalFrict(1)
      do KK=1,NM-1
         N1 = KK
         N2 = KK+1
c *         
         frct2 = getNodalFrict(N2)
         FFA = .5*(frct2 + frct1)
         frct1 = frct2
c *
         dTdx = (TEM(N2)-TEM(N1))/LE
         VA = .5*(VEL(N1)+VEL(N2))
         PA = .5*(PRE(N1)+PRE(N2))
         TA = .5*(TEM(N1)+TEM(N2))
         if (PA.lt.0.0) then
            write(LOGUNIT,*) 'error: negative pressure at elem # = ',KK
            Status = -1
         endif
         if (TA.lt.0.0) then
            write(LOGUNIT,*) 
     &	         'error: negative temperature at elem # = ',KK
            Status = -1
         endif
         RHOA = DHE(PA,TA)
         CVA = CVHE(PA,TA)
         SA = SNDHE(PA,TA)
         PHIA = GRUNHE(PA,TA)
         FSFA = SUPFLDHE(PA,TA)
         if (FSFA.gt.0.0) then
            if (dTdx.ge.1e-6) then
               kgm=(FSFA/dTdx**2)**0.333333
            else
               kgm=(FSFA/1e-12)**0.333333
            endif
         else
            kgm = 0.0
         endif         
c * m-matrix
         M(1,1) = RHOA
         M(2,2) = AREA
         M(3,3) = AREA*RHOA*CVA
c * a-matrix (of the Euler equations) 
         A(1,1) = RHOA*VA
         A(1,2) = AREA
         A(2,1) = SA*SA*RHOA
         A(2,2) = AREA*VA
         A(3,1) = RHOA*PHIA*CVA*TA
         A(3,3) = AREA*RHOA*CVA*VA
c * s-matrix (of the frction term)        
         S(1,1) = 2.0*RHOA*FFA/DH*ABS(VA)
         S(2,1) =-2.0*PHIA*RHOA*VA*FFA/DH*ABS(VA)
         S(3,1) =-2.0*RHOA*VA*FFA/DH*ABS(VA)
c * g-matrix (of the counter current heat diffusion
c *           + the numerical viscosity)
         G(1,1) = 0.5*RHOA*LE*(ABS(VA)+SA)
         G(2,2) = PHIA*AREA*kgm + 0.5*AREA*LE*ABS(VA)
         G(3,3) = AREA*kgm + 0.5*RHOA*CVA*AREA*LE*ABS(VA)
c * q-vector (of the heat load)
         Q(2) = PHIA*Q0
         Q(3) = Q0
c *         
         do JJ=1,NDOF
            do II=1,NDOF
c *               
               MEL(II,JJ)           = LE*M(II,JJ)/3.
               MEL(II,JJ+NDOF)      = LE*M(II,JJ)/6.
               MEL(II+NDOF,JJ)      = LE*M(II,JJ)/6.
               MEL(II+NDOF,JJ+NDOF) = LE*M(II,JJ)/3.
c *
               AEL(II,JJ)           = -.5*A(II,JJ)
               AEL(II,JJ+NDOF)      = +.5*A(II,JJ)
               AEL(II+NDOF,JJ)      = -.5*A(II,JJ)
               AEL(II+NDOF,JJ+NDOF) = +.5*A(II,JJ)
c *
               SEL(II,JJ)           = LE*S(II,JJ)/3.
               SEL(II,JJ+NDOF)      = LE*S(II,JJ)/6.
               SEL(II+NDOF,JJ)      = LE*S(II,JJ)/6.
               SEL(II+NDOF,JJ+NDOF) = LE*S(II,JJ)/3.
c *
               GEL(II,JJ)           = +G(II,JJ)/LE
               GEL(II,JJ+NDOF)      = -G(II,JJ)/LE
               GEL(II+NDOF,JJ)      = -G(II,JJ)/LE
               GEL(II+NDOF,JJ+NDOF) = +G(II,JJ)/LE               
            enddo
c *            
            QEL(JJ)      = 0.5*LE*Q(JJ)
            QEL(JJ+NDOF) = 0.5*LE*Q(JJ)            
         enddo
         NOFF = NDOF*(KK-1)
         do II=1,ELDOF
            if (QEL(II).NE.0.0)
     &           SYSLOD(II+NOFF) = SYSLOD(II+NOFF) + QEL(II)
            do JJ=1,ELDOF
               J = NOFF + JJ
               I = KBAND + II - JJ + 1
               MMAT(I,J) = MMAT(I,J) + MEL(II,JJ)
               AMAT(I,J) = AMAT(I,J) + AEL(II,JJ)
               SMAT(I,J) = SMAT(I,J) + SEL(II,JJ)
               GMAT(I,J) = GMAT(I,J) + GEL(II,JJ)
            enddo
         enddo
      enddo
      end
      
C ######################################################################
      function getNodalFrict(INODE)
C ######################################################################
      implicit none
      include 'cpipe_parm.inc'
      include 'cpipe_vars.inc'
      integer  INODE
      real     getNodalFrict
c *
      real v, p, t
      real re
c *      
      real BlasiusFrict
      real DHE, VISCHE
c *
      v = VEL(INODE)
      p = PRE(INODE)
      t = TEM(INODE)
      re = DHE(p,t)*abs(v)*DH/VISCHE(p,t)
      getNodalFrict = BlasiusFrict(re)
      return
      end

C ######################################################################
      function BlasiusFrict(re)
C######################################################################
      implicit none
      real re
      real BlasiusFrict
c *      
      real f_bl, f_la
c * Constants for Blasius frction factor      
      real a_bl,b_bl,remin_bl
      data a_bl     / 0.079/
      data b_bl     / 0.250/
      data remin_bl /10.000/
c * Constants fort laminal flow friction factor      
      real a_la ,remin_la
      data a_la     /16.000/
      data remin_la /1.0e-1/
c * Laminal flow frction factor     
      if(re.gt.remin_la) then
         f_la = a_la/re
      else
         f_la = a_la/remin_la
      endif
c * Blasius friction factor
      if(re.gt.remin_bl) then
         f_bl=a_bl/re**b_bl
      else
         f_bl=a_bl/remin_bl**b_bl
      endif
c *
      BlasiusFrict = max(f_bl, f_la)
      return
      end
