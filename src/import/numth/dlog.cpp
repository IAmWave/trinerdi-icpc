/*
 O( \sqrt{P} \log P )  discrete logarithm algorithm by Shanks
 
 parameters: A, B, P
 expects: P is a prime, 1 < A < P < 2^31
 
 returns: one possible \log_A B (mod P)   or -1, if none
*/
long long DLOG (long long A, long long B, long long P) {
  long long M = (long long)ceil(sqrt(P-1.0));

  vector< pair<long long, int> > P1, P2;
  long long pom = MODEXP(A,M,P);
  
  P1.push_back(make_pair(1,0));
  for (int i=1; i<M; i++) P1.push_back(make_pair( (P1[i-1].first * pom)%P ,i)); 
  sort(P1.begin(), P1.end());

  long long Ainv = MODEXP(A,P-2,P);
  P2.push_back(make_pair(B,0));
  for (int i=1; i<M; i++) P2.push_back(make_pair( (P2[i-1].first * Ainv)%P, i));
  sort(P2.begin(), P2.end());
  
  int i,j;
  for (i=0, j=0; P1[i].first != P2[j].first; ) {
    if (P1[i].first < P2[j].first) i++; else j++;
    if ( i==M || j==M ) return -1;
  }
  return ( M * P1[i].second + P2[j].second ) % (P-1);
}
