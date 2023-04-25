C ######################################################################
      subroutine IOWTSTR(Str, Status)
C ######################################################################
      implicit none
      character*(*) Str
      integer Status
c *   
      write(6,'(a)', iostat=Status) Str
c *      
      end
	  
C ######################################################################
      subroutine IORDSTR(Str, Status)
C ######################################################################
      implicit none
      character*(*) Str
      integer Status
c *    
      read(5, '(a)', iostat=Status) Str
c *      
      end
