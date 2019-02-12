      function fortran_fun( a )
      real*8 a, fortran_fun
      print *,'passa'
      print *,'a = ', a
      fortran_fun = a+1;
      return
      end

      function fortran_fun2( a, size )
      double precision a(*), fortran_fun2, res
      integer*4 size, i;
      print *,'size = ',size
      print *,'a = ', (a(i),i=1,size)
      res = 0
      do i=1,size
        res = res + a(i)
      end do
      fortran_fun2 = res
      return
      end

      subroutine print_string( str, str_len )
      character str(*)
      integer*4 str_len
      print *,'str = ',(str(i),i=1,str_len)
      return
      end
