c######################################################################
      subroutine ChWorkDir(DirPath, Status)
c ######################################################################
c #
      implicit none
c *
      character*(*) DirPath  
      integer  Status
c *
      Status = ChDir(DirPath)
c *
      return
      end
