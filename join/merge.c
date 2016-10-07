/*
 * From Williams et al.: PathCrawler: Automatic Generation of Path
 * Tests by Combining Static and Dynamic Analysis
 */

void merge (int t1[],int t2[],int t3[],int l1,int l2){
  int i = 0;
  int j = 0;
  int k = 0;
  while (i < l1 && j < l2) {
    if (t1[i] < t2[j]) {
      t3[k] = t1[i];
      i++; }
    else {
      t3[k] = t2[j];
      j++; }
    k++; }
  while (i < l1) {
    t3[k] = t1[i];
    i++;
    k++; }
  while (j < l2) {
    t3[k] = t2[j];
    j++;
    k++; }
}
