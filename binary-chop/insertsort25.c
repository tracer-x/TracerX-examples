/*
 *  insertsort.c
 *  
 *
 *  Created by Chu Duc Hiep on 10/19/10.
 *  Copyright 2010 National University of Singapore. All rights reserved.
 *
 */

int main()
{
	unsigned int    a[25];
	int temp;

	int             i, j;
	i = 2;
	while (i < 25) {
		j = i;
		while (j>0 && a[j] < a[j - 1]) {
			temp = a[j];
			a[j] = a[j - 1];
			a[j - 1] = temp;
			j--;
		}
		i++;
	}
	return 1;
}



