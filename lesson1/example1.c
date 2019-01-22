/*
  this is a comment

  start with the cheracter / followed by *
  endwith the character * followed by /

*/

/* commnet in a single line */

/*
 * well shaped comment
 *
 */

/*-------------------------*\
 |                         |
 | well shaped comment     |
 |                         |
\*-------------------------*/

int /* return value of type integer */
/* main is the "official" name of the program,
   no more entry points */
main()
/* () commas "containes" the argumentsi
  of the function "main", in this case no arguments */
{
  /*----------------------------------------*\
   * a block (of instruction) is            *
   *   "anything" contained between { and } *
  \*----------------------------------------*/

  return 0; /* return value of function "main" */
}

/*
  C is a free-from language so that there are no
  strict writing rule.
  For example you can write all in one line:

  int main() {}

  or like that

  int
  main

(

       ) {
}


  to compile the code on a UNIX like OS

  gcc example1.c

  or

  clang example1.c

  which generate the executable a.out

  is better to activate ALL the warning
  (WARNING)

  gcc -Wall example1.c

  or

  clang -Wall example1.c
  clang -Weverything example1.c <- paranoic level

  to change the name of the executable (di default):

  gcc -Wall example1.c -o example1
  clang -Wall example1.c -o example1
*/
