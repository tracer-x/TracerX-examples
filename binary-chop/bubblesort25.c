int main()
{

  int i, j, a[25], tmp;
  i = 0;
  while (i < 25-1) {
    j = 0;
    while (j < 25-1-i) {

      if (a[j] > a[j+1]) {

        tmp = a[j+1];
	
	a[j+1] = a[j];
	
	a[j] = tmp;
      }      
      j++;      
    }           
    i++;
  }
}
